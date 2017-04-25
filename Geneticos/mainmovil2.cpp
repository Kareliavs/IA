#include <iostream>
#include <stdio.h>
#include<random>
#include <vector>
#include <time.h>
#include <math.h>
#include <stack>
#include "obstacle.hpp"
///COMPILA ASI ----->g++ -std=c++11 main.cpp -o demo -lglut -lGL


//////////////////////GRAFICO////////////////////////
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <cstring>

using namespace std;

float tamanno = 1.0f;
int up, down,left1,right1,individuos;
int alto, ancho;
int indice=0; 
vector < pair<float,float> > puntos,lines, puntos_recorridos;
int camino_indicado=0;
vector < pair<pair<float,float>,pair<float,float>> > aristas,camino;
vector <pair<vector<int>,float>> todos_caminos;
pair<float,float>  punto_inicio;
int coord_ini, coord_fin;
float maxx,minx,maxy,miny;
int N_OBS, avance;
float costo=0;
vector<int>Llenos,Llenos2;

vector<cObstacle> obstacles;

float distancia(float x1, float x2, float y1, float y2)
{

    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
#include "genetico.hpp"

//int j=0;
float distancia_total(vector<int> vect)
{
	//vect.push_bacK(0);	
	float dist=0;
	vect.push_back(1);
	for(int i=0;i<vect.size()-1;i++)
	{	
		dist+=distancia(puntos[vect[i]].first,puntos[vect[i+1]].first,puntos[vect[i]].second,puntos[vect[i+1]].second);	
	}
	return dist;


}

vector<int>  desordenar(vector<pair<int,int>> ordenado)
{
	vector<int> desordenado;
	//cout<<"here"<<N_OBS<<endl;
	desordenado.push_back(coord_ini);
	ordenado[coord_ini].second=1;
	int veces=N_OBS-1;
	for(int i=0;i<veces;i++)
	{       int elemento=rand()%(N_OBS);
		while(ordenado[elemento].second==1)
		{      elemento=rand()%(N_OBS); 
		}
		desordenado.push_back(elemento);
		ordenado[elemento].second=1;
	}
	desordenado.push_back(coord_ini);
	return desordenado;
}
void indiviuos_aleatorios()
{
	vector<pair<int,int>> auxiliar;
	for(int i=0;i<N_OBS;i++)
	{
		auxiliar.push_back(make_pair(i+1,0));	
	}
	
	for(int i=0;i<individuos;i++)
	{       //cout<<endl<<"CAMINO DEL INDIVIDUO "<<i<<endl;
		todos_caminos.push_back(make_pair(desordenar(auxiliar),0.0));
	}
	
	for(int i=0;i<individuos;i++)
	{
		todos_caminos[i].second=distancia_total(todos_caminos[i].first); 
		//cout<<"dist"<<todos_caminos[i].second<<endl;
	}
	
}



void IniciarGLUT() 
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Algoritmo genetico");
}


void PintarEscena() 
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();	
	///cuadrado blanco
	maxx=minx=0;
	maxy=miny=0;

 	for(int i =0; i<puntos.size(); i++)
	  {
		if(puntos[i].first>maxx)maxx=puntos[i].first+1;////x
		if(puntos[i].first<minx)minx=puntos[i].first-1;////x
		if(puntos[i].second>maxy)maxy=puntos[i].second+1;///y
		if(puntos[i].second<miny)miny=puntos[i].second-1;///y
	  } 
              
   	glColor3f(0.1f,0.1f,0.1f); 
	   
	glRectf(minx,miny,maxx, maxy);

///////////////////////////////////////////////EJES//////////////////////////////////////////////////////
	glLineWidth(2.0); 
	glColor3f(2.47,0.94,0.37);
	glBegin(GL_LINES);
	glVertex3f(-1000, 0.0, 0.0);
	glVertex3f(1000, 0, 0);
	glVertex3f(0, -1000.0, 0.0);
	glVertex3f(0, 1000, 0);
	glEnd();
///////////////////////////////////////////////ARISTAS//////////////////////////////////////////////////////
	glLineWidth(1.0); 
	glColor3f(0.1f,0.7f,1.0f);
	glBegin(GL_LINES);
	for(int i=0;i<aristas.size();i++)
	{
		glVertex3f(aristas[i].first.first, aristas[i].first.second,0.0);	
		glVertex3f(aristas[i].second.first, aristas[i].second.second,0.0);	
	}
	glEnd();
///////////////////////////////////////////////ARISTAS CAMINO//////////////////////////////////////////////////////
	glLineWidth(1.0); 
	glColor3f(1.1f,0.7f,0.0f);
	glBegin(GL_LINES);
	for(int i=0;i<camino.size();i++)
	{
		glVertex3f(camino[i].first.first, camino[i].first.second,0.0);	
		glVertex3f(camino[i].second.first, camino[i].second.second,0.0);	
	}
	glEnd();
///////////////////////////////////////////////OTROS PUNTOS//////////////////////////////////////////////////////
   	glPointSize(10.5);
   	glBegin(GL_POINTS);
   	glColor3f(0.1f,0.5f,0.9f);
     
      	for(int i =0; i<puntos.size(); i++)
	{
		glVertex3f(puntos[i].first,puntos[i].second,0.0f);
                  // sleep(1);
	}
   	 glEnd();
     
   

   	///////////////////////////////////////////////CAMINO//////////////////////////////////////////////////////
	glPointSize(12.5);
	glBegin(GL_POINTS);
  	glColor3f(0.7f,0.3f,1.0f);
     
      	for(int i =0; i<puntos_recorridos.size(); i++)
	{
		glVertex3f(puntos_recorridos[i].first,puntos_recorridos[i].second,0.0f);             
        }
      	glEnd();
	//////////////////////////////////////////INICIO//////////////////////////////ROJO
	glPointSize(10.5);
	glBegin(GL_POINTS);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(punto_inicio.first,punto_inicio.second,0.0f);
	glEnd();
  
 	glutSwapBuffers();
}   


 
void ReProyectar(int w, int h) 
{
   ancho = w;
   alto = h;
   
   GLfloat formato;

   if(h == 0) h = 1;
      
    glViewport(-10, -10, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   formato = (GLfloat)w / (GLfloat)h;
    if (w <= h) glOrtho (-10.0f*tamanno, 10.0f*tamanno, -10.0f*tamanno / formato, 10.0f*tamanno / formato, 1.0f, -1.0f);
    else glOrtho (-10.0f*tamanno * formato, 10.0f*tamanno * formato, -10.0f*tamanno, 10.0f*tamanno, 1.0f, -1.0f);
    glutDisplayFunc(PintarEscena);
}

void Zoom(int value) 
{
   if (up) tamanno = tamanno * 1.2;//1.01f;
   if (down) tamanno = tamanno / 1.2;//1.01f;
   if (left1)
   {
	costo=0;
	Llenos.clear();	
	puntos_recorridos.clear();
        camino.clear();	

	Llenos2.clear();	
	vector<int> soluciones; 
	
//	ll=0;
	seleccion();
	
   }
  
   if(right1)
   {
	
    }
    ReProyectar(ancho,alto);
    glutTimerFunc(33,Zoom,1);
    glutPostRedisplay();
    
}

void Flechas(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 1;
   if (key==GLUT_KEY_DOWN) down = 1;
   if (key==GLUT_KEY_LEFT) left1 = 1;
   if (key==GLUT_KEY_RIGHT) right1 = 1;
}

void FlechasUp(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 0;
   if (key==GLUT_KEY_DOWN) down = 0;
   if (key==GLUT_KEY_LEFT) left1 = 0;
   if (key==GLUT_KEY_RIGHT) right1 = 0;
}

//////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
    cout<<"Ingrese el numero de ciudades ";
    cin>>N_OBS;
    cout<<endl<<"Numero de individuos";
    cin>>individuos;
   
    avance=1;
    
    srand(time(NULL));
    ///PUNTOS ALEATORIOS
    for(int i=0; i<N_OBS; ++i)
    {
        float auxx=rand()%50-rand()%50;
        float auxy=rand()%50-rand()%50;
        cObstacle auxobs(auxx,auxy);

	auxobs.m_id=indice;       
        indice++; 
	obstacles.push_back(auxobs);
	puntos.push_back(make_pair(auxx,auxy));
    }

    //uno=distancia(curiosity.m_x,meta.first,curiosity.m_y,meta.second);
    coord_ini=rand()%puntos.size();
    indiviuos_aleatorios(); 

    glutInit(&argc,argv); //Solo necesario en Linux
    IniciarGLUT();
    glutReshapeFunc(ReProyectar);
    glutDisplayFunc(PintarEscena);
    glutTimerFunc(33,Zoom,1);
    glutSpecialFunc(Flechas);
    glutSpecialUpFunc(FlechasUp);
    glutMainLoop();

    return 0;
}

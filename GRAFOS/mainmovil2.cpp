#include <iostream>
#include <stdio.h>
#include<random>
#include <vector>
#include <time.h>
#include <math.h>

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
int up, down,left1,right1;
int alto, ancho;
int indice=0;
float proximidad;
vector < pair<float,float> > puntos,lines, puntos_recorridos;
vector < pair<pair<float,float>,pair<float,float>> > aristas,camino;
vector <vector<float>> grafo;
pair<float,float>  meta;
pair<float,float>  punto_inicio;
int coord_ini, coord_fin;
float maxx,minx,maxy,miny;
int N_OBS, avance;
float costo=0;
vector<int>Llenos;

vector<cObstacle> obstacles;

float distancia(float x1, float x2, float y1, float y2)
{

    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
#include "hillclimbing.hpp"
#include "Aasterisco.hpp"
//int j=0;
void grafo_aux(float x1, float x2, int id)
{
	for(int i=0; i<puntos.size();i++)
	{      //cout<<"distance: "<<distancia(x1,puntos[i].first,x2,puntos[i].second)<<endl;
		
		if(puntos[i].first!=x1 and puntos[i].second!=x2 and distancia(x1,puntos[i].first,x2,puntos[i].second)<=proximidad)
		{
			aristas.push_back(make_pair(make_pair(x1,x2),make_pair(puntos[i].first,puntos[i].second)));
			//cout<<"here"<<endl;	
			//j++; 
			grafo[id][i]=distancia(x1,puntos[i].first,x2,puntos[i].second);//matriz de adyacencia con distancia 
		}	

	}
}
void grafo_construir()
{	////MATRIZ DE ADYACENCIA
	vector<float> vect;	
	for(int i=0; i<puntos.size();i++)
		vect.push_back(0);	
	for(int i=0; i<puntos.size();i++)
		grafo.push_back(vect);

	for(int i=0; i<puntos.size();i++)
	{  
		grafo_aux(puntos[i].first,puntos[i].second,i);
	}	
	//cout<<"numero de aristas"<<j<<endl;
	/*for(int i=0; i<puntos.size();i++)
	{
		for(int j=0; j<puntos.size();j++)
			cout<<grafo[i][j]<<" ";
		cout<<endl;	
	}*/
}
void IniciarGLUT() 
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Hill climbing");
}


void PintarEscena() 
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();	
	///cuadrado blanco
	maxx=minx=meta.first;
	maxy=miny=meta.second;

 	for(int i =0; i<puntos.size(); i++)
	  {
		if(puntos[i].first+proximidad>maxx)maxx=puntos[i].first+proximidad+1;////x
		if(puntos[i].first-proximidad<minx)minx=puntos[i].first-proximidad-1;////x
		if(puntos[i].second+proximidad>maxy)maxy=puntos[i].second+proximidad+1;///y
		if(puntos[i].second-proximidad<miny)miny=puntos[i].second-proximidad-1;///y
	  } 
              
   	glColor3f(0.1f,0.1f,0.1f); 
	   
	glRectf(minx,miny,maxx, maxy);
//////////////////////////////////////////////RADIOS///////////////////////////////////////////////////////
	glColor3f(0.1f,0.1f,0.2f);///RADIO DE ACCION 
	glPointSize(1.5);
	glBegin(GL_POINTS);
	for(int i =0; i<puntos.size(); i++)
	{
		for (double ii = 0.0; ii < 10; ii+=0.01)   
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle 
			float x = proximidad * cosf(ii)+puntos[i].first;//calculate the x component 
			float y = proximidad * sinf(ii)+puntos[i].second;//calculate the y component 
			glVertex2f(x , y);//output vertex 
		} 
    	}
   	glEnd();
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
     
   


   ///////////////////////////////////////////////META//////////////////////////////////////////////////////
	glPointSize(12.5);
	glBegin(GL_POINTS);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(meta.first,meta.second,0.0f);
	glEnd();
	
	
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
	hill_climbing(grafo);
   }
  
   if(right1)
   {
	costo=0;
	Llenos.clear();	
	puntos_recorridos.clear();
        camino.clear();	
	a_asterisco(grafo);
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
    
    cout<<"Ingrese el numero de puntos";
    cin>>N_OBS;
    cout<<endl<<"Proximidad tolerada";
    cin>>proximidad;
    avance=1;
    
    srand(time(NULL));
    ///PUNTOS ALEATORIOS
    int limite=proximidad;//50
    if(N_OBS==200)limite=50;
    for(int i=0; i<N_OBS; ++i)
    {
        float auxx=rand()%limite-rand()%limite;
        float auxy=rand()%limite-rand()%limite;
        cObstacle auxobs(auxx,auxy);

	auxobs.m_id=indice;       
        indice++; 
	obstacles.push_back(auxobs);
	puntos.push_back(make_pair(auxx,auxy));
    }

    //uno=distancia(curiosity.m_x,meta.first,curiosity.m_y,meta.second);
    coord_ini=rand()%puntos.size();
    coord_fin=rand()%puntos.size();
    
    punto_inicio=puntos[coord_ini];
    meta=puntos[coord_fin];
    grafo_construir();
   

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

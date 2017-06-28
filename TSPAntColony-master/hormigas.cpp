//Hormiguitas para el Problema del Agente Viajero

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <fstream>

using namespace std;
#define MAX_TOURS 20
#define MAX_TIME (MAX_TOURS * MAX_ciudades)
#define MAX_ciudades 40
#define MAX_DISTANCIA 200 /*Distancia entre ciudadClasees*/
#define MAX_TOUR (MAX_ciudades * MAX_DISTANCIA)
#define MAX_HORMIGAS 80  /*Cantidad de Hormigas*/

using namespace std;

//ciudadClase Clase
struct ciudadClase{
	int x,y;
};

struct hormiga{

	int actualciudad, siguienteciudad, pathIndice;
	int tabu[MAX_ciudades]; /*Posibles ciudadClasees que la hormiga puede visitar 0 No visitado 1 Si*/
	int path[MAX_ciudades];
	double tamanioPath;
};

//Parámetros para el Problema de als Hormigas

#define ALPHA 1.0
#define BETA 5.0 //Este parámetro eleva el peso de la distancia sobre la feromona
#define RHO 0.5 //Tasa de evaporación
#define QVAL 100
#define INIT_PHER (1.0/MAX_ciudades)


ciudadClase ciudad[MAX_ciudades];
hormiga arrayHormigas[MAX_HORMIGAS];

/*Creamos las matrices de Adyacencia : Distancia y Feromonas*/
double dist[MAX_ciudades][MAX_ciudades];
double feromona[MAX_ciudades][MAX_ciudades];

double best=(double)MAX_TOUR;
int bestIndex;

/*Leer la ubicación de los nodos en TSP.txt*/
void init()
{
	int from,to,ant;

    ifstream f1;

    //f1.open("TSP.txt");

	//creating ciudad

	for(from = 0; from < MAX_ciudades; from++)
	{
		//Ubicamos las ciudades Aleatoriamente
		
		ciudad[from].x = rand()%MAX_DISTANCIA;

		ciudad[from].y = rand()%MAX_DISTANCIA;
        

        /*Leemos la primera línea: Ejemp: 64 73  -> La primera ciudadClase C1.x=64 y C1.y=73*/
        /*f1>>ciudad[from].x;
        f1>>ciudad[from].y;*/	

        cout<<ciudad[from].x<<" "<<ciudad[from].y<<endl;
		//printf("\n %d %d",ciudad[from].x, ciudad[from].y);

		/*Inicializamos la distancia de la que viene a la que va en 0.0, por ahora to=from=0.0*/
		for(to=0;to<MAX_ciudades;to++)
		{
			dist[from][to] = 0.0;
			feromona[from][to] = INIT_PHER;
		}
	}

	//Calculando la distancia

	/*Se calcula la distancia de una ciudad a todas las ciudad posibles (todos contra todos)*/
	for(from = 0; from < MAX_ciudades; from++)
	{
		for( to =0; to < MAX_ciudades; to++)
		{
			if(to!=from && dist[from][to]==0.0)
			{
				int xd = pow( abs(ciudad[from].x - ciudad[to].x), 2);
				int yd = pow( abs(ciudad[from].y - ciudad[to].y), 2);

				/*Se genera una matriz de adyacencia*/
				dist[from][to] = sqrt(xd + yd);
				dist[to][from] = dist[from][to];

			}
		}
	}


	//Inicialización de Hormigas

	to = 0;
	for( ant = 0; ant < MAX_HORMIGAS; ant++)
	{
		/*Para la hormiga 0, actualciudad = 0, así sucesivamente*/
		/*if(to == MAX_ciudades)
			to=0;*/
		/*Si hay más hormigas que ciudadClasees , se usa modulo*/
		arrayHormigas[ant].actualciudad = to++ % MAX_ciudades;

		for(from = 0; from < MAX_ciudades; from++)
		{
			/*Seteamos los array tabu y path de la hormiga con 0 y -1*/
			arrayHormigas[ant].tabu[from] = 0;
			arrayHormigas[ant].path[from] = -1;
		}

		arrayHormigas[ant].pathIndice = 1;
		arrayHormigas[ant].path[0] = arrayHormigas[ant].actualciudad;
		arrayHormigas[ant].siguienteciudad = -1;
		arrayHormigas[ant].tamanioPath = 0;

		// cargando la primera ciudadClase en la lista de tabúes

		arrayHormigas[ant].tabu[arrayHormigas[ant].actualciudad] =1;

	}
}

//Si las feromonas se evaporaron, las horigas pierden su camino; por ello
//Es necesario reinicializarlas; volverlas a distribuir
void restartarrayHormigas()
{
	int ant,i,to=0;

	/*Difiere de inicializar; pues ahora ya conoce los caminos, no es todo contra todos*/
	for(ant = 0; ant<MAX_HORMIGAS; ant++)
	{
		/*Cuando la hormiga decide entre dos caminos, el mejor*/
		if(arrayHormigas[ant].tamanioPath < best)
		{
			best = arrayHormigas[ant].tamanioPath;
			bestIndex = ant;
		}

		arrayHormigas[ant].siguienteciudad = -1;
		arrayHormigas[ant].tamanioPath = 0.0;

		for(i=0;i<MAX_ciudades;i++)
		{
			arrayHormigas[ant].tabu[i] = 0;
			arrayHormigas[ant].path[i] = -1;
		}

		if(to == MAX_ciudades)
			to=0;

		arrayHormigas[ant].actualciudad = to++;

		arrayHormigas[ant].pathIndice = 1;
		arrayHormigas[ant].path[0] = arrayHormigas[ant].actualciudad;

		arrayHormigas[ant].tabu[arrayHormigas[ant].actualciudad] = 1;
	}
}


/*Hallando el numerador de la ecuación:*/
/*Ecuación: Para hallar la probabilidad de elegir una arista*/
double antProduct(int from, int to)
{
	return(( pow( feromona[from][to], ALPHA) * pow( (1.0/ dist[from][to]), BETA)));
}

int selectsiguienteciudad( int ant )
{
	int from, to;
	double denom = 0.0;

	from=arrayHormigas[ant].actualciudad;

	for(to=0;to<MAX_ciudades;to++)
	{
		if(arrayHormigas[ant].tabu[to] == 0)
		{
			/*Hallando el denominador de la ecuación:*/
			denom += antProduct( from, to );
		}
	}

	assert(denom != 0.0);

	do
	{
		double p;
		to++;

		if(to >= MAX_ciudades)
			to=0;
		if(arrayHormigas[ant].tabu[to] == 0)
		{
			/*Se halla la ecuación mencionada anteriormente.*/
			p = antProduct(from,to)/denom;
			//printf("\n%lf %lf", (double)rand()/RAND_MAX,p);
			double x = ((double)rand()/RAND_MAX);
			if(x < p)
			{
				//Si p es suficientemente alta la escogemos, dependiendo del número aleatorio
				//printf("%lf %lf Yo!",p,x);

				break;
			}
		}
	}while(1);

	return to;
}

int simulatearrayHormigas()
{
	int k;
	int moving = 0;

	for(k=0; k<MAX_HORMIGAS; k++)
	{
		// comprobar si hay más ciudades para visitar
		if( arrayHormigas[k].pathIndice < MAX_ciudades )
		{
			arrayHormigas[k].siguienteciudad = selectsiguienteciudad(k); /*Seleccionamos la Siguiente ciudadClase*/
			/*siguienteciudad deja de ser tabu*/
			arrayHormigas[k].tabu[arrayHormigas[k].siguienteciudad] = 1;
			/*En el array path se añade la ciudadClase visitada, siguienteciudad*/
			arrayHormigas[k].path[arrayHormigas[k].pathIndice++] = arrayHormigas[k].siguienteciudad;

			/*Se añade la distancia de la nueva ciudadClase visitada*/
			arrayHormigas[k].tamanioPath += dist[arrayHormigas[k].actualciudad][arrayHormigas[k].siguienteciudad];


			// manejar último caso-> última ciudadClase a primera
			if(arrayHormigas[k].pathIndice == MAX_ciudades)
			{
				arrayHormigas[k].tamanioPath += dist[arrayHormigas[k].path[MAX_ciudades -1]][arrayHormigas[k].path[0]];
			}

			arrayHormigas[k].actualciudad = arrayHormigas[k].siguienteciudad;
			moving++;

		}
	}

	return moving;
}

//Actualizando feromonas de los trayectos (Aristas)
void actualizarTrayectos()
{
	int from,to,i,ant;

	//Evaporando/Debilitando Feromonas 

	for(from=0; from<MAX_ciudades;from++)
	{
		for(to=0;to<MAX_ciudades;to++)
		{
			if(from!=to)
			{	
				/*Se modifica la matriz de adyacencia, alterando la amtriz de feromonas*/
				feromona[from][to] *=( 1.0 - RHO);
				
				/*Aplica el factor de Evaporacion*/
				if(feromona[from][to]<0.0)
				{
					feromona[from][to] = INIT_PHER;
				}
			}
		}
	}

	
	// Fortaleciendo feromonas
	for(ant=0;ant<MAX_HORMIGAS;ant++)
	{
		for(i=0;i<MAX_ciudades;i++)
		{
			/*Modifica la matriz d adyacencia de las feromonas*/
			if( i < MAX_ciudades-1 )
			{
				from = arrayHormigas[ant].path[i];
				to = arrayHormigas[ant].path[i+1];
			}
			else
			{
				from = arrayHormigas[ant].path[i];
				to = arrayHormigas[ant].path[0];
			}
			/*Fortalece la feromona de i trayectoria*/

			feromona[from][to] += (QVAL/ arrayHormigas[ant].tamanioPath);
			feromona[to][from] = feromona[from][to];

		}
	}

	/*Debilita nuevamente Feromonas por Tiempo*/
	for (from=0; from < MAX_ciudades;from++)
	{
		for( to=0; to<MAX_ciudades; to++)
		{
			feromona[from][to] *= RHO;
		}
	}

}

/*Función que escribe el mejor camino en Data.txt*/
void escribirData(int bestIndex)
{
	ofstream f1;
	f1.open("Data.txt");
	hormiga antBest;
	antBest = arrayHormigas[bestIndex];
	//f1<<antBest.actualciudad<<" "<<antBest.tamanioPath<<"\n";
	int i;
	for(i=0;i<MAX_ciudades;i++)
	{
		f1<<antBest.path[i]<<" ";
	}

	f1.close();

	f1.open("city_data.txt");
	for(i=0;i<MAX_ciudades;i++)
	{
		f1<<ciudad[i].x<<" "<<ciudad[i].y<<"\n";
	}
	f1.close();

}



int main()
{
	int curTime = 0;

    cout<<"Hormiguitas para TSP:"<<endl;
	//cout<<"MaxTime="<<MAX_TIME; /**/

	srand(time(NULL));

	init();

	while( curTime++ < MAX_TIME)
	{
		if( simulatearrayHormigas() == 0)
		{
			actualizarTrayectos();

			if(curTime != MAX_TIME)
				restartarrayHormigas();

			//cout<<"\n Time is "<<curTime<<"("<<best<<")";

		}
	}

	cout<<"La mejor Ruta es: = "<<best<<endl;

	escribirData(bestIndex);

	return 0;
}













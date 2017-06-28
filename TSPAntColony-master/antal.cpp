//Ant algorithms for Travelling salesman Problem

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <fstream>

using namespace std;
#define MAX_CITIES 40
#define MAX_DIST 200
#define MAX_TOUR (MAX_CITIES * MAX_DIST)
#define MAX_ANTS 80

using namespace std;

//Initial Definiton of the problem
struct cityType{
	int x,y;
};

struct antType{

	int curCity, nextCity, pathIndex;
	int tabu[MAX_CITIES]; /*Posibles ciudades que la hormiga puede visitar	*/
	int path[MAX_CITIES];
	double tourLength;
};

//Parámetros para el Problema de als Hormigas

#define ALPHA 1.0
#define BETA 5.0 //Este parámetro eleva el peso de la distancia sobre la feromona
#define RHO 0.5 //Tasa de evaporación
#define QVAL 100
#define MAX_TOURS 20
#define MAX_TIME (MAX_TOURS * MAX_CITIES)
#define INIT_PHER (1.0/MAX_CITIES)


cityType cities[MAX_CITIES];
antType ants[MAX_ANTS];

double dist[MAX_CITIES][MAX_CITIES];

double phero[MAX_CITIES][MAX_CITIES];

double best=(double)MAX_TOUR;
int bestIndex;

/*Leer la ubicación de los nodos en TSP.txt*/
void init()
{
	int from,to,ant;

    ifstream f1;

    //f1.open("TSP.txt");

	//creating cities

	for(from = 0; from < MAX_CITIES; from++)
	{
		//randomly place cities
		
		cities[from].x = rand()%MAX_DIST;

		cities[from].y = rand()%MAX_DIST;
        

        /*Leemos la primera línea: Ejemp: 64 73  -> La primera ciudad C1.x=64 y C1.y=73*/
        /*f1>>cities[from].x;
        f1>>cities[from].y;*/	

        cout<<cities[from].x<<" "<<cities[from].y<<endl;
		//printf("\n %d %d",cities[from].x, cities[from].y);

		/*Inicializamos la distancia de la que viene a la que va en 0.0, por ahora to=from=0.0*/
		for(to=0;to<MAX_CITIES;to++)
		{
			dist[from][to] = 0.0;
			phero[from][to] = INIT_PHER;
		}
	}

	//Calculando la distancia

	/*Se calcula la distancia de una ciudad a todas las ciudades posibles (todos contra todos)*/
	for(from = 0; from < MAX_CITIES; from++)
	{
		for( to =0; to < MAX_CITIES; to++)
		{
			if(to!=from && dist[from][to]==0.0)
			{
				int xd = pow( abs(cities[from].x - cities[to].x), 2);
				int yd = pow( abs(cities[from].y - cities[to].y), 2);

				/*Se genera una matriz de adyacencia*/
				dist[from][to] = sqrt(xd + yd);
				dist[to][from] = dist[from][to];

			}
		}
	}


	//Inicialización de Hormigas

	to = 0;
	for( ant = 0; ant < MAX_ANTS; ant++)
	{
		/*Para la hormiga 0, ciudadActual = 0, así sucesivamente*/
		/*if(to == MAX_CITIES)
			to=0;*/
		/*Si hay más hormigas que ciudades , se usa modulo*/
		ants[ant].curCity = to++ % MAX_CITIES;

		for(from = 0; from < MAX_CITIES; from++)
		{
			/*Seteamos los array tabu y path de la hormiga con 0 y -1*/
			ants[ant].tabu[from] = 0;
			ants[ant].path[from] = -1;
		}

		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;
		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0;

		// cargando la primera ciudad en la lista de tabúes

		ants[ant].tabu[ants[ant].curCity] =1;

	}
}

//Si las feromonas se evaporaron, las horigas pierden su camino; por ello
//Es necesario reinicializarlas; volverlas a distribuir
void restartAnts()
{
	int ant,i,to=0;

	/*Difiere de inicializar; pues ahora ya conoce los caminos, no es todo contra todos*/
	for(ant = 0; ant<MAX_ANTS; ant++)
	{
		/*Cuando la hormiga decide entre dos caminos, el mejor*/
		if(ants[ant].tourLength < best)
		{
			best = ants[ant].tourLength;
			bestIndex = ant;
		}

		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0.0;

		for(i=0;i<MAX_CITIES;i++)
		{
			ants[ant].tabu[i] = 0;
			ants[ant].path[i] = -1;
		}

		if(to == MAX_CITIES)
			to=0;

		ants[ant].curCity = to++;

		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;

		ants[ant].tabu[ants[ant].curCity] = 1;
	}
}


/*Hallando el numerador de la ecuación:*/
/*Ecuación: Para hallar la probabilidad de elegir una arista*/
double antProduct(int from, int to)
{
	return(( pow( phero[from][to], ALPHA) * pow( (1.0/ dist[from][to]), BETA)));
}

int selectNextCity( int ant )
{
	int from, to;
	double denom = 0.0;

	from=ants[ant].curCity;

	for(to=0;to<MAX_CITIES;to++)
	{
		if(ants[ant].tabu[to] == 0)
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

		if(to >= MAX_CITIES)
			to=0;
		if(ants[ant].tabu[to] == 0)
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

int simulateAnts()
{
	int k;
	int moving = 0;

	for(k=0; k<MAX_ANTS; k++)
	{
		// comprobar si hay más ciudades para visitar
		if( ants[k].pathIndex < MAX_CITIES )
		{
			ants[k].nextCity = selectNextCity(k); /*Seleccionamos la Siguiente Ciudad*/
			/*NextCity deja de ser tabu*/
			ants[k].tabu[ants[k].nextCity] = 1;
			/*En el array path se añade la ciudad visitada, nextCity*/
			ants[k].path[ants[k].pathIndex++] = ants[k].nextCity;

			/*Se añade la distancia de la nueva ciudad visitada*/
			ants[k].tourLength += dist[ants[k].curCity][ants[k].nextCity];


			// manejar último caso-> última ciudad a primera
			if(ants[k].pathIndex == MAX_CITIES)
			{
				ants[k].tourLength += dist[ants[k].path[MAX_CITIES -1]][ants[k].path[0]];
			}

			ants[k].curCity = ants[k].nextCity;
			moving++;

		}
	}

	return moving;
}

//Actualizando feromonas de los trayectos (Aristas)
void updateTrails()
{
	int from,to,i,ant;

	//Evaporando/Debilitando Feromonas 

	for(from=0; from<MAX_CITIES;from++)
	{
		for(to=0;to<MAX_CITIES;to++)
		{
			if(from!=to)
			{	
				/*Se modifica la matriz de adyacencia, alterando la amtriz de feromonas*/
				phero[from][to] *=( 1.0 - RHO);
				
				/*Aplica el factor de Evaporacion*/
				if(phero[from][to]<0.0)
				{
					phero[from][to] = INIT_PHER;
				}
			}
		}
	}

	
	// Fortaleciendo feromonas
	for(ant=0;ant<MAX_ANTS;ant++)
	{
		for(i=0;i<MAX_CITIES;i++)
		{
			/*Modifica la matriz d adyacencia de las feromonas*/
			if( i < MAX_CITIES-1 )
			{
				from = ants[ant].path[i];
				to = ants[ant].path[i+1];
			}
			else
			{
				from = ants[ant].path[i];
				to = ants[ant].path[0];
			}
			/*Fortalece la feromona de i trayectoria*/

			phero[from][to] += (QVAL/ ants[ant].tourLength);
			phero[to][from] = phero[from][to];

		}
	}

	/*Debilita nuevamente Feromonas por Tiempo*/
	for (from=0; from < MAX_CITIES;from++)
	{
		for( to=0; to<MAX_CITIES; to++)
		{
			phero[from][to] *= RHO;
		}
	}

}

/*Función que escribe el mejor camino en Data.txt*/
void emitDataFile(int bestIndex)
{
	ofstream f1;
	f1.open("Data.txt");
	antType antBest;
	antBest = ants[bestIndex];
	//f1<<antBest.curCity<<" "<<antBest.tourLength<<"\n";
	int i;
	for(i=0;i<MAX_CITIES;i++)
	{
		f1<<antBest.path[i]<<" ";
	}

	f1.close();

	f1.open("city_data.txt");
	for(i=0;i<MAX_CITIES;i++)
	{
		f1<<cities[i].x<<" "<<cities[i].y<<"\n";
	}
	f1.close();

}



int main()
{
	int curTime = 0;

    cout<<"S-ACO:";
	cout<<"MaxTime="<<MAX_TIME; /**/

	srand(time(NULL));

	init();

	while( curTime++ < MAX_TIME)
	{
		if( simulateAnts() == 0)
		{
			updateTrails();

			if(curTime != MAX_TIME)
				restartAnts();

			cout<<"\n Time is "<<curTime<<"("<<best<<")";

		}
	}

	cout<<"\nSACO: Best tour = "<<best<<endl<<endl<<endl;

	emitDataFile(bestIndex);

	return 0;
}













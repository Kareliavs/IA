#include <iostream>
#include <vector>

using namespace std;


float minimo()
{       float min=1000000;
	
	for(int i=0; i<todos_caminos.size();i++)
	{       //cout<<"estos son"<<todos_caminos[i].second<<endl;
		if(todos_caminos[i].second<min) 
		{
			min=todos_caminos[i].second;
			camino_indicado=i;
		}
	}
	return min;
}
float promedio()
{       float prom=0;
	for(int i=0; i<todos_caminos.size();i++)
	{       
		prom+=todos_caminos[i].second;
	}
	return prom/N_OBS;
}
void seleccion()
{	
	cout<<"Minima distancia"<<minimo()<<endl;
	cout<<"Camino indicado"<<camino_indicado<<endl;	
}

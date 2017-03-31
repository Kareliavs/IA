#include <iostream>
#include <vector>

using namespace std;


int cercanoA(int de)
{       int llegada;
	float min=10000,mini;//sqrt((proximidad*4)*2);cout<<"HERE"<<min<<endl;	
	for(int i=0; i<puntos.size();i++)
	{       
		float dist=distancia(puntos[i].first,puntos[coord_fin].first,puntos[i].second,puntos[coord_fin].second); 
		if(grafo[de][i]!=0 and dist+grafo[de][i]<=min )
		{
			min=dist+grafo[de][i]; //nuevo minimo
			mini=grafo[de][i];
			llegada=i;	
		}
	}
	costo+=mini;
	puntos_recorridos.push_back(puntos[de]);
	Llenos[de]=1;
        camino.push_back(make_pair(puntos[de],puntos[llegada] ));
	return llegada;
}
void a_asterisco(vector <vector<float>> grafo)
{	cout<<"------------------ A* ------------------------"<<endl;
	int a,de;//de=origen //a= destino
	bool prueba=true;
        de=coord_ini;
	for(int i=0; i<puntos.size();i++)
	{  
		Llenos.push_back(0);
	}
	while (de!=coord_fin) 
	{
		if(Llenos[de]==1)
		{
			cout<<"no se puede llegar con el camino más próximo(rio)"<<endl;
			prueba=false;		
			break;
		}
		de=cercanoA(de);		
	}

	if(prueba)	cout<<"LLEGO ! Costo "<<costo<<endl;
}

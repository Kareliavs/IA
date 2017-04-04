// a → de
// b→ a

//int padre[100];
//int d[100]; 
//int f[100];
/*int tiempo;
void DFS_visitar(int i, int tiempo)
{
	relacion[i].first=1;
	tiempo=tiempo+1;
	//d[i]=tiempo;
	cout<<i<<"es papa de : ";
	for(int j =0; j<relacion[i].second.size(); j++)
	{
		if(relacion[j].first==0)
		{
			//padre[j]=i;
			cout<<j<<" "; 
			DFS_visitar(j,tiempo);
		
		}
	}
        cout<<endl; 
	relacion[i].first=2;
	tiempo= tiempo +1;
	//f[i]=tiempo; 


}
void DFS(vector<vector<float>> G)
{	
	for(int i =0; i<G.size(); i++)
	{
		relacion[i].first=0; 
		//padre[i]=0;		
	}
	tiempo=0;
	for(int i =0; i<G.size(); i++)
	{	
	if(relacion[i].first==0)
			DFS_visitar(i,tiempo);
	}
	
}
*/
#include <iostream>
#include <vector>
#include <list>

using namespace std;
//list<int> pila;

/*vector<int> q; 
int r=-1,f=0;
void BFS_aux(int coord)
{
	for(int i =0; i< puntos.size(); i++)
		if(grafo[coord][i] && !Llenos2[i])	
			q[++r]=i;
	if(f<=r)
	{
		Llenos2[q[f]]=1;
		BFS_aux(q[f++]);		
	}

}*/
vector<int>  sols2;
int ll2=0;
void DFS()
{	

	vector<int >aux,aux2,aux3;
	aux.push_back(coord_ini);
	int tmp;
	cout<<"------------------ DFS ------------------------"<<aux.size()<<" "<<ll2<<" "<<puntos.size()<<endl;
	
	
	
	while(aux.size()>0 and ll2!=puntos.size())
	{      cout<<"dentro del while INI"<<coord_ini<<"FIN"<<coord_fin <<endl;
		tmp=aux[0];	
		
		//cout<<"porte  "<<aux.size()<<" and "<<relacion[tmp].second.size()<<endl;
		if(Llenos2[tmp]==0)
		{cout<<"CULPABLE "<<tmp;
			aux.erase(aux.begin());
			if(tmp==coord_fin){sols2.push_back(tmp);return;}	
			else{
			cout<<"**************************"<<endl;
			for(int i=0; i<aux.size();i++)
				  cout<<", "<<aux[i];	
                        cout<<"**************************"<<endl;
			for(int i=0; i<relacion[tmp].second.size();i++)		
			{       //cout<<", "<<relacion[tmp].second[i];
				int relaciones=0;
				for(int j=0; j<familia[tmp].size();j++)
				{	cout<<"comparo "<<relacion[tmp].second[i]<<" con "<<familia[tmp][j]<<endl;
					if(relacion[tmp].second[i]==familia[tmp][j])
					{       cout<<"son iguales"<<endl;
						relaciones++;
						break;
					}
					//cout<<"ici"<<endl;
				}	//cout<<"out"<<endl;		
				if(relaciones==0)
				{	aux2=aux;
					aux.clear();
					aux.push_back(relacion[tmp].second[i]);
					for(int i=0; i<aux2.size();i++)
						aux.push_back(aux2[i]);
					cout<<"PORTE:  "<<aux.size()<<endl;
					familia[tmp].push_back(relacion[tmp].second[i]); 			
				}
			}}
/*
		aux3=aux2;
		for(int i=0; i<aux.size();i++)
			aux3.push_back(aux[i]);
		aux=aux3;
		cout<<"UPS i did it again"<<aux.size()<<endl;*/
		}
		cout<<"saLIANDO";
		Llenos2[tmp]=1;	
		ll2++;
	}
}


void DFS_ORG()
{	ll2=0;
	DFS();
	if(ll2==puntos.size() and sols2.size()==0)
		cout<<"No hay camino"<<endl;
	for(int i=0; i<sols2.size();i++)
	{	cout<<"solution " <<sols2[i]<<endl;
		camino.push_back(make_pair(puntos[coord_ini],puntos[familia[sols2[i]][0]] ));
		for(int j=0; j<familia[sols2[i]].size();j++)
		{	cout<<familia[sols2[i]][j]<<"..";
	         	puntos_recorridos.push_back(puntos[familia[sols2[i]][j]]);
			if(j<familia[sols2[i]].size()-1)
        		camino.push_back(make_pair(puntos[familia[sols2[i]][j]],puntos[familia[sols2[i]][j+1]] ));
			else
			camino.push_back(make_pair(puntos[familia[sols2[i]][j]],puntos[coord_fin] ));
		}
	}

/*	for(int i =0; i< puntos.size();i++)
		q.push_back(0);
	BFS_aux(coord_ini);
	for(int i =0; i< puntos.size();i++)
		if(Llenos2[i])
			cout<<i<<" ";
		else	
			cout<<"no se puede llegar con el camino más próximo(rio)"<<endl;
*/			//cout<<"LLEGO ! Costo "<<costo<<endl;
}
/*
void DFS(vector <vector<float>> grafo)
{	cout<<"------------------ DFS ------------------------"<<endl;
	
	for(int i =0; i<relacion.size();i++)
	{	cout<<i<<": ";
		for(int j=0; j<relacion[i].second.size();j++)
			cout<<relacion[i].second[j]<<" ";
		cout<<endl;		
	}
}*/
/*int DFS_aux(int coord)
{	
	pila.push_front(coord);
	
	if(coord!=coord_fin)
	{
		pila.erase (pila.begin());
		for(int j=0; j<relacion[coord].second.size();j++)
		{
			
				
			int count=0;
			for(int k=0; k<familia[relacion[coord].second[j]].size();k++)				
				if(j==familia[relacion[coord].second[j]][k])
					count++;
			if(count==0)			
			{	pila.push_front(relacion[coord].second[j]);

				familia[relacion[coord].second[j]].push_back(coord);
			}	
			//if (count==0)
				//DFS_aux(j);	
							
		}	
		return -1;	
	}
	else
		return coord; 
	
}
void DFS()
{
	cout<<"------------------ DFS ------------------------"<<endl;
	int respuesta= DFS_aux(coord_ini);
cout<<"ici"<<endl;
	if(respuesta==-1)
		cout<<"No hay camino"<<endl; 	
	else
	{
		for(int k=0; k<familia[respuesta].size();k++)				
			cout<<familia[respuesta][k]<<"   ";
	
	}

}*/

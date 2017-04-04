#include <iostream>
#include <vector>

using namespace std;
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
vector<int>  sols;
int ll=0;
void BFS()
{	cout<<"------------------ BFS ------------------------"<<endl;
	vector<int >aux;
	aux.push_back(coord_ini);
	int tmp;
	
	
	while(aux.size()>0 and ll!=puntos.size())
	{      
		tmp=aux[0];	
		
		//cout<<"porte  "<<aux.size()<<" and "<<relacion[tmp].second.size()<<endl;
		if(Llenos2[tmp]==0)
		{cout<<"CULPABLE "<<tmp;
		aux.erase(aux.begin());
		if(tmp==coord_fin)sols.push_back(tmp);	
		for(int i=0; i<relacion[tmp].second.size();i++)		
		{       //cout<<", "<<relacion[tmp].second[i];
			int relaciones=0;
			for(int j=0; j<familia[tmp].size();j++)
			{	//cout<<"comparo "<<relacion[tmp].second[i]<<" con "<<familia[tmp][j]<<endl;
				if(relacion[tmp].second[i]==familia[tmp][j])
				{       //cout<<"son iguales"<<endl;
					relaciones++;
					break;
				}
				//cout<<"ici"<<endl;
			}	//cout<<"out"<<endl;		
			if(relaciones==0)
			{	aux.push_back(relacion[tmp].second[i]);	
				familia[tmp].push_back(relacion[tmp].second[i]); 			
			}
		}
		cout<<endl;
		}
		Llenos2[tmp]=1;	
		ll++;
	}
}


void BFS_ORG()
{	BFS();
	if(ll==puntos.size() and sols.size()==0)
		cout<<"No hay camino"<<endl;
	for(int i=0; i<sols.size();i++)
	{	cout<<"solution " <<sols[i]<<endl;
		camino.push_back(make_pair(puntos[coord_ini],puntos[familia[sols[i]][0]] ));
		for(int j=0; j<familia[sols[i]].size();j++)
		{	cout<<familia[sols[i]][j]<<"..";
	         	puntos_recorridos.push_back(puntos[familia[sols[i]][j]]);
			if(j<familia[sols[i]].size()-1)
        		camino.push_back(make_pair(puntos[familia[sols[i]][j]],puntos[familia[sols[i]][j+1]] ));
			else
			camino.push_back(make_pair(puntos[familia[sols[i]][j]],puntos[coord_fin] ));
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

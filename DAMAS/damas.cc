
#include "Tablero.h"

int la_respuesta[tam][tam];

class minmax
{
public:
	Tablero* m_root;	
	int m_lvl_max;
	bool m_turno;
	minmax(int matriz[tam][tam],bool turno,int lvl)
	{
		m_root=new Tablero(turno,matriz);
		//equals_matrices(m_root->tabl,matriz);
		m_lvl_max=lvl;
		m_turno = turno;
	}

	void contruir_arbol()
	{
		vector< pair< pair<int,int>, vector< pair<int,int> > > >jugadas_posibles_aux;//Vector Supremo segundo
		vector<Tablero* >jugadas;
		Tablero* aux;

		jugadas.push_back(m_root);
		int cont=1;
		aux=m_root;
		Tablero* tmp;
		while(jugadas.size()>0 && cont<=m_lvl_max/*&& aux->m_lvl<=m_lvl_max*/)
		{
			if(aux->m_lvl>=m_lvl_max)break;
			aux=jugadas[0];
			jugadas.erase(jugadas.begin());
			//aux->jugadas_posibles.clear();
			//aux->turno=(aux->turno+1)%2;
			aux->jugadas_permitidas();
			jugadas_posibles_aux=aux->jugadas_posibles;
			for(int i=0;i<aux->jugadas_posibles.size();i++)
			{
				cout<<"para el elemento "<<aux->jugadas_posibles[i].first.first<<", "<<aux->jugadas_posibles[i].first.second<<" sus jugadas posbiles son: ";
				for(int j=0;j<aux->jugadas_posibles[i].second.size();j++)
				{
					cout<<"("<<aux->jugadas_posibles[i].second[j].first<<", "<<aux->jugadas_posibles[i].second[j].second<<"); ";
				}
				cout<<endl;
			}
			//cout<<"aux->jugadas_posibles.size()---->"<<aux->jugadas_posibles.size()<<endl;
			for(int i=0;i<aux->jugadas_posibles.size();i++)
			{
				for(int j=0;j<aux->jugadas_posibles[i].second.size();j++)
				{
					aux->m_child.push_back(new Tablero((m_turno),aux->tabl,aux->m_lvl));
					//aux->m_child[aux->m_child.size()-1]->jugadas_permitidas();
					//tmp=aux->m_child[aux->m_child.size()-1];
					//tmp->jugadas_permitidas();

					aux->m_child[aux->m_child.size()-1]->siguiente_jugada(aux->jugadas_posibles[i].first.first,aux->jugadas_posibles[i].first.second,aux->jugadas_posibles[i].second[j].first,aux->jugadas_posibles[i].second[j].second);
					jugadas.push_back(aux->m_child[aux->m_child.size()-1]);
					/*aux->m_child.push_back(new Tablero(m_turno,aux->tabl,aux->m_lvl+1));
					aux->m_child[aux->m_child.size()-1]->siguiente_jugada(jugadas_posibles_aux[i].first.first,jugadas_posibles_aux[i].first.second,jugadas_posibles_aux[i].second[j].first,jugadas_posibles_aux[i].second[j].second);
					jugadas.push_back(aux->m_child[aux->m_child.size()-1]);*/
				}
			}
			m_turno=!m_turno;
			cout<<"TURNO!!!!!!!!!!!!!!!!!!!!!!! "<<m_turno<<endl;
			cont++;
			//cout<<aux->m_lvl<<endl;
		}
	}
/*
	void contruir_arbol()
	{
		Tablero* ptr = m_root;
		vector< pair< pair<int,int>, vector< pair<int,int> > > >jugadas_posibles_aux;//Vector Supremo segundo
	
		for(int i=0;i<jugadas_posibles_aux.size();i++)
			{
				for(int j=0;j<jugadas_posibles_aux[i].second.size();j++)
				{
					ptr = new Tablero(ptr->m_turno,ptr->tabl,ptr->m_lvl+1); ;
				}
			}
	}
	void contruir_arbol_restante(Tablero* ptr)
	{
		//ptr = m_root;
		vector< pair< pair<int,int>, vector< pair<int,int> > > >jugadas_posibles_aux;//Vector Supremo segundo
		if(ptr->m_lvl>=m_lvl_max)return ;
		for(int i=0;i<jugadas_posibles_aux.size();i++)
			{
				for(int j=0;j<jugadas_posibles_aux[i].second.size();j++)
				{
					ptr = new Tablero(ptr->m_turno,ptr->tabl,ptr->m_lvl+1); ;
				}
			}
	}
*/
};

/*
int main()
{
	/*Tablero a(1);
	//cout<<a.tab[0][-1]<<endl;
	print_tablero(a.tabl);
	cout<<"-----------------------"<<endl;
	a.jugadas_permitidas();
	print_tablero(a.tabl);
	cout<<"-----------------------------"<<endl;
	cout<<"posibles jugadas"<<endl;
	for(int i=0;i<a.jugadas_posibles.size();i++)
	{
		cout<<"posicion: "<<a.jugadas_posibles[i].first.first<<", "<<a.jugadas_posibles[i].first.second<<endl;
	}
	int tab[tam][tam];
	equals_matrices(tab,a.tabl);
	a.puede_comer(7,1,tab);
	cout<<"-------------------------------------------"<<endl;
	print_tablero(tab);
	cout<<"TAMAÑO DE JGUADAS POSIBLES:>::>:>::>:>"<<a.jugadas_posibles.size()<<endl;
	cout<<"TAMAÑO DE JGUADAS POSIBLES:>::>:>::>:>"<<a.jugadas_posibles.size()<<endl;
	for(int i=0;i<a.jugadas_posibles.size();i++)
	{
		cout<<"para el elemento "<<a.jugadas_posibles[i].first.first<<", "<<a.jugadas_posibles[i].first.second<<" sus jugadas posbiles son: ";
		for(int j=0;j<a.jugadas_posibles[i].second.size();j++)
		{
			cout<<"("<<a.jugadas_posibles[i].second[j].first<<", "<<a.jugadas_posibles[i].second[j].second<<"); ";
		}
		cout<<endl;
	}*/
	/*Tablero a(1);				///con 1 mueven las negras(-1)(1er jugador) y con 0 mueven las rojas(1).
	print_tablero(a.tabl);
	int i,j,i1,j1;
	cout<<"humano... selecciona la ficha que quieres mover.."<<endl;
	cin>>i;cin>>j;
	//falta si es que puede comer--preguntar
	cout<<"humano... selecciona la posicion a la que deseas mover la ficha seleccionada.."<<endl;
	cin>>i1;cin>>j1;
	a.jugadas_permitidas();
	a.siguiente_jugada(i,j,i1,j1);
	print_tablero(a.tabl);
	minmax b(a.tabl,0,4);
	//cout<<"nivel maximo"<<b.m_lvl_max<<endl;
	cin>>i1;
	cout<<endl;
	b.contruir_arbol();
	print_tablero(b.m_root->m_child[0]->tabl);
	cout<<"lvl---------->"<<b.m_root->m_child[0]->m_lvl<<endl;
	cout<<endl;
	print_tablero(b.m_root->m_child[0]->m_child[0]->tabl);
	cout<<"lvl---------->"<<b.m_root->m_child[0]->m_child[0]->m_lvl<<endl;
	cout<<endl;
	print_tablero(b.m_root->m_child[0]->m_child[0]->m_child[0]->tabl);
	//cout<<"lvl---------->"<<b.m_root->m_child[0]->m_child[0]->m_child[0]->m_lvl<<endl;
	cout<<endl;
	//print_tablero(b.m_root->m_child[0]->m_child[0]->m_child[0]->m_child[0]->tabl);

	return 0;
}*/

///falta min_max y borrar un 2 molesto...

int disponibles(int turno)
{
	Tablero a(turno,tab,lvl);
	a.jugadas_permitidas();
	vector<int>ceros;
        for(int i=0; i<tam; i++)
		ceros.push_back(0);
	for(int i=0; i<tam; i++)
		reinas2.push_back(ceros);
       
	for(int i=0;i<a.jugadas_posibles.size();i++)
	{
		reinas2[a.jugadas_posibles[i].first.first][a.jugadas_posibles[i].first.second]=1;
		//cout<<"ici "<<a.jugadas_posibles[i].first.first<<" , "<<a.jugadas_posibles[i].first.second<<endl;
	}
	

}
/*
int damas(int x, int y,int turno)
{
	Tablero a(turno);
	cout<<"-----------------------"<<endl;
	a.jugadas_permitidas();

	int tab[tam][tam];
	equals_matrices(tab,a.tabl);
	if(reinas2[x][y]==1)
	{
		a.puede_comer(x,y,tab);
	

		cout<<"-------------------------------------------"<<endl;
		//a.print_tablero();
		for(int i=0; i<tam; i++)
			for(int j=0;j<tam; j++)
				reinas[i][j]=tab[i][j]; 
		cout<<"LET IT GO "<<endl;
	 
		print_tablero(tab);
	}
	else 
		cout<<"movida no esta habilitada"<<endl; 
	       // reinas2.clear();
	
	return 0;
}*/
void puede_moverse(int i, int j)
{
	Tablero a(turno,tab,lvl);	
	equals_matrices(tab,a.tabl);
	a.puede_comer(i,j,tab);
	cout<<"-------------------------------------------"<<endl;
	//print_tablero(tab);
	cout<<"TAMAÑO DE JGUADAS POSIBLES:>::>:>::>:>"<<a.jugadas_posibles.size()<<endl;
	cout<<"TAMAÑO DE JGUADAS POSIBLES:>::>:>::>:>"<<a.jugadas_posibles.size()<<endl;

	for(int i=0;i<a.jugadas_posibles.size();i++)
	{
		cout<<"para el elemento "<<a.jugadas_posibles[i].first.first<<", "<<a.jugadas_posibles[i].first.second<<" sus jugadas posbiles son: ";
		for(int j=0;j<a.jugadas_posibles[i].second.size();j++)
		{
			cout<<"("<<a.jugadas_posibles[i].second[j].first<<", "<<a.jugadas_posibles[i].second[j].second<<"); ";
		}
		cout<<endl;
	}

}

int damas(int i,int j,int i1, int j1, int turno)
{
	Tablero a(turno,tab,lvl);
		
	if(a.siguiente_jugada(i,j,i1,j1))
	{
		equals_matrices(tab,a.tabl);
		for(int i=0; i<tam; i++)
				for(int j=0;j<tam; j++)
					reinas[i][j]=tab[i][j]; 
		
		cout<<"estoy aqui";
		minmax b(a.tabl,0,4);
		cout<<"aqui";
		//cout<<"nivel maximo"<<b.m_lvl_max<<endl;
		//cin>>i1;
		cout<<endl;
		b.contruir_arbol();
		print_tablero(a.tabl);
		/*print_tablero(b.m_root->m_child[0]->tabl);
		cout<<"lvl---------->"<<b.m_root->m_child[0]->m_lvl<<endl;
		cout<<endl;
		print_tablero(b.m_root->m_child[0]->m_child[0]->tabl);
		cout<<"lvl---------->"<<b.m_root->m_child[0]->m_child[0]->m_lvl<<endl;
		cout<<endl;
		print_tablero(b.m_root->m_child[0]->m_child[0]->m_child[0]->tabl);*/
		//cout<<"lvl---------->"<<b.m_root->m_child[0]->m_child[0]->m_child[0]->m_lvl<<endl;
		cout<<endl;
		return 0;
	}
	else
	{
		cout<<"no era posible"<<endl;
		return 1;	
	}
	
}
/*
int main()
{
	
	Tablero a(1);				///con 1 mueven las negras(1er jugador) y con 2 mueven las rojas.
	print_tablero(a.tabl);
	int i,j,i1,j1;

	cout<<"humano... selecciona la ficha que quieres mover.."<<endl;
	cin>>i;cin>>j;
	//falta si es que puede comer--preguntar
	cout<<"humano... selecciona la posicion a la que deseas mover la ficha seleccionada.."<<endl;
	cin>>i1;cin>>j1;

	a.siguiente_jugada(i,j,i1,j1);
	print_tablero(a.tabl);
	cin>>i1;
	cout<<endl;
	minmax b(a.tabl,0,4);
	b.contruir_arbol();
	print_tablero(b.m_root->m_child[1]->tabl);
	cout<<endl;
	print_tablero(b.m_root->m_child[1]->m_child[0]->tabl);
	cout<<endl;
	print_tablero(b.m_root->m_child[1]->m_child[0]->m_child[0]->tabl);

	return 0;
}*/

///falta min_max y borrar un 2 molesto...

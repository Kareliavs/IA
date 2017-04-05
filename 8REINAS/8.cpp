#include <iostream>
#include <vector>
#include <deque>
#include <queue> 
using namespace std;
#define tam 8
vector<vector<vector<int>>>para_graficar;
class Tablero{
  public:
    int mat[tam][tam];
    int reinas=0;
    vector<Tablero*> m_child;
    Tablero(int r)
    {
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                mat[i][j] = 0;
            }
        }
        reinas=r;
    }
    
    void siguiente_jugada(int matrix[tam][tam],int fil,int col)
    {
      for(int i=0;i<tam;i++)
      {
        for(int j=0;j<tam;j++)
        {
          mat[i][j]=matrix[i][j];
        }
      } 
      insertar(fil,col);
    }
    void insertar(int fil,int col)
    {
        int af=fil;int ac=col;

        //fila/columna
        for(int i=0;i<tam;i++){mat[i][col]=-1;mat[fil][i]=-1;}

        //diagonales
        while(af > 0 && ac > 0){af--;ac--; mat[af][ac]=-1;}ac=col;af=fil;
        while(af < tam-1 && ac < tam-1){af++;ac++; mat[af][ac]=-1;}ac=col;af=fil;
        while(af > 0 && ac < tam-1){af--;ac++; mat[af][ac]=-1;}ac=col;af=fil;
        while(af < tam-1 &&  ac > 0){af++;ac--; mat[af][ac]=-1;}
        mat[fil][col]=1;
        reinas++;
    }
    
    void print_tablero()
    {
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                cout<<"["<<mat[i][j]<<" ]\t";
            }
            cout<<endl;
        }
    }
};

class Arbol{
    public:
        Tablero* m_root;
        Arbol(int i,int j)
        {
          m_root=NULL;
          m_root=new Tablero(0);
          m_root->insertar(i,j);
        }

        Arbol()
        {
        	m_root=NULL;
        	m_root=new Tablero(0);
        }
        
        void insertar_reina()
        {
        	vector<Tablero* >jugadas;
        	jugadas.push_back(m_root);
        	Tablero* tmp;
        	while(jugadas.size()>0)
        	{
        		tmp=jugadas[0];
        		if(tmp->reinas==tam)break;
        		jugadas.erase(jugadas.begin());
        		for(int i=0;i<tam;i++)
	            {
	                if(tmp->mat[tmp->reinas][i]==0)
	                {
	                  tmp->m_child.push_back(new Tablero(tmp->reinas));
	                  tmp->m_child[tmp->m_child.size()-1]->siguiente_jugada(tmp->mat,tmp->reinas,i);
	                  jugadas.push_back(tmp->m_child[tmp->m_child.size()-1]);
	                }
	            }
        	}
        }

        //recorrido en amplitud
        void Soluciones(vector<Tablero* > &sols)
        {
        	vector<Tablero* >aux;
        	aux.push_back(m_root);
        	Tablero* tmp;
        	while(aux.size()>0)
        	{
	        	tmp=aux[0];
	        	aux.erase(aux.begin());
	        	if(tmp->reinas==tam)sols.push_back(tmp);
	        	for(int i=0;i<tmp->m_child.size();i++)
	        	{
	        		aux.push_back(tmp->m_child[i]);
	        	}	
        	}        	       	
        }
	///RECORRIDO EN PROFUNCDIDAD	
	void Soluciones_Profundidad(vector<Tablero* > &sols)
        {
            deque<Tablero *> aux;
            aux.push_front(m_root);
            Tablero* tmp;
            while(!aux.empty())
            {
                tmp=aux.front();
                aux.pop_front();
                if(tmp->reinas==tam)sols.push_back(tmp);
                for(int i=0;i<tmp->m_child.size();i++)
                {
                    aux.push_front(tmp->m_child[i]);
                }
            }

        }
};

void imprimir_soluciones(vector<Tablero*> soluciones)
{
	char c;
	for(int s=0;s<soluciones.size();s++)
	{
		cout<<s+1<<") ";
		for(int i=0;i<tam;i++)
		{
			for(int j=0;j<tam;j++)
			{
				if(soluciones[s]->mat[i][j]==1)
				{
					c=65+i;
					cout<<c<<j+1<<", ";
					para_graficar[s][i][j]=1;
				}
			}
		}
		cout<<endl;
	}
}

int ocho_reinas()
{
    //Arbol a(0,1);
    for(int i=0; i<92;i++)
	para_graficar.push_back(reinas);
    Arbol a;
    
    a.m_root->print_tablero();
    cout<<"-------------------------------------------------\n"<<endl;
    a.insertar_reina();
    vector<Tablero*>soluciones;
    int mode; 
    cout<<"(DFS 1 / BFS 2)"<<endl;
    //cin >> mode; 
    //if(mode==1) 
        a.Soluciones_Profundidad(soluciones);
    //else if (mode==2) 
//	a.Soluciones(soluciones);

    cout<<"EL NUMERO DE SOLUCIONES ES: "<<soluciones.size()<<endl;
    /*for(int i=0;i<soluciones.size();i++)
    {
    	soluciones[i]->print_tablero();
    	cout<<"-------------------------------------------------\n"<<endl;
    }*/
    imprimir_soluciones(soluciones);
    
    return 0;
}





























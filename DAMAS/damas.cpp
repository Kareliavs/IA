#include <iostream>
#include <vector>

using namespace std;

#define tam 8

void equals_matrices(int a[tam][tam],int b[tam][tam])
{
	for(int i=0;i<tam;i++)
	{
		for(int j=0;j<tam;j++)
		{
			a[i][j]=b[i][j];
		}
	}
}

void print_tablero(int tabl[tam][tam])
    {
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                cout<<"["<<tabl[i][j]<<" ]\t";
            }
            cout<<endl;
        }
    }

class Tablero
{
public:
	int tabl[tam][tam];
	bool turno;				//1 es turno del primero, 0 del segndo
	vector< pair< int , int > > jugadas;
	vector< pair< pair<int,int>, vector< pair<int,int> > > >jugadas_posibles;//Vector Supremo 

	Tablero(bool flag)				//-1 negras(1er jugador), 1 rojas(2do jugador) -11 o 11 reina.
	{
		turno=flag;
		for(int i=0;i<tam;i++)
		{
			for(int j=0;j<tam;j++)
			{
				tabl[i][j]=0;
			}
		}
		//----------negras--------
		for(int i=0;i<tam;i+=2){tabl[0][i]=-1;}
		for(int i=1;i<tam;i+=2){tabl[1][i]=-1;}
		for(int i=0;i<tam;i+=2){tabl[2][i]=-1;}
		//----------rojas--------
		for(int i=1;i<tam;i+=2){tabl[7][i]=1;}
		for(int i=0;i<tam;i+=2){tabl[6][i]=1;}
		for(int i=1;i<tam;i+=2){tabl[5][i]=1;}
	}
	
	

//si explota es por culpa de este!
    int puede_comer(int i,int j,int tab[tam][tam])/// 1 puede comer, 2 puede mover y 0 no puede hacer nada!
    {
    	int flag=0;
    	
    	bool he_comido=0;

    	vector< pair<int,int> > movimientosFicha;
    	if(turno)
    	{
    		if(tab[i][j] == -11)//si es que es una reina
    		{
    			if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] > 0 ))
    			{
    				if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    				{
    					tab[i-2][j-2]=-2;
    					movimientosFicha.push_back(make_pair(i-2,j-2));
    					flag++;
    					he_comido=1;
    					//return 1;
    				}
    			}

    			if( ( i-1>=0 && j+1<tam && tab[i-1][j-1] > 0 ))
    			{
    				if( ( i-2>=0 && j+2<tam && tab[i-2][j+2] == 0 ) )	
    				{
    					tab[i-2][j+2]=-2;
    					movimientosFicha.push_back(make_pair(i-2,j+2));

    					flag++;
    					he_comido=1;
    					//return 1;
    				}
    			}
    		}
    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] > 0 ))
    		{
    			if( ( i+2<tam && j+2<tam && tab[i+2][j+2] == 0 ) )	
    			{
    				tab[i+2][j+2]=-2;
    				movimientosFicha.push_back(make_pair(i+2,j+2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if( i+1<tam && j-1>=0 && tab[i+1][j-1] > 0 )
    		{
    			if( i+2<tam && j-2>=0 && tab[i+2][j-2] == 0 )
    			{
    				tab[i+2][j-2]=-2;
    				movimientosFicha.push_back(make_pair(i+2,j-2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if(!he_comido)
    		{
    			if(tab[i][j] == -11)
    			{
		    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 ))
		    		{ 
		    			tab[i-1][j-1]=-2; flag++;/*return 2;*/
		    			movimientosFicha.push_back(make_pair(i-1,j-1));
		    		}
		    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 ))
		    		{ 
		    			tab[i-1][j+1]=-2; flag++;/*return 2;*/
		    			movimientosFicha.push_back(make_pair(i-1,j+1));
		    		}
    			}

	    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 ))
	    		{
	    			tab[i+1][j+1]=-2; flag++;/*return 2;*/
	    			movimientosFicha.push_back(make_pair(i+1,j+1));
	    		}
	    		if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 ))
	    		{
	    			tab[i+1][j-1]=-2; flag++;/*return 2;*/
	    			movimientosFicha.push_back(make_pair(i+1,j-1));
	    		}
    		}
    	}
    	else
    	{
    		if(tab[i][j] == 11)
    		{
    			if( ( i+1<tam && j+1<tam && tab[i+1][j+1] < 0 ))
	    		{
	    			if( ( i+2<tam && j+2<tam && tab[i+2][j+2] == 0 ) )	
	    			{
	    				tab[i+2][j+2]=2;
	    				movimientosFicha.push_back(make_pair(i+2,j+2));
	    				flag++;
	    				he_comido=1;
	    				//return 1;
	    			}
	    		}
	    		if( i+1<tam && j-1>=0 && tab[i+1][j-1] < 0 )
	    		{
	    			if( i+2<tam && j-2>=0 && tab[i+2][j-2] == 0 )
	    			{
	    				tab[i+2][j-2]=2;
	    				movimientosFicha.push_back(make_pair(i+2,j-2));
	    				flag++;
	    				he_comido=1;
	    				//return 1;
	    			}
	    		}
    		}
    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] < 0 ))
    		{
    			if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    			{
    				tab[i-2][j-2]=2;
    				movimientosFicha.push_back(make_pair(i-2,j-2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}

    		if( ( i-1>=0 && j+1<tam && tab[i-1][j-1] < 0 ))
    		{
    			if( ( i-2>=0 && j+2<tam && tab[i-2][j+2] == 0 ) )	
    			{
    				tab[i-2][j+2]=2;
    				movimientosFicha.push_back(make_pair(i-2,j+2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if(!he_comido)
    		{
    			if(tab[i][j] == 11)
    			{
		    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 ))
		    		{
		    			tab[i+1][j+1]=2; flag++;/*return 2;*/
		    			movimientosFicha.push_back(make_pair(i+1,j+1));
		    		}
	    			if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 ))
	    			{
	    				tab[i+1][j-1]=2; flag++;/*return 2;*/
	    				movimientosFicha.push_back(make_pair(i+1,j-1));
	    			}
    			}

	    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 ))
	    		{
	    			tab[i-1][j-1]=2; flag++;/*return 2*/;
	    			movimientosFicha.push_back(make_pair(i-1,j-1));
	    		}
	    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 ))
	    		{
	    			tab[i-1][j+1]=2; flag++;/*return 2*/;
	    			movimientosFicha.push_back(make_pair(i-1,j+1));
	    		}
    		}
    	}
    	if(flag!=0)
    		{
    			jugadas.push_back(make_pair(i,j));
    			jugadas_posibles.push_back(make_pair(make_pair(i,j),movimientosFicha));
    			//movimientosFicha.push_back(i,j);//El último elemnto = ficha
    			//jugadas_posibles.push_back(movimientosFicha);

    		}
    	return 0;
    }

    void jugadas_permitidas()
    {
    	int dama,reina;
    	if(turno){dama=-1;reina=-11;}
    	else{dama=1;reina=11;}
    	int tab[tam][tam];
    	//cout<<"se igualo! prueba ->"<<tab[7][7]<<endl;
    	//equals_matrices(tab,tabl);
    	for(int i=0;i<tam;i++)
    	{
    		for(int j=0;j<tam;j++)
    		{
    			if(tabl[i][j]==dama || tabl[i][j]==reina)puede_comer(i,j,tab);
    			equals_matrices(tab,tabl);
    		}
    	}
    }
};

class minmax
{
 
};
/*
   void print_tablero(int tablero[tam][tam])
    {
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                cout<<"["<<tablero[i][j]<<" ]\t";
            }
            cout<<endl;
        }
    }



*/
int disponibles(int turno)
{
	Tablero a(turno);

	//cout<<a.tab[0][-1]<<endl;
	//a.print_tablero();
	//cout<<"-----------------------"<<endl;
	a.jugadas_permitidas();
	//a.print_tablero();
	//cout<<"-----------------------------"<<endl;
	//cout<<"posibles jugadas"<<endl;
	vector<int>ceros;
        for(int i=0; i<tam; i++)
		ceros.push_back(0);
	for(int i=0; i<tam; i++)
		reinas2.push_back(ceros);
        if(banderitas==0)
	for(int i=0;i<a.jugadas.size();i++)
	{
		//cout<<"posicion: "<<a.jugadas[i].first<<", "<<a.jugadas[i].second<<endl;
		reinas2[a.jugadas[i].first][a.jugadas[i].second]=1;
	}
	

}
int damas(int x, int y,int turno)
{
	Tablero a(turno);
	//cout<<a.tab[0][-1]<<endl;
	//print_tablero();
	cout<<"-----------------------"<<endl;
	a.jugadas_permitidas();
	//a.print_tablero();
	/*cout<<"-----------------------------"<<endl;
	cout<<"posibles jugadas"<<endl;
	for(int i=0;i<a.jugadas.size();i++)
	{
		cout<<"posicion: "<<a.jugadas[i].first<<", "<<a.jugadas[i].second<<endl;
		reinas2[a.jugadas[i].first][a.jugadas[i].second]=1;
	}*/

	int tab[tam][tam];
	equals_matrices(tab,a.tabl);
	if(reinas2[x][y]==1){
		a.puede_comer(x,y,tab);
	

		cout<<"-------------------------------------------"<<endl;
		//a.print_tablero();
		for(int i=0; i<tam; i++)
			for(int j=0;j<tam; j++)
				reinas[i][j]=tab[i][j]; 
		cout<<"LET IT GO "<<endl;
	 
		print_tablero(tab);}
	else 
		cout<<"movida no esta habilitada"<<endl; 
	       // reinas2.clear();
	
	return 0;
}

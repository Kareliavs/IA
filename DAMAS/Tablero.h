
#include "funciones.h"

class Tablero
{
public:
	int tabl[tam][tam];
	bool turno;				//1 es turno del primero, 0 del segndo
    int fichas_negras,fichas_rojas;
    int m_lvl;
    vector<Tablero*>m_child;
	vector< pair< pair<int,int>, vector< pair<int,int> > > >jugadas_posibles;//Vector Supremo 

	Tablero(bool flag,int lvl=0)				//-1 negras(1er jugador), 1 rojas(2do jugador) -11 o 11 reina.
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

        fichas_rojas=12;
        fichas_negras=12;
        m_lvl=lvl;
	}

    Tablero(bool flag,int mat[tam][tam],int lvl=0)
    {
        turno=flag;
        equals_matrices(tabl,mat);
        fichas_rojas=12;
        fichas_negras=12;
        m_lvl=lvl;
    }



    void actualizar_num_fichas()
    {
        fichas_negras=0;
        fichas_rojas=0;
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                if(tabl[i][j]==1 || tabl[i][j]==11)fichas_rojas++;
                if(tabl[i][j]==-1 || tabl[i][j]==-11)fichas_negras++;
            }
        }
    }
	
	

//si explota es por culpa de este!,
//aparte... true si la ficha tiene al menos una movida |false
    bool puede_comer(int i,int j,int tab[tam][tam])/// 1 puede comer, 2 puede mover y 0 no puede hacer nada!
    {
    	int flag=0;                ///si es que fue posible acer una jugada se suma 1
    	
    	bool he_comido=0;

    	vector< pair<int,int> > movimientosFicha;
    	if(turno)
    	{
            //cout<<"entro en turno 1"<<endl;
            //cout<<"entro"<<endl;
    		/*if(tab[i][j] == -11)//si es que es una reina
    		{
    			if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] > 0 ))
    			{
    				if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    				{
    					//tab[i-2][j-2]=-2;
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
    					//tab[i-2][j+2]=-2;
    					movimientosFicha.push_back(make_pair(i-2,j+2));
    					flag++;
    					he_comido=1;
    					//return 1;
    				}
    			}
    		}*/
    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] > 0 ))
    		{
    			if( ( i+2<tam && j+2<tam && tab[i+2][j+2] == 0 ) )	
    			{
    				//tab[i+2][j+2]=-2;
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
    				//tab[i+2][j-2]=-2;
    				movimientosFicha.push_back(make_pair(i+2,j-2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if(!he_comido)
    		{
    			/*if(tab[i][j] == -11)
    			{
		    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 ))
		    		{ 
		    			//tab[i-1][j-1]=-2;
                        flag++;
		    			movimientosFicha.push_back(make_pair(i-1,j-1));
		    		}
		    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 ))
		    		{ 
		    			//tab[i-1][j+1]=-2;
                        flag++;
		    			movimientosFicha.push_back(make_pair(i-1,j+1));
		    		}
    			}*/

	    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 ))
	    		{
	    			//tab[i+1][j+1]=-2;
                    flag++;/*return 2;*/
	    			movimientosFicha.push_back(make_pair(i+1,j+1));
	    		}
	    		if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 ))
	    		{
	    			//tab[i+1][j-1]=-2;
                    flag++;/*return 2;*/
	    			movimientosFicha.push_back(make_pair(i+1,j-1));
	    		}
    		}
    	}
    	else
    	{
            //cout<<"entro en turno 2"<<endl;
    		/*if(tab[i][j] == 11)
    		{
    			if( ( i+1<tam && j+1<tam && tab[i+1][j+1] < 0 ))
	    		{
	    			if( ( i+2<tam && j+2<tam && tab[i+2][j+2] == 0 ) )	
	    			{
	    				//tab[i+2][j+2]=2;
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
	    				//tab[i+2][j-2]=2;
	    				movimientosFicha.push_back(make_pair(i+2,j-2));
	    				flag++;
	    				he_comido=1;
	    				//return 1;
	    			}
	    		}
    		}*/
    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] < 0 ))
    		{
    			if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    			{
    				//tab[i-2][j-2]=2;
    				movimientosFicha.push_back(make_pair(i-2,j-2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}

    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] < 0 ))
    		{
    			if( ( i-2>=0 && j+2<tam && tab[i-2][j+2] == 0 ) )	
    			{
    				//tab[i-2][j+2]=2;
    				movimientosFicha.push_back(make_pair(i-2,j+2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if(!he_comido)
    		{
    			/*if(tab[i][j] == 11)
    			{
		    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 ))
		    		{
		    			//tab[i+1][j+1]=2;
                        flag++;
		    			movimientosFicha.push_back(make_pair(i+1,j+1));
		    		}
	    			if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 ))
	    			{
	    				//tab[i+1][j-1]=2;
                        flag++;
	    				movimientosFicha.push_back(make_pair(i+1,j-1));
	    			}
    			}*/

	    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 ))
	    		{
	    			//tab[i-1][j-1]=2;
                    flag++;/*return 2*/;
	    			movimientosFicha.push_back(make_pair(i-1,j-1));
	    		}
	    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 ))
	    		{
	    			//tab[i-1][j+1]=2;
                    flag++;/*return 2*/;
	    			movimientosFicha.push_back(make_pair(i-1,j+1));
	    		}
    		}
    	}
    	if(flag!=0)
    	{
    		//jugadas.push_back(make_pair(i,j));
    		jugadas_posibles.push_back(make_pair(make_pair(i,j),movimientosFicha));
            return 1;
    		//movimientosFicha.push_back(i,j);//El último elemnto = ficha
    		//jugadas_posibles.push_back(movimientosFicha);
    	}
    	return 0;
    }

    void jugadas_permitidas()
    {
    	int dama;
    	if(turno){dama=-1;}
    	else{dama=1;}
    	int tab[tam][tam];
    	//cout<<"se igualo! prueba ->"<<tab[7][7]<<endl;
    	equals_matrices(tab,tabl);
    	for(int i=0;i<tam;i++)
    	{
    		for(int j=0;j<tam;j++)
    		{
                if(tabl[i][j]==dama)puede_comer(i,j,tab);
                equals_matrices(tab,tabl);
            }
        }
    }


bool siguiente_jugada(int i_o,int j_o,int i_f,int j_f)
{
        
    //cout<<"entre!!!!!"<<endl;
   // jugadas_posibles.clear();
    //int tab[tam][tam];
    //equals_matrices(tab,tabl);
    //cout<<"TURNO>>>>>>>>>>>>>>><"<<turno<<endl;
    //if(!puede_comer(i_o,j_o,tab))return 0;
    //cout<<"PASO....."<<endl;
    //jugadas_posibles.clear();
    //jugadas_permitidas();
 /*   cout<<"tammm>>>>>>>>>>>>>>>"<<jugadas_posibles.size()<<endl;
    vector< pair<int,int> >pos_finales;
    pair<int,int>pos_final;
    pair<int,int>pos_inicial;
    pos_final=make_pair(i_f,j_f);
    pos_inicial=make_pair(i_o,j_o);
    int i;int fl=0;
    for(i=0;i<jugadas_posibles.size();i++)
    {
        if(pos_inicial==jugadas_posibles[i].first){
            ++fl;
            break;
        }
    }
    if(fl==0)return 0;
    pos_finales=jugadas_posibles[i].second;
    cout<<"Para la ficha en la pos ("<<i_o<<", "<<j_o<<") Las pos Finales son; "<<endl;
    for(int i=0;i<pos_finales.size();i++)
    {
        cout<<"Pos i:"<<pos_finales[i].first<<" Pos j: "<<pos_finales[i].second<<endl;
    }
    bool flag=0;
    for(i=0;i<pos_finales.size();i++)
    {
        if(pos_finales[i]==pos_final)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)return 0;
*/

    int tmp;
    tmp=tabl[i_o][j_o];
    if(abs(i_f-i_o)==2)
    {
        if(i_f-i_o>0 && j_f-j_o>0)tabl[i_o+1][j_o+1]=0;
        if(i_f-i_o>0 && j_f-j_o<0)tabl[i_o+1][j_o-1]=0;
        if(i_f-i_o<0 && j_f-j_o<0)tabl[i_o-1][j_o-1]=0;
        if(i_f-i_o<0 && j_f-j_o>0)tabl[i_o-1][j_o+1]=0;

        if(tabl[i_o][j_o]==-1 || tabl[i_o][j_o]==-11){fichas_rojas--;}
        else{ fichas_negras--;}
    }
    tabl[i_o][j_o]=0;
    tabl[i_f][j_f]=tmp;

   
    m_lvl=m_lvl+1;

    //jugadas_posibles.clear();
   return 1;
}















}; 

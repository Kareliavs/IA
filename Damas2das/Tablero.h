#include "Funciones.h"
#ifndef IADAMASMINMAC_TABLERO_H
#define IADAMASMINMAC_TABLERO_H

class Tablero
{
public:
    vector<Tablero*>mChild;
    Tablero* mParent;
    int** mTablero;
    bool mTurno;
    int mNivelMinMax;
    pair< pair<int,int>, vector< pair<int,int> > >  mJugadasPorFicha;
    vector<int**> mTablerosUpdate;
    int fichas_negras,fichas_rojas,vertice;
    /*Variables Alfa y Beta*/
    int valor=0;
    int alfa=-9999; ///si es maximizador
    int betha=9999;///si es minimizador


    Tablero(int** Matriz,bool turno,int nivelMinMax)
    {
        mTablero= new int*[tam];
        for(int i=0;i<tam;i++)
        {
            mTablero[i]=new int[tam];
        }
        mParent=NULL;
        igualarMatrices(mTablero,Matriz);
        mTurno = turno;
        mNivelMinMax = nivelMinMax;
        fichas_rojas=12;
        fichas_negras=12;
        vertice=0;

    }



    /*Reglas de las damas Parámetro Ficha a Evaluar movimientos*/
    bool movimientosFicha(int i,int j)
    {
        vector< pair<int,int> > movimientosFicha; /*Movimientos que puede Realizar c/ficha*/
        int comio = 0;
        int flag  = 0;

        if(mTurno == 0) /*Fichas Rojas :  Valor en la Matriz -1*/
        {
            /*Si la ficha puede Comer, el algoritmo fuerza a realizar esta jugada*/
            if( ( i+1<tam && j+1<tam && mTablero[i+1][j+1] ==1 ))
            {
                if( ( i+2<tam && j+2<tam && mTablero[i+2][j+2] == 0 ) )
                {
                    movimientosFicha.push_back(make_pair(i+2,j+2));
                    flag++; comio++;
                }
            }
            if( i+1<tam && j-1>=0 && mTablero[i+1][j-1] == 1 )
            {
                if( i+2<tam && j-2>=0 && mTablero[i+2][j-2] == 0 )
                {
                    movimientosFicha.push_back(make_pair(i+2,j-2));
                    flag++; comio++;

                }
            }
            if(comio == 0)
            {
                /*Si no comio aun podría moverse*/
                if( ( i+1<tam && j+1<tam && mTablero[i+1][j+1] == 0 ))
                {
                    movimientosFicha.push_back(make_pair(i+1,j+1));
                    flag++;
                }
                if( ( i+1<tam && j-1>=0 && mTablero[i+1][j-1] == 0 ))
                {
                    movimientosFicha.push_back(make_pair(i+1,j-1));
                    flag++;
                }
            }
        }

        else /*Fichas Negras Valor en la Matriz 1*/
        {
            if( ( i-1>=0 && j-1>=0 && mTablero[i-1][j-1] == -1 ))
            {
                if( ( i-2>=0 && j-2>=0 && mTablero[i-2][j-2] == 0 ) )
                {
                    movimientosFicha.push_back(make_pair(i-2,j-2));
                    flag++; comio++;
                }
            }

            if( ( i-1>=0 && j+1<tam && mTablero[i-1][j+1] == -1 ))
            {
                if( ( i-2>=0 && j+2<tam && mTablero[i-2][j+2] == 0 ) )
                {
                    movimientosFicha.push_back(make_pair(i-2,j+2));
                    flag++; comio++;
                }
            }

            if(comio == 0)
            {
                if( ( i-1>=0 && j-1>=0 && mTablero[i-1][j-1] == 0 ))
                {
                    movimientosFicha.push_back(make_pair(i-1,j-1));
                    flag++;
                }
                if( ( i-1>=0 && j+1<tam && mTablero[i-1][j+1] == 0 ))
                {
                    movimientosFicha.push_back(make_pair(i-1,j+1));
                    flag++;
                }
            }

        }

        if(flag!=0)
        {
            mJugadasPorFicha = make_pair(make_pair(i,j),movimientosFicha);
            return 1;
            /*cout<<"Los mov de la ficha "<<i<<" , "<<j<<"son: "<<endl;
            for(int i=0;i<movimientosFicha.size();i++)
            {
                cout<<movimientosFicha[i].first<<" , "<<movimientosFicha[i].second<<endl;
            }*/

        }
        return 0;
    }

    /*Ya con los movimientos de c/ficha queda realizar las N jugadas posibles y actualizar el tablero*/
    void realizarJugada()
    {
        /*Si es el turno de las fichas Rojas*/
        if(mTurno == 0)
        {
            for(int i=0; i<tam;i++)
            {
                for(int j=0;j<tam;j++)
                {
                    if(mTablero[i][j] == -1) /*Si es una ficha Roja Analiza posibles Mov por c/ficha*/
                    {
                        if(movimientosFicha(i,j)== 1)
                            updateTablero(i,j,-1);
                    }
                }
            }

        }
        else
        {
            for(int i=0; i<tam;i++)
            {
                for(int j=0;j<tam;j++)
                {
                    if(mTablero[i][j] == 1) /*Si es una ficha Negra Analiza posibles Mov por c/ficha*/
                    {
                        if(movimientosFicha(i,j)== 1)
                            updateTablero(i,j,1);
                    }
                }
            }

        }

    }

    void updateTablero(int fichaPosi, int fichaPosj,int value)
    {
        int posFinali,posFinalj;
        for(int i=0;i<mJugadasPorFicha.second.size();i++)
        {
            int** matriz;
            matriz= new int*[tam];
            for(int a=0;a<tam;a++)
            {
                matriz[a]=new int[tam];
            }
            igualarMatrices(matriz,mTablero);
            posFinali = mJugadasPorFicha.second[i].first;
            posFinalj = mJugadasPorFicha.second[i].second;

            /*Si el Mov es comer Pintamos la Tabla*/
            if(abs(posFinali-fichaPosi)== 2)
            {
                if(posFinali-fichaPosi>0 && posFinalj-fichaPosj>0)matriz[fichaPosi+1][fichaPosj+1]=0;
                if(posFinali-fichaPosi>0 && posFinalj-fichaPosj<0)matriz[fichaPosi+1][fichaPosj-1]=0;
                if(posFinali-fichaPosi<0 && posFinalj-fichaPosj<0)matriz[fichaPosi-1][fichaPosj-1]=0;
                if(posFinali-fichaPosi<0 && posFinalj-fichaPosj>0)matriz[fichaPosi-1][fichaPosj+1]=0;
                if(value==1){fichas_rojas--;}
                else{fichas_negras--;}
            }
            if(mTurno==0){valor=fichas_rojas-fichas_negras;}
            else{valor=fichas_negras-fichas_rojas;}
            matriz[fichaPosi][fichaPosj]=0;
            matriz[posFinali][posFinalj]=value;
            //printTablero(matriz);
            mTablerosUpdate.push_back(matriz);
        }

    }

};







#endif //IADAMASMINMAC_TABLERO_H

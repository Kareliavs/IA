#include "Tablero.h"
#include <queue> 

class miniMax
{
public:
    Tablero* mRoot;
    int** mTablerito;
    int mMaxLevel;
    bool mTurno;
    miniMax(int** matriz,bool turno,int level)
    {
        mTablerito= new int*[tam];
        for(int i=0;i<tam;i++)
        {
            mTablerito[i]=new int[tam];
        }
        mRoot = NULL;
        igualarMatrices(mTablerito,matriz);
        mMaxLevel = level;
        mTurno =  turno;
        mRoot= new Tablero(mTablerito,mTurno,0);
    }


    Tablero* construirArbolNivelBase()
    {
cout<<"se construira..."<<endl;
        vector<Tablero* > next_jugadas;
        Tablero *aux;
        next_jugadas.push_back(mRoot);
        while(next_jugadas.size()>0)
        {
            aux=next_jugadas[0];
            //cout<<"maxlevel"<<mRoot->mNivelMinMax<<endl;
            //cout<<"entro"<<endl;
            if(aux->mNivelMinMax>mMaxLevel)break;
            next_jugadas.erase(next_jugadas.begin());
            aux->realizarJugada();
            Tablero* ptr;
            for(int i=0;i<aux->mTablerosUpdate.size();i++)
            {
                ptr=new Tablero(aux->mTablerosUpdate[i],!aux->mTurno,aux->mNivelMinMax+1);
                ptr->mParent=aux;                
                aux->mChild.push_back(ptr);
                next_jugadas.push_back(ptr);
            }
        }
	return minmax();
    }

    void actualizar_hijos(Tablero* ptr)///copia el alfa beta del padre a los hijos
    {
        for(int i=0;i<ptr->mChild.size();i++)
        {
            ptr->mChild[i]->alfa=ptr->alfa;
            ptr->mChild[i]->betha=ptr->betha;
        }
    }

    Tablero* minmax()
    {
        deque<Tablero *> aux;
        aux.push_front(mRoot);
        Tablero* tmp=mRoot;
        Tablero* mejor_jugada;
        int cont=0;
        int contAux;
        bool flag=true;


        //bool flag=1;        //1 maximizador, 0 minimizador
        while(!aux.empty())
        {
            for(int i=0;i<tmp->mChild.size();i++)
            {
                aux.push_front(tmp->mChild[i]);
                if(flag)
                {
                    cont++;
                }
            }
            flag=false;
            tmp=aux.front();
                //cout<<"hola"<<endl;
            
            if(tmp->mChild.size() == 0)
            {
                
                if(tmp->mParent){
                    if(tmp->mParent->mNivelMinMax % 2!= 0)  ///minimizador
                    {
                       // cout<<"es minimizador"<<endl;
                        if(tmp->mParent->alfa < tmp->mParent->betha)
                        {
                            if(tmp->mParent->betha>tmp->valor)
                            {
                                if(tmp->mParent != mRoot )contAux;
                                tmp->mParent->betha = tmp->valor;
                                tmp->mParent->vertice = tmp->valor;
                                actualizar_hijos(tmp->mParent);

                            }

                            
                        }
                        else if(tmp->mParent = mRoot ){contAux=cont;}
                    }
                    else
                    {
                       // cout<<"es maximizador"<<endl;
                        if(tmp->mParent->alfa > tmp->mParent->betha)
                        {
                            if(tmp->mParent->alfa>tmp->valor)
                            {
                                if(tmp->mParent != mRoot )contAux++;
                                tmp->mParent->alfa = tmp->valor;
                                tmp->mParent->vertice = tmp->valor;
                                actualizar_hijos(tmp->mParent);
                            }
                            //else{tmp->mParent->mChild.pop_back();}
                        }
                        else if(tmp->mParent = mRoot ){contAux=cont;}   
                        
                    }

                    if(tmp->mParent != mRoot ){
                        tmp->mParent->mChild.pop_back();
                    }

                    if(contAux==cont)
                    {
                        int val=0;
                        for(int i=0;i<mRoot->mChild.size();i++)
                        {
                            if(mRoot->mChild[i]->vertice>=val)
                            {
                                mejor_jugada=mRoot->mChild[i];
                                val=mRoot->mChild[i]->vertice;
                            }
                        }

                        return mejor_jugada;
                    }


                   // cout<<"size1 "<<aux.size()<<endl;
                    
                }
                    aux.pop_front();            
                    //cout<<"size2 "<<aux.size()<<endl;
                    //cout<<"hi"<<endl;
            }
         
        
        }
            //cout<<"libre!!!!!!"<<endl;
    }


   /* void construirArbolNivelBase()
    {
        mRoot= new Tablero(mTablerito,mTurno,0);
        mRoot->realizarJugada();
        Tablero* ptr;
        for(int i=0;i<mRoot->mTablerosUpdate.size();i++)
        {
            ptr = new Tablero(mRoot->mTablerosUpdate[i],!mTurno,mRoot->mNivelMinMax+1);
            mRoot->mChild.push_back(ptr);
            construirArbolNivelMaximo(mRoot);
        }
    }
    void construirArbolNivelMaximo(Tablero* &ptr)
    {
        for(int i=0; i<ptr->mChild.size();i++)
        {
            if(ptr->mChild[i]->mNivelMinMax <= mMaxLevel)
            {
                ptr->mChild[i]->realizarJugada();
                Tablero* aux;
                for(int j=0;j<ptr->mChild[i]->mTablerosUpdate.size();j++)
                {
                    aux = new Tablero(ptr->mChild[i]->mTablerosUpdate[j],!(ptr->mChild[ei]->mTurno),ptr->mChild[i]->mNivelMinMax+1);
                    ptr->mChild[i]->mChild.push_back(aux);
                }
                Tablero *ptr1 =ptr->mChild[i];
                construirArbolNivelMaximo(ptr1);
            }
        }
    }*/

};

int** tabl;
int inicializar() {

    
    tabl= new int*[tam];
    for(int i=0;i<tam;i++)
    {
        tabl[i]=new int[tam];
    }
    //int tabl[tam][tam];
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
    cout<<"ESTOY AQUI"<<endl;
    //miniMax arbol(tabl,0,4);
}

int damasjuego(int x,int y, int xx, int yy,int lvl)
{
    //cout<<"Matriz Original: "<<endl;
    /*cout<<"**********************************************************"<<endl;
    for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
            cout<<"["<<tabl[i][j]<<" ]\t";
        }
        cout<<endl;
    }
    cout<<"**********************************************************"<<endl;*/
    /*Tablero tablerito(tabl,0,0);
    tablerito.realizarJugada();*/
    tabl[x][y]=0;
    damas[x][y]=0;

    tabl[xx][yy]=1;
   // if(turno=1)
     damas[xx][yy]=1;
    //if(turno=0)
    // damas[xx][yy]=-1;
     for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
            cout<<"["<<tabl[i][j]<<" ]\t";
        }
        cout<<endl;
    }
    miniMax arbol(tabl,0,lvl);

    Tablero* aux=arbol.construirArbolNivelBase();

    cout<<"Imprimiendo Hijos "<<endl;
    /*for(int i=0;i<arbol.mRoot->mChild.size();i++)
    {
        cout<<"Turno "<<arbol.mRoot->mChild[i]->mTurno<<" Level: "<<arbol.mRoot->mChild[i]->mNivelMinMax<<endl;
        printTablero(arbol.mRoot->mChild[i]->mTablero);
    }*/
    //printTablero(arbol.mRoot->mTablero);
    //printTablero(arbol.mRoot->mChild[0]->mTablero);
    //printTablero(arbol.mRoot->mChild[0]->mChild[0]->mTablero);
    //printTablero(arbol.mRoot->mChild[0]->mChild[0]->mChild[0]->mTablero);
    //arbol.minmax();
    //Tablero* aux=arbol.minmax();
     printTablero(aux->mTablero);
     for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
            damas[i][j]=aux->mTablero[i][j];
	    tabl[i][j]=damas[i][j];
	   // cout<<damas[i][j]<<" ";
        }
	cout<<endl;
    }	
    //aux->mTablero
    return 0;
}   

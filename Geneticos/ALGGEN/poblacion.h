#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;

vector <pair<vector<int>,float>> nuevaPoblacion;
vector < pair<float,float> > puntos;
vector < vector<int> > newCaminos; /*Vaciar al finalizar c/generacion*/
vector<float>promedios;

vector <pair<vector<int>,float>> mejores_caminos;

float distancia(float x1, float x2, float y1, float y2)
{

    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
float distancia_total(vector<int> vect)

{
    //vect.push_bacK(0);
    float dist=0;
    ///vect.push_back(1);
    for(int i=0;i<vect.size()-1;i++)
    {
        dist+=distancia(puntos[vect[i]].first,puntos[vect[i+1]].first,puntos[vect[i]].second,puntos[vect[i+1]].second);
    }
    return dist;


}
float promedioNew(vector <pair<vector<int>,float>>& todosCaminos,int numIndividuos)
{
    float prom=0;
    for(int i=0; i<todosCaminos.size();i++)
    {
        prom+=todosCaminos[i].second;
    }
    return prom/numIndividuos;
}
/*Elitismo: Preservamos nuestro mejor individio:*/
void elitismo(vector <pair<vector<int>,float>> todosCaminos, int indice )
{
    pair<vector<int>,float> mejorIndividuo;
    mejorIndividuo = make_pair(todosCaminos[indice].first,todosCaminos[indice].second);
    nuevaPoblacion.push_back(mejorIndividuo);
}

void PMX(vector<int>& newIndividuo,vector<int> indice1,vector<int>indice2,int corteInit,int corteFin)
{
    for(int i=corteInit;i<corteFin;i++)
    {
        for(int j=0;j<indice1.size();j++)
        {
            if(newIndividuo[i] == indice1[j])
            {
                newIndividuo[i] = indice2[j];
                //break;
                for(int k=0;k<indice2.size();k++)
                {
                    if(newIndividuo[i] == indice1[k])
                    {
                        newIndividuo[i] = indice2[k];
                        break;
                    }
                    else
                    {
                        j=indice1.size();
                        //break;

                    }

                }
            }

        }
    }

}

void escogerPoblacion(vector <pair<vector<int>,float>>& todosCaminos,int numIndividuos)
{
    float distancia;
    for(int i=0;i<newCaminos.size();i++)
    {
        distancia = distancia_total(newCaminos[i]);
        nuevaPoblacion.push_back(make_pair(newCaminos[i],distancia));
    }
    //Aqui haces ordenar el vector -> como te dije seria algo asi
    /*vectpr [122333] ditancia 8
     * vectpr [31231231] ditancia 2
     * vectpr [664564] ditancia 18
     * vectpr [34] ditancia 55
     * lo q debe hacer
     * vectpr [31231231] ditancia 2
     * vectpr [122333] ditancia 8
     * vectpr [664564] ditancia 18
     * ectpr [34] ditancia 55
     * */
     /*for(int i=0;i<nuevaPoblacion.size();i++)
	cout<<nuevaPoblacion[i].second<<" , ";*/
     sort(nuevaPoblacion.begin(), nuevaPoblacion.end(), [](const std::pair<vector<int>,float>&left, const pair<vector<int>,float> &right) {
    return left.second < right.second;
});
    /*cout<<endl<<"ordenado"<<endl;
for(int i=0;i<nuevaPoblacion.size();i++)
	cout<<nuevaPoblacion[i].second<<" , ";*/
    //Una vez ordenado esocgeremos los mejores 10 de los 20 generados (si en el input usimos individuos =10)
    todosCaminos.clear();
    //Se agregan los mejore 10
    for(int i=0;i<numIndividuos;i++)
        todosCaminos.push_back(nuevaPoblacion[i]);

    /*cout<<"La nueva Generacion es: "<<endl;
    for(int i=0;i<nuevaPoblacion.size();i++)
    {
        cout<<"La distancia es: "<<distancia<<endl;
        for(int j=0;j<nuevaPoblacion[i].first.size();j++) {
            cout<<nuevaPoblacion[i].first[j]<<" ; ";
        }
        cout<<endl;
    }*/
    float prom=promedioNew(todosCaminos,numIndividuos);
    cout<<"El Nuevo Promedio: "<<prom<<endl;
    mejores_caminos.push_back(todosCaminos[0]);
    promedios.push_back(prom);
    //Hacer esto 1000 veces

    newCaminos.clear();
    //-->esto NO TODAVIA todosCaminos.push_back(nuevaPoblacion[0]);/*Se ha preservado el Mejor Individuo OJO desordenado*/
}

void cruzamientoPMX(vector<int> individuo1,vector<int>individuo2)
{
    /*Cruzamiento que Recibe 2 individuos y Genera otros 2*/
    int corteInit = 3;
    int corteFin  = 6;
    vector<int> indice1,indice2;
    vector<int> newIndividuo1,newIndividuo2;

    //cout<<" Individuo 1: "<<endl;
    /*for(int i=0;i<individuo1.size();i++)
        cout<<individuo1[i]<<" ; ";
    cout<<endl;*/
    for(int i=corteInit;i<=corteFin;i++)
    {
        indice1.push_back(individuo2[i]);
        indice2.push_back(individuo1[i]);
    }

    newIndividuo1 = individuo1;
    newIndividuo2 = individuo2;

    PMX(newIndividuo1,indice1,indice2,0,corteInit);
    PMX(newIndividuo2,indice2,indice1,0,corteInit);

    int j=0;
    for(int i=corteInit;i<=corteFin;i++)
    {
        newIndividuo1[i]=indice1[j];
        newIndividuo2[i]=indice2[j];
        j++;
    }

    PMX(newIndividuo1,indice1,indice2,corteFin+1,individuo1.size());
    PMX(newIndividuo2,indice2,indice1,corteFin+1,individuo2.size());
    newCaminos.push_back(individuo1);
    newCaminos.push_back(individuo2);
    newCaminos.push_back(newIndividuo1);
    newCaminos.push_back(newIndividuo2);
/*
    cout<<"New Individuo 1: "<<endl;
    for(int i=0;i<newIndividuo1.size();i++)
        cout<<newIndividuo1[i]<<" ; ";
    cout<<endl;

    cout<<"New Individuo 2: "<<endl;
    for(int i=0;i<newIndividuo2.size();i++)
        cout<<newIndividuo2[i]<<" ; ";
    cout<<endl;*/
}

//Lamo a ruleta la mita de veces
void seleccionRuleta( vector< pair<int,int> > valuesVec , vector <pair<vector<int>,float>> todosCaminos)
{
    /*Seleccion de Individuos para Cruzamiento PMX*/
    vector<int> ruleta;
    for(int i=0;i<valuesVec.size();i++)
    {
        for(int j=0;j<valuesVec[i].first-1;j++)
        {
            ruleta.push_back(valuesVec[i].second);
        }
    }

    /*cout<<"Array de probabilidades: "<<endl;
    for(int i=0;i<ruleta.size();i++)
        cout<<ruleta[i]<<" ; ";
    cout<<endl;*/
    /*Se seleccionan los individuos Probalisticamente*/
    vector<int> individuo1,individuo2;
    int indice1,indice2;
    indice1 = rand()%99;
    indice2 = rand()%99;
    while(ruleta[indice2]==ruleta[indice1])
        indice2 = rand()%99;
    /*cout<<"indice1: "<<indice1<<endl;
    cout<<"indice2: "<<indice2<<endl;*/
    individuo1 = todosCaminos[ruleta[indice1]].first;
    individuo2 = todosCaminos[ruleta[indice2]].first;

    cruzamientoPMX(individuo1,individuo2);

}

void seleccionProporcion(vector <pair<vector<int>,float>> todosCaminos,int numIndividuos)
{
    float distancia;
    float total;
    float sumaDistancias = 0;
    float proporcion = 0;
    float valorProporcion;
    float cien = 0;
    vector<float> CB; /*C/B*/
    vector< pair<int,int> > valuesVec; /*C/B*/
    pair<int,int> values;

    for(int i=0;i<todosCaminos.size();i++)
    {
        sumaDistancias += distancia_total(todosCaminos[i].first);
    }
    //cout<<"DisTotal: "<<sumaDistancias<<endl;

    for(int i=0;i<todosCaminos.size();i++)
    {
        distancia = todosCaminos[i].second;
        total = sumaDistancias - distancia;
        CB.push_back((total/distancia));
        //cout<<"CB: "<<(total/distancia)<<endl;
        proporcion += (total/distancia);

    }

    //cout<<"Propor: "<<proporcion<<endl;
    for(int i=0;i<CB.size();i++)
    {
        valorProporcion = (CB[i]/proporcion*100);
        //cout<<"valorProporcion: "<<valorProporcion<<endl;
        cien += valorProporcion;
        values = make_pair(valorProporcion,i); /*90 veces distancia que le corresponde al individo 1*/
        valuesVec.push_back(values);
    }
    //cout<<"Cien: "<<cien<<endl;

    //seleccionRuleta(valuesVec,todosCaminos);
    for(int i=0;i<(numIndividuos/2);i++)
        seleccionRuleta(valuesVec,todosCaminos);
}
void seleccionAleatoria(vector <pair<vector<int>,float>> todosCaminos,int numIndividuos)
{
    vector<int> individuo1,individuo2;
    sort(todosCaminos.begin(), todosCaminos.end(), [](const std::pair<vector<int>,float>&left, const pair<vector<int>,float> &right) {
        return left.second < right.second;
    });


    for(int i=0;i<(numIndividuos/2)+1;i+=2)
    {
        individuo1 = todosCaminos[i].first ;
        individuo2 = todosCaminos[i+1].first ;
        cruzamientoPMX(individuo1,individuo2);

    }

}

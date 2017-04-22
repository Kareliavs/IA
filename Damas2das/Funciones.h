#include <iostream>
#include <vector>
using namespace std;

#define tam 8

#ifndef IADAMASMINMAC_FUNCIONES_H
#define IADAMASMINMAC_FUNCIONES_H

void igualarMatrices(int** Mat1, int** Mat2)
{
    for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
            Mat1[i][j]=Mat2[i][j];
        }
    }
}

void printTablero(int** tabl)
{
    cout<<"**********************************************************"<<endl;
    for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
            cout<<"["<<tabl[i][j]<<" ]\t";
        }
        cout<<endl;
    }
    cout<<"**********************************************************"<<endl;
    cout<<endl;
}

#endif //IADAMASMINMAC_FUNCIONES_H

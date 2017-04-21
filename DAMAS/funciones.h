#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>


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

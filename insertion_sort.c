#include "item.h"

//ideia: Comparar com o da esquerda e deslocar enquanto for menor.

void sort(Item *a, int lo, int hi) 
{
    int i, j;

    for(i=lo+1; i<=hi; i++)
    {
        for(j=i; j>lo; j--)
        {
            if(less(a[j-1], a[j])) break;
            exch(a[j-1], a[j]);
        }
    }
}


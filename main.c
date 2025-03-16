#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "item.h"
#include "sort.h"
#include "fila.h"
#include "arvore.h"

int main(){
    No* raiz = criaNo(4, NULL);

    insereArvore(&raiz, 20);
    imprimeArvore(raiz);
    printf("\n");
    
    insereArvore(&raiz, 75);
    imprimeArvore(raiz);
    printf("\n");

    insereArvore(&raiz, 77);
    imprimeArvore(raiz);
    printf("\n");
    
    insereArvore(&raiz, 78);
    imprimeArvore(raiz);
    printf("\n");

    insereArvore(&raiz, 55);
    imprimeArvore(raiz);
    printf("\n");

    insereArvore(&raiz, 62);
    imprimeArvore(raiz);
    printf("\n");

    insereArvore(&raiz, 51);
    imprimeArvore(raiz);
    printf("\n");
    
    insereArvore(&raiz, 40);
    insereArvore(&raiz, 60);
    insereArvore(&raiz, 45);

    printf("\nArvore completa:\n");
    imprimeArvore(raiz);

    return 0;
}



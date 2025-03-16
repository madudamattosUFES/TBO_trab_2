#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "item.h"
#include "sort.h"
#include "fila.h"
#include "arvore.h"

int main(){
    No* raiz = criaNo(4, NULL);

    printf("Insere 20\n");
    insereArvore(&raiz, 20);
    imprimeArvore(raiz);
    printf("\n");
    
    printf("Insere 75\n");
    insereArvore(&raiz, 75);
    imprimeArvore(raiz);
    printf("\n");

    printf("Insere 77\n");
    insereArvore(&raiz, 77);
    imprimeArvore(raiz);
    printf("\n");
    
    printf("Insere 78\n");
    insereArvore(&raiz, 78);
    imprimeArvore(raiz);
    printf("\n");

    printf("Insere 55\n");
    insereArvore(&raiz, 55);
    imprimeArvore(raiz);
    printf("\n");

    printf("Insere 62\n");
    insereArvore(&raiz, 62);
    imprimeArvore(raiz);
    printf("\n");
    
    printf("Insere 51\n");
    insereArvore(&raiz, 51);
    imprimeArvore(raiz);
    printf("\n");
    
    printf("Insere 40\n");
    insereArvore(&raiz, 40);
    imprimeArvore(raiz);
    printf("\n");

    printf("Insere 60\n");
    insereArvore(&raiz, 60);
    imprimeArvore(raiz);
    printf("\n");
    
    printf("Insere 45\n");
    insereArvore(&raiz, 45);
    imprimeArvore(raiz);
    printf("\n");

    printf("\nArvore completa:\n");
    imprimeArvore(raiz);

    return 0;
}



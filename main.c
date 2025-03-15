#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "item.h"
#include "sort.h"
#include "fila.h"
#include "arvore.h"

int main(){
    No* raiz = criaNo(4, NULL);

    raiz = insereArvore(raiz, 20);
    raiz = insereArvore(raiz, 75);
    raiz = insereArvore(raiz, 77);
    raiz = insereArvore(raiz, 78);
    raiz = insereArvore(raiz, 55);
    raiz = insereArvore(raiz, 62);
    raiz = insereArvore(raiz, 51);
    raiz = insereArvore(raiz, 40);
    raiz = insereArvore(raiz, 60);
    raiz = insereArvore(raiz, 45);

    imprimeArvoreBPorNivel(raiz);


    return 0;
}
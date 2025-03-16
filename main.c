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
    insereArvore(&raiz, 75);
    insereArvore(&raiz, 77);
    insereArvore(&raiz, 78);
    insereArvore(&raiz, 55);
    insereArvore(&raiz, 62);
    insereArvore(&raiz, 51);
    insereArvore(&raiz, 40);
    insereArvore(&raiz, 60);
    insereArvore(&raiz, 45);

    imprimeArvore(raiz);

    return 0;
}
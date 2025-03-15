#include "fila.h"
#include <stdio.h>
#include <stdlib.h>


Fila* criaFila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (!f) return NULL;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void insereInicFila(Fila* f, void* elemento) {
    if (!f || !elemento) return;
    
    Celula* novo = (Celula*) malloc(sizeof(Celula));
    if (!novo) return;

    novo->dado = elemento;
    novo->prox = f->ini;
    f->ini = novo;

    if (f->fim == NULL) {
        f->fim = novo;
    }
}

void insereFila(Fila* f, void* elemento) {
    if (!f || !elemento) return;

    Celula* novo = (Celula*) malloc(sizeof(Celula));
    if (!novo) return;

    novo->dado = elemento;
    novo->prox = NULL;

    if (f->fim) {
        f->fim->prox = novo;
    } else {
        f->ini = novo;
    }

    f->fim = novo;
}

void* retiraFila(Fila* f) {
    if (!f || !f->ini) return NULL;

    Celula* removido = f->ini;
    void* dado = removido->dado;

    f->ini = removido->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(removido);
    return dado;
}

int ehVaziaFila(Fila* f) {
    if (!f) return -1;
    return (f->ini == NULL);
}

void destroiFila(Fila* f) {
    if (!f) return;

    Celula* atual = f->ini;
    while (atual) {
        Celula* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    free(f);
}

void imprimeFila(Fila* f, void (*imprimeElemento)(void*)) {
    if (!f || !imprimeElemento) return;

    Celula* atual = f->ini;
    while (atual) {
        imprimeElemento(atual->dado);
        atual = atual->prox;
    }
}

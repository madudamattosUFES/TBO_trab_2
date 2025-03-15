#ifndef FILA_H
#define FILA_H

typedef struct fila Fila;

// Cria uma fila vazia
Fila* criaFila();

// Insere um elemento no início da fila
void insereInicFila(Fila* f, void* elemento);

// Insere um elemento no final da fila
void insereFila(Fila* f, void* elemento);

// Retira um elemento do início da fila
void* retiraFila(Fila* f);

// Verifica se a fila está vazia
int ehVaziaFila(Fila* f);

// Destroi a fila
void destroiFila(Fila* f);

// Imprime os elementos da fila com uma função genérica de impressão
void imprimeFila(Fila* f, void (*imprimeElemento)(void*));

#endif

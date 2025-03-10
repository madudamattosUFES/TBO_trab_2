#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>

// Definição da estrutura No
typedef struct no No;

// Função para criar um novo nó
No* novoNo(int ordem, No* pai);

// Função para buscar uma chave na árvore
No* buscaChave(No* no, void* chave);

// Função para inserir uma chave na árvore
void insereChave(No* raiz, void* chave);

#endif // ARVORE_H
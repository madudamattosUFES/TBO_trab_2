#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>
#include <stdbool.h>

// Declaração incompleta da estrutura No
typedef struct no No;

// Função para criar um novo nó
No* criaNo(int ordem, No* pai);

// Função para buscar uma chave na árvore
No* buscaChave(No* no, int chave);

// Função para verificar se um nó é folha
bool ehNoFolha(No* no);

// Função para remover uma chave da árvore
No* removeArvore(No* raiz, int chave, int ordem);

// Função para verificar se um nó contém uma chave
bool noContemChave(No* no, int chave);

// Função para verificar se um nó possui pai
bool noPossuiPai(No* no);

// Função para retornar o irmão esquerdo de um nó
No* retornaIrmaoEsquerdo(No* no);

// Função para retornar o irmão direito de um nó
No* retornaIrmaoDireito(No* no);

// Função para imprimir a árvore em largura (por nível)
void imprimeArvore(No* raiz);

// Função para liberar um nó
void liberaNo(No* no);

// Função para liberar a árvore
void liberaArvore(No* no);

void insereArvore(No** raiz, int chave);

No* insereNo(No* no, int chave);

#endif // ARVORE_H
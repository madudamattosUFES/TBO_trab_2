#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"


struct no {
    int nChaves; // número de chaves no nó
    No* pai; // ptr para o pai
    int* chaves; // ptr para o array de chaves
   //void* dadosRegistro; // ptr generico para o array de struct q define chaves e outras informações necessarias (a ser usado futuramente)
    No** filhos; // ptr para o array de ponteiros para os filhos 
};

// para uma ordem d da arvore -> max 2d filhos e min d filhos
No* criaNo(int ordem, No* pai) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->nChaves = 0;
    novoNo->pai = pai;
    novoNo->chaves = malloc(2 * ordem * sizeof(int));
    novoNo->filhos = malloc(( 2 * ordem + 1) * sizeof(No*));

    for(int i=0; i<ordem; i++){

    }

    return novoNo;
}

No* buscaChave(No* no, void* chave) { 
    if(no){
        int i=0;
        while(i< no->nChaves && chave > no->chaves[i]) i++;
        if(i < no->nChaves && chave == no->chaves[i]) return no; // encontrou chave
        else if(no->filhos[i]) return buscaChave(no->filhos[i], chave); // busca nos filhos
        else return no; // buscou até o nó folha e não encontrou, retorna o nó onde a chave deveria estar
    } else return NULL;
}

bool noContemChave(No* no, int chave) {
    for(int i = 0; i < no->nChaves; i++) {
        if(no->chaves[i] == chave) return true;
    }
    return false;
}

bool noCheio(No* no, int ordem) {
    return no->nChaves == ordem;
}


void insereChave(No* raiz, void* chave) {
    
    No* no = buscaChave(raiz, chave);
    
    // se o no ja estiver na arvore, nao insere
    if(noContemChave(no, chave)){
        printf("Chave já inserida na árvore!\n");
        return;
    }

    // se o nó não estiver cheio, insere a chave no nó
    if(!noCheio(no, ordem)) {
        int i = no->nChaves - 1;
        while(i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->nChaves++;
    } 

    // se o nó estiver cheio, divide o nó, sobe o do meio para o pai e cria outro no 
    // as d primeiras chaves ficam no nó original, a chave d+1 sobe para o pai, na nova pagina ficam as restantes
 
    
    
    // se o nó estiver cheio, divide o nó 


}
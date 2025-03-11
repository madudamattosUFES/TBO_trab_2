#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"
#include "item.h"


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
    novoNo->filhos = malloc(( 2 * ordem  + 1) * sizeof(No*));

    // inicializa vetores
    for(int i=0; i<ordem; i++){
        novoNo->chaves[i] = 0;
        novoNo->filhos[i] = NULL;
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

bool noPossuiPai(No* no) {
    return no->pai != NULL;
}

bool noCheio(No* no, int ordem) {
    return no->nChaves == ordem;
}

void insereNo(No* no, int chave, int ordem) {
    if(no->nChaves == 0) {
        no->chaves[0] = chave;
        return;
    }
    else{
        int i = no->nChaves - 1;
        while(i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
    }

    no->nChaves++;

    return;
}

void insereArvore(No* raiz, void* chave, int ordem) {
    
    No* no = buscaChave(raiz, chave);
    
    // se o no ja estiver na arvore, nao insere
    if(noContemChave(no, chave)){
        printf("Chave já inserida na árvore!\n");
        return;
    }

    // se o nó não estiver cheio, insere a chave no nó
    if(!noCheio(no, ordem)) {
        insereNo(no, chave, ordem);
    } else {
        // se o nó estiver cheio, divide o nó, sobe o do meio para o pai e cria outro nó
        No* novoNo = criaNo(ordem, no->pai);
        int vetorAux[ordem + 1];
        int i;

        // essa etapa é só para descobrir qual é a chave de valor intermediario que irá subir pro nó-pai
        for(i=0; i<=ordem; i++) {
            vetorAux[i] = no->chaves[i];
        }
        vetorAux[i+1] = chave; // insere a chave no vetor auxiliar
        sort(vetorAux, 0, ordem); // insertion sort para ordenar o vetor auxiliar

        int indiceDoMeio = ordem/2;
        int chaveDoMeio = vetorAux[indiceDoMeio] ;

        // as d primeiras chaves ficam no nó original, a chave d+1 sobe para o pai, na nova página ficam as restantes
        // atualiza a primeira metade do nó com os valores certos
        for(i=0; i<indiceDoMeio; i++) {
            no->chaves[i] = vetorAux[i];
        }
        for(i=indiceDoMeio; i<=ordem;i++){
            no->chaves[i] = -1;
        }

        // atualiza o novo nó com os novos valores
        for(i=indiceDoMeio+1; i<=ordem; i++) {
            novoNo->chaves[i-indiceDoMeio-1] = vetorAux[i];
        }

        if(noPossuiPai(no)){
            insereNo(no->pai, chaveDoMeio, ordem);
            // atualiza os filhos do pai para receber o nó partido
            for(i=0; i<=no->pai->nChaves; i++){
                if(no->pai->filhos[i] == no){
                    no->pai->filhos[i] = no;
                    no->pai->filhos[i+1] = novoNo;
                    novoNo->pai = no->pai;
                    break;
                }
            }
        }else{
            // se não tem pai é pq é raiz, nesse caso o tratamento é diferente
            No* novoPai = criaNo(ordem, NULL);
            insereNo(novoPai, chaveDoMeio, ordem);
            // atualiza os filhos do novo pai
            novoPai->filhos[0] = no;
            novoPai->filhos[1] = novoNo;
            no->pai = novoPai;
            novoNo->pai = novoPai;
        }
    }

}

void imprimeArvore(No* no, int ordem){
    
}

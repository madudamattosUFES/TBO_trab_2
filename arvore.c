#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"
#include "item.h"
#include "sort.h"
#include "fila.h"

struct no {
    int nChaves; // número de chaves no nó
    No* pai; // ptr para o pai
    int* chaves; // ptr para o array de chaves
   //void* dadosRegistro; // ptr generico para o array de struct q define chaves e outras informações necessarias (a ser usado futuramente)
    No** filhos; // ptr para o array de ponteiros para os filhos 
    int d; // ordem da arvore
};


// para uma ordem d da arvore -> max 2d filhos e min d filhos
No* criaNo(int ordem, No* pai) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->nChaves = 0;
    novoNo->pai = pai;
    novoNo->d = ordem;
    novoNo->chaves = malloc(2 * ordem * sizeof(int));
    novoNo->filhos = malloc(( 2 * ordem  + 1) * sizeof(No*));

    // inicializa vetores
    for(int i=0; i<ordem; i++){
        novoNo->chaves[i] = 0;
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}


No* buscaChave(No* no, int chave) { 
    if(no){
        int i=0;
        while(i < no->nChaves && chave > no->chaves[i]) i++;
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


bool noCheio(No* no) {
    return no->nChaves == no->d;
}

No* insereNo(No* no, int chave) {
    int i = no->nChaves - 1;

    // Encontra a posição correta para a nova chave
    while (i >= 0 && chave < no->chaves[i]) {
        no->chaves[i + 1] = no->chaves[i];
        i--;
    }
    no->chaves[i + 1] = chave;
    no->nChaves++;

    int ordem = no->d;

    // Se o nó está cheio, faz o particionamento
    if (no->nChaves == ordem) {
        No* novoNo = criaNo(ordem, no->pai);
        int meio = ordem / 2;

        // maracutaia para descobrir a chave de valor intermediario que vai subir
        int vetorAux[ordem + 1];
        for(int i=0; i<= ordem; i++){
            vetorAux[i] = no->chaves[i];
        }
        vetorAux[i+1] = chave; // insere a chave no vetor auxiliar
        insertion_sort(vetorAux, 0, ordem); // insertion sort para ordenar o vetor auxiliar

        int chaveDoMeio = vetorAux[meio];
        
        // -------------------------------------------------

        if(chave == chaveDoMeio){
            // Atualiza o novo nó com a segunda metade das chaves
            for (i = meio + 1; i <= ordem; i++) {
                novoNo->chaves[i - (meio + 1)] = vetorAux[i];
                novoNo->filhos[i - (meio + 1)] = no->filhos[i];
                if (novoNo->filhos[i - (meio + 1)] != NULL) {
                    novoNo->filhos[i - (meio + 1)]->pai = novoNo;
                }
            }
            novoNo->filhos[i - (meio + 1)] = no->filhos[i];
            if (novoNo->filhos[i - (meio + 1)]) {
                novoNo->filhos[i - (meio + 1)]->pai = novoNo;
            }

            // Atualiza a qtd de chaves 
            novoNo->nChaves =  meio;
            no->nChaves = meio -1;

        }
        else if(chave < chaveDoMeio){
            // a chave nova vai entrar no nó atual e a chave que sobe vai ser vetorAux[meio-1]
            for(int i=0; i<meio; i++){
                if(no->chaves[i] == vetorAux[i]){
                    continue;
                }
                vetorAux[i] = no->chaves[i];
                if(no->filhos[i]){
                    no->filhos[i] = no->filhos[i+1];
                }
            }
            // Atualiza o novo nó com a segunda metade das chaves
            for (i = meio + 1; i <= ordem; i++) {
                novoNo->chaves[i - (meio + 1)] = vetorAux[i];
                novoNo->filhos[i - (meio + 1)] = no->filhos[i];
                if (novoNo->filhos[i - (meio + 1)] != NULL) {
                    novoNo->filhos[i - (meio + 1)]->pai = novoNo;
                }
            }
            novoNo->filhos[i - (meio + 1)] = no->filhos[i];
            if (novoNo->filhos[i - (meio + 1)]) {
                novoNo->filhos[i - (meio + 1)]->pai = novoNo;
            }

            // Atualiza a qtd de chaves 
            novoNo->nChaves =  meio -1;
            no->nChaves = meio;
        } 
        else {
            // a chave nova vai entrar no novo nó e a chave que sobe vai ser vetorAux[meio+1] 
            // Atualiza o novo nó com a segunda metade das chaves de vetorAux e insere a chave na posição correta, ajustando a posição dos filhos se necessário 
            for (i = meio + 1; i <=  ordem; i++) {
                novoNo->chaves[i - (meio + 1)] = vetorAux[i];
                novoNo->filhos[i - (meio + 1)] = no->filhos[i];
                novoNo->filhos[i - (meio + 1)] = no->filhos[i];
                if (novoNo->filhos[i - (meio + 1)] != NULL) {
                    novoNo->filhos[i - (meio + 1)]->pai = novoNo;
                }

                // if(vetorAux[i] >= chave){
                //     novoNo->filhos[i-(meio+1) + 1] = no->filhos[i];
                //     if(novoNo->filhos[i-(meio+1) + 1]){
                //         novoNo->filhos[i-(meio+1) + 1]->pai = novoNo;
                //     }
                // }
            }
            novoNo->filhos[i - (meio + 1)] = no->filhos[i];
            if (novoNo->filhos[i - (meio + 1)]) {
                novoNo->filhos[i - (meio + 1)]->pai = novoNo;
            }

            // Atualiza a qtd de chaves 
            novoNo->nChaves =  meio;
            no->nChaves = meio - 1; // nao mudar isso ! 
        }

        // -------------------------------------------------


        // Se o nó possui pai, insere a chave do meio no pai
        if (no->pai) {
            insereNo(no->pai, chaveDoMeio);
            // Atualiza os filhos do pai para receber o nó partido
            for (i = 0; i <= no->pai->nChaves; i++) {
                if (no->pai->filhos[i] == no) {
                    for (int j = no->pai->nChaves; j > i; j--) {
                        no->pai->filhos[j + 1] = no->pai->filhos[j];
                    }
                    no->pai->filhos[i + 1] = novoNo;
                    novoNo->pai = no->pai;
                    break;
                }
            }
        } else {
            // Se não tem pai, é a raiz, então divide e cria um novo pai
            No* novoPai = criaNo(ordem, NULL);
            novoPai->chaves[0] = chaveDoMeio;
            novoPai->filhos[0] = no;
            novoPai->filhos[1] = novoNo;
            novoPai->nChaves = 1;
            no->pai = novoPai;
            novoNo->pai = novoPai;
            return novoPai; // Retorna a nova raiz
        }
    }

    // Se o nó atualizado for a raiz, então retorna a nova raiz, se não retorna o próprio nó.
    return no->pai ? no->pai : no; 
}

void insereArvore(No** raiz, int chave) {
    No* no = *raiz;
    while (!ehNoFolha(no)) {
        int i = 0;
        while (i < no->nChaves && chave > no->chaves[i]) {
            i++;
        }
        no = no->filhos[i];
    }
    No* novaRaiz = insereNo(no, chave);
    if (novaRaiz != *raiz) {
        *raiz = novaRaiz; // Atualiza a raiz se necessário
    }
}

No* retornaIrmaoEsquerdo(No* no){
    if(noPossuiPai(no)){
        for(int i=0; i<=no->pai->nChaves; i++){
            if(no->pai->filhos[0] == no){
                return NULL;
            }
            if(no->pai->filhos[i] == no){
                return no->pai->filhos[i-1];
            }
        }
    }
    return NULL;
}


No* retornaIrmaoDireito(No* no){
    if(noPossuiPai(no)){
        for(int i=0; i<=no->pai->nChaves; i++){
            if(no->pai->filhos[i] == no){
                return no->pai->filhos[i+1];
            }
        }
    }
    return NULL;
}


bool ehNoFolha(No* no){
    for(int i=0; i<=no->nChaves; i++){
        if(no->filhos[i]){
            return false;
        }
    }
    return true;
}


// // Caso 1 : Se o nó é folha e ficou com mais de 50% de sua capacidade -> faz nada, encerra. 
// // Caso 2: Verifica se o nó é intermediário, troca a chave a ser removida pela chave do antecessor -> se a folha ficar com mais de 50% de sua capacidade, encerra.
//     // se nao tiver antecessor troca pelo sucessor
// // Caso 3: Se o nó ficar com menos de 50% de sua capacidade, redistribui as chaves entre os irmãos
// // Caso 4: Se o nó ficar com menos de 50% de sua capacidade e não puder redistribuir entre irmaos, concatena         
// No* removeArvore(No* raiz, int chave, int ordem){
//     int j=0, i=0;
//     //busca o nó para ver se esta na arvore 
//     No* no = buscaChave(raiz, chave);
//     if(no){
//         No* irmaoEsquerdo = retornaIrmaoEsquerdo(no);
//         No* irmaoDireito = retornaIrmaoDireito(no);
        
//         int indiceChave = -1;
//         for(i=0; i<no->nChaves; i++){
//             if(no->chaves[i] == chave){
//                 indiceChave = i;
//                 break;
//             }
//         }

//         // Remove e ve em qual dos casos caiu
//         if(ehNoFolha(no)){
//             for(i=0; i<no->nChaves; i++){
//                 if(no->chaves[i] == chave){
//                     for(j=i; j<no->nChaves; j++){
//                         no->chaves[j] = no->chaves[j+1];
//                     }
//                     no->chaves[j] = -1;
//                     no->nChaves--;
//                     break;
//                 }
//             }
            
//             // se o nó ficar com menos de 50% de sua capacidade, redistribui as chaves entre os irmãos
//             if(no->nChaves < no->d){
//                 // se tiver irmão a esquerda
//                 if(irmaoEsquerdo){
//                     if(irmaoEsquerdo->nChaves > no->d){
//                         // redistribui as chaves
//                         no->chaves[0] = irmaoEsquerdo->chaves[irmaoEsquerdo->nChaves-1];
//                         irmaoEsquerdo->chaves[irmaoEsquerdo->nChaves-1] = -1;
//                         irmaoEsquerdo->nChaves--;
//                         no->nChaves++;
//                     }else{
//                         // concatena os nós
//                         for(i=0; i<no->nChaves; i++){
//                             irmaoEsquerdo->chaves[irmaoEsquerdo->nChaves] = no->chaves[i];
//                             irmaoEsquerdo->nChaves++;
//                         }
//                         liberaNo(no);
//                     }
//                 }else if(irmaoDireito){
//                     if(irmaoDireito->nChaves > no->d){
//                         // redistribui as chaves
//                         no->chaves[no->nChaves] = irmaoDireito->chaves[0];
//                         irmaoDireito->chaves[0] = -1;
//                         irmaoDireito->nChaves--;
//                         no->nChaves++;
//                     }else{
//                         // concatena os nós
//                         for(i=0; i<irmaoDireito->nChaves; i++){
//                             no->chaves[no->nChaves] = irmaoDireito->chaves[i];
//                             no->nChaves++;
//                         }
//                         liberaNo(irmaoDireito);
//                     }
//                 }
//             }
//             if(no->nChaves < no->d){
                
                
//             }

//             for(i=0; i<no->nChaves; i++){
//                 if(no->chaves[i] == chave){
//                     for(j=i; j<no->nChaves; j++){
//                         no->chaves[j] = no->chaves[j+1];
//                     }
//                     no->chaves[j] = -1;
//                     no->nChaves--;
//                     break;
//                 }
//             }

//         } else if(no == raiz){
//             // é um nó raiz 
//         } else {
//             // é nó intermediário
//             // busca o nó imediatamente anterior para substituir
//             No* noAnterior = no->filhos[no->nChaves];
//             while(noAnterior->filhos[0]){
//                 noAnterior = noAnterior->filhos[noAnterior->nChaves];
//             }
//             int chaveAnterior = noAnterior->chaves[noAnterior->nChaves-1];
//             no->chaves[i] = chaveAnterior;

//         }

//     }else{
//         printf("Nó não encontrado na árvore!\n");
//         return NULL;
//     }

// }


void imprimeArvore(No* raiz) {
    if (raiz == NULL) return;

    Fila* fila = criaFila();
    insereFila(fila, raiz);

    while (!ehVaziaFila(fila)) {
        int nivelTamanho = 0;
        Fila* filaNivel = criaFila();

        // Conta o número de nós no nível atual
        Celula* atual = fila->ini;
        while (atual) {
            nivelTamanho++;
            atual = atual->prox;
        }

        // Processa todos os nós no nível atual
        while (nivelTamanho > 0) {
            No* noAtual = (No*) retiraFila(fila);

            // Imprime todas as chaves do nó atual
            printf("[");
            for (int i = 0; i < noAtual->nChaves; i++) {
                printf("key: %d, ", noAtual->chaves[i]);
            }
            printf("]");

            // Adiciona todos os filhos do nó atual à fila do próximo nível
            for (int i = 0; i <= noAtual->nChaves; i++) {
                if (noAtual->filhos[i] != NULL) {
                    insereFila(filaNivel, noAtual->filhos[i]);
                }
            }

            nivelTamanho--;
        }
        printf("\n"); // Nova linha após cada nível

        // Troca a fila atual pela fila do próximo nível
        destroiFila(fila);
        fila = filaNivel;
    }

    destroiFila(fila);
}


void liberaNo(No* no) {
    if(!no) return;
    free(no->chaves);
    free(no->filhos);
    free(no);
}


void liberaArvore(No* no){
    if(no){
        for(int i=0; i<=no->nChaves; i++){
            liberaArvore(no->filhos[i]);
        }
        liberaNo(no);
    }
}

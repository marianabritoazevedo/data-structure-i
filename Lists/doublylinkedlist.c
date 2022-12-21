#include <stdlib.h>
#include <stdio.h>

struct no{
    struct no *ant;
    int val;
    struct no *prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar() {
   //Criar doublylinkedlist com qtd=0 e cauda e cabeça nulas
  struct doublylinkedlist* dlista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
  dlista->cabeca = NULL;
  dlista->cauda = NULL;
  dlista->qtdade = 0;
  return dlista;
}

struct no* alocarNovoNo(int valor){
    //Criar novo nó com o valor passado e o anterior e proximo nulos
  struct no* novoNo = (struct no*)malloc(sizeof(struct no));
  novoNo->val = valor;
  novoNo->prox = NULL;
  novoNo->ant = NULL;
  return novoNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor){
  //CONFERIR
  if(lista->qtdade == 0){
    struct no* novoNo = alocarNovoNo(valor);
    lista->cabeca = novoNo;
    lista->cauda = novoNo;
  }else{
    struct no* novoNo = alocarNovoNo(valor);
    struct no* atualCabeca = lista->cabeca;
    novoNo->prox = atualCabeca;
    atualCabeca->ant = novoNo;
    lista->cabeca = novoNo;
  }
  lista->qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor){
  if(lista->qtdade == 0){
    inserirElementoNoInicio(lista, valor);
  }else{
    struct no* aux = lista->cauda;
    struct no* novoNo = alocarNovoNo(valor);
    aux->prox = novoNo;
    novoNo->ant = lista->cauda; //que é o meso que o auxiliar
    lista->cauda = novoNo;
    lista->qtdade++;
  }
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao){
  if(posicao > lista->qtdade){
    return;
  }
  if(posicao == 0){
    inserirElementoNoInicio(lista, valor);
  }else if(lista->qtdade == posicao){
    inserirElementoNoFim(lista, valor);
  }else{
    struct no* novoNo = alocarNovoNo(valor);
    struct no* noAntes = lista->cabeca;
    int cont = 0;
    while(cont < posicao-1){
      noAntes = noAntes->prox;
      cont++;
    }
    struct no* noDepois = noAntes->prox;
    novoNo->ant = noAntes;
    novoNo->prox = noDepois;
    noAntes->prox = novoNo;
    noDepois->ant = novoNo;
    lista->qtdade++;
  }
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao){
  if(posicao >= 0 && posicao < lista->qtdade){
    struct no* aux = lista->cabeca;
    int cont = 0;
    while(cont < posicao){
      aux = aux->prox;
      cont++;
    }
    return aux->val;
  }else{
    return -1;
  }
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
  if(lista->qtdade == 1){
    if(posicao == 0){
      struct no* rem = lista->cabeca;
      free(rem);
      lista->cabeca = NULL;
      lista->cauda = NULL;
      lista->qtdade--;
    }
    return;
  }  
  if (posicao >= 0 && posicao < lista->qtdade) {
        if (posicao == 0) {
            struct no* rem = lista->cabeca;
            struct no* depoisRem = rem->prox;
            lista->cabeca = depoisRem;
            if (depoisRem != NULL) {
                depoisRem->ant = NULL;
            }
            free(rem);
            lista->qtdade--;
        }
        else if (posicao == lista->qtdade - 1) {
            struct no* rem = lista->cauda;
            struct no* antesRem = rem->ant;
            antesRem->prox = NULL;
            lista->cauda = antesRem;
            free(rem);
            lista->qtdade--;
        }
        else {
            struct no* rem = lista->cabeca;
            int cont = 0;
            while (cont < posicao) {
                rem = rem->prox;
                cont++;
            }
            struct no* noAntes = rem->ant;
            struct no* noDepois = rem->prox;
            noAntes->prox = noDepois;
            noDepois->ant = noAntes;
            free(rem);
            lista->qtdade--;
        }
    }
}

void imprimirLista(struct no** cabeca) {
    //usamos o aux para percorrer a lista
    if ((*cabeca) != NULL) {
        struct no* aux = (*cabeca);
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}

void imprimirLista2(struct doublylinkedlist* lista) {
    //usamos o aux para percorrer a lista
    if ((lista->cabeca) != NULL) {
        struct no* aux = (lista->cabeca);
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]\n");
    }
    else {
        printf("A lista está vazia!\n");
    }
}


int main(){
  struct doublylinkedlist* lista = inicializar();
  inserirElementoNoInicio(lista, 2);
  inserirElementoNoInicio(lista, 3);
  imprimirLista2(lista);
  inserirElementoNoFim(lista, 55);
  imprimirLista2(lista);
  inserirElementoEmPosicao(lista, 1, 1);
  imprimirLista2(lista);
  inserirElementoEmPosicao(lista, 44, 2);
  imprimirLista2(lista);
  removerElementoEmPosicao(lista, 3);
  imprimirLista2(lista);
  return 0;
}
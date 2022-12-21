#include <stdlib.h>
#include <stdio.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
  //Criar linkedlist com cabeça sem apontar para nada e tamanho zero
  struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
  lista->cabeca = NULL;
  lista->qtdade = 0;
  return lista;
}

struct no* alocarNovoNo(int valor) {
  //Criar struct do novo no
  //Atribuir o valor correspondente ao novo nó e o prox nó será NULL
  struct no* novoNo = (struct no*)malloc(sizeof(struct no));
  novoNo->val = valor;
  novoNo->prox = NULL;
  return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    //se a lista está vazia, apontar a cabeça da lista para o nó recém criado
    if(lista->cabeca == NULL){
      struct no* novoNo = alocarNovoNo(valor);
      lista->cabeca = novoNo;
    }else{
      //Se a lista não está vazia, percorrer até o último elemento da lista
      //E atualizar o seu valor de "prox"
      struct no* aux = lista->cabeca;
      while(aux->prox != NULL){
        aux = aux->prox;
      }
      struct no* novoNo = alocarNovoNo(valor);
      aux->prox = novoNo;
    }
  //Indicar que houve o aumento da lista
  lista->qtdade++;
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {
  //se a lista está vazia, o novoNo será a cabeça da lista
    if(lista->cabeca == NULL){
      struct no* novoNo = alocarNovoNo(valor);
      lista->cabeca = novoNo;
    }else{
      //o próximo do novoNo será o que estava na lista->cabeça, e agora o novoNo é a cabeça da lista
      struct no* novoNo = alocarNovoNo(valor);
      novoNo->prox = lista->cabeca;
      lista->cabeca = novoNo;
    }
  lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
  //verificar se a posição é válida
    if(posicao >= 0 && posicao <= lista->qtdade){
      if(posicao == 0){
        inserirElementoNoInicio(lista, valor);
      }else if(posicao == lista->qtdade){
        inserirElementoNoFim(lista, valor);
      }else{
        struct no* aux = lista->cabeca;
        int cont = 0;
        //chegar ao elemento 1 casa antes da posição desejada para mudar seu valor de prox
        while(cont < posicao-1){
          aux = aux->prox;
          cont++;
        }
        struct no* novoNo = alocarNovoNo(valor);
        novoNo->prox = aux->prox;
        aux->prox = novoNo;
        lista->qtdade++;
      }
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if(posicao >= 0 && posicao < lista->qtdade){
      struct no* aux = lista->cabeca;
      int cont = 0;
      //ir até o elemento e retornar seu valor
      while(cont < posicao){
        aux = aux->prox;
        cont++;
      }
      return aux->val;
    }else{
      return -1;
    }
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if(posicao >= 0 && posicao < lista->qtdade){
      if(posicao == 0){
        struct no* rem = lista->cabeca;
        lista->cabeca = rem->prox;
        free(rem);
        lista->qtdade--;
      }else{
        struct no* aux = lista->cabeca;
        int cont = 0;
        while(cont < posicao-1){
          aux = aux->prox;
          cont++;
        }
        struct no* rem = aux->prox;
        aux->prox = rem->prox;
        free(rem);
        lista->qtdade--;
      }
    }
}

void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
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
  struct linkedlist* lista = inicializar();
  imprimirLista(lista);
  inserirElementoNoFim(lista, 4);
  inserirElementoNoFim(lista, 50);
  imprimirLista(lista);
  inserirElementoNoInicio(lista, 10);
  imprimirLista(lista);
  inserirElementoEmPosicao(lista,0,0);
  inserirElementoEmPosicao(lista,5,4);
  imprimirLista(lista);
  inserirElementoEmPosicao(lista,1,1);
  inserirElementoEmPosicao(lista,4,5);
  imprimirLista(lista);
  int p1 = obterElementoEmPosicao(lista,0);
  printf("%d\n",p1);
  int p2 = obterElementoEmPosicao(lista,2);
  printf("%d\n",p2);
  int p3 = obterElementoEmPosicao(lista,6);
  printf("%d\n",p3);
  int p4 = obterElementoEmPosicao(lista,7);
  printf("%d\n",p4);
  removerElementoEmPosicao(lista,0);
  removerElementoEmPosicao(lista,5);
  removerElementoEmPosicao(lista,2);
  imprimirLista(lista);
  return 0;
}
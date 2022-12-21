#include <stdio.h>
#include <stdlib.h>

struct arraylist {
    int* vetor;
    int qtdade;
    int capacidade;
};

struct arraylist* inicializar(int capacidade) {
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));
    lista->vetor = (int*)calloc(capacidade, sizeof(int));
    lista->qtdade = 0;
    lista->capacidade = capacidade;
    return lista;
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
  //Verificar se a posição passada pelo usuário é válida e retornar valor
  if(posicao >= 0 && posicao < lista->qtdade){
    return lista->vetor[posicao];
  }
  return 0;
}

void duplicarCapacidade(struct arraylist* lista) {
  lista->vetor = (int*)realloc(lista->vetor, 2*lista->capacidade*sizeof(int));
  lista->capacidade = 2*lista->capacidade;
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
  //Verificar se é necessário duplicar o tamanho da lista
  if(lista->qtdade == lista-> capacidade){
    duplicarCapacidade(lista);
  }
  lista->vetor[lista->qtdade] = valor;
  lista->qtdade++;
}

void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
  //Verificar se é necessário duplicar o tamanho da lista, já que será inserido um novo elemento
  //Verificar se a posição é válida
  if(posicao >= 0 && posicao <= lista->qtdade){
    if(lista->qtdade == lista->capacidade){
      duplicarCapacidade(lista);
    }
    //Deslocar todos os elementos uma casa para trás para dar espaço ao novo elemento naquela posição
    for(int i = lista-> qtdade; i > posicao; i--){
      lista->vetor[i] = lista->vetor[i-1];
    }
    //Colocar o novo elemento naquele lugar
    lista->vetor[posicao] = valor;
    //Atualizar a quantidade de elementos na lista
    lista->qtdade++;
  }
}

void atualizarElemento(struct arraylist* lista, int valor, int posicao) {
  //Conferir se posição é válida e atualizar o novo elemento
  if(posicao > 0 && posicao < lista->qtdade){
    lista->vetor[posicao] = valor;
  }
}

void removerElementoNoFim(struct arraylist* lista) {
  //Necessário apenas decrementar a váriável qtdade da lista;
  lista->qtdade--;
}

void removerElementoEmPosicao(struct arraylist* lista, int posicao) {
  //Passar elementos da direita para esquerda
  for(int i = posicao; i < lista->qtdade-1;i++){
    lista->vetor[i] = lista->vetor[i+1];
  }
  //Atualizar qtdade
  lista->qtdade--;
}

void exibirLista(struct arraylist* lista) {
    printf("[");
    for (int i = 0; i < lista->qtdade; i++) {
        printf("%d", lista->vetor[i]);
        if (i < lista->qtdade - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
  struct arraylist* l = inicializar(10);
  inserirElementoNoFim(l, 5);
  inserirElementoNoFim(l, 10);
  inserirElementoNoFim(l, 3);
  exibirLista(l);
  int elemento = obterElementoEmPosicao(l, 1);
  printf("Elemento na posição = %d\n", elemento);
  inserirElementoEmPosicao(l,35,1);
  exibirLista(l);
  atualizarElemento(l,44,2);
  exibirLista(l);
  removerElementoNoFim(l);
  exibirLista(l);
  removerElementoEmPosicao(l,0);
  exibirLista(l);
  return 0;
}
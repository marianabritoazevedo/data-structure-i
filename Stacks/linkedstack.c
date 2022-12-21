#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct no{
    int val;
    struct no *prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar() {
  struct linkedstack* pilha = (struct linkedstack*)malloc(sizeof(struct linkedstack));
  pilha->topo = NULL;
  pilha->qtdade = 0;
  return pilha;
}

struct no* alocarNovoNo(int valor){
  struct no* novoNo = (struct no*)malloc(sizeof(struct no));
  novoNo->val = valor;
  novoNo->prox = NULL;
  return novoNo;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct linkedstack* pilha) {
  if(pilha == NULL){
    return true;
  }
  if(pilha->qtdade == 0){
    return true;
  }else{
    return false;
  }
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack** pilha, int valor){
  if((*pilha) == NULL){
    *pilha = inicializar();
  }
  if((*pilha)->qtdade == 0){
    struct no* novoNo = alocarNovoNo(valor);
    (*pilha)->topo = novoNo;
    (*pilha)->qtdade++;
  }else{
    struct no* novoNo = alocarNovoNo(valor);
    struct no* atualTopo = (*pilha)->topo;
    (*pilha)->topo = novoNo;
    (*pilha)->qtdade++;
    novoNo->prox = atualTopo;
  }
}

//decrementar qtdade se a pilha não estiver nula ou vazia
void desempilhar(struct linkedstack* pilha) {
  if(pilha == NULL){
    return;
  }
  if(pilha->qtdade > 0){
    struct no* topoAtual = pilha->topo;
    struct no* novoTopo = topoAtual->prox;
    pilha->topo = novoTopo;
    free(topoAtual);
    pilha->qtdade--;
  }
  
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack* pilha) {
  if(pilha == NULL){
    return INT_MIN;
  }
  if(pilha->qtdade != 0){
    struct no* topoAtual = pilha->topo;
    int valTopo = topoAtual->val;
    struct no* novoTopo = topoAtual->prox;
    pilha->topo = novoTopo;
    free(topoAtual);
    pilha->qtdade--;
    return valTopo;
  }else{
    return INT_MIN;
  }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack* pilha){
  if(pilha == NULL){
    return INT_MIN;
  }
  if(pilha->qtdade == 0){
    return INT_MIN;
  }else{
    struct no* top = pilha->topo;
    return top->val;
  }
}

void exibirPilha(struct linkedstack* pilha) {
    //usamos o aux para percorrer a lista
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;
        //navega partindo do topo até chegar NULL
        printf("_\n");
        do {
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_\n");
    }
    else {
        printf("A pilha está vazia!");
    }
}

int main(){
  struct linkedstack* pilha = inicializar();
  empilhar(&pilha, 3);
  empilhar(&pilha, 9);
  empilhar(&pilha, 8);
  exibirPilha(pilha);
  printf("%d\n", topo(pilha));
  desempilhar(pilha);
  exibirPilha(pilha);
  return 0;
}
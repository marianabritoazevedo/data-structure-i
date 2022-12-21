#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

struct linkedqueue* inicializar() {
  struct linkedqueue* fila = (struct linkedqueue*)malloc(sizeof(struct linkedqueue));
  fila->frente = NULL;
  fila->tras = NULL;
  fila->qtdade = 0;
  return fila;
}

struct no* alocarNovoNo(int valor) {
  struct no* novoNo = (struct no*)malloc(sizeof(struct no));
  novoNo->val = valor;
  novoNo->prox = NULL;
  return novoNo;
}

bool vazia(struct linkedqueue* fila) {
  if(fila == NULL){
    return true;
  }
  if(fila->qtdade == 0){
    return true;
  }else{
    return false;
  }
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue** fila, int val) {
  if((*fila)==NULL){
    (*fila) = inicializar();
  }
  if((*fila)->qtdade == 0){
    struct no* novoNo = alocarNovoNo(val);
    (*fila)->frente = novoNo;
    (*fila)->tras = novoNo;
    (*fila)->qtdade++;
  }else{
    struct no* novoNo = alocarNovoNo(val);
    struct no* atualTras = (*fila)->tras;
    atualTras->prox = novoNo;
    (*fila)->tras = novoNo;
    (*fila)->qtdade++;
  }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o nó removido (free)
int desenfileirar(struct linkedqueue* fila) {
  if(fila == NULL){
    return INT_MIN;
  }
  if(fila->qtdade == 0){
    return INT_MIN;
  }else{
    if(fila->qtdade == 1){
      struct no* aux = fila->frente;
      int valor = aux->val;
      fila->frente = NULL;
      fila->tras = NULL;
      fila->qtdade--;
      free(aux);
      return valor;
    }else{
      struct no* atualFrente = fila->frente;
      int valor = atualFrente->val;
      struct no* novaFrente = atualFrente->prox;
      fila->frente = novaFrente;
      fila->qtdade--;
      free(atualFrente);
      return valor;
    }
  }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct linkedqueue* fila) {
  if(fila == NULL){
    return INT_MIN;
  }
  if(fila->qtdade == 0){
    return INT_MIN;
  }else{
    struct no* aux = fila->frente;
    int valor = aux->val;
    return valor;
  }
}

int main(){
  struct linkedqueue* fila = inicializar();
  enfileirar(&fila, 5);
  enfileirar(&fila, 4);
  enfileirar(&fila, 3);
  
  return 0;
}
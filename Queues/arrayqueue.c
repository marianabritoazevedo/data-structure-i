#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct arrayqueue {
    int frente; //índice do elemento que está na frente da fila
    int tras;   //índice do elemento que está no fim da fila
    int* elementos;
    int tamanho;    //tam do array
    int qtdade;     //qtdade de elementos no array    
};

struct arrayqueue* inicializar(int tamArray) {
  struct arrayqueue* fila = (struct arrayqueue*)malloc(sizeof(struct arrayqueue));
  fila->elementos = (int*)calloc(tamArray, sizeof(int));
  fila->tamanho = tamArray;
  fila->qtdade = 0;
  fila->frente = -1;
  fila->tras = -1;
  return fila;
}

//se a fila estiver nula, instancie a fila com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arrayqueue**
//se a fila encher, simplesmente não enfileire
void enfileirar(struct arrayqueue** fila, int val) {
  if((*fila) == NULL){
    (*fila) = inicializar(10);
  }
  //frente e trás apontam para o mesmo valor
  if((*fila)->qtdade == 0){
    (*fila)->frente++;
    (*fila)->tras++;
    (*fila)->elementos[(*fila)->tras] = val;
    (*fila)->qtdade++;
  }else{
    //se for diferente do tamanho, ainda cabe colocar mais um para enfileirar
    if((*fila)->qtdade != (*fila)->tamanho){
      (*fila)->tras++;
      (*fila)->tras = (*fila)->tras % (*fila)->tamanho;
      (*fila)->elementos[(*fila)->tras] = val;
      (*fila)->qtdade++;
    }
  }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int desenfileirar(struct arrayqueue* fila) {
  if(fila == NULL){
    return INT_MIN;
  }
  if(fila->qtdade == 0){
    return INT_MIN;
  }else{
    int valor = fila->elementos[fila->frente];
    fila->frente++;
    fila->frente = fila->frente % fila->tamanho;
    fila->qtdade--;
    return valor;
  }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct arrayqueue* fila) {
  if(fila == NULL){
    return INT_MIN;
  }
  if(fila->qtdade == 0){
    return INT_MIN;
  }else{
    int valor = fila->elementos[fila->frente];
    return valor;
  }
}
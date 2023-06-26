//Uma árvore unival (valor universal) é uma árvore na qual todos os nós dela possuem o mesmo valor
//Codigo de contagem de subárvores unival.
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  struct no *pai;      // ponteiro para o nó pai
  struct no *esquerda; // ponteiro para o nó filho a esquerda
  struct no *direita;  // ponteiro para o nó filho a direita
  int valor;           // conteúdo de um nó arbitrário da árvore
} No;

typedef struct arvore {
  struct no *raiz;
} Arvore;

Arvore *criar() {
  Arvore *arvore;
  arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  return arvore;
}

No *adicionar(Arvore *arvore, No *pai, int valor) {
  No *no = malloc(sizeof(No));

  no->pai = pai;
  no->esquerda = NULL;
  no->direita = NULL;
  no->valor = valor;

  if (pai == NULL) {
    arvore->raiz = no;
  }

  return no;
}

int contarSubarvoresUnival(No *raiz, int *contador) {
  if (raiz == NULL)
    return 1;

  int esquerdaUnival = contarSubarvoresUnival(raiz->esquerda, contador);
  int direitaUnival = contarSubarvoresUnival(raiz->direita, contador);

  if (esquerdaUnival && direitaUnival) {
      if (raiz->esquerda != NULL && raiz->esquerda->valor != raiz->valor)
        return 0;
      if (raiz->direita != NULL && raiz->direita->valor != raiz->valor)
        return 0;
    (*contador)++;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  // Criação da Árvore
  Arvore *a = criar();
  No *noRaiz = adicionar(a, NULL, 0);
  No *no0 = adicionar(a, noRaiz, 0);
  No *no1 = adicionar(a, noRaiz, 1);
  noRaiz->esquerda = no0;
  noRaiz->direita = no1;

  No *no1A = adicionar(a, no1, 1);
  No *no1B = adicionar(a, no1, 1);
  no1->esquerda = no1A;
  no1->direita = no1B;

  No *no1C = adicionar(a, no1A, 1);
  No *no1D = adicionar(a, no1A, 1);
  no1A->esquerda = no1C;
  no1A->direita = no1D;

  int contador = 0;
  contarSubarvoresUnival(a->raiz, &contador);
  printf("%d\n", contador);
}

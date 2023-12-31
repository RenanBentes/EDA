//Básico de implantação de Árvore Binária
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

Arvore *cria() {
  Arvore *arvore;
  arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;

  return arvore;
}

int vazia(Arvore *arvore) { return (arvore->raiz == NULL); }

No *adicionarNo(Arvore *arvore, int valor) {
  No *no = malloc(sizeof(No));
  no->pai = NULL;
  no->esquerda = NULL;
  no->direita = NULL;
  no->valor = valor;

  if (arvore->raiz == NULL) {
    arvore->raiz = no;
    return no;
  }

  No *atual = arvore->raiz;

  while (1) {
    if (valor <= atual->valor) {
      if (atual->esquerda == NULL) {
        atual->esquerda = no;
        no->pai = atual;
        break;
      } else {
        atual = atual->esquerda;
      }
    } else {
      if (atual->direita == NULL) {
        atual->direita = no;
        no->pai = atual;
        break;
      } else {
        atual = atual->direita;
      }
    }
  }

  return no;
}

void remover(Arvore *arvore, No *no) {
  if (no->esquerda != NULL)
    remover(arvore, no->esquerda);

  if (no->direita != NULL)
    remover(arvore, no->direita);

  if (no->pai == NULL) {
    arvore->raiz = NULL;
  } else {
    if (no->pai->esquerda == no)
      no->pai->esquerda = NULL;
    else
      no->pai->direita = NULL;
  }
  free(no);
}

void percorrerPreOrdem(No *no) {
  if (no != NULL) {
    printf("%d ", no->valor);
    percorrerPreOrdem(no->esquerda);
    percorrerPreOrdem(no->direita);
  }
}

void percorrerInOrdem(No *no) {
  if (no != NULL) {
    percorrerInOrdem(no->esquerda);
    printf("%d ", no->valor);
    percorrerInOrdem(no->direita);
  }
}

void percorrerPosOrdem(No *no) {
  if (no != NULL) {
    percorrerPosOrdem(no->esquerda);
    percorrerPosOrdem(no->direita);
    printf("%d ", no->valor);
  }
}

void exibe(void *v) {
  int *i = (int *)v;
  printf("%d\n", *i);
}

void percorrerLargura(No *no) {
  if (no == NULL) {
    return;
  }

  No *ordem[100];
  int proximo = 0;
  int lido = 0;
  ordem[lido++] = no;

  while (proximo < lido) {
    No *Atual = ordem[proximo++];
    printf("%d ", Atual->valor);

    if (Atual->esquerda)
      ordem[lido++] = Atual->esquerda;
    if (Atual->direita)
      ordem[lido++] = Atual->direita;
  }
}

int pesquisarChave(No *no, int chave, int contador) {
  if (no == NULL)
    return contador;

  if (no->valor == chave)
    return contador + 1;
  else if (no->valor > chave)
    return pesquisarChave(no->esquerda, chave, contador + 1);
  else
    return pesquisarChave(no->direita, chave, contador + 1);
}

int main(int argc, char *argv[]) {
  // Criação da Árvore
  Arvore *a = cria();
  adicionarNo(a, 4);
  adicionarNo(a, 2);
  adicionarNo(a, 1);
  adicionarNo(a, 3);
  adicionarNo(a, 8);
  adicionarNo(a, 9);
  adicionarNo(a, 6);
  adicionarNo(a, 5);
  adicionarNo(a, 7);

  // Pesquisa binária para localizar um nó dada uma chave de acesso.
  int chave = 5, contador = 0;
  contador = pesquisarChave(a->raiz, chave, contador);
  printf("Pesquisar chave 5\n %d\n", contador);

  // Printf de algumas funções
  printf("PreOrdem\n");
  percorrerPreOrdem(a->raiz);
  printf("\nInOrdem\n");
  percorrerInOrdem(a->raiz);
  printf("\nPosOrdem\n");
  percorrerPosOrdem(a->raiz);
  printf("\nLargura\n");
  percorrerLargura(a->raiz);
  printf("\n");
}

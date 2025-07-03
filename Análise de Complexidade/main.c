#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Contadores globais para medir esforço
long long contador_avl = 0;
long long contador_rb = 0;
long long contador_b = 0;

// ===================== ÁRVORE AVL =====================
typedef struct no_avl {
  struct no_avl *pai;
  struct no_avl *esquerda;
  struct no_avl *direita;
  int valor;
  int altura;
} NoAVL;

typedef struct arvore_avl {
  struct no_avl *raiz;
} ArvoreAVL;

void balanceamento_avl(ArvoreAVL *, NoAVL *);
int altura_avl(NoAVL *);
int fb_avl(NoAVL *);
NoAVL *rsd_avl(ArvoreAVL *, NoAVL *);
NoAVL *rse_avl(ArvoreAVL *, NoAVL *);
NoAVL *rdd_avl(ArvoreAVL *, NoAVL *);
NoAVL *rde_avl(ArvoreAVL *, NoAVL *);
NoAVL *remover_avl(ArvoreAVL *, int);

int max(int a, int b) { return a > b ? a : b; }

ArvoreAVL *criar_avl() {
  ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
  arvore->raiz = NULL;
  return arvore;
}

int vazia_avl(ArvoreAVL *arvore) { return arvore->raiz == NULL; }

void adicionar_avl(ArvoreAVL *arvore, int valor) {
  contador_avl++;
  NoAVL *no = arvore->raiz;

  while (no != NULL) {
    contador_avl++;
    if (valor > no->valor) {
      if (no->direita != NULL) {
        no = no->direita;
      } else {
        break;
      }
    } else {
      if (no->esquerda != NULL) {
        no = no->esquerda;
      } else {
        break;
      }
    }
  }

  NoAVL *novo = malloc(sizeof(NoAVL));
  novo->valor = valor;
  novo->pai = no;
  novo->esquerda = NULL;
  novo->direita = NULL;
  novo->altura = 1;

  if (no == NULL) {
    arvore->raiz = novo;
  } else {
    if (valor > no->valor) {
      no->direita = novo;
    } else {
      no->esquerda = novo;
    }
    balanceamento_avl(arvore, no);
  }
}

NoAVL *localizar_avl(NoAVL *no, int valor) {
  while (no != NULL) {
    contador_avl++;
    if (no->valor == valor) {
      return no;
    }
    no = valor < no->valor ? no->esquerda : no->direita;
  }
  return NULL;
}

void balanceamento_avl(ArvoreAVL *arvore, NoAVL *no) {
  while (no != NULL) {
    contador_avl++;
    no->altura = max(altura_avl(no->esquerda), altura_avl(no->direita)) + 1;
    int fator = fb_avl(no);

    if (fator > 1) {
      if (fb_avl(no->esquerda) > 0) {
        rsd_avl(arvore, no);
      } else {
        rdd_avl(arvore, no);
      }
    } else if (fator < -1) {
      if (fb_avl(no->direita) < 0) {
        rse_avl(arvore, no);
      } else {
        rde_avl(arvore, no);
      }
    }
    no = no->pai;
  }
}

int altura_avl(NoAVL *no) {
  contador_avl++;
  return no != NULL ? no->altura : 0;
}

int fb_avl(NoAVL *no) {
  contador_avl++;
  int esquerda = 0, direita = 0;
  if (no->esquerda != NULL) {
    esquerda = no->esquerda->altura;
  }
  if (no->direita != NULL) {
    direita = no->direita->altura;
  }
  return esquerda - direita;
}

NoAVL *rse_avl(ArvoreAVL *arvore, NoAVL *no) {
  contador_avl++;
  NoAVL *pai = no->pai;
  NoAVL *direita = no->direita;

  if (direita->esquerda != NULL) {
    direita->esquerda->pai = no;
  }

  no->direita = direita->esquerda;
  no->pai = direita;

  direita->esquerda = no;
  direita->pai = pai;

  if (pai == NULL) {
    arvore->raiz = direita;
  } else {
    if (pai->esquerda == no) {
      pai->esquerda = direita;
    } else {
      pai->direita = direita;
    }
  }

  no->altura = max(altura_avl(no->esquerda), altura_avl(no->direita)) + 1;
  direita->altura =
      max(altura_avl(direita->esquerda), altura_avl(direita->direita)) + 1;

  return direita;
}

NoAVL *rsd_avl(ArvoreAVL *arvore, NoAVL *no) {
  contador_avl++;
  NoAVL *pai = no->pai;
  NoAVL *esquerda = no->esquerda;

  if (esquerda->direita != NULL) {
    esquerda->direita->pai = no;
  }

  no->esquerda = esquerda->direita;
  no->pai = esquerda;

  esquerda->direita = no;
  esquerda->pai = pai;

  if (pai == NULL) {
    arvore->raiz = esquerda;
  } else {
    if (pai->esquerda == no) {
      pai->esquerda = esquerda;
    } else {
      pai->direita = esquerda;
    }
  }

  no->altura = max(altura_avl(no->esquerda), altura_avl(no->direita)) + 1;
  esquerda->altura =
      max(altura_avl(esquerda->esquerda), altura_avl(esquerda->direita)) + 1;

  return esquerda;
}

NoAVL *rde_avl(ArvoreAVL *arvore, NoAVL *no) {
  contador_avl++;
  no->direita = rsd_avl(arvore, no->direita);
  return rse_avl(arvore, no);
}

NoAVL *rdd_avl(ArvoreAVL *arvore, NoAVL *no) {
  contador_avl++;
  no->esquerda = rse_avl(arvore, no->esquerda);
  return rsd_avl(arvore, no);
}

NoAVL *minimo_avl(NoAVL *no) {
  while (no->esquerda != NULL) {
    contador_avl++;
    no = no->esquerda;
  }
  return no;
}

NoAVL *remover_avl(ArvoreAVL *arvore, int valor) {
  contador_avl++;
  NoAVL *no = localizar_avl(arvore->raiz, valor);
  if (no == NULL)
    return NULL;

  NoAVL *pai = no->pai;

  // Caso 1: Nó folha
  if (no->esquerda == NULL && no->direita == NULL) {
    if (pai == NULL) {
      arvore->raiz = NULL;
    } else if (pai->esquerda == no) {
      pai->esquerda = NULL;
    } else {
      pai->direita = NULL;
    }
    free(no);
  }
  // Caso 2: Nó com apenas um filho
  else if (no->esquerda == NULL || no->direita == NULL) {
    NoAVL *filho = (no->esquerda != NULL) ? no->esquerda : no->direita;

    if (pai == NULL) {
      arvore->raiz = filho;
    } else if (pai->esquerda == no) {
      pai->esquerda = filho;
    } else {
      pai->direita = filho;
    }

    if (filho != NULL) {
      filho->pai = pai;
    }
    free(no);
  }
  // Caso 3: Nó com dois filhos
  else {
    NoAVL *sucessor = minimo_avl(no->direita);
    no->valor = sucessor->valor;

    // Remove o sucessor (que tem no máximo um filho à direita)
    if (sucessor->pai->esquerda == sucessor) {
      sucessor->pai->esquerda = sucessor->direita;
    } else {
      sucessor->pai->direita = sucessor->direita;
    }

    if (sucessor->direita != NULL) {
      sucessor->direita->pai = sucessor->pai;
    }

    pai = sucessor->pai;
    free(sucessor);
  }

  if (pai != NULL) {
    balanceamento_avl(arvore, pai);
  }

  return no;
}

// ===================== ÁRVORE RUBRO-NEGRA =====================
enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no_rb {
  struct no_rb *pai;
  struct no_rb *esquerda;
  struct no_rb *direita;
  Cor cor;
  int valor;
} NoRB;

typedef struct arvore_rb {
  struct no_rb *raiz;
  struct no_rb *nulo;
} ArvoreRB;

NoRB *criarNo_rb(ArvoreRB *, NoRB *, int);
void balancear_rb(ArvoreRB *, NoRB *);
void rotacionarEsquerda_rb(ArvoreRB *, NoRB *);
void rotacionarDireita_rb(ArvoreRB *, NoRB *);
NoRB *remover_rb(ArvoreRB *, int);

ArvoreRB *criar_rb() {
  ArvoreRB *arvore = malloc(sizeof(ArvoreRB));
  arvore->nulo = NULL;
  arvore->raiz = NULL;

  arvore->nulo = criarNo_rb(arvore, NULL, 0);
  arvore->nulo->cor = Preto;

  return arvore;
}

int vazia_rb(ArvoreRB *arvore) { return arvore->raiz == NULL; }

NoRB *criarNo_rb(ArvoreRB *arvore, NoRB *pai, int valor) {
  contador_rb++;
  NoRB *no = malloc(sizeof(NoRB));

  no->pai = pai;
  no->valor = valor;
  no->direita = arvore->nulo;
  no->esquerda = arvore->nulo;

  return no;
}

NoRB *adicionarNo_rb(ArvoreRB *arvore, NoRB *no, int valor) {
  contador_rb++;
  if (valor > no->valor) {
    if (no->direita == arvore->nulo) {
      no->direita = criarNo_rb(arvore, no, valor);
      no->direita->cor = Vermelho;
      return no->direita;
    } else {
      return adicionarNo_rb(arvore, no->direita, valor);
    }
  } else {
    if (no->esquerda == arvore->nulo) {
      no->esquerda = criarNo_rb(arvore, no, valor);
      no->esquerda->cor = Vermelho;
      return no->esquerda;
    } else {
      return adicionarNo_rb(arvore, no->esquerda, valor);
    }
  }
}

NoRB *adicionar_rb(ArvoreRB *arvore, int valor) {
  contador_rb++;
  if (vazia_rb(arvore)) {
    arvore->raiz = criarNo_rb(arvore, arvore->nulo, valor);
    arvore->raiz->cor = Preto;
    return arvore->raiz;
  } else {
    NoRB *no = adicionarNo_rb(arvore, arvore->raiz, valor);
    balancear_rb(arvore, no);
    return no;
  }
}

NoRB *localizar_rb(ArvoreRB *arvore, int valor) {
  if (!vazia_rb(arvore)) {
    NoRB *no = arvore->raiz;

    while (no != arvore->nulo) {
      contador_rb++;
      if (no->valor == valor) {
        return no;
      } else {
        no = valor < no->valor ? no->esquerda : no->direita;
      }
    }
  }
  return NULL;
}

void balancear_rb(ArvoreRB *arvore, NoRB *no) {
  while (no->pai->cor == Vermelho) {
    contador_rb++;
    if (no->pai == no->pai->pai->esquerda) {
      NoRB *tio = no->pai->pai->direita;

      if (tio->cor == Vermelho) {
        tio->cor = Preto;
        no->pai->cor = Preto;
        no->pai->pai->cor = Vermelho;
        no = no->pai->pai;
      } else {
        if (no == no->pai->direita) {
          no = no->pai;
          rotacionarEsquerda_rb(arvore, no);
        } else {
          no->pai->cor = Preto;
          no->pai->pai->cor = Vermelho;
          rotacionarDireita_rb(arvore, no->pai->pai);
        }
      }
    } else {
      NoRB *tio = no->pai->pai->esquerda;

      if (tio->cor == Vermelho) {
        tio->cor = Preto;
        no->pai->cor = Preto;
        no->pai->pai->cor = Vermelho;
        no = no->pai->pai;
      } else {
        if (no == no->pai->esquerda) {
          no = no->pai;
          rotacionarDireita_rb(arvore, no);
        } else {
          no->pai->cor = Preto;
          no->pai->pai->cor = Vermelho;
          rotacionarEsquerda_rb(arvore, no->pai->pai);
        }
      }
    }
  }
  arvore->raiz->cor = Preto;
}

void rotacionarEsquerda_rb(ArvoreRB *arvore, NoRB *no) {
  contador_rb++;
  NoRB *direita = no->direita;
  no->direita = direita->esquerda;

  if (direita->esquerda != arvore->nulo) {
    direita->esquerda->pai = no;
  }

  direita->pai = no->pai;

  if (no->pai == arvore->nulo) {
    arvore->raiz = direita;
  } else if (no == no->pai->esquerda) {
    no->pai->esquerda = direita;
  } else {
    no->pai->direita = direita;
  }

  direita->esquerda = no;
  no->pai = direita;
}

void rotacionarDireita_rb(ArvoreRB *arvore, NoRB *no) {
  contador_rb++;
  NoRB *esquerda = no->esquerda;
  no->esquerda = esquerda->direita;

  if (esquerda->direita != arvore->nulo) {
    esquerda->direita->pai = no;
  }

  esquerda->pai = no->pai;

  if (no->pai == arvore->nulo) {
    arvore->raiz = esquerda;
  } else if (no == no->pai->esquerda) {
    no->pai->esquerda = esquerda;
  } else {
    no->pai->direita = esquerda;
  }

  esquerda->direita = no;
  no->pai = esquerda;
}

NoRB *minimo_rb(ArvoreRB *arvore, NoRB *no) {
  while (no->esquerda != arvore->nulo) {
    contador_rb++;
    no = no->esquerda;
  }
  return no;
}

void fixRemocao_rb(ArvoreRB *arvore, NoRB *no) {
  while (no != arvore->raiz && no->cor == Preto) {
    contador_rb++;
    if (no == no->pai->esquerda) {
      NoRB *irmao = no->pai->direita;

      if (irmao->cor == Vermelho) {
        irmao->cor = Preto;
        no->pai->cor = Vermelho;
        rotacionarEsquerda_rb(arvore, no->pai);
        irmao = no->pai->direita;
      }

      if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
        irmao->cor = Vermelho;
        no = no->pai;
      } else {
        if (irmao->direita->cor == Preto) {
          irmao->esquerda->cor = Preto;
          irmao->cor = Vermelho;
          rotacionarDireita_rb(arvore, irmao);
          irmao = no->pai->direita;
        }

        irmao->cor = no->pai->cor;
        no->pai->cor = Preto;
        irmao->direita->cor = Preto;
        rotacionarEsquerda_rb(arvore, no->pai);
        no = arvore->raiz;
      }
    } else {
      NoRB *irmao = no->pai->esquerda;

      if (irmao->cor == Vermelho) {
        irmao->cor = Preto;
        no->pai->cor = Vermelho;
        rotacionarDireita_rb(arvore, no->pai);
        irmao = no->pai->esquerda;
      }

      if (irmao->direita->cor == Preto && irmao->esquerda->cor == Preto) {
        irmao->cor = Vermelho;
        no = no->pai;
      } else {
        if (irmao->esquerda->cor == Preto) {
          irmao->direita->cor = Preto;
          irmao->cor = Vermelho;
          rotacionarEsquerda_rb(arvore, irmao);
          irmao = no->pai->esquerda;
        }

        irmao->cor = no->pai->cor;
        no->pai->cor = Preto;
        irmao->esquerda->cor = Preto;
        rotacionarDireita_rb(arvore, no->pai);
        no = arvore->raiz;
      }
    }
  }
  no->cor = Preto;
}

NoRB *remover_rb(ArvoreRB *arvore, int valor) {
  contador_rb++;
  NoRB *no = localizar_rb(arvore, valor);
  if (no == NULL)
    return NULL;

  NoRB *y = no;
  NoRB *x;
  Cor cor_original = y->cor;

  if (no->esquerda == arvore->nulo) {
    x = no->direita;
    if (no->pai == arvore->nulo) {
      arvore->raiz = x;
    } else if (no == no->pai->esquerda) {
      no->pai->esquerda = x;
    } else {
      no->pai->direita = x;
    }
    x->pai = no->pai;
  } else if (no->direita == arvore->nulo) {
    x = no->esquerda;
    if (no->pai == arvore->nulo) {
      arvore->raiz = x;
    } else if (no == no->pai->esquerda) {
      no->pai->esquerda = x;
    } else {
      no->pai->direita = x;
    }
    x->pai = no->pai;
  } else {
    y = minimo_rb(arvore, no->direita);
    cor_original = y->cor;
    x = y->direita;

    if (y->pai == no) {
      x->pai = y;
    } else {
      if (y->pai->esquerda == y) {
        y->pai->esquerda = x;
      } else {
        y->pai->direita = x;
      }
      x->pai = y->pai;
      y->direita = no->direita;
      y->direita->pai = y;
    }

    if (no->pai == arvore->nulo) {
      arvore->raiz = y;
    } else if (no == no->pai->esquerda) {
      no->pai->esquerda = y;
    } else {
      no->pai->direita = y;
    }

    y->pai = no->pai;
    y->esquerda = no->esquerda;
    y->esquerda->pai = y;
    y->cor = no->cor;
  }

  if (cor_original == Preto) {
    fixRemocao_rb(arvore, x);
  }

  free(no);
  return no;
}

// ===================== ÁRVORE B =====================
typedef struct no_b {
  int total;
  int *chaves;
  struct no_b **filhos;
  struct no_b *pai;
} NoB;

typedef struct arvore_b {
  NoB *raiz;
  int ordem;
} ArvoreB;

ArvoreB *criaArvore_b(int);
NoB *criaNo_b(ArvoreB *);
int pesquisaBinaria_b(NoB *, int);
int localizaChave_b(ArvoreB *, int);
NoB *localizaNo_b(ArvoreB *, int);
void adicionaChaveNo_b(NoB *, NoB *, int);
int transbordo_b(ArvoreB *, NoB *);
NoB *divideNo_b(ArvoreB *, NoB *);
void adicionaChaveRecursivo_b(ArvoreB *, NoB *, NoB *, int);
void adicionaChave_b(ArvoreB *, int);
void removerChave_b(ArvoreB *, int);
void removerChaveRecursivo_b(ArvoreB *, NoB *, int);

ArvoreB *criaArvore_b(int ordem) {
  contador_b++;
  ArvoreB *a = malloc(sizeof(ArvoreB));
  a->ordem = ordem;
  a->raiz = criaNo_b(a);
  return a;
}

NoB *criaNo_b(ArvoreB *arvore) {
  contador_b++;
  int max = arvore->ordem * 2;
  NoB *no = malloc(sizeof(NoB));

  no->pai = NULL;
  no->chaves = malloc(sizeof(int) * (max + 1));
  no->filhos = malloc(sizeof(NoB *) * (max + 2));
  no->total = 0;

  for (int i = 0; i < max + 2; i++)
    no->filhos[i] = NULL;

  return no;
}

int pesquisaBinaria_b(NoB *no, int chave) {
  contador_b++;
  int inicio = 0, fim = no->total - 1, meio;

  while (inicio <= fim) {
    contador_b++;
    meio = (inicio + fim) / 2;

    if (no->chaves[meio] == chave) {
      return meio;
    } else if (no->chaves[meio] > chave) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
  }
  return inicio;
}

int localizaChave_b(ArvoreB *arvore, int chave) {
  contador_b++;
  NoB *no = arvore->raiz;

  while (no != NULL) {
    contador_b++;
    int i = pesquisaBinaria_b(no, chave);

    if (i < no->total && no->chaves[i] == chave) {
      return 1;
    } else {
      no = no->filhos[i];
    }
  }
  return 0;
}

NoB *localizaNo_b(ArvoreB *arvore, int chave) {
  contador_b++;
  NoB *no = arvore->raiz;

  while (no != NULL) {
    contador_b++;
    int i = pesquisaBinaria_b(no, chave);

    if (no->filhos[i] == NULL)
      return no;
    else
      no = no->filhos[i];
  }
  return NULL;
}

void adicionaChaveNo_b(NoB *no, NoB *novo, int chave) {
  contador_b++;
  int i = pesquisaBinaria_b(no, chave);

  for (int j = no->total - 1; j >= i; j--) {
    no->chaves[j + 1] = no->chaves[j];
    no->filhos[j + 2] = no->filhos[j + 1];
  }

  no->chaves[i] = chave;
  no->filhos[i + 1] = novo;
  no->total++;
}

int transbordo_b(ArvoreB *arvore, NoB *no) {
  contador_b++;
  return no->total > arvore->ordem * 2;
}

NoB *divideNo_b(ArvoreB *arvore, NoB *no) {
  contador_b++;
  int meio = no->total / 2;
  NoB *novo = criaNo_b(arvore);
  novo->pai = no->pai;

  for (int i = meio + 1; i < no->total; i++) {
    novo->filhos[novo->total] = no->filhos[i];
    novo->chaves[novo->total] = no->chaves[i];
    if (novo->filhos[novo->total] != NULL)
      novo->filhos[novo->total]->pai = novo;
    novo->total++;
  }

  novo->filhos[novo->total] = no->filhos[no->total];
  if (novo->filhos[novo->total] != NULL)
    novo->filhos[novo->total]->pai = novo;
  no->total = meio;
  return novo;
}

void adicionaChaveRecursivo_b(ArvoreB *arvore, NoB *no, NoB *novo, int chave) {
  contador_b++;
  adicionaChaveNo_b(no, novo, chave);

  if (transbordo_b(arvore, no)) {
    int promovido = no->chaves[arvore->ordem];
    NoB *novo_no = divideNo_b(arvore, no);

    if (no->pai == NULL) {
      contador_b++;
      NoB *pai = criaNo_b(arvore);
      pai->filhos[0] = no;
      adicionaChaveNo_b(pai, novo_no, promovido);

      no->pai = pai;
      novo_no->pai = pai;
      arvore->raiz = pai;
    } else {
      adicionaChaveRecursivo_b(arvore, no->pai, novo_no, promovido);
    }
  }
}

void adicionaChave_b(ArvoreB *arvore, int chave) {
  contador_b++;
  NoB *no = localizaNo_b(arvore, chave);
  adicionaChaveRecursivo_b(arvore, no, NULL, chave);
}

// ================= INÍCIO DA LÓGICA DE REMOÇÃO DA ÁRVORE B =================

// Função auxiliar para verificar se um nó é uma folha
int ehFolha_b(NoB *no) { return no->filhos[0] == NULL; }

// Função auxiliar para remover uma chave de um nó específico
void removerChaveDoNo_b(NoB *no, int pos) {
  contador_b++;
  for (int i = pos + 1; i < no->total; ++i) {
    no->chaves[i - 1] = no->chaves[i];
  }
  no->total--;
}

// Função auxiliar para remover um ponteiro de filho de um nó
void removerFilhoDoNo_b(NoB *no, int pos) {
  contador_b++;
  for (int i = pos + 1; i <= no->total + 1; ++i) {
    no->filhos[i - 1] = no->filhos[i];
  }
}

// Função para obter o predecessor de uma chave em um nó
int getPred_b(NoB *no, int idx) {
  contador_b++;
  NoB *cur = no->filhos[idx];
  while (!ehFolha_b(cur)) {
    cur = cur->filhos[cur->total];
  }
  return cur->chaves[cur->total - 1];
}

// Função para obter o sucessor de uma chave em um nó
int getSucc_b(NoB *no, int idx) {
  contador_b++;
  NoB *cur = no->filhos[idx + 1];
  while (!ehFolha_b(cur)) {
    cur = cur->filhos[0];
  }
  return cur->chaves[0];
}

// Função para emprestar uma chave do irmão anterior
void emprestaDoAnt_b(NoB *no, int idx) {
  contador_b++;
  NoB *filho = no->filhos[idx];
  NoB *irmao = no->filhos[idx - 1];

  for (int i = filho->total - 1; i >= 0; --i)
    filho->chaves[i + 1] = filho->chaves[i];

  if (!ehFolha_b(filho)) {
    for (int i = filho->total; i >= 0; --i)
      filho->filhos[i + 1] = filho->filhos[i];
  }

  filho->chaves[0] = no->chaves[idx - 1];

  if (!ehFolha_b(filho)) {
    filho->filhos[0] = irmao->filhos[irmao->total];
    if (filho->filhos[0])
      filho->filhos[0]->pai = filho;
  }

  no->chaves[idx - 1] = irmao->chaves[irmao->total - 1];

  filho->total++;
  irmao->total--;
}

// Função para emprestar uma chave do próximo irmão
void emprestaDoProx_b(NoB *no, int idx) {
  contador_b++;
  NoB *filho = no->filhos[idx];
  NoB *irmao = no->filhos[idx + 1];

  filho->chaves[filho->total] = no->chaves[idx];

  if (!ehFolha_b(filho)) {
    filho->filhos[filho->total + 1] = irmao->filhos[0];
    if (filho->filhos[filho->total + 1])
      filho->filhos[filho->total + 1]->pai = filho;
  }

  no->chaves[idx] = irmao->chaves[0];

  for (int i = 1; i < irmao->total; ++i)
    irmao->chaves[i - 1] = irmao->chaves[i];

  if (!ehFolha_b(irmao)) {
    for (int i = 1; i <= irmao->total; ++i)
      irmao->filhos[i - 1] = irmao->filhos[i];
  }

  filho->total++;
  irmao->total--;
}

void merge_b(NoB *no, int idx) {
  contador_b++;
  NoB *filho = no->filhos[idx];
  NoB *irmao = no->filhos[idx + 1];

  filho->chaves[filho->total] = no->chaves[idx];

  for (int i = 0; i < irmao->total; ++i)
    filho->chaves[filho->total + 1 + i] = irmao->chaves[i];

  if (!ehFolha_b(filho)) {
    for (int i = 0; i <= irmao->total; ++i) {
      filho->filhos[filho->total + 1 + i] = irmao->filhos[i];
      if (filho->filhos[filho->total + 1 + i])
        filho->filhos[filho->total + 1 + i]->pai = filho;
    }
  }

  removerChaveDoNo_b(no, idx);
  removerFilhoDoNo_b(no, idx + 1);

  filho->total += irmao->total + 1;

  free(irmao->chaves);
  free(irmao->filhos);
  free(irmao);
}

void removerChaveRecursivo_b(ArvoreB *arvore, NoB *no, int chave) {
  contador_b++;
  int idx = pesquisaBinaria_b(no, chave);

  // Caso 1: A chave está presente neste nó
  if (idx < no->total && no->chaves[idx] == chave) {
    if (ehFolha_b(no)) { // Se o nó for folha
      removerChaveDoNo_b(no, idx);
    } else { // Se o nó não for folha
      NoB *filho_esq = no->filhos[idx];
      NoB *filho_dir = no->filhos[idx + 1];

      if (filho_esq->total >= arvore->ordem) {
        int pred = getPred_b(no, idx);
        no->chaves[idx] = pred;
        removerChaveRecursivo_b(arvore, filho_esq, pred);
      } else if (filho_dir->total >= arvore->ordem) {
        int succ = getSucc_b(no, idx);
        no->chaves[idx] = succ;
        removerChaveRecursivo_b(arvore, filho_dir, succ);
      } else {
        merge_b(no, idx);
        removerChaveRecursivo_b(arvore, filho_esq, chave);
      }
    }
  } else { // Caso 2: A chave não está neste nó
    if (ehFolha_b(no)) {
      // A chave não está na árvore
      return;
    }

    // Verifica se o filho onde a chave deveria estar precisa de ajuste
    int ultimo = (idx == no->total);
    NoB *filho = no->filhos[idx];
    if (filho->total < arvore->ordem) {
      NoB *irmao_esq = (idx > 0) ? no->filhos[idx - 1] : NULL;
      NoB *irmao_dir = (idx < no->total) ? no->filhos[idx + 1] : NULL;

      if (irmao_esq && irmao_esq->total >= arvore->ordem) {
        emprestaDoAnt_b(no, idx);
      } else if (irmao_dir && irmao_dir->total >= arvore->ordem) {
        emprestaDoProx_b(no, idx);
      } else {
        if (irmao_dir) {
          merge_b(no, idx);
        } else {
          merge_b(no, idx - 1);
          filho =
              irmao_esq; // O nó a ser investigado agora é o irmão da esquerda
        }
      }
    }

    removerChaveRecursivo_b(arvore, filho, chave);
  }
}

// Função pública para iniciar a remoção
void removerChave_b(ArvoreB *arvore, int chave) {
  if (!arvore->raiz) {
    return;
  }

  removerChaveRecursivo_b(arvore, arvore->raiz, chave);

  // Se a raiz ficar vazia, seu primeiro filho se torna a nova raiz
  if (arvore->raiz->total == 0) {
    NoB *tmp = arvore->raiz;
    if (ehFolha_b(tmp)) {
      // A árvore está vazia, mas mantemos a raiz para futuras inserções
    } else {
      arvore->raiz = tmp->filhos[0];
      arvore->raiz->pai = NULL;
      free(tmp->chaves);
      free(tmp->filhos);
      free(tmp);
    }
  }
}

// ===================== FUNÇÕES DE TESTE =====================
void gerar_dados_aleatorios(int *dados, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    dados[i] = rand() % 100000;
  }
}

void teste_adicao(FILE *arquivo_csv) {
  fprintf(arquivo_csv,
          "Tamanho,AVL_Media,RB_Media,B1_Media,B5_Media,B10_Media\n");

  for (int tamanho = 100; tamanho <= 10000; tamanho += 100) {
    long long soma_avl = 0, soma_rb = 0, soma_b1 = 0, soma_b5 = 0, soma_b10 = 0;

    // Executar 10 testes para cada tamanho
    for (int teste = 0; teste < 10; teste++) {
      int *dados = malloc(tamanho * sizeof(int));
      gerar_dados_aleatorios(dados, tamanho);

      // Teste AVL
      contador_avl = 0;
      ArvoreAVL *avl = criar_avl();
      for (int i = 0; i < tamanho; i++) {
        adicionar_avl(avl, dados[i]);
      }
      soma_avl += contador_avl;

      // Teste Rubro-Negra
      contador_rb = 0;
      ArvoreRB *rb = criar_rb();
      for (int i = 0; i < tamanho; i++) {
        adicionar_rb(rb, dados[i]);
      }
      soma_rb += contador_rb;

      // Teste Árvore B ordem 1
      contador_b = 0;
      ArvoreB *b1 = criaArvore_b(1);
      for (int i = 0; i < tamanho; i++) {
        adicionaChave_b(b1, dados[i]);
      }
      soma_b1 += contador_b;

      // Teste Árvore B ordem 5
      contador_b = 0;
      ArvoreB *b5 = criaArvore_b(5);
      for (int i = 0; i < tamanho; i++) {
        adicionaChave_b(b5, dados[i]);
      }
      soma_b5 += contador_b;

      // Teste Árvore B ordem 10
      contador_b = 0;
      ArvoreB *b10 = criaArvore_b(10);
      for (int i = 0; i < tamanho; i++) {
        adicionaChave_b(b10, dados[i]);
      }
      soma_b10 += contador_b;

      // Liberar memória
      free(dados);
      free(avl);
      free(rb);
      free(b1);
      free(b5);
      free(b10);
    }

    // Calcular médias
    double media_avl = (double)soma_avl / 10.0;
    double media_rb = (double)soma_rb / 10.0;
    double media_b1 = (double)soma_b1 / 10.0;
    double media_b5 = (double)soma_b5 / 10.0;
    double media_b10 = (double)soma_b10 / 10.0;

    fprintf(arquivo_csv, "%d,%.2f,%.2f,%.2f,%.2f,%.2f\n", tamanho, media_avl,
            media_rb, media_b1, media_b5, media_b10);

    printf("Tamanho %d concluído\n", tamanho);
  }
}

void teste_remocao(FILE *arquivo_csv) {
  fprintf(arquivo_csv,
          "Tamanho,AVL_Media,RB_Media,B1_Media,B5_Media,B10_Media\n");

  for (int tamanho = 100; tamanho <= 10000; tamanho += 100) {
    long long soma_avl = 0, soma_rb = 0, soma_b1 = 0, soma_b5 = 0, soma_b10 = 0;

    // Executar 10 testes para cada tamanho
    for (int teste = 0; teste < 10; teste++) {
      int *dados = malloc(tamanho * sizeof(int));
      int *dados_remover = malloc((tamanho / 2) * sizeof(int));
      gerar_dados_aleatorios(dados, tamanho);

      // Selecionar dados para remoção (metade dos dados)
      for (int i = 0; i < tamanho / 2; i++) {
        dados_remover[i] = dados[i];
      }

      // Teste AVL
      ArvoreAVL *avl = criar_avl();
      for (int i = 0; i < tamanho; i++) {
        adicionar_avl(avl, dados[i]);
      }
      contador_avl = 0; // Reset contador para medir apenas remoção
      for (int i = 0; i < tamanho / 2; i++) {
        remover_avl(avl, dados_remover[i]);
      }
      soma_avl += contador_avl;

      // Teste Rubro-Negra
      ArvoreRB *rb = criar_rb();
      for (int i = 0; i < tamanho; i++) {
        adicionar_rb(rb, dados[i]);
      }
      contador_rb = 0; // Reset contador para medir apenas remoção
      for (int i = 0; i < tamanho / 2; i++) {
        remover_rb(rb, dados_remover[i]);
      }
      soma_rb += contador_rb;

      // Teste Árvore B ordem 1
      ArvoreB *b1 = criaArvore_b(1);
      for (int i = 0; i < tamanho; i++) {
        adicionaChave_b(b1, dados[i]);
      }
      contador_b = 0; // Reset contador para medir apenas remoção
      for (int i = 0; i < tamanho / 2; i++) {
        removerChave_b(b1, dados_remover[i]);
      }
      soma_b1 += contador_b;

      // Teste Árvore B ordem 5
      ArvoreB *b5 = criaArvore_b(5);
      for (int i = 0; i < tamanho; i++) {
        adicionaChave_b(b5, dados[i]);
      }
      contador_b = 0; // Reset contador para medir apenas remoção
      for (int i = 0; i < tamanho / 2; i++) {
        removerChave_b(b5, dados_remover[i]);
      }
      soma_b5 += contador_b;

      // Teste Árvore B ordem 10
      ArvoreB *b10 = criaArvore_b(10);
      for (int i = 0; i < tamanho; i++) {
        adicionaChave_b(b10, dados[i]);
      }
      contador_b = 0; // Reset contador para medir apenas remoção
      for (int i = 0; i < tamanho / 2; i++) {
        removerChave_b(b10, dados_remover[i]);
      }
      soma_b10 += contador_b;

      // Liberar memória
      free(dados);
      free(dados_remover);
      free(avl);
      free(rb);
      free(b1);
      free(b5);
      free(b10);
    }

    // Calcular médias
    double media_avl = (double)soma_avl / 10.0;
    double media_rb = (double)soma_rb / 10.0;
    double media_b1 = (double)soma_b1 / 10.0;
    double media_b5 = (double)soma_b5 / 10.0;
    double media_b10 = (double)soma_b10 / 10.0;

    fprintf(arquivo_csv, "%d,%.2f,%.2f,%.2f,%.2f,%.2f\n", tamanho, media_avl,
            media_rb, media_b1, media_b5, media_b10);

    printf("Tamanho %d concluído (remoção)\n", tamanho);
  }
}

int main() {
  srand(time(NULL));

  printf("Iniciando análise de complexidade das estruturas de dados...\n");
  printf("Este processo pode demorar alguns minutos.\n\n");

  // Teste de adição
  FILE *arquivo_adicao = fopen("resultados_adicao.csv", "w");
  if (arquivo_adicao == NULL) {
    printf("Erro ao criar arquivo de resultados para adição!\n");
    return 1;
  }

  printf("Executando testes de adição...\n");
  teste_adicao(arquivo_adicao);
  fclose(arquivo_adicao);
  printf("Resultados de adição salvos em 'resultados_adicao.csv'\n\n");

  // Teste de remoção
  FILE *arquivo_remocao = fopen("resultados_remocao.csv", "w");
  if (arquivo_remocao == NULL) {
    printf("Erro ao criar arquivo de resultados para remoção!\n");
    return 1;
  }

  printf("Executando testes de remoção...\n");
  teste_remocao(arquivo_remocao);
  fclose(arquivo_remocao);
  printf("Resultados de remoção salvos em 'resultados_remocao.csv'\n\n");

  printf("Análise concluída com sucesso!\n");
  printf("Arquivos gerados:\n");
  printf(
      "- resultados_adicao.csv: Contém os resultados dos testes de adição\n");
  printf(
      "- resultados_remocao.csv: Contém os resultados dos testes de remoção\n");

  return 0;
}

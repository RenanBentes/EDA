#include <stdio.h>
#include <stdlib.h>

// --- Estruturas de Dados ---

typedef struct no
{
    int valor;
    int altura;
    struct no *esquerda;
    struct no *direita;

} No;

typedef struct arvore
{
    No *raiz;
} Arvore;

// --- Protótipos das Funções ---

// Funções públicas
Arvore *criarArvore();
void destruirArvore(Arvore *arvore);
void adicionar(Arvore *arvore, int valor);
No *localizar(No *no, int valor);
void percorrerEmOrdem(No *no, void (*callback)(int));

// Funções auxiliares internas (static)
static No *criarNo(int valor);
static void destruirNoRecursivo(No *no);
static int alturaNo(No *no);
static int fatorBalanceamento(No *no);
static void atualizarAltura(No *no);
static No *rotacaoDireita(No *y);
static No *rotacaoEsquerda(No *x);
static No *adicionarRecursivo(No *no, int valor);

// --- Implementação ---

int max(int a, int b)
{
    return a > b ? a : b;
}

Arvore *criarArvore()
{
    Arvore *arvore = malloc(sizeof(Arvore));
    if (arvore == NULL)
    {
        perror("Falha ao alocar memória para a árvore");
        exit(EXIT_FAILURE);
    }
    arvore->raiz = NULL;
    return arvore;
}

void destruirArvore(Arvore *arvore)
{
    if (arvore == NULL)
        return;
    destruirNoRecursivo(arvore->raiz);
    free(arvore);
}

void adicionar(Arvore *arvore, int valor)
{
    if (arvore == NULL)
        return;
    printf("Adicionando %d\n", valor);
    arvore->raiz = adicionarRecursivo(arvore->raiz, valor);
}

No *localizar(No *no, int valor)
{
    while (no != NULL)
    {
        if (valor == no->valor)
        {
            return no;
        }
        no = valor < no->valor ? no->esquerda : no->direita;
    }
    return NULL;
}

void percorrerEmOrdem(No *no, void (*callback)(int))
{
    if (no != NULL)
    {
        percorrerEmOrdem(no->esquerda, callback);
        callback(no->valor);
        percorrerEmOrdem(no->direita, callback);
    }
}

// --- Implementação das Funções Auxiliares ---
static No *criarNo(int valor)
{
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
    {
        perror("Falha ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    novo->valor = valor;
    novo->altura = 1;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

static void destruirNoRecursivo(No *no)
{
    if (no == NULL)
        return;

    destruirNoRecursivo(no->esquerda);
    destruirNoRecursivo(no->direita);
    free(no);
}

static int alturaNo(No *no)
{
    return (no == NULL) ? 0 : no->altura;
}

static int fatorBalanceamento(No *no)
{
    if (no == NULL)
        return 0;
    return alturaNo(no->esquerda) - alturaNo(no->direita);
}

static void atualizarAltura(No *no)
{
    no->altura = 1 + max(alturaNo(no->esquerda), alturaNo(no->direita));
}

static No *rotacaoDireita(No *y)
{
    printf("RSD(%d)\n", y->valor);
    No *x = y->esquerda;
    No *T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

static No *rotacaoEsquerda(No *x)
{
    printf("RSE(%d)\n", x->valor);
    No *y = x->direita;
    No *T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

static No *adicionarRecursivo(No *no, int valor)
{

    if (no == NULL)
    {
        return criarNo(valor);
    }

    if (valor < no->valor)
    {
        no->esquerda = adicionarRecursivo(no->esquerda, valor);
    }
    else if (valor > no->valor)
    {
        no->direita = adicionarRecursivo(no->direita, valor);
    }
    else
    {

        return no;
    }

    atualizarAltura(no);
    int fb = fatorBalanceamento(no);

    // Caso Esquerda-Esquerda
    if (fb > 1 && valor < no->esquerda->valor)
    {
        return rotacaoDireita(no);
    }

    // Caso Direita-Direita
    if (fb < -1 && valor > no->direita->valor)
    {
        return rotacaoEsquerda(no);
    }

    // Caso Esquerda-Direita (Rotação Dupla)
    if (fb > 1 && valor > no->esquerda->valor)
    {
        printf("RDD(%d)\n", no->valor);
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso Direita-Esquerda (Rotação Dupla)
    if (fb < -1 && valor < no->direita->valor)
    {
        printf("RDE(%d)\n", no->valor);
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    return no;
}

void visitar(int valor)
{
    printf("%d ", valor);
}

int main()
{
    Arvore *a = criarArvore();
    adicionar(a, 1);
    adicionar(a, 2);
    adicionar(a, 3);
    adicionar(a, 7);
    adicionar(a, 6);
    adicionar(a, 5);
    adicionar(a, 4);

    printf("\nPercorrendo em ordem: ");
    percorrerEmOrdem(a->raiz, visitar);
    printf("\n");
    destruirArvore(a);
    printf("Memória da árvore liberada com sucesso.\n");

    return 0;
}

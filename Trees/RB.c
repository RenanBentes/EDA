#include <stdio.h>
#include <stdlib.h>

// --- Estruturas de Dados ---

typedef enum
{
    VERMELHO,
    PRETO
} Cor;

typedef struct no
{
    int valor;
    Cor cor;
    struct no *pai;
    struct no *esquerda;
    struct no *direita;
} No;

typedef struct arvore
{
    No *raiz;
    No *nulo; // Nó sentinela
} Arvore;

// --- Protótipos das Funções ---

// Funções públicas
Arvore *criarArvore();
void destruirArvore(Arvore *arvore);
void adicionar(Arvore *arvore, int valor);
No *localizar(const Arvore *arvore, int valor);
void percorrerEmOrdem(const Arvore *arvore, const No *no, void (*callback)(int));

// Funções auxiliares (static)
static No *criarNo(Arvore *arvore, No *pai, int valor);
static void destruirNoRecursivo(Arvore *arvore, No *no);
static void balancearInsercao(Arvore *arvore, No *no);
static void rotacionarEsquerda(Arvore *arvore, No *x);
static void rotacionarDireita(Arvore *arvore, No *y);

// --- Implementação ---

Arvore *criarArvore()
{
    Arvore *arvore = malloc(sizeof(Arvore));
    // Verificar falha de alocação
    if (arvore == NULL)
    {
        perror("Falha ao alocar Arvore");
        exit(EXIT_FAILURE);
    }

    // Criar e configurar o nó sentinela primeiro
    No *nulo = malloc(sizeof(No));
    if (nulo == NULL)
    {
        perror("Falha ao alocar nó sentinela");
        exit(EXIT_FAILURE);
    }
    nulo->cor = PRETO;
    nulo->valor = 0;
    nulo->pai = nulo->esquerda = nulo->direita = nulo;

    arvore->nulo = nulo;
    arvore->raiz = arvore->nulo;

    return arvore;
}

// Função para liberar toda a memória
void destruirArvore(Arvore *arvore)
{
    if (arvore == NULL)
        return;
    destruirNoRecursivo(arvore, arvore->raiz);
    free(arvore->nulo);
    free(arvore);
}

static void destruirNoRecursivo(Arvore *arvore, No *no)
{
    if (no == arvore->nulo)
        return;
    destruirNoRecursivo(arvore, no->esquerda);
    destruirNoRecursivo(arvore, no->direita);
    free(no);
}

static No *criarNo(Arvore *arvore, No *pai, int valor)
{
    No *no = malloc(sizeof(No));
    if (no == NULL)
    {
        perror("Falha ao alocar nó");
        exit(EXIT_FAILURE);
    }
    no->valor = valor;
    no->pai = pai;
    no->cor = VERMELHO;
    no->esquerda = arvore->nulo;
    no->direita = arvore->nulo;
    return no;
}

void adicionar(Arvore *arvore, int valor)
{
    No *y = arvore->nulo;
    No *x = arvore->raiz;

    while (x != arvore->nulo)
    {
        y = x;
        if (valor < x->valor)
        {
            x = x->esquerda;
        }
        else if (valor > x->valor)
        {
            x = x->direita;
        }
        else
        {
            return;
        }
    }

    No *novo_no = criarNo(arvore, y, valor);

    if (y == arvore->nulo)
    {
        arvore->raiz = novo_no;
    }
    else if (novo_no->valor < y->valor)
    {
        y->esquerda = novo_no;
    }
    else
    {
        y->direita = novo_no;
    }

    if (novo_no->pai == arvore->nulo)
    {
        novo_no->cor = PRETO;
        return;
    }
    if (novo_no->pai->pai == arvore->nulo)
    {
        return;
    }

    balancearInsercao(arvore, novo_no);
}

static void balancearInsercao(Arvore *arvore, No *k)
{
    No *u; // Tio

    while (k->pai->cor == VERMELHO)
    {
        if (k->pai == k->pai->pai->direita)
        {                              // Pai de K é filho à direita
            u = k->pai->pai->esquerda; // Tio é o filho à esquerda
            if (u->cor == VERMELHO)
            {
                // --- CASO 1: Tio é vermelho -> Apenas recolorir ---
                u->cor = PRETO;
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai; // Move o foco para o avô para continuar a verificação
            }
            else
            {
                if (k == k->pai->esquerda)
                {
                    // --- CASO 2: Tio é preto e K é um filho à esquerda -> Rotação Direita ---
                    k = k->pai;
                    rotacionarDireita(arvore, k);
                }
                // --- CASO 3: Tio é preto e K é um filho à direita -> Rotação Esquerda ---
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacionarEsquerda(arvore, k->pai->pai);
            }
        }
        else
        {                             // Pai de K é filho à esquerda (código espelhado)
            u = k->pai->pai->direita; // Tio é o filho à direita
            if (u->cor == VERMELHO)
            {
                // --- CASO 1: Tio é vermelho -> Apenas recolorir ---
                u->cor = PRETO;
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai;
            }
            else
            {
                if (k == k->pai->direita)
                {
                    // --- CASO 2: Tio é preto e K é um filho à direita -> Rotação Esquerda ---
                    k = k->pai;
                    rotacionarEsquerda(arvore, k);
                }
                // --- CASO 3: Tio é preto e K é um filho à esquerda -> Rotação Direita ---
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacionarDireita(arvore, k->pai->pai);
            }
        }
        if (k == arvore->raiz)
        {
            break;
        }
    }
    arvore->raiz->cor = PRETO;
}

static void rotacionarEsquerda(Arvore *arvore, No *x)
{
    No *y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != arvore->nulo)
    {
        y->esquerda->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == arvore->nulo)
    {
        arvore->raiz = y;
    }
    else if (x == x->pai->esquerda)
    {
        x->pai->esquerda = y;
    }
    else
    {
        x->pai->direita = y;
    }
    y->esquerda = x;
    x->pai = y;
}

static void rotacionarDireita(Arvore *arvore, No *y)
{
    No *x = y->esquerda;
    y->esquerda = x->direita;
    if (x->direita != arvore->nulo)
    {
        x->direita->pai = y;
    }
    x->pai = y->pai;
    if (y->pai == arvore->nulo)
    {
        arvore->raiz = x;
    }
    else if (y == y->pai->direita)
    {
        y->pai->direita = x;
    }
    else
    {
        y->pai->esquerda = x;
    }
    x->direita = y;
    y->pai = x;
}

// --- Funções de Percurso e Localização ---

No *localizar(const Arvore *arvore, int valor)
{
    No *no = arvore->raiz;
    while (no != arvore->nulo)
    {
        if (valor == no->valor)
        {
            return no;
        }
        no = (valor < no->valor) ? no->esquerda : no->direita;
    }
    return NULL;
}

void percorrerEmOrdem(const Arvore *arvore, const No *no, void (*callback)(int))
{
    if (no != arvore->nulo)
    {
        percorrerEmOrdem(arvore, no->esquerda, callback);
        callback(no->valor);
        percorrerEmOrdem(arvore, no->direita, callback);
    }
}

void visitar(int valor)
{
    printf("%d ", valor);
}

// --- Função Principal ---

int main()
{
    Arvore *a = criarArvore();
    adicionar(a, 7);
    adicionar(a, 6);
    adicionar(a, 5);
    adicionar(a, 4);
    adicionar(a, 3);
    adicionar(a, 2);
    adicionar(a, 1);

    printf("Em ordem: ");
    percorrerEmOrdem(a, a->raiz, visitar);
    printf("\n");

    destruirArvore(a);
    printf("Memória da árvore liberada com sucesso.\n");

    return 0;
}

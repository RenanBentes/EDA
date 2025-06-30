#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturas de dados
typedef struct no
{
    int total;
    int *chaves;
    struct no **filhos;
    struct no *pai;
    int eh_folha;
} No;

typedef struct arvoreB
{
    No *raiz;
    int ordem;
    long long operacoes;
} ArvoreB;

void destroiNo(No *no);
void destroiArvore(ArvoreB *arvore);

// --- Funções de Criação e Destruição ---

ArvoreB *criaArvore(int ordem)
{
    ArvoreB *a = malloc(sizeof(ArvoreB));
    if (a == NULL)
    {
        perror("Falha ao alocar ArvoreB");
        exit(1);
    }
    a->ordem = ordem;
    a->operacoes = 0;

    No *raiz = malloc(sizeof(No));
    if (raiz == NULL)
    {
        perror("Falha ao alocar No");
        exit(1);
    }

    int max = ordem * 2;
    raiz->pai = NULL;
    raiz->total = 0;
    raiz->eh_folha = 1;

    raiz->chaves = malloc(sizeof(int) * max);
    if (raiz->chaves == NULL)
    {
        perror("Falha ao alocar chaves");
        exit(1);
    }

    raiz->filhos = malloc(sizeof(No *) * (max + 1));
    if (raiz->filhos == NULL)
    {
        perror("Falha ao alocar filhos");
        exit(1);
    }

    a->raiz = raiz;
    return a;
}

void destroiNo(No *no)
{
    if (no == NULL)
        return;

    if (!no->eh_folha)
    {
        for (int i = 0; i <= no->total; i++)
        {
            destroiNo(no->filhos[i]);
        }
    }
    free(no->chaves);
    free(no->filhos);
    free(no);
}

void destroiArvore(ArvoreB *arvore)
{
    if (arvore == NULL)
        return;
    destroiNo(arvore->raiz);
    free(arvore);
}

// --- Funções de Busca ---

void percorreArvore(const No *no)
{
    if (no != NULL)
    {
        for (int i = 0; i < no->total; i++)
        {
            if (!no->eh_folha)
            {
                percorreArvore(no->filhos[i]);
            }
            printf("%d ", no->chaves[i]);
        }
        if (!no->eh_folha)
        {
            percorreArvore(no->filhos[no->total]);
        }
    }
}

int pesquisaBinaria(const No *no, int chave)
{
    int inicio = 0, fim = no->total - 1, meio;
    while (inicio <= fim)
    {
        meio = inicio + (fim - inicio) / 2;
        if (no->chaves[meio] == chave)
        {
            return meio;
        }
        else if (no->chaves[meio] > chave)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }
    return inicio;
}

No *localizaNo(ArvoreB *arvore, int chave)
{
    No *no = arvore->raiz;
    while (!no->eh_folha)
    {
        arvore->operacoes++;
        int i = pesquisaBinaria(no, chave);
        if (i < no->total && no->chaves[i] == chave)
        {
            return no;
        }
        no = no->filhos[i];
    }
    return no;
}

// --- Funções de Inserção e Divisão ---

void adicionaChaveNo(No *no, int chave, No *filho_dir)
{
    int i = pesquisaBinaria(no, chave);

    memmove(&no->chaves[i + 1], &no->chaves[i], (no->total - i) * sizeof(int));

    memmove(&no->filhos[i + 2], &no->filhos[i + 1], (no->total - i) * sizeof(No *));

    no->chaves[i] = chave;
    no->filhos[i + 1] = filho_dir;
    no->total++;
}

void divideNo(ArvoreB *arvore, No *no_cheio)
{
    arvore->operacoes++;
    int ordem = arvore->ordem;
    int meio_idx = ordem;

    int chave_promovida = no_cheio->chaves[meio_idx];

    No *novo_no = malloc(sizeof(No));
    novo_no->pai = no_cheio->pai;
    novo_no->eh_folha = no_cheio->eh_folha;
    novo_no->total = ordem;
    novo_no->chaves = malloc(sizeof(int) * (ordem * 2));
    novo_no->filhos = malloc(sizeof(No *) * (ordem * 2 + 1));

    memcpy(novo_no->chaves, &no_cheio->chaves[meio_idx + 1], (ordem - 1) * sizeof(int));

    if (!no_cheio->eh_folha)
    {
        memcpy(novo_no->filhos, &no_cheio->filhos[meio_idx + 1], ordem * sizeof(No *));
        for (int i = 0; i <= novo_no->total; i++)
        {
            if (novo_no->filhos[i] != NULL)
                novo_no->filhos[i]->pai = novo_no;
        }
    }

    novo_no->total = ordem - 1;
    no_cheio->total = meio_idx;

    if (no_cheio->pai == NULL)
    {
        arvore->operacoes++;
        No *nova_raiz = malloc(sizeof(No));
        nova_raiz->pai = NULL;
        nova_raiz->eh_folha = 0;
        nova_raiz->total = 1;
        nova_raiz->chaves = malloc(sizeof(int) * (ordem * 2));
        nova_raiz->filhos = malloc(sizeof(No *) * (ordem * 2 + 1));

        nova_raiz->chaves[0] = chave_promovida;
        nova_raiz->filhos[0] = no_cheio;
        nova_raiz->filhos[1] = novo_no;

        no_cheio->pai = nova_raiz;
        novo_no->pai = nova_raiz;
        arvore->raiz = nova_raiz;
    }
    else
    {
        adicionaChaveNo(no_cheio->pai, chave_promovida, novo_no);
        if (no_cheio->pai->total > ordem * 2)
        {
            divideNo(arvore, no_cheio->pai);
        }
    }
}

void adicionaChave(ArvoreB *arvore, int chave)
{
    No *no = localizaNo(arvore, chave);
    arvore->operacoes++;

    adicionaChaveNo(no, chave, NULL);

    if (no->total > arvore->ordem * 2)
    {
        divideNo(arvore, no);
    }
}

// --- Função Principal ---

int main()
{
    int ordem_arvore = 2;
    ArvoreB *arvore = criaArvore(ordem_arvore);

    adicionaChave(arvore, 12);
    adicionaChave(arvore, 3);
    adicionaChave(arvore, 5);
    adicionaChave(arvore, 7);
    adicionaChave(arvore, 15);
    adicionaChave(arvore, 99);
    adicionaChave(arvore, 1);
    adicionaChave(arvore, 8);
    adicionaChave(arvore, 10);
    adicionaChave(arvore, 20);
    adicionaChave(arvore, 25);

    printf("Árvore percorrida em ordem: ");
    percorreArvore(arvore->raiz);
    printf("\nNúmero de operações: %lld\n", arvore->operacoes);
    destroiArvore(arvore);
    printf("Memória da árvore liberada com sucesso.\n");

    return 0;
}

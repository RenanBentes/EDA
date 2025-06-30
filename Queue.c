#include <stdio.h>
#include <stdlib.h>

// --- Estruturas de Dados ---

// Define o nó da lista ligada que compõe a fila.
typedef struct no
{
    int valor;
    struct no *proximo;
} No;

// Define a estrutura da Fila.
typedef struct fila
{
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

// --- Protótipos das Funções ---

Fila *criarFila();
void destruirFila(Fila *fila);
void enfileirar(Fila *fila, int valor); // enqueue
int desenfileirar(Fila *fila);          // dequeue
int frente(const Fila *fila);           // front/peek
int estaVazia(const Fila *fila);
void imprimirFila(const Fila *fila);

// --- Implementação ---

Fila *criarFila()
{
    Fila *fila = malloc(sizeof(Fila));
    // Verificar falha de alocação.
    if (fila == NULL)
    {
        perror("Falha ao alocar memória para a Fila");
        exit(EXIT_FAILURE);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

// Libera toda a memória alocada para a fila e seus nós.
void destruirFila(Fila *fila)
{
    if (fila == NULL)
        return;

    // Percorre a fila, liberando cada nó.
    while (!estaVazia(fila))
    {
        desenfileirar(fila);
    }

    // Libera a estrutura da fila em si.
    free(fila);
}

int estaVazia(const Fila *fila)
{
    return fila->tamanho == 0;
}

void enfileirar(Fila *fila, int valor)
{
    No *novoNo = malloc(sizeof(No));
    if (novoNo == NULL)
    {
        perror("Falha ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }
    novoNo->valor = valor;
    novoNo->proximo = NULL;

    if (estaVazia(fila))
    {
        // Se a fila está vazia, o novo nó é tanto o início quanto o fim.
        fila->inicio = novoNo;
        fila->fim = novoNo;
    }
    else
    {
        // Se não, o novo nó é adicionado após o fim atual.
        fila->fim->proximo = novoNo;
        // O ponteiro de fim da fila é atualizado para o novo nó.
        fila->fim = novoNo;
    }
    fila->tamanho++;
}

int desenfileirar(Fila *fila)
{
    // Verifica se a fila não está vazia.
    if (estaVazia(fila))
    {
        fprintf(stderr, "Erro: Impossível desenfileirar. A fila está vazia.\n");
        return -1;
    }

    // Guarda o nó do início para poder liberá-lo.
    No *noRemovido = fila->inicio;
    int valorRemovido = noRemovido->valor;

    // O início da fila passa a ser o próximo elemento.
    fila->inicio = noRemovido->proximo;

    // Caso especial: se a fila ficou vazia após a remoção,
    // o ponteiro de fim também deve ser nulo.
    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    free(noRemovido);
    fila->tamanho--;

    return valorRemovido;
}

int frente(const Fila *fila)
{
    if (estaVazia(fila))
    {
        fprintf(stderr, "Erro: Impossível ver a frente. A fila está vazia.\n");
        return -1;
    }
    return fila->inicio->valor;
}

void imprimirFila(const Fila *fila)
{
    if (estaVazia(fila))
    {
        printf("Fila: [ Vazia ]\n");
        return;
    }

    printf("Fila: [ Início -> ");
    No *atual = fila->inicio;
    while (atual != NULL)
    {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("<- Fim ]\n");
}

// --- Função Principal para Testes ---

int main()
{
    Fila *f = criarFila();

    printf("--- Testando a Fila ---\n");
    imprimirFila(f);

    printf("\nEnfileirando 10, 20 e 30...\n");
    enfileirar(f, 10);
    enfileirar(f, 20);
    enfileirar(f, 30);
    imprimirFila(f);
    printf("Tamanho da fila: %d\n", f->tamanho);
    printf("Elemento na frente: %d\n", frente(f));

    printf("\nDesenfileirando um elemento...\n");
    int valor = desenfileirar(f);
    printf("Valor desenfileirado: %d\n", valor);
    imprimirFila(f);
    printf("Elemento na frente agora: %d\n", frente(f));

    printf("\nEnfileirando 40...\n");
    enfileirar(f, 40);
    imprimirFila(f);

    printf("\nDesenfileirando todos os elementos...\n");
    desenfileirar(f);
    desenfileirar(f);
    desenfileirar(f);
    imprimirFila(f);

    printf("\nTentando desenfileirar de uma fila vazia...\n");
    desenfileirar(f);

    destruirFila(f);
    printf("\nMemória da fila liberada com sucesso.\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// --- Estruturas de Dados ---

// Define o nó que armazenará o valor e o ponteiro para o próximo elemento.
typedef struct no
{
    int valor;
    struct no *proximo;
} No;

// Define a estrutura da Pilha.
typedef struct pilha
{
    No *topo;
    int tamanho;
} Pilha;

// --- Protótipos das Funções ---

Pilha *criarPilha();
void destruirPilha(Pilha *pilha);
void empilhar(Pilha *pilha, int valor); // push
int desempilhar(Pilha *pilha);          // pop
int topo(const Pilha *pilha);           // peek
int estaVazia(const Pilha *pilha);
void imprimirPilha(const Pilha *pilha);

// --- Implementação ---

Pilha *criarPilha()
{
    Pilha *pilha = malloc(sizeof(Pilha));
    // Verificar falha de alocação.
    if (pilha == NULL)
    {
        perror("Falha ao alocar memória para a Pilha");
        exit(EXIT_FAILURE);
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Libera toda a memória alocada para a pilha e seus nós.
void destruirPilha(Pilha *pilha)
{
    if (pilha == NULL)
        return;

    // Percorre a pilha, liberando cada nó.
    while (!estaVazia(pilha))
    {
        desempilhar(pilha);
    }

    // Libera a estrutura da pilha em si.
    free(pilha);
}

int estaVazia(const Pilha *pilha)
{
    return pilha->tamanho == 0;
}

void empilhar(Pilha *pilha, int valor)
{
    // Cria um novo nó.
    No *novoNo = malloc(sizeof(No));
    if (novoNo == NULL)
    {
        perror("Falha ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }
    novoNo->valor = valor;
    novoNo->proximo = pilha->topo;

    pilha->topo = novoNo;
    pilha->tamanho++;
}

int desempilhar(Pilha *pilha)
{
    // Verifica se a pilha não está vazia.
    if (estaVazia(pilha))
    {
        fprintf(stderr, "Erro: Impossível desempilhar. A pilha está vazia.\n");
        return -1;
    }

    No *noRemovido = pilha->topo;
    int valorRemovido = noRemovido->valor;
    pilha->topo = noRemovido->proximo;

    free(noRemovido);
    pilha->tamanho--;

    return valorRemovido;
}

int topo(const Pilha *pilha)
{
    // Verifica se a pilha não está vazia.
    if (estaVazia(pilha))
    {
        fprintf(stderr, "Erro: Impossível ver o topo. A pilha está vazia.\n");
        return -1; // Retorna um valor de erro.
    }
    return pilha->topo->valor;
}

void imprimirPilha(const Pilha *pilha)
{
    if (estaVazia(pilha))
    {
        printf("Pilha: [ Vazia ]\n");
        return;
    }

    printf("Pilha: [ Topo -> ");
    No *atual = pilha->topo;
    while (atual != NULL)
    {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("]\n");
}

// --- Função Principal para Testes ---

int main()
{
    Pilha *p = criarPilha();

    printf("--- Testando a Pilha ---\n");
    imprimirPilha(p);

    printf("\nEmpilhando 10, 20 e 30...\n");
    empilhar(p, 10);
    empilhar(p, 20);
    empilhar(p, 30);
    imprimirPilha(p);
    printf("Tamanho da pilha: %d\n", p->tamanho);
    printf("Elemento no topo: %d\n", topo(p));

    printf("\nDesempilhando um elemento...\n");
    int valor = desempilhar(p);
    printf("Valor desempilhado: %d\n", valor);
    imprimirPilha(p);
    printf("Elemento no topo agora: %d\n", topo(p));

    printf("\nDesempilhando mais dois elementos...\n");
    desempilhar(p);
    desempilhar(p);
    imprimirPilha(p);

    printf("\nTentando desempilhar de uma pilha vazia...\n");
    desempilhar(p);
    destruirPilha(p);
    printf("\nMemória da pilha liberada com sucesso.\n");

    return 0;
}

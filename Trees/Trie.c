#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Estruturas e Constantes ---

// Define o tamanho do alfabeto que a Trie suportará.
// Para este exemplo, usaremos apenas letras minúsculas de 'a' a 'z'.
#define TAMANHO_ALFABETO 26

typedef struct trie_no
{
    struct trie_no *filhos[TAMANHO_ALFABETO];
    // Marcador booleano para indicar se este nó é o fim de uma palavra válida.
    int ehFimDePalavra;
} TrieNo;

typedef struct trie
{
    TrieNo *raiz;
} Trie;

// --- Protótipos das Funções ---

// Funções públicas
Trie *criarTrie();
void destruirTrie(Trie *trie);
void inserir(Trie *trie, const char *palavra);
int buscar(Trie *trie, const char *palavra);
void sugerir(Trie *trie, const char *prefixo);

// Funções auxiliares (static)
static TrieNo *criarNo();
static void destruirNoRecursivo(TrieNo *no);
static void sugerirRecursivo(TrieNo *no, char *prefixoAtual);
static int charParaIndice(char c);

// --- Implementação ---

// Converte um caractere ('a'-'z') para um índice de array (0-25).
static int charParaIndice(char c)
{
    // Garante que o caractere seja minúsculo antes de converter.
    return tolower(c) - 'a';
}

Trie *criarTrie()
{
    Trie *trie = malloc(sizeof(Trie));
    // Verificar falha de alocação.
    if (trie == NULL)
    {
        perror("Falha ao alocar memória para a Trie");
        exit(EXIT_FAILURE);
    }
    trie->raiz = criarNo();
    return trie;
}

static TrieNo *criarNo()
{
    TrieNo *no = malloc(sizeof(TrieNo));
    if (no == NULL)
    {
        perror("Falha ao alocar memória para o nó da Trie");
        exit(EXIT_FAILURE);
    }
    no->ehFimDePalavra = 0; // Falso por padrão

    // Inicializa todos os filhos como NULL.
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        no->filhos[i] = NULL;
    }
    return no;
}

// Função para liberar toda a memória alocada.
void destruirTrie(Trie *trie)
{
    if (trie == NULL)
        return;
    destruirNoRecursivo(trie->raiz);
    free(trie);
}

static void destruirNoRecursivo(TrieNo *no)
{
    if (no == NULL)
        return;
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        destruirNoRecursivo(no->filhos[i]);
    }
    free(no);
}

void inserir(Trie *trie, const char *palavra)
{
    if (trie == NULL || palavra == NULL)
        return;

    TrieNo *atual = trie->raiz;
    int tamanho = strlen(palavra);

    for (int i = 0; i < tamanho; i++)
    {
        int indice = charParaIndice(palavra[i]);

        // Ignora caracteres que não pertencem ao nosso alfabeto.
        if (indice < 0 || indice >= TAMANHO_ALFABETO)
        {
            continue;
        }

        // Se o caminho para este caractere não existe, cria um novo nó.
        if (atual->filhos[indice] == NULL)
        {
            atual->filhos[indice] = criarNo();
        }
        // Move para o próximo nó.
        atual = atual->filhos[indice];
    }

    // Ao final da palavra, marca o nó atual como o fim de uma palavra válida.
    atual->ehFimDePalavra = 1;
}

int buscar(Trie *trie, const char *palavra)
{
    if (trie == NULL || palavra == NULL)
        return 0;

    TrieNo *atual = trie->raiz;
    int tamanho = strlen(palavra);

    for (int i = 0; i < tamanho; i++)
    {
        int indice = charParaIndice(palavra[i]);
        if (indice < 0 || indice >= TAMANHO_ALFABETO)
        {
            return 0;
        }

        // Se o caminho não existe, a palavra não está na Trie.
        if (atual->filhos[indice] == NULL)
        {
            return 0;
        }
        atual = atual->filhos[indice];
    }

    return (atual != NULL && atual->ehFimDePalavra);
}

// Função pública que inicia a busca por sugestões.
void sugerir(Trie *trie, const char *prefixo)
{
    if (trie == NULL || prefixo == NULL)
        return;

    TrieNo *atual = trie->raiz;
    int tamanho = strlen(prefixo);

    // 1. Navega até o nó que representa o final do prefixo.
    for (int i = 0; i < tamanho; i++)
    {
        int indice = charParaIndice(prefixo[i]);
        if (indice < 0 || indice >= TAMANHO_ALFABETO || atual->filhos[indice] == NULL)
        {
            printf("Nenhuma palavra encontrada com o prefixo '%s'\n", prefixo);
            return;
        }
        atual = atual->filhos[indice];
    }

    // 2. A partir do nó do prefixo, encontra todas as palavras descendentes.
    // Aloca memória para construir as palavras encontradas.
    char prefixo_mutavel[100];
    strcpy(prefixo_mutavel, prefixo);

    printf("Sugestões para o prefixo '%s':\n", prefixo);
    sugerirRecursivo(atual, prefixo_mutavel);
}

// Função recursiva que explora a Trie a partir de um nó e imprime as palavras.
static void sugerirRecursivo(TrieNo *no, char *prefixoAtual)
{
    if (no == NULL)
        return;
    if (no->ehFimDePalavra)
    {
        printf("- %s\n", prefixoAtual);
    }

    // Percorre todos os filhos possíveis.
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        if (no->filhos[i] != NULL)
        {
            char proximoPrefixo[100];
            sprintf(proximoPrefixo, "%s%c", prefixoAtual, 'a' + i);
            sugerirRecursivo(no->filhos[i], proximoPrefixo);
        }
    }
}

// --- Função Principal para Testes ---

int main()
{
    Trie *dicionario = criarTrie();

    // Inserindo palavras no dicionário
    inserir(dicionario, "casa");
    inserir(dicionario, "casarao");
    inserir(dicionario, "caso");
    inserir(dicionario, "caminhao");
    inserir(dicionario, "caminho");
    inserir(dicionario, "lua");
    inserir(dicionario, "luz");

    // Testando a função de busca
    printf("--- Teste de Busca ---\n");
    printf("Buscando 'casa': %s\n", buscar(dicionario, "casa") ? "Encontrado" : "Não encontrado");
    printf("Buscando 'cas': %s\n", buscar(dicionario, "cas") ? "Encontrado" : "Não encontrado");
    printf("Buscando 'luz': %s\n", buscar(dicionario, "luz") ? "Encontrado" : "Não encontrado");
    printf("Buscando 'sol': %s\n", buscar(dicionario, "sol") ? "Encontrado" : "Não encontrado");
    printf("\n");

    // Testando a função de sugestão/autocompletar
    printf("--- Teste de Sugestão ---\n");
    sugerir(dicionario, "cas");
    printf("\n");
    sugerir(dicionario, "lu");
    printf("\n");
    sugerir(dicionario, "cam");

    destruirTrie(dicionario);
    printf("\nMemória da Trie liberada com sucesso.\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int mergesort(int[], int);
void _mergesort(int[], int, int, int *);
void merge(int[], int, int, int, int *);
void _mergesortBU(int[], int, int, int *);

int quicksort(int[], int);
void _quicksort(int[], int, int, int *);
int partition(int[], int, int, int *);

int *populaVetorCasoMedio(int n) {
    int *v = malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        v[i] = rand() % n;
    }
    return v;
}

void troca(int *v, int i, int j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int bubblesort(int *v, int n) {
    int i, j, c = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            c++;
            if (v[i] > v[j]) {
                troca(v, i, j);
                c++;
            }
        }
    }
    return c;
}

int bubblesort2(int v[], int n) {
    int i, c = 0, trocou;
    do {
        trocou = 0;
        for (i = 0; i < n - 1; i++) {
            c++;
            if (v[i] > v[i + 1]) {
                c++;
                troca(v, i, i + 1);
                trocou = 1;
            }
        }
    } while (trocou);
    return c;
}

int *copiaVetor(int *v, int n) {
    int *copia = malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        copia[i] = v[i];
    }
    return copia;
}

int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void countingSort(int arr[], int n, int exp, int *R) {
    int output[n];
    int count[10] = {0};

    (*R)++;
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
        (*R)++;
    }
    (*R)++;
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
        (*R)++;
    }
    (*R)++;
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        (*R)++;
    }
    (*R)++;
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        (*R)++;
    }
}

int radixsort(int arr[], int n) {
    int R = 0;
    int max = findMax(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, n, exp, &R);
        R++;
    }
    return R;
}

void heapify(int v[], int n, int i, int *c) {
    int raiz = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    (*c)++;
    if (esquerda < n && v[esquerda] > v[raiz]) {
        raiz = esquerda;
    }

    (*c)++;
    if (direita < n && v[direita] > v[raiz]) {
        raiz = direita;
    }

    if (raiz != i) {
        (*c)++;
        troca(v, i, raiz);
        heapify(v, n, raiz, c);
    }
}

int heapsort(int v[], int n) {
    int c = 0;
    int i;
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i, &c);
    }

    for (i = n - 1; i > 0; i--) {
        c++;
        troca(v, 0, i);
        heapify(v, i, 0, &c);
    }

    return c;
}

int insertionsort(int v[], int n) {
    int pivo, j, c = 0, i;
    for (i = 1; i < n; i++) {
        pivo = v[i];
        j = i - 1;
        c++;
        while (j >= 0 && pivo < v[j]) {
            c++; // troca
            v[j + 1] = v[j];
            j--;
            c++;
        }
        c++; // troca
        v[j + 1] = pivo;
    }
    return c;
}

void merge(int v[], int inicio, int meio, int fim, int *c) {
    int aux[fim - inicio + 1];
    int i = inicio, j = meio + 1, k = 0;

    (*c)++;
    while (i <= meio && j <= fim) { // Intercala
        aux[k++] = v[i] <= v[j] ? v[i++] : v[j++];
        (*c)++;
    }

    (*c)++;
    while (i <= meio) {
        aux[k++] = v[i++];
        (*c)++;
    }

    (*c)++;
    while (j <= fim) {
        aux[k++] = v[j++];
        (*c)++;
    }

    (*c)++;
    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = aux[k];
        (*c)++;
    }
}

int mergesort(int v[], int n) {
    int c = 0;
    _mergesort(v, 0, n - 1, &c);
    return c;
}

void _mergesort(int v[], int inicio, int fim, int *c) {
    int meio = (inicio + fim) / 2;

    if (inicio < fim) {
        _mergesort(v, inicio, meio, c);
        _mergesort(v, meio + 1, fim, c);

        merge(v, inicio, meio, fim, c);
    }
}

int mergesortBU(int v[], int n) {
    int c = 0;
    _mergesortBU(v, 0, n - 1, &c);
    return c;
}

void _mergesortBU(int v[], int inicio, int fim, int *c) {
    int i, meio;
    for (meio = 1; meio < fim - inicio + 1; meio *= 2 * meio) {
        for (i = inicio; i <= fim - meio; i += 2 * meio) {
            int j = (i + (2 * meio)) - 1;
            if (j > fim)
                j = fim;

            merge(v, i, i + meio - 1, j, c);
        }
    }
}

int quicksort(int v[], int n) {
    int c = 0;
    _quicksort(v, 0, n - 1, &c);
    return c;
}

void _quicksort(int v[], int inicio, int fim, int *c) {
    if (inicio < fim) {
        int meio = partition(v, inicio, fim, c);

        _quicksort(v, inicio, meio - 1, c);
        _quicksort(v, meio + 1, fim, c);
    }
}

int partition(int v[], int inicio, int fim, int *c) {
    int pivo = v[fim];
    int i = (inicio - 1);
    int j;
    for (j = inicio; j <= fim - 1; j++) {
        (*c)++;
        if (v[j] < pivo) {
            i++;
            (*c)++;
            troca(v, i, j);
        }
    }
    (*c)++;
    troca(v, i + 1, fim);
    return i + 1;
}

int main() {
    int n;
    int repeticoes = 30;
    int i, j = 1000;
    int *casoMedio;

    unsigned long long int operacoesBubblesort = 0;
    unsigned long long int operacoesBubblesort2 = 0;
    unsigned long long int operacoesHeapsort = 0;
    unsigned long long int operacoesInsertionSort = 0;
    unsigned long long int operacoesMergeSort = 0;
    unsigned long long int operacoesMergeSort2 = 0;
    unsigned long long int operacoesQuickSort = 0;
    unsigned long long int operacoesRadixSort = 0;

    remove("dados.csv");

    FILE *arquivo = fopen("dados.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    fprintf(arquivo, "Bubblesort;Bubblesort2;Heapsort;InsertionSort;MergeSort;"
                     "MergeSort2;QuickSort;RadixSort\n");

    for (n = 1; n <= j; n++) {
        for (i = 0; i < repeticoes; i++) {
            casoMedio = populaVetorCasoMedio(j);

            operacoesBubblesort += bubblesort(copiaVetor(casoMedio, n), n);
            operacoesBubblesort2 += bubblesort2(copiaVetor(casoMedio, n), n);
            operacoesHeapsort += heapsort(copiaVetor(casoMedio, n), n);
            operacoesInsertionSort += insertionsort(copiaVetor(casoMedio, n), n);
            operacoesMergeSort += mergesort(copiaVetor(casoMedio, n), n);
            operacoesMergeSort2 += mergesortBU(copiaVetor(casoMedio, n), n);
            operacoesQuickSort += quicksort(copiaVetor(casoMedio, n), n);
            operacoesRadixSort += radixsort(copiaVetor(casoMedio, n), n);
        }

        operacoesBubblesort /= repeticoes;
        operacoesBubblesort2 /= repeticoes;
        operacoesHeapsort /= repeticoes;
        operacoesInsertionSort /= repeticoes;
        operacoesMergeSort /= repeticoes;
        operacoesMergeSort2 /= repeticoes;
        operacoesQuickSort /= repeticoes;
        operacoesRadixSort /= repeticoes;

        fprintf(arquivo, "%llu;%llu;%llu;%llu;%llu;%llu;%llu;%llu\n",
                operacoesBubblesort, operacoesBubblesort2, operacoesHeapsort,
                operacoesInsertionSort, operacoesMergeSort, operacoesMergeSort2,
                operacoesQuickSort, operacoesRadixSort);

        free(casoMedio);
    }

    fclose(arquivo);

    return 0;
}

import pandas as pd
import matplotlib.pyplot as plt

# Carrega o arquivo CSV
df = pd.read_csv('dados.csv', delimiter=';')

# Extrai as colunas do DataFrame
bubblesort = df['Bubblesort']
bubblesort2 = df['Bubblesort2']
heapsort = df['Heapsort']
insertion_sort = df['InsertionSort']
merge_sort = df['MergeSort']
merge_sort2 = df['MergeSort2']
quick_sort = df['QuickSort']
radix_sort = df['RadixSort']

# Define os valores de 'n' para o eixo x
n = range(1, len(df) + 1)

# Plota os gráficos
plt.semilogy(n, bubblesort, label='Bubblesort')
plt.semilogy(n, bubblesort2, label='Bubblesort2')
plt.semilogy(n, heapsort, label='Heapsort')
plt.semilogy(n, insertion_sort, label='InsertionSort')
plt.semilogy(n, merge_sort, label='MergeSort')
plt.semilogy(n, merge_sort2, label='MergeSort2')
plt.semilogy(n, quick_sort, label='QuickSort')
plt.semilogy(n, radix_sort, label='RadixSort')

# Configurações do gráfico
plt.xlabel('n')
plt.ylabel('Operações')
plt.title('Desempenho dos Algoritmos de Ordenação')
plt.legend()

# Exibe o gráfico
plt.show()
Estruturas de Dados em C
Este repositório é uma coleção de implementações de estruturas de dados clássicas, desenvolvidas em linguagem C pura. O

Cada implementação segue um padrão, com foco em:

Gerenciamento de Memória Seguro: Prevenção de vazamentos de memória com funções de criação e destruição.

Código Robusto: Verificação de falhas de alocação e tratamento de casos de borda.

Clareza e Legibilidade: Código bem comentado e funções modulares.

📚 Tabela de Conteúdos
Estruturas Implementadas

Como Compilar e Executar

Detalhes das Estruturas

Como Contribuir

🚀 Estruturas Implementadas
Categoria

Estrutura

Arquivo

Estruturas Lineares

Pilha (Stack) - LIFO

Pilha.c



Fila (Queue) - FIFO

Fila.c

Árvores

Árvore AVL - Auto-balanceada (Fator de Balanço)

arvores/ArvoreAVL.c



Árvore Rubro-Negra - Auto-balanceada (Cores)

arvores/ArvoreRB.c



Árvore B - Otimizada para disco

arvores/ArvoreB.c



Árvore Trie - Árvore de Prefixos (Autocompletar)

arvores/ArvoreTrie.c

🛠️ Como Compilar e Executar
Cada arquivo .c contém sua própria função main() com exemplos de uso, permitindo que sejam compilados e testados individualmente.

Para compilar um arquivo, você precisará de um compilador C, como o GCC.

# Exemplo para compilar a Fila
gcc Fila.c -o Fila

# Exemplo para compilar a Árvore AVL
gcc arvores/ArvoreAVL.c -o ArvoreAVL

Após a compilação, um arquivo executável será criado. Para executá-lo:

# No Windows
.\Fila.exe
.\ArvoreAVL.exe

# No Linux ou macOS
./Fila
./ArvoreAVL

🌟 Detalhes das Estruturas
Pilha (Pilha.c)
Política: LIFO (Last-In, First-Out).

Operações Principais: empilhar (push), desempilhar (pop), topo (peek).

Complexidade: Todas as operações principais têm complexidade de tempo O(1).

Uso Ideal: Gerenciamento de chamadas de função, algoritmos de backtracking, análise de expressões.

Fila (Fila.c)
Política: FIFO (First-In, First-Out).

Operações Principais: enfileirar (enqueue), desenfileirar (dequeue), frente (front).

Complexidade: Todas as operações principais têm complexidade de tempo O(1).

Uso Ideal: Gerenciamento de tarefas, buffers, algoritmos de busca em largura (BFS).

Árvore AVL (arvores/ArvoreAVL.c)
Tipo: Árvore binária de busca auto-balanceada.

Mecanismo: Mantém o balanceamento através de rotações (simples e duplas) baseadas no "fator de balanceamento" de cada nó.

Complexidade: Busca, inserção e remoção em O(log n).

Característica: É estritamente balanceada, o que pode resultar em mais rotações, mas garante buscas muito rápidas.

Árvore Rubro-Negra (arvores/ArvoreRB.c)
Tipo: Árvore binária de busca auto-balanceada.

Mecanismo: Usa 5 propriedades baseadas na coloração dos nós (Vermelho/Preto) para garantir um balanceamento aproximado.

Complexidade: Busca, inserção e remoção em O(log n).

Característica: É menos estrita que a AVL, resultando em menos rotações na inserção/remoção, sendo uma escolha comum para implementações práticas (ex: std::map em C++).

Árvore B (arvores/ArvoreB.c)
Tipo: Árvore de busca auto-balanceada de ordem m.

Mecanismo: Permite que os nós tenham um número variável de filhos (até m). Os dados são mantidos ordenados dentro de cada nó.

Complexidade: Busca, inserção e remoção em O(log n).

Característica: Reduz a altura da árvore drasticamente, otimizando o número de acessos a disco. É a base de dados para a maioria dos sistemas de arquivos e bancos de dados.

Árvore Trie (arvores/ArvoreTrie.c)
Tipo: Árvore de prefixos.

Mecanismo: Cada nó representa um caractere e o caminho da raiz até um nó representa um prefixo.

Complexidade: Inserção e busca de uma palavra de tamanho k é O(k).

Característica: Extremamente eficiente para funcionalidades de autocompletar e verificação ortográfica.

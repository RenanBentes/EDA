# Estruturas de Dados em C

Este repositório é uma coleção de implementações de estruturas de dados clássicas, desenvolvidas em linguagem C pura.

## Estruturas Implementadas

| Categoria | Estrutura | Arquivo |
|-----------|-----------|---------|
| **Estruturas Lineares** | Pilha (Stack) - LIFO | `Stack.c` |
| | Fila (Queue) - FIFO | `Queue.c` |
| **Árvores** | Árvore AVL - Auto-balanceada (Fator de Balanço) | `Trees/AVL.c` |
| | Árvore Rubro-Negra - Auto-balanceada (Cores) | `Trees/RB.c` |
| | Árvore B - Otimizada para disco | `Trees/B.c` |
| | Árvore Trie - Árvore de Prefixos (Autocompletar) | `Trees/Trie.c` |

## 🌟 Detalhes das Estruturas

### Pilha (`Stack.c`)
- **Política**: LIFO (Last-In, First-Out)
- **Operações Principais**: empilhar (push), desempilhar (pop), topo (peek)
- **Complexidade**: Todas as operações principais têm complexidade de tempo O(1)
- **Uso Ideal**: Gerenciamento de chamadas de função, algoritmos de backtracking, análise de expressões

### Fila (`Queue.c`)
- **Política**: FIFO (First-In, First-Out)
- **Operações Principais**: enfileirar (enqueue), desenfileirar (dequeue), frente (front)
- **Complexidade**: Todas as operações principais têm complexidade de tempo O(1)
- **Uso Ideal**: Gerenciamento de tarefas, buffers, algoritmos de busca em largura (BFS)

### Árvore AVL (`Trees/AVL.c`)
- **Tipo**: Árvore binária de busca auto-balanceada
- **Mecanismo**: Mantém o balanceamento através de rotações (simples e duplas) baseadas no "fator de balanceamento" de cada nó
- **Complexidade**: Busca, inserção e remoção em O(log n)
- **Característica**: É estritamente balanceada, o que pode resultar em mais rotações, mas garante buscas muito rápidas

### Árvore Rubro-Negra (`Trees/RB.c`)
- **Tipo**: Árvore binária de busca auto-balanceada
- **Mecanismo**: Usa 5 propriedades baseadas na coloração dos nós (Vermelho/Preto) para garantir um balanceamento aproximado
- **Complexidade**: Busca, inserção e remoção em O(log n)
- **Característica**: É menos estrita que a AVL, resultando em menos rotações na inserção/remoção, sendo uma escolha comum para implementações práticas.

### Árvore B (`Trees/B.c`)
- **Tipo**: Árvore de busca auto-balanceada de ordem m
- **Mecanismo**: Permite que os nós tenham um número variável de filhos (até m). Os dados são mantidos ordenados dentro de cada nó
- **Complexidade**: Busca, inserção e remoção em O(log n)
- **Característica**: Reduz a altura da árvore drasticamente, otimizando o número de acessos a disco. É a base de dados para a maioria dos sistemas de arquivos e bancos de dados

### Árvore Trie (`Trees/Trie.c`)
- **Tipo**: Árvore de prefixos
- **Mecanismo**: Cada nó representa um caractere e o caminho da raiz até um nó representa um prefixo
- **Complexidade**: Inserção e busca de uma palavra de tamanho k é O(k)
- **Característica**: Extremamente eficiente para funcionalidades de autocompletar e verificação ortográfica


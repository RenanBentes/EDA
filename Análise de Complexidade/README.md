# 📊 Análise de Complexidade de Estruturas de Dados

Uma ferramenta para análise comparativa de performance entre diferentes estruturas de dados em árvore: **Árvore AVL**, **Árvore Rubro-Negra** e **Árvore B** (com diferentes ordens).

## 🎯 Objetivos

Este projeto tem como objetivo:
- Medir e comparar o esforço computacional das operações de inserção e remoção
- Analisar o comportamento das estruturas com diferentes tamanhos de dados
- Gerar visualizações gráficas para análise da complexidade
- Fornecer dados empíricos para validar as complexidades teóricas

## 🌳 Estruturas Implementadas

### 1. **Árvore AVL**
- Árvore binária de busca auto-balanceada
- Fator de balanceamento: -1, 0, +1
- Operações: O(log n) no pior caso

### 2. **Árvore Rubro-Negra**
- Árvore binária de busca com coloração de nós
- Propriedades que garantem balanceamento
- Operações: O(log n) no pior caso

### 3. **Árvore B**
- Árvore m-ária balanceada
- Testadas com ordens: 1, 5 e 10
- Otimizada para armazenamento em disco
- Operações: O(log n) no pior caso

## 📁 Estrutura do Projeto

```
📦 projeto-analise-arvores/
├── 📄 main.c                    # Implementação das estruturas e testes
├── 📄 grafico.py               # Geração de gráficos com matplotlib
├── 📄 README.md                # Este arquivo
├── 📊 resultados_adicao.csv    # Dados dos testes de inserção
├── 📊 resultados_remocao.csv   # Dados dos testes de remoção
└── 📁 graficos/                # Diretório com gráficos gerados
    ├── 🖼️ insercao.png         # Gráfico de inserção
    └── 🖼️ remocao.png          # Gráfico de remoção
```

## 🚀 Como Executar

### Pré-requisitos
- **GCC** (compilador C)
- **Python 3.x**
- **matplotlib** e **pandas** (para gráficos)

### Instalação das dependências Python
```bash
pip install matplotlib pandas
```

### Executar a análise
```bash
# 1. Compilar o programa C
gcc -o main main.c

# 2. Executar os testes (pode demorar alguns minutos)
./main

# 3. Gerar os gráficos
python grafico.py
```

## 📈 Metodologia dos Testes

### Parâmetros de Teste
- **Tamanhos testados**: 100 a 10.000 elementos (incremento de 100)
- **Repetições**: 10 execuções por tamanho para obter média estatística
- **Dados**: Valores aleatórios entre 0 e 99.999
- **Métrica**: Contagem de operações básicas (comparações, atribuições, etc.)

### Operações Testadas
1. **Inserção**: Inserção de todos os elementos
2. **Remoção**: Remoção de 50% dos elementos inseridos

## 📊 Resultados

### Arquivos CSV Gerados
- `resultados_adicao.csv`: Esforço computacional para inserções
- `resultados_remocao.csv`: Esforço computacional para remoções

### Gráficos
Os gráficos são gerados em escala logarítmica para melhor visualização:
- **Eixo X**: Tamanho dos conjuntos de dados
- **Eixo Y**: Esforço computacional (escala logarítmica)

## 🔍 Análise dos Resultados

### Inserção
- **Árvore AVL**: Comportamento consistente com O(log n)
- **Árvore Rubro-Negra**: Performance similar à AVL
- **Árvore B**: Desempenho varia conforme a ordem

### Remoção
- **Complexidade**: Todas mantêm O(log n) teórico
- **Diferenças práticas**: Variações devido aos algoritmos de balanceamento

## 💡 Características Técnicas

### Medição de Complexidade
- **Contadores globais** para cada estrutura
- Incremento a cada operação básica
- Reset automático entre diferentes testes

### Implementação Robusta
- Gerenciamento completo de memória
- Tratamento de casos especiais
- Algoritmos clássicos de balanceamento

### Visualização Profissional
- Gráficos com cores distintas para cada estrutura
- Escala logarítmica para melhor análise
- Grade e formatação profissional

## 🎨 Customização

### Modificar Parâmetros de Teste
No arquivo `main.c`, altere:
```c
// Alterar range de tamanhos testados
for (int tamanho = 100; tamanho <= 10000; tamanho += 100)

// Alterar número de repetições
for (int teste = 0; teste < 10; teste++)
```

### Personalizar Gráficos
No arquivo `grafico.py`:
```python
# Alterar cores das estruturas
cores = {
    'AVL': '#F5AC31',
    'Rubro-Negra': '#7B0B03',
    'B1': '#2738F5',
    'B5': '#7F0060',
    'B10': '#517538'
}
```

## 📋 Formato dos Dados

### CSV de Resultados
```csv
Tamanho,AVL_Media,RB_Media,B1_Media,B5_Media,B10_Media
100,285.40,324.60,189.20,156.80,142.30
200,612.50,698.30,412.90,335.60,301.20
...
```

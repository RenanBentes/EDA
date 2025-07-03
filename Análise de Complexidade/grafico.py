import pandas as pd
import matplotlib.pyplot as plt
import os

# --- Cria o diretório para salvar os gráficos ---
output_dir = 'graficos'
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Carregar dados
try:
    df_insercao = pd.read_csv('resultados_adicao.csv')
    df_remocao = pd.read_csv('resultados_remocao.csv')
except FileNotFoundError:
    print(
        "Erro: Verifique se os arquivos 'resultados_adicao.csv' e 'resultados_remocao.csv' estão na mesma pasta que o script.")
    exit()

tamanhos = df_insercao['Tamanho']

# Dados de inserção
avl_insert = df_insercao['AVL_Media']
rb_insert = df_insercao['RB_Media']
btree1_insert = df_insercao['B1_Media']
btree5_insert = df_insercao['B5_Media']
btree10_insert = df_insercao['B10_Media']

# Dados de remoção
avl_remove = df_remocao['AVL_Media']
rb_remove = df_remocao['RB_Media']
btree1_remove = df_remocao['B1_Media']
btree5_remove = df_remocao['B5_Media']
btree10_remove = df_remocao['B10_Media']

# Cores
cores = {
    'AVL': '#F5AC31',
    'Rubro-Negra': '#7B0B03',
    'B1': '#2738F5',
    'B5': '#7F0060',
    'B10': '#517538'
}


# Função para criar gráfico
def criar_grafico(dados, titulo, nome_arquivo):
    plt.figure(figsize=(12, 8))

    # Plotar
    for estrutura, (nome_completo, valores, cor) in dados.items():
        plt.semilogy(tamanhos, valores,
                     label=nome_completo,
                     color=cor,
                     linewidth=2,
                     linestyle='-',
                     solid_capstyle='round')

    # Eixos
    plt.xlabel('Tamanho dos Conjuntos', fontsize=14, fontweight='bold')
    plt.ylabel('Esforço Computacional (Escala Logarítmica)', fontsize=14, fontweight='bold')

    plt.title(titulo, fontsize=16, fontweight='bold', pad=20)

    # Linhas de grade
    plt.grid(True, which="major", ls="-", alpha=0.6, color='#4F4F4F', linewidth=0.8)
    plt.grid(True, which="minor", ls=":", alpha=0.4, color='#4F4F4F', linewidth=0.5)

    # Legenda
    plt.legend(loc='upper left', fontsize=11, frameon=True,
               facecolor='white', edgecolor='black', shadow=True, framealpha=0.95)
    # Aparência
    ax = plt.gca()
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['left'].set_linewidth(1.2)
    ax.spines['bottom'].set_linewidth(1.2)
    ax.set_axisbelow(True)

    # Ajustes
    plt.tight_layout()
    # Salva o arquivo no diretório de output
    caminho_completo = os.path.join(output_dir, nome_arquivo)
    plt.savefig(caminho_completo, dpi=300, bbox_inches='tight',
                facecolor='white', edgecolor='none')
    print(f"Gráfico salvo em: {caminho_completo}")
    plt.show()


# Preparar dados para inserção
dados_insercao = {
    'AVL': ('Árvore AVL', avl_insert, cores['AVL']),
    'RB': ('Árvore Rubro-Negra', rb_insert, cores['Rubro-Negra']),
    'B1': ('Árvore B (ordem 1)', btree1_insert, cores['B1']),
    'B5': ('Árvore B (ordem 5)', btree5_insert, cores['B5']),
    'B10': ('Árvore B (ordem 10)', btree10_insert, cores['B10'])
}

# Preparar dados para remoção
dados_remocao = {
    'AVL': ('Árvore AVL', avl_remove, cores['AVL']),
    'RB': ('Árvore Rubro-Negra', rb_remove, cores['Rubro-Negra']),
    'B1': ('Árvore B (ordem 1)', btree1_remove, cores['B1']),
    'B5': ('Árvore B (ordem 5)', btree5_remove, cores['B5']),
    'B10': ('Árvore B (ordem 10)', btree10_remove, cores['B10'])
}

# Criar gráficos
print("✅ Gerando gráficos...")

criar_grafico(dados_insercao,
              'Performance das Operações de Inserção',
              'insercao.png')

criar_grafico(dados_remocao,
              'Performance das Operações de Remoção',
              'remocao.png')

print("✅ Gráficos gerados com sucesso!")

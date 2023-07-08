#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_CLASSES 6

double calcularMedia(double *amostra, int numElementos) {
    double soma = 0.0;

    for (int i = 0; i < numElementos; i++) {
        soma += amostra[i];
    }

    return soma / numElementos;
}

double calcularMediana(double *amostra, int numElementos) {
    if (numElementos % 2 == 0) {
        int meio1 = numElementos / 2 - 1;
        int meio2 = numElementos / 2;
        return (amostra[meio1] + amostra[meio2]) / 2.0;
    } else {
        int meio = numElementos / 2;
        return amostra[meio];
    }
}

double calcularModa(double *amostra, int numElementos) {
    int frequenciaMaxima = 0;
    double moda = 0.0;

    for (int i = 0; i < numElementos; i++) {
        int frequencia = 1;

        for (int j = i + 1; j < numElementos; j++) {
            if (amostra[j] == amostra[i]) {
                frequencia++;
            }
        }

        if (frequencia > frequenciaMaxima) {
            frequenciaMaxima = frequencia;
            moda = amostra[i];
        }
    }

    return moda;
}

double calcularPontoMedio(double *amostra, int numElementos) {
    //Se o vetor estiver ordenado, se não dara erro
    return (amostra[0] + amostra[numElementos - 1]) / 2.0;
}

int comparar(const void* a, const void* b) {
    double x = *(const double*)a;
    double y = *(const double*)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

double calcularMediaHarmonica(double velocidadeAB, double velocidadeBC, double velocidadeCA) {
    double inversoAB = 1.0 / velocidadeAB;
    double inversoBC = 1.0 / velocidadeBC;
    double inversoCA = 1.0 / velocidadeCA;

    double somaInversos = inversoAB + inversoBC + inversoCA;
    double velocidadeMedia = 3.0 / somaInversos;

    return velocidadeMedia;
}

double calcularMediaGeometrica(double* taxas, int numTaxas) {
    double produtoTaxas = 1.0;

    for (int i = 0; i < numTaxas; i++) {
        produtoTaxas *= taxas[i];
    }

    double taxaMediaVariacao = pow(produtoTaxas, 1.0 / numTaxas) - 1.0;

    return taxaMediaVariacao;
}

double calcularMediaQuadratica(double* valores, int numValores) {
    double somaQuadrados = 0.0;

    for (int i = 0; i < numValores; i++) {
        somaQuadrados += pow(valores[i], 2.0);
    }

    double mediaQuadratica = sqrt(somaQuadrados / numValores);

    return mediaQuadratica;
}

void calcularEstatisticas(double *amostra, int numElementos) {
    // Ordenar a amostra em ordem crescente
    qsort(amostra, numElementos, sizeof(double), comparar);

    // Calcular a média
    double media = calcularMedia(amostra, numElementos);

    // Calcular a mediana
    double mediana = calcularMediana(amostra, numElementos);

    // Calcular a moda
    double moda = calcularModa(amostra, numElementos);

    // Calcular o ponto médio
    double pontoMedio = calcularPontoMedio(amostra, numElementos);

    // Imprimir as estatísticas
    printf("Media: %.2f\n", media);
    printf("Mediana: %.2f\n", mediana);
    printf("Moda: %.2f\n", moda);
    printf("Ponto Medio: %.2f\n", pontoMedio);
}

void construirDistribuicaoFrequencia(double* teste, int numElementos) {
    double menorValor = teste[0];
    double maiorValor = teste[0];

    // Encontrar o menor e maior valor na amostra
    for (int i = 1; i < numElementos; i++) {
        if (teste[i] < menorValor)
            menorValor = teste[i];
        if (teste[i] > maiorValor)
            maiorValor = teste[i];
    }

    // Calcular a amplitude total da distribuição
    double amplitudeTotal = maiorValor - menorValor;

    // Calcular a amplitude de classe
    double amplitudeClasse = amplitudeTotal / NUM_CLASSES;

    // Inicializar os limites das classes
    double limitesInferiores[NUM_CLASSES];
    double limitesSuperiores[NUM_CLASSES];

    for (int i = 0; i < NUM_CLASSES; i++) {
        limitesInferiores[i] = menorValor + (i * amplitudeClasse);
        limitesSuperiores[i] = limitesInferiores[i] + amplitudeClasse;
    }

    // Inicializar as frequências das classes
    int frequencias[NUM_CLASSES] = { 0 };

    // Contar as frequências das classes
    for (int i = 0; i < numElementos; i++) {
        for (int j = 0; j < NUM_CLASSES; j++) {
            if (teste[i] >= limitesInferiores[j] && teste[i] < limitesSuperiores[j]) {
                frequencias[j]++;
                break;
            }
        }
    }

    // Calcular as frequências relativas e acumuladas
    double frequenciasRelativas[NUM_CLASSES];
    double frequenciasAcumuladas[NUM_CLASSES];

    int somaFrequencias = 0;
    for (int i = 0; i < NUM_CLASSES; i++) {
        somaFrequencias += frequencias[i];
    }

    for (int i = 0; i < NUM_CLASSES; i++) {
        frequenciasRelativas[i] = (double)frequencias[i] / somaFrequencias;
        frequenciasAcumuladas[i] = (double)somaFrequencias / numElementos;
        somaFrequencias -= frequencias[i];
    }

    // Imprimir a distribuição de frequência
    printf("Classes\t\tFrequencia\tFrequencia Relativa\tFrequencia Acumulada\n");
    for (int i = 0; i < NUM_CLASSES; i++) {
        printf("%.2f - %.2f\t%d\t\t%.4f\t\t\t%.4f\n", limitesInferiores[i], limitesSuperiores[i], frequencias[i],
               frequenciasRelativas[i], frequenciasAcumuladas[i]);
    }
}

void calcularInformacoesDistribuicao(int* limitesInferiores, int* limitesSuperiores, int* frequencias, int numClasses) {
    int amplitudeClasse[numClasses];
    int pontosMedios[numClasses];
    float fronteirasInferiores[numClasses];
    float fronteirasSuperiores[numClasses];

    for (int i = 0; i < numClasses; i++) {
        amplitudeClasse[i] = (limitesSuperiores[i] - limitesInferiores[i]);
        pontosMedios[i] = (limitesSuperiores[i] + limitesInferiores[i]) / 2;
        fronteirasInferiores[i] = limitesInferiores[i]+0.5;
        fronteirasSuperiores[i] = limitesSuperiores[i]+0.5;
    }

    printf("\nAmplitude de Classe:\n");
    for (int i = 0; i < numClasses; i++) {
        printf("%d - %d: %d\n", limitesInferiores[i], limitesSuperiores[i], amplitudeClasse[i]);
    }

    printf("\nPontos Medios das Classes:\n");
    for (int i = 0; i < numClasses; i++) {
        printf("%d - %d: %d\n", limitesInferiores[i], limitesSuperiores[i], pontosMedios[i]);
    }
    printf("\n");
    printf("\nFronteiras das Classes:\n");
    for (int i = 0; i < numClasses; i++) {
        printf("%.1f - %.1f \n", fronteirasInferiores[i], fronteirasSuperiores[i]);
    }
    printf("\n");
}

double calcularAmplitude(double* amostra, int numElementos) {
    double min = amostra[0];
    double max = amostra[0];

    for (int i = 1; i < numElementos; i++) {
        if (amostra[i] < min) {
            min = amostra[i];
        }
        if (amostra[i] > max) {
            max = amostra[i];
        }
    }

    return max - min;
}

double calcularDesvioMedio(double* amostra, int numElementos) {
    double somaDesvios = 0.0;

    for (int i = 0; i < numElementos; i++) {
        somaDesvios += fabs(amostra[i] - amostra[0]);
    }

    return somaDesvios / numElementos;
}

double calcularDesvioPadrao(double* amostra, int numElementos) {
    double somaQuadradosDesvios = 0.0;
    double media = amostra[0];

    for (int i = 1; i < numElementos; i++) {
        somaQuadradosDesvios += pow(amostra[i] - media, 2.0);
    }

    double variancia = somaQuadradosDesvios / numElementos;

    return sqrt(variancia);
}

double calcularVariancia(double* amostra, int numElementos) {
    double somaQuadradosDesvios = 0.0;
    double media = amostra[0];

    for (int i = 1; i < numElementos; i++) {
        somaQuadradosDesvios += pow(amostra[i] - media, 2.0);
    }

    return somaQuadradosDesvios / numElementos;
}

double calcularCoeficienteVariacao(double* amostra, int numElementos) {
    double media = amostra[0];
    double desvioPadrao = calcularDesvioPadrao(amostra, numElementos);

    return (desvioPadrao / media) * 100;
}

int main() {
    int opcao;
    printf("Selecione uma opcao:\n");
    printf("1 - Analise de uma Distribuicao de Frequencia\n2 - Construcao de distribuicao de frequencia\n3 - Medidas de Tendencia comuns\n");
    printf("4 - Media Harmonica\n5 - Media Geometrica\n6 - Media Quadratica(RMS)\n");
    printf("7 - Medidas de Variacao\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            int limitesInferiores[] = {90, 100, 110, 120, 130, 140, 150};
            int limitesSuperiores[] = {99, 109, 119, 129, 139, 149, 159};
            int frequencias[] = {1, 4, 17, 12, 5, 0, 1};
            int numClasses = sizeof(frequencias) / sizeof(frequencias[0]);
            calcularInformacoesDistribuicao(limitesInferiores, limitesSuperiores, frequencias, numClasses);
            break;
        }

        case 2: {
            double teste[] = {
                    3.53, 3.57, 3.89, 3.78, 3.99, 4.05, 3.98, 4.00, 3.60, 3.28,
                    3.76, 4.01, 4.03, 4.00, 3.46, 3.50, 3.57, 3.39, 3.78, 3.69,
                    4.05, 3.78, 4.00, 3.30, 3.88, 3.76, 4.21, 4.23, 4.00, 3.56,
                    3.53, 3.47, 3.89, 3.58, 3.90, 4.00, 3.98, 4.00, 3.64, 3.28,
                    3.75, 4.21, 4.03, 4.00, 3.46, 3.55, 3.27, 3.84, 3.78, 3.99,
                    4.01, 3.48, 4.05, 3.60, 3.22, 3.70, 4.01, 4.05, 4.04, 3.46
            };
            int numElementos = sizeof(teste) / sizeof(teste[0]);
            construirDistribuicaoFrequencia(teste, numElementos);
            break;
        }

        case 3: {
            double amostraA[] = {6.5, 6.6, 6.7, 6.8, 7.1, 7.3, 7.4, 7.7, 7.7, 7.7};
            int numElementosA = sizeof(amostraA) / sizeof(amostraA[0]);
            double amostraB[] = {4.2, 5.4, 5.8, 6.2, 6.7, 7.7, 7.7, 8.5, 9.3, 10.0};
            int numElementosB = sizeof(amostraB) / sizeof(amostraB[0]);
            printf("Amostra A:\n");
            calcularEstatisticas(amostraA, numElementosA);
            printf("\n");
            printf("Amostra B:\n");
            calcularEstatisticas(amostraB, numElementosB);
            printf("\n");

            break;
        }

        case 4:{
            double velocidadeAB = 30.0;  // Velocidade entre A e B em km/h
            double velocidadeBC = 40.0;  // Velocidade entre B e C em km/h
            double velocidadeCA = 50.0;  // Velocidade entre C e A em km/h
            double velocidadeMedia = calcularMediaHarmonica(velocidadeAB, velocidadeBC, velocidadeCA);
            printf("A velocidade media em todo o trecho percorrido e: %.2f km/h\n", velocidadeMedia);
            break;
        }

        case 5:{
            double taxas[] = { 0.10, 0.08, 0.09, 0.12, 0.07 };
            int numTaxas = sizeof(taxas) / sizeof(taxas[0]);
            double taxaMediaVariacao = calcularMediaGeometrica(taxas, numTaxas);
            printf("A taxa media de variacao dos juros e: %.2f\n", taxaMediaVariacao);
            break;
        }

        case 6:{
            double valores[] = { 110.0, 0.0, -60.0, 12.0 };
            int numValores = sizeof(valores) / sizeof(valores[0]);
            double rms = calcularMediaQuadratica(valores, numValores);
            printf("A RMS dos valores da medicao de energia e: %.2f volts\n", rms);
            break;

        }

        case 7:{
            double amostraA[] = { 6.5, 6.6, 6.7, 6.8, 7.1, 7.3, 7.4, 7.7, 7.7, 7.7 };
            int numElementosA = sizeof(amostraA) / sizeof(amostraA[0]);
            double amplitudeA = calcularAmplitude(amostraA, numElementosA);
            double desvioMedioA = calcularDesvioMedio(amostraA, numElementosA);
            double desvioPadraoA = calcularDesvioPadrao(amostraA, numElementosA);
            double varianciaA = calcularVariancia(amostraA, numElementosA);
            double coeficienteVariacaoA = calcularCoeficienteVariacao(amostraA, numElementosA);
            printf("Amostra:\n");
            printf("Amplitude: %.2f\n", amplitudeA);
            printf("Desvio Medio: %.2f\n", desvioMedioA);
            printf("Desvio Padrao: %.2f\n", desvioPadraoA);
            printf("Variancia: %.2f\n", varianciaA);
            printf("Coeficiente de Variacao: %.2f%%\n", coeficienteVariacaoA);
            printf("\n");
            break;
        }

        default:
            printf("Opcao errada\n");
            break;
    }

    return 0;
}

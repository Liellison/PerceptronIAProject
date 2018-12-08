#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAXAAPRENDIZAGEM 0.001
#define MAXGERACOES 100

int calculoSaida(float pesos[],float entrada){
    float sum = entrada * pesos[0] + pesos[1];
    return (sum >= 0) ? 1 : -1;
}

int main (int argc,char *argv[]){
    float entrada[21], pesos[2],globalError, localError;
    int i, geracoes, pContador, p, saidaDesejada[21], saida;

    FILE *conjuntoDeTreinamento;
    if((conjuntoDeTreinamento = fopen("conjuntodetreinamento.txt", "r"))== NULL){
        printf("Não consegui abrir o Conjunto de Treinamento");
        exit(1);
    }
    i=0;
    while(fscanf(conjuntoDeTreinamento, "%d %d", &entrada[i], &saidaDesejada[i]) != EOF){
       if (saidaDesejada[i] == 0) {
            saidaDesejada[i] = -1;
        }
       i++; 
    }

    pContador = i;

    pesos[0] = 1;
    pesos[1] = 1;

    geracoes = 0;

    do{
        geracoes++;
        globalError = 0;
        for(p=0; p < pContador; p++){
            saida = calculoSaida(pesos, entrada[p]);

            localError = saidaDesejada[p] - saida;
            pesos[0] += TAXAAPRENDIZAGEM * localError * entrada[p];
            pesos[1] += TAXAAPRENDIZAGEM * localError;

            globalError += (localError * localError);

            printf("Geracao %d : RMSE = %.4f\n", geracoes, sqrt(globalError/pContador));
        }
    } while(globalError !=0 && geracoes<=MAXGERACOES);

    printf("\nPesos Finais: %.2f*x + %.2f*y + %.2f = 0\n", pesos[0], pesos[1], pesos[2]);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAXAAPRENDIZAGEM 0.0000000000000001
#define MAXEPOCAS 1000000

int calculoSaida(float pesos[],float entrada){
    float sum = entrada * pesos[1] + pesos[0];
    return sum;
}

int main (int argc,char *argv[]){
    float entrada[21], pesos[2],globalError, localError;
    int i, epocas, pContador, p, saidaDesejada[21], saida;

    FILE *conjuntoDeTreinamento;
    if((conjuntoDeTreinamento = fopen("conjuntodetreinamento.txt", "r"))== NULL){
        printf("Não consegui abrir o Conjunto de Treinamento");
        exit(1);
    }
    i=0;
    while(fscanf(conjuntoDeTreinamento, "%f %f", &entrada[i], &saidaDesejada[i]) != EOF){
       i++; 
    }

    pContador = i;

    pesos[0] = 1;
    pesos[1] = 1;

    epocas = 0;

    do{
        epocas++;
        globalError = 0;
        for(p=0; p < pContador; p++){
            saida = calculoSaida(pesos, entrada[p]);

            localError = saidaDesejada[p] - saida;
            pesos[1] += TAXAAPRENDIZAGEM * localError * entrada[p];
            pesos[0] += TAXAAPRENDIZAGEM * localError;

            globalError += (localError * localError);
        }
    } while(globalError !=0 && epocas<=MAXEPOCAS);

    printf("\nPesos Finais: %f*b + %f*x \n", pesos[0], pesos[1]);
    return 0;
}
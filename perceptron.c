#include <stdio.h>
#include <stdlib.h>

int main (int argc,char *argv[]){
    int i, entrada[21], saidaDesejada[21];
    FILE *conjuntoDeTreinamento;
    if((conjuntoDeTreinamento = fopen("conjuntodetreinamento.txt", "r"))== NULL){
        printf("Não consegui abrir o Conjunto de Treinamento");
        exit(1);
    }
    i=0;
    while(fscanf(conjuntoDeTreinamento, "%d %d", &entrada[i], &saidaDesejada[i]) != EOF){
       i++; 
    }

    printf("%d", saidaDesejada[0]);

    return 0;
}
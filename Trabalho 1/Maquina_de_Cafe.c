//Maquina de Cafe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int a1, a2, a3;
    int tempo1, tempo2, tempo3;
    int melhor, qnt_melhor = 0;
    char saida[12] = ""; //para conseguir detectar quando o OU

    //entrada e verifica��o padr�o.
    do{
        printf("Insira quantas pessoas trabalham no ANDAR 1: ");
        scanf("%d", &a1);
        if(a1 < 0 || a1 > 1000) printf("O numero de pessoas precisa estar entre 0 e 1000!\n");
    } while(a1 < 0 || a1 > 1000);

    do{
        printf("Insira quantas pessoas trabalham no ANDAR 2: ");
        scanf("%d", &a2);
        if(a2 < 0 || a2 > 1000) printf("O numero de pessoas precisa estar entre 0 e 1000!\n");
    } while(a2 < 0 || a2 > 1000);

    do{
        printf("Insira quantas pessoas trabalham no ANDAR 3: ");
        scanf("%d", &a3);
        if(a3 < 0 || a3 > 1000) printf("O numero de pessoas precisa estar entre 0 e 1000!\n");
    } while(a3 < 0 || a3 > 1000);

    // calcula o tempo que levaria em todos os cen�rios
    // exemplo:
    // A maquina no andar 1 significa que as pessoas do andar 2 levam 2 minutos para subir e descer.
    // as pessoas do andar 3 levam 4 minutos.
    tempo1 = a2 * 2 + a3 * 4;
    tempo2 = a1 * 2 + a3 * 2;
    tempo3 = a1 * 4 + a2 * 2;

    // Compara os tempos
    melhor = tempo1;
    if(melhor > tempo2) melhor = tempo2;
    if(melhor > tempo3) melhor = tempo3;

    //Parte da sa�da (mostrar corretamente o plural e o OU)
    if(melhor == tempo1) strcpy(saida, "1");

    if(melhor == tempo2) {
        if(melhor == tempo1) strcat(saida, " OU 2"); //se j� existir um valor antes, usar o OU
        else strcpy(saida, "2");
    }
    if(melhor == tempo3) {
        if(melhor == tempo2 || melhor == tempo1) strcat(saida, " OU 3");
        else strcpy(saida, "3");
    }

    if(tempo1==0&&tempo2==0&&tempo3==0) {
        printf("\nNenhuma maquina necessaria!");
    }
    else {
        printf("Tempo: %d\n", melhor);
        if(strlen(saida) == 1) //Se o valor da sa�da for "1", "2" ou "3", printar o resultado no singular.
            printf("Maquina localizada no andar: ");
        else printf("Maquina localizada nos andares: ");
    

    printf("%s", saida); //a sa�da � concatenada ao printf (n�o foi usado \n, portanto a linha segue a mesma).
    }

    printf("\n\n");
}

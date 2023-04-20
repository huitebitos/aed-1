//Azulejos
#include <stdio.h>
#include <stdlib.h>

int main(){
    int azulejos, a, b;
    int pintados;

    do{
        //checagem e inicializa��o
        pintados = 0;
        do{
            printf(" -> Insira a quantidade de azulejos: ");
            scanf("%d", &azulejos);
            if((azulejos < 3 || azulejos > 10000) && azulejos != 0)
                printf("ERRO! A quantidade de azulejos deve estar entre 3 e 10000!\n");
        } while((azulejos < 3 || azulejos > 10000) && azulejos != 0);

        //logica aplicada: se a quantidade de azulejos for 0, nao checar os outros valores, ja que a itera�ao sera pulada
        do{
            printf(" -> Insira A: ");
            scanf("%d", &a);
            if((a < 2 || a == 0) && azulejos != 0) //para A poder ser 0, azulejos tambem precisa ser 0.
                printf("ERRO! A precisa ser maior ou igual a 2\n");
        } while((a < 2 || a == 0) && azulejos != 0);

        do{
            printf(" -> Insira B: ");
            scanf("%d", &b);
            if(b > azulejos || (b == 0 && azulejos != 0)) //se b for 0, azulejos precis ser tambem
                printf("ERRO! B precisa ser menor ou igual a quantidade de azulejos E diferente de 0\n");
        } while(b > azulejos || (b == 0 && azulejos != 0));

        if(azulejos == 0 && a == 0 && b == 0) //condi��o de parada.
            break;
        if(azulejos == 0) { //se s� a quantidade de azulejos for 0, pular a iteracao
            printf("[SAIDA] Azulejos Pintados: 0\n\n");
            continue;
        }

        for (int i = 1; i <= azulejos; i++){
            if (i % a == 0 || i % b == 0) pintados++; //se for m�ltiplo de A ou B.
        }

        printf("[SAIDA] Azulejos Pintados: %d\n\n", pintados);
    } while (a != 0 || b != 0 || azulejos != 0); // A condi��o de parada � N = A = B = 0
}

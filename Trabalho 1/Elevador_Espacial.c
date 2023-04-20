//Elevador Espacial
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int andar, fila;
    int c1, d1, u1, c2, d2, u2, u3;
    int novoAndar = 0;

    do {
        printf("\nInsira um andar: ");
        scanf("%d", &andar);
        if(andar > 1000000 || andar < 1) printf("O valor precisa estar entre 1 e 1.000.000!");
    } while (andar > 1000000 || andar < 1);
    
    fila = andar;
    //executar enquanto tiver valores a serem somados.
    while (fila > 0) {
        novoAndar++;
        //decompor o número
        u1 = (novoAndar % 10);
        d1 = (novoAndar % 100      - novoAndar % 10)      / 10;
        c1 = (novoAndar % 1000     - novoAndar % 100)     / 100;
        u2 = (novoAndar % 10000    - novoAndar % 1000)    / 1000;
        d2 = (novoAndar % 100000   - novoAndar % 10000)   / 10000;
        c2 = (novoAndar % 1000000  - novoAndar % 100000)  / 100000;
        u3 = (novoAndar % 10000000 - novoAndar % 1000000) / 1000000;
        // Se alguma das condições bater (ter 4 ou 13), adiciona 1 na fila.
        if(u1 == 4 || // 0 000 004
           d1 == 4 || // 0 000 040
           c1 == 4 || // 0 000 400
           u2 == 4 || // 0 004 000
           d2 == 4 || // 0 040 000
           c2 == 4 || // 0 400 000
           ((u3 == 1) && (c2 == 3)) || // 1 300 000
           ((c2 == 1) && (d2 == 3)) || // 0 130 000
           ((d2 == 1) && (u2 == 3)) || // 0 013 000
           ((u2 == 1) && (c1 == 3)) || // 0 001 300
           ((c1 == 1) && (d1 == 3)) || // 0 000 130
           ((d1 == 1) && (u1 == 3))) { // 0 000 013
                fila++;
        }

        fila--; //depois de adicionar, subtrai um da fila.
    }
    printf("Novo numero: %d\n", novoAndar);
}

/*  Resolva beecrowd | 2358 (Bact�ria II)

- Considere um caso de teste para cada execu��o;

- Os dados de execu��o dever�o ser recebidos via argumento do programa
  na linha de comando;

- Caso haja mais de uma solu��o, imprima todas elas, sem repeticoes;

- Aten��o, a sua solu��o n�o precisa necessariamente rodar tamb�m no
  ambiente beecrowd. L� exige-se o uso de t�cnicas avan�adas de organiza��o
  de dados para a constru��o de uma solu��o que atenda aos testes do
  ambiente beecrowd.



    Exemplos de execu��es

    app 3 GCTTTCGACGAT GATCGAGCTTCGAA GGTCTAGCTAAT TCGA
    SAIDA_2 = Quantidade de bacterias: 3
    SAIDA_3 = Bacteria: GCTTTCGACGAT
    SAIDA_3 = Bacteria: GATCGAGCTTCGAA
    SAIDA_3 = Bacteria: GGTCTAGCTAAT
    SAIDA_4 = Virus: TCGA
    SAIDA_5 = Bacteria infectada: GCTT
    SAIDA_5 = Bacteria infectada: GAGCTA
    SAIDA_5 = Bacteria infectada: GGTCTAGCTAAT
    SAIDA_6 = DNA resultante: GCT


    app 5 AGCT TGC CGCAA TGTC ATGTTC T
    SAIDA_2 = Quantidade de bacterias: 5
    SAIDA_3 = Bacteria: AGCT
    SAIDA_3 = Bacteria: TGC
    SAIDA_3 = Bacteria: CGCAA
    SAIDA_3 = Bacteria: TGTC
    SAIDA_3 = Bacteria: ATGTTC
    SAIDA_4 = Virus: T
    SAIDA_5 = Bacteria infectada: AGC
    SAIDA_5 = Bacteria infectada: GC
    SAIDA_5 = Bacteria infectada: CGCAA
    SAIDA_5 = Bacteria infectada: GC
    SAIDA_5 = Bacteria infectada: AGC
    SAIDA_6 = DNA resultante: GC


    app 2 AAAACGTGAGTGTAT AAAATGTAGGTGAAAA T
    SAIDA_2 = Quantidade de bacterias: 2
    SAIDA_3 = Bacteria: AAAACGTGAGTGTAT
    SAIDA_3 = Bacteria: AAAATGTAGGTGAAAA
    SAIDA_4 = Virus: T
    SAIDA_5 = Bacteria infectada: AAAACGGAGGA
    SAIDA_5 = Bacteria infectada: AAAAGAGGGAAAA
    SAIDA_6 = DNA resultante: AAAA
    SAIDA_6 = DNA resultante: GAGG

    app 2 AGTC AG
    SAIDA_1 = Quantidade invalida de argumentos!
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIMITE_BACTERIAS 20
#define COMPR_BACTERIAS 1000
#define COMPR_VIRUS 1000

#define SAIDA_1 "\nSAIDA_1 = Quantidade invalida de argumentos!"
#define SAIDA_2 "\nSAIDA_2 = Quantidade de bacterias: %d"
#define SAIDA_3 "\nSAIDA_3 = Bacteria: %s"
#define SAIDA_4 "\nSAIDA_4 = Virus: %s"
#define SAIDA_5 "\nSAIDA_5 = Bacteria infectada: %s"
#define SAIDA_6 "\nSAIDA_6 = DNA resultante: %s"

int getBiggestLength(char arr[LIMITE_BACTERIAS][COMPR_BACTERIAS], int len) {
    int length = 0; //inicializa com um valor pequeno
    for (int i = 0; i < len; i++)
        length = strlen(arr[i]) > length ? strlen(arr[i]) : length;
    
    return length;
    
}

void separar(char *dest, char *texto, char *remover)
{
    char *rem = strstr(texto, remover);
    char *finish = rem + strlen(remover);
    char start[50];
    size_t tamanho = strlen(finish) + strlen(remover) - 1;
    tamanho = strlen(texto) - tamanho - 1;
    strncpy(start, texto, tamanho);
    start[tamanho] = '\0';
    strcat(start, finish);
    strcpy(dest, start);
}

int existsInArray(char *texto, char array[LIMITE_BACTERIAS][COMPR_BACTERIAS], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if (!strcmp(texto, array[i])) //são iguais
            return 1;
    }
    
    return 0; //não existe
}

int findCommon(char* t1, char* t2, char substrings[LIMITE_BACTERIAS][COMPR_BACTERIAS], int *index){
    size_t x = strlen(t1);
    size_t y = strlen(t2);
    
    //criar uma array[x+1][y+1] para memorizar
    int memoria[x+1][y+1];
    int change = 0; //quantidade de letras modificadas

    for (int i = 0; i <= x; i++) {    //é menor igual porque o tamanho é x+1 e y+1.
        for (int j = 0; j <= y; j++){
            if (i == 0 || j == 0)
                memoria[i][j] = 0;
            else if (t1[i-1] == t2[j-1]) {//o -1 é necessário pois o index 0 precisa ser incluso
                memoria[i][j] = 1 + memoria[i-1][j-1];
                change = memoria[i][j] > change ? memoria[i][j] : change;
            }
            else memoria[i][j] = 0;
        }
    }
    
    char substring[COMPR_BACTERIAS] = "";
    for (int i = 0; i <= x; i++) {    
        for (int j = 0; j <= y; j++){
              if(memoria[i][j] > 1) {
                if (memoria[i][j] == 2) strncat(substring, &t1[i-2], 1);
                strncat(substring, &t1[i-1], 1);
                if (memoria[i+1][j+1] != memoria[i][j] + 1 || j == y){ //substring em comum acabou 
                    strcat(substring, "\0");
                    if (!existsInArray(substring, substrings, *index)) //evitar que a mesma substring se repita
                        strcpy(substrings[(*index)++], substring);
                    strcpy(substring, "");
                }
            }
        }
    }
    
    return change;
}

int main(int argc, char *argv[])
{
    int nBacterias;
    char BACTERIAS[LIMITE_BACTERIAS][COMPR_BACTERIAS];
    char VIRUS[COMPR_VIRUS];

    char BACTERIAS_INFECTADAS[LIMITE_BACTERIAS][COMPR_BACTERIAS];

    char SUBSTRINGS[LIMITE_BACTERIAS][COMPR_BACTERIAS];
    int SUBSIZE = 0; //tamanho do vetor de substrings

    char DNAS[LIMITE_BACTERIAS][COMPR_BACTERIAS];
    int DNA_SIZE = 0;

    if (argc < 4)
        printf(SAIDA_1);
    else
    {
        nBacterias = atoi(argv[1]);
        if (argc != nBacterias + 3)
            printf(SAIDA_1);
        else
        {
            // inicialização
            for (int i = 0; i < nBacterias; i++) // transferir do argv para a array
                strcpy(BACTERIAS[i], argv[2 + i]);
            strcpy(VIRUS, argv[nBacterias + 2]);
          
            // remoção
            for (int i = 0; i < nBacterias; i++)
            {
                char temp[COMPR_BACTERIAS];
                strcpy(temp, BACTERIAS[i]);
                while (strstr(temp, VIRUS) != NULL)
                    separar(temp, temp, VIRUS); // remover o virus da bacteria até não for mais possível
                strcpy(BACTERIAS_INFECTADAS[i], temp);
            }
       
            //cria a array de substrings      
            for (int i = 0; i < nBacterias - 1; i++)
                for (int j = i + 1; j < nBacterias; j++)
                    findCommon(BACTERIAS_INFECTADAS[i], BACTERIAS_INFECTADAS[j], SUBSTRINGS, &SUBSIZE);

            // loopa o vetor de BACTERIAS e compara com o das substrings
            if (nBacterias > 2)
                for (int i = 0; i < nBacterias; i++)
                    for (int j = 0; j < SUBSIZE; j++)
                    {
                        int c = findCommon(BACTERIAS_INFECTADAS[i], SUBSTRINGS[j], SUBSTRINGS, &SUBSIZE);
                        if (c <= 1 || c != strlen(SUBSTRINGS[j])) // se houver uma letra ou zero ou se a substring se dividiu em mais SUBSTRINGS, zera o valor
                            strcpy(SUBSTRINGS[j], "");
                    }

            //cria um array com os DNAS (substrings) de maior tamanho
            int len = getBiggestLength(SUBSTRINGS, SUBSIZE);
            for (int i = 0; i < SUBSIZE; i++)
                if (strlen(SUBSTRINGS[i]) == len)
                    strcpy(DNAS[DNA_SIZE++], SUBSTRINGS[i]);
             

            //saida
            printf(SAIDA_2, nBacterias);
            for (int i = 0; i < nBacterias; i++)
                printf(SAIDA_3, BACTERIAS[i]);
            printf(SAIDA_4, VIRUS);
            for (int i = 0; i < nBacterias; i++)
                printf(SAIDA_5, BACTERIAS_INFECTADAS[i]);
            for (int i = 0; i < DNA_SIZE; i++)
                printf(SAIDA_6, DNAS[i]);

        }
    }
    return 0;
}

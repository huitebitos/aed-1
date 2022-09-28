/*
 ______     __         __  __     __   __     ______     ______
/\  __ \   /\ \       /\ \/\ \   /\ "-.\ \   /\  __ \   /\  ___\
\ \  __ \  \ \ \____  \ \ \_\ \  \ \ \-.  \  \ \ \/\ \  \ \___  \
 \ \_\ \_\  \ \_____\  \ \_____\  \ \_\\"\_\  \ \_____\  \/\_____\
  \/_/\/_/   \/_____/   \/_____/   \/_/ \/_/   \/_____/   \/_____/

                    * Emmerson Badocco
                   * Gustavo Kermaunar
                     * Gustavo Martins
                        * Victor Keony
                    * Vinícius Schautz



*/

/*
    //   ) ) //   ) )  //   ) )
   //   / / //___/ /  ((
  //   / / / __  (      \\
 //   / / //    ) )       ) )
((___/ / //____/ / ((___ / /
                Observação

           É possível otimizar o tempo do código drásticamente utilizando
           suffix arrays, porém, para a construção do mesmo, é necessário
           utilizar 'struct', assunto que, antes da realização do trabalho, 
           não foi ensinado, e, portanto, não é permitido o uso.


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


//Objetivo: em um array de tamanho 'len', retornar o tamanho do maior elemento.
//Parâmetros: um array 'arr' e o tamanho 'len' do array.
int getBiggestLength(char arr[LIMITE_BACTERIAS][COMPR_BACTERIAS], int len) 
{
    int length = 0; //inicializa com um valor pequeno
    for (int i = 0; i < len; i++)
        length = strlen(arr[i]) > length ? strlen(arr[i]) : length;
    
    return length;
    
}

/*
Objetivo: Dado um array de caracteres 'texto', remover a parte 'remover' do texto e 
          armazená-lo em um array de caracteres 'dest'.
Parâmetros: array de caracteres 'dest' e 'texto' para o destino e o texto, respectivamente
            array de caracteres 'remover', que se refere a parte de deverá ser removida.
*/
void separar(char *dest, char *texto, char *remover) 
{
    char *rem = strstr(texto, remover); //parte a ser removida
    char *finish = rem + strlen(remover); 
    char start[50];
    size_t tamanho = strlen(finish) + strlen(remover) - 1;
    // [start] + [rem] + [finish] = texto

    tamanho = strlen(texto) - tamanho - 1; //subtrai a parte removida e o final do texto
    strncpy(start, texto, tamanho); //copia o texto até a parte que foi removida
    start[tamanho] = '\0';
    strcat(start, finish);
    strcpy(dest, start);
}

//Objetivo: ver se existe uma string 'texto' em um array 'array'.
//Parâmetros: uma string 'texto', um array 'array' e o tamanho 'arraySize' do array. 
int existsInArray(char *texto, char array[LIMITE_BACTERIAS][COMPR_BACTERIAS], int arraySize) {
    for (int i = 0; i < arraySize; i++) 
        if (!strcmp(texto, array[i])) //são iguais
            return 1;
    return 0; //não existe
}

/*
Objetivo: encontrar os caracteres em comum de duas strings 't1' e 't2'
          e armazenar em um array 'substrings' e retornar quantos caracteres foram alterados.
Parâmetros: duas strings 't1' e 't2' para serem comparadas e um array 'substrings' de tamanho
            'index'.
*/
int findCommon(char* t1, char* t2, char substrings[LIMITE_BACTERIAS][COMPR_BACTERIAS], int *index){
    size_t x = strlen(t1);
    size_t y = strlen(t2);
    
    //criar uma array[x+1][y+1] para memorizar
    int memoria[x+1][y+1];
    int change = 0; //quantidade de letras modificadas

    for (int i = 0; i <= x; i++) //é menor igual porque o tamanho é x+1 e y+1.
    {    
        for (int j = 0; j <= y; j++)
        {
            if (i == 0 || j == 0)
                memoria[i][j] = 0;
            else if (t1[i-1] == t2[j-1])//o -1 é necessário pois o index 0 precisa ser incluso
            {
                memoria[i][j] = 1 + memoria[i-1][j-1];
                change = memoria[i][j] > change ? memoria[i][j] : change;
            }
            else memoria[i][j] = 0;
        }
    }
    
    char substring[COMPR_BACTERIAS] = "";
    for (int i = 0; i <= x; i++) 
    {    
        for (int j = 0; j <= y; j++)
        {
            if(memoria[i][j] >= 1) 
            {
                int _i = i;
                int _j = j;
                //se não colocar isso, ele começa pela segundo caracter (memoria[i][j] > 1)
                while (1) 
                {            
                    strncat(substring, &t1[_i - 1], 1);
                    int aux = memoria[_i][_j];
                    memoria[_i][_j] = 0;
                    _i++;
                    _j++;
                    if (memoria[_i][_j] != 1 + aux || _j == y)
                    {
                        strcat(substring, "\0");
                        break;
                    }
                }
                if (!existsInArray(substring, substrings, *index)) //evitar que a mesma substring se repita
                    strcpy(substrings[(*index)++], substring);
                strcpy(substring, "");
            }
        }
    }
    return change;
}

//Rotina principal
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
            // seria possivel usar um 'if (nBacterias > 2)', já que não há razões para comparar, a fim de salvar esforço computacional, mas a diferença seria mínima
            for (int i = 0; i < nBacterias; i++)
                for (int j = 0; j < SUBSIZE; j++)
                {
                    int c = findCommon(BACTERIAS_INFECTADAS[i], SUBSTRINGS[j], SUBSTRINGS, &SUBSIZE);
                    if (c < 1 || c != strlen(SUBSTRINGS[j])) // se houver uma letra ou zero ou se a substring se dividiu em mais SUBSTRINGS, zera o valor
                        strcpy(SUBSTRINGS[j], "\0");
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
            if (nBacterias == 1) //caso só houver UMA bactéria, a substring em comum é ela mesma.
                printf(SAIDA_6, BACTERIAS_INFECTADAS[0]);

        }
    }
    return 0;
}

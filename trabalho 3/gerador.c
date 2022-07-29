/*
INTEGRANTES DO GRUPO
- Emerson B. Filho
- Gustavo K. Volobueff
- Gustavo M. Gonçalves
- Victor Keony O. Takatu
- Vinícius A. Schautz
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

//clientes
char cpf_clientes[50][15] = {};
char contas_clientes[50][10] = {};
int saques_clientes[50][10] = {};
int saques_clientes_total[50][1] = {}; //total sacado por cada cliente em "Mostrar"
int clientes_contador = 0;
//quantidade
int cedulas[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800};
int limite[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800};
int saqueCedulas[] = {0, 0, 0, 0, 0, 0, 0, 0};

int saldo;

//geradores aleatórios
char geraAlfabeto() {
   int i;
   char letras[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
   i=rand()%26;
   return(letras[i]-32);
}
char geraNumero() {
   int i;
   char numeros[] = { '0','1','2','3','4','5','6','7','8','9'};
   i=rand()%9;
   return(numeros[i]);
}

//dígitos verificadores
int obtem_primeiro_digito_verificador(char cpf[]) {
   int digito=0;

   for (int i = 0; i < 9; i++) {
      digito += (cpf[i] - '0') * (10 - i);
   }
   digito = 11 - (digito % 11) >= 10 ? 0 : 11 - (digito % 11);
   return (digito);
}
int obtem_segundo_digito_verificador(char cpf[]) {
   int digito=0;

   for (int i = 0; i < 10; i++) {
      digito += (cpf[i] - '0') * (11 - i);
   }
   digito = 11 - (digito % 11) >= 10 ? 0 : 11 - (digito % 11);
   return (digito);
}

//mensagem de erro
void errorMsg(char msg[]){
   printf("[ERRO] %s\n", msg);
}

//header de relatórios
void criarInterface(char interface[]){
   printf("-----------------------------------------------------------------------\n");
   printf("%s\n", interface);
   printf("-----------------------------------------------------------------------\n");
}

//formato 999.999.999-99
//retorna 1 se cpf for válido e 0 se for inválido
int verifica_cpf_valido(char cpf[]) {
   int valido = 1;
   char _cpf[] = {cpf[0], cpf[1], cpf[2], cpf[4], cpf[5], cpf[6], cpf[8], cpf[9], cpf[10], cpf[12], cpf[13]};
   
   if (_cpf[0] == _cpf[1] && 
      _cpf[1] == _cpf[2] && 
      _cpf[2] == _cpf[3] &&
      _cpf[3] == _cpf[4] &&
      _cpf[4] == _cpf[5] &&        //se todos os dígitos forem iguais, é invalido
      _cpf[5] == _cpf[6] &&
      _cpf[6] == _cpf[7] &&
      _cpf[7] == _cpf[8] &&
      _cpf[8] == _cpf[9] &&
      _cpf[9] == _cpf[10])
         valido = 0;
   
   if (!(obtem_primeiro_digito_verificador(_cpf) + '0' == _cpf[9] && obtem_segundo_digito_verificador(_cpf) + '0' == _cpf[10]))
      valido = 0; //se os dígitos verificadores informados forem inválidos

   if (!(isdigit(cpf[0]) &&
   isdigit(cpf[1]) &&
   isdigit(cpf[2]) &&
   cpf[3] == '.' &&
   isdigit(cpf[4]) &&
   isdigit(cpf[5]) &&             //se não estiver no formato certo (999.999.999-99), é inválido
   isdigit(cpf[6]) &&
   cpf[7] == '.' &&
   isdigit(cpf[8]) &&
   isdigit(cpf[9]) &&
   isdigit(cpf[10]) &&
   cpf[11] == '-' &&
   isdigit(cpf[12]) &&
   isdigit(cpf[13])))
      valido = 0;
   
   return valido;
}

//verifica se a conta esta no formato 999.999-X
int verifica_conta_valida(char conta[]){

   if(isdigit(conta[0]) &&
   isdigit(conta[1]) &&
   isdigit(conta[2]) &&
   conta[3] == '.' &&
   isdigit(conta[4]) &&
   isdigit(conta[5]) &&
   isdigit(conta[6]) &&
   conta[7] == '-' &&
   isalpha(conta[8]))
      return 1;

   return 0;
}

//retorna o index da conta (se existir); caso não exista, retorna -1
int indexConta(char conta[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(conta, contas_clientes[i]) == 0)
         return i;
   }
   return -1;
}

//retorna o index do CPF, ou -1 caso não exista
int indexCPF(char cpf[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(cpf, cpf_clientes[i]) == 0)
         return i;
   }
   return -1;
}

//alterações de CPF e de conta
int alterar_cpf(char valor[], char novoValor[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(valor, cpf_clientes[i]) == 0) {
         strcpy(cpf_clientes[i], novoValor);
         return 1;
      }
   }
   return 0;
}
//
int alterar_conta(char valor[], char novoValor[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(valor, contas_clientes[i]) == 0) {
         strcpy(contas_clientes[i], novoValor);
         return 1;
      }
   }
   return 0;
}


//Objetivo: transformar um CPF de 99999999999 para 999.999.999-99
void insere_pontuacao_cpf(char origem[], char destino[]){
      destino[0] = origem[0]; 
      destino[1] = origem[1]; 
      destino[2] = origem[2]; 
      destino[3] = '.';
      destino[4] = origem[3]; 
      destino[5] = origem[4]; 
      destino[6] = origem[5]; 
      destino[7] = '.';
      destino[8] = origem[6]; 
      destino[9] = origem[7]; 
      destino[10] = origem[8]; 
      destino[11] = '-';
      destino[12] = origem[9]; 
      destino[13] = origem[10];
      destino[14] = '\0'; 
}

//Objetivo: transformar uma conta de 999999X para 999.999-X e deixar a última letra em maiúsculo
void insere_pontuacao_conta(char origem[], char destino[]){
   if(strlen(origem) == 7) {
      destino[0] = origem[0];
      destino[1] = origem[1];
      destino[2] = origem[2];
      destino[3] = '.';
      destino[4] = origem[3];
      destino[5] = origem[4];
      destino[6] = origem[5];
      destino[7] = '-';
      destino[8] = toupper(origem[6]);
      destino[9] = '\0';  
   }
   else if (strlen(origem) == 8 && !isdigit(origem[3])){ //tem 8 dígitos e o valor 000[.]000X (o quarto char não é um dígito)
      destino[0] = origem[0];
      destino[1] = origem[1];
      destino[2] = origem[2];
      destino[3] = origem[3];
      destino[4] = origem[4];
      destino[5] = origem[5];
      destino[6] = origem[6];
      destino[7] = '-';
      destino[8] = toupper(origem[7]);
      destino[9] = '\0';     
   }
   else if (strlen(origem) == 8 && !isdigit(origem[6])){ //tem 8 dígitos e o valor 000000[-]X (o sétimo char não é um dígito)
      destino[0] = origem[0];
      destino[1] = origem[1];
      destino[2] = origem[2];
      destino[3] = '.';
      destino[4] = origem[3];
      destino[5] = origem[4];
      destino[6] = origem[5];
      destino[7] = origem[6];
      destino[8] = toupper(origem[7]);
      destino[9] = '\0';    
   }
   else if(strlen(origem) == 9){ //ja está formatado
      destino[0] = origem[0];
      destino[1] = origem[1];
      destino[2] = origem[2];
      destino[3] = origem[3];
      destino[4] = origem[4];
      destino[5] = origem[5];
      destino[6] = origem[6];
      destino[7] = origem[7];
      destino[8] = toupper(origem[8]);
      destino[9] = '\0';  
   }
}

//Números por extenso
void centenaExtenso(int n1, int n2, int n3, char valExtenso[]){
   if (n1 != 0){
      if(n1 == 1 && n2 == 0 && n2 == 0)
         strcat(valExtenso, "cem ");
      else if(n1 == 1)
            strcat(valExtenso, "cento ");
      else if(n1 == 2)
         strcat(valExtenso, "duzentos ");  
      else if(n1 == 3)
         strcat(valExtenso, "trezentos ");  
      else if(n1 == 4)
         strcat(valExtenso, "quatrocentos ");  
      else if(n1 == 5)
         strcat(valExtenso, "quinhentos ");  
      else if(n1 == 6)
         strcat(valExtenso, "seiscentos ");  
      else if(n1 == 7)
         strcat(valExtenso, "setecentos ");
      else if(n1 == 8)
         strcat(valExtenso, "oitocentos ");
      else if(n1 == 9)
         strcat(valExtenso, "novecentos ");       
   }
   if(n2 != 0) { //segundo dígito 0 [0] 0 0 0 0
      if(n1 != 0)
         strcat(valExtenso, "e ");
      if(n2 == 1 && n3 == 0) //onze, doze, etc
         strcat(valExtenso, "dez ");
      else if(n2 == 1 && n3 == 1) 
         strcat(valExtenso, "onze ");
      else if(n2 == 1 && n3 == 2) 
         strcat(valExtenso, "doze ");
      else if(n2 == 1 && n3 == 3) 
         strcat(valExtenso, "treze "); 
      else if(n2 == 1 && n3 == 4) 
         strcat(valExtenso, "quatorze "); 
      else if(n2 == 1 && n3 == 5) 
         strcat(valExtenso, "quinze "); 
      else if(n2 == 1 && n3 == 6) 
         strcat(valExtenso, "dezesseis "); 
      else if(n2 == 1 && n3 == 7) 
         strcat(valExtenso, "dezessete "); 
      else if(n2 == 1 && n3 == 8) 
         strcat(valExtenso, "dezoito "); 
      else if(n2 == 1 && n3 == 9) 
         strcat(valExtenso, "dezenove "); 
      else if (n2 == 2)
         strcat(valExtenso, "vinte ");
      else if (n2 == 3)
         strcat(valExtenso, "trinta ");
      else if (n2 == 4)
         strcat(valExtenso, "quarenta ");
      else if (n2 == 5)
         strcat(valExtenso, "cinquenta ");
      else if (n2 == 6)
         strcat(valExtenso, "sessenta ");
      else if (n2 == 7)
         strcat(valExtenso, "setenta ");
      else if (n2 == 8)
         strcat(valExtenso, "oitenta ");
      else if (n2 == 9)
         strcat(valExtenso, "noventa ");            
   }
   if(n3 != 0 && n2 != 1) {
      if(n2 != 0 || n1 != 0)
         strcat(valExtenso, "e ");

      if(n3 == 1 && (n2 != 0 || n1 != 0)) 
         strcat(valExtenso, "um ");
      else if(n3 == 2) 
         strcat(valExtenso, "dois ");
      else if(n3 == 3) 
         strcat(valExtenso, "tres "); 
      else if(n3 == 4) 
         strcat(valExtenso, "quatro "); 
      else if(n3 == 5) 
         strcat(valExtenso, "cinco "); 
      else if(n3 == 6) 
         strcat(valExtenso, "seis "); 
      else if(n3 == 7) 
         strcat(valExtenso, "sete "); 
      else if(n3 == 8) 
         strcat(valExtenso, "oito "); 
      else if(n3 == 9) 
         strcat(valExtenso, "nove ");
      }
}
//objetivo: tirar o espaço do final da string
void trim(char str[]){
   if (str[strlen(str)-1] == ' ')
      str[strlen(str)-1] = '\0';
}  

void valorExtenso(int num, char valExtenso[]){
   strcpy(valExtenso, ""); //resetar o valor extenso
   int e6 = num % 10;
   int e5 = (num % 100) / 10;
   int e4 = (num % 1000) / 100;
   int e3 = (num % 10000) / 1000;
   int e2 = (num % 100000) / 10000;
   int e1 = (num % 1000000) / 100000;

   if(num == 1)
      strcat(valExtenso, "um ");
   else if(num == 0)
      strcat(valExtenso, "zero ");

   centenaExtenso(e1, e2, e3, valExtenso);
   if((e1 != 0 || e2 != 0 || e3 != 0) && (e4 != 0 && ( e5 == 0 || e6 == 0)))
      strcat(valExtenso, "mil e ");
   else if(e1 != 0 || e2 != 0 || e3 != 0)
      strcat(valExtenso, "mil ");
   centenaExtenso(e4, e5, e6, valExtenso);
   trim(valExtenso);
}

//Objetivo: gerar aleatoriamente um número de conta corrente no formato 999.999-X
//Parâmetros: c onde armazera a conta gerada
//Retorno: nenhum
void geraContaCorrente(char c[]) {
   do {  
      c[0] = geraNumero();
      c[1] = geraNumero();
      c[2] = geraNumero();
      c[3] = '.';
      c[4] = geraNumero();
      c[5] = geraNumero();
      c[6] = geraNumero();
      c[7] = '-';
      c[8] = geraAlfabeto();
      c[9] = '\0';
   }
   while (indexConta(c) != -1);
}

void gera_cpf_valido(char cpf[]) {
   char _cpf[11] = {};
   do {
      srand(time(NULL));
      for(int i = 0; i < 9; i++){
         _cpf[i] = geraNumero();
      }
      _cpf[9] = obtem_primeiro_digito_verificador(_cpf) + '0';
      _cpf[10] = obtem_segundo_digito_verificador(_cpf) + '0';
      insere_pontuacao_cpf(_cpf, cpf);
   } while(indexCPF(cpf) != -1);
}

//Objetivo: ler um valor e determinar se ele é um CPF ou uma CONTA, ou então se ele nao é nenhum dos dois
//Parâmetros: string que vai ser alterada
//Retornos: -1 para CONTA, 1 para CPF, 0 para nenhum dos dois
int validar_informacao(char* destino, char* display){
   char val[15];
   printf("%s\n --> ", display);
   scanf("%s", &val);

   if((strlen(val) >= 7) && (strlen(val) <=9)) //conta (ainda não validada)
      insere_pontuacao_conta(val, destino);
   else if (strlen(val) == 11) //cpf sem pontuação (não validado)
      insere_pontuacao_cpf(val, destino);
   else strcpy(destino, val);

   if(verifica_cpf_valido(destino)) //retorna 1 se for um CPF válido
      return 1;
   else if (verifica_conta_valida(destino)) //retorna -1 se for uma CONTA válida
      return -1;
   else //retorna 0 se nenhum dos dois
      return 0;
 }

//Funções de saque

//Transforma um index no seu respectivo valor
//Parâmetros: index
int indexNota(int i){
   int valor = 0;
   if (i == 0)
      valor = 450;
   if (i == 1)
      valor = 250;
   if (i == 2)
      valor = 50;
   if (i == 3)
      valor = 20;
   if (i == 4)
      valor = 10;
   if (i == 5)
      valor = 5;
   if (i == 6)
      valor = 2;
   if (i == 7)
      valor = 1;
   return valor;
}

void calcularSaldo(){ //Saldo existente
   saldo = 0;
   for (int i = 0; i < (sizeof(cedulas)/sizeof(cedulas[0])); i++){
      saldo += cedulas[i] * indexNota(i);
   }
}

int realizar_saque(int index){ //Checar etc
   calcularSaldo();
   int saque, i;
   char txt[80];
   printf("Valor a ser sacado > ");
   scanf("%d", &saque);
   int saqueHolder = saque;

   if (saque > saldo) { //erro
      errorMsg("Saldo insuficiente no caixa!\n");
      return -1;
   }

   for (i = 0; i < sizeof(saqueCedulas)/sizeof(saqueCedulas[0]); i++){
      saqueCedulas[i] = 0;
   }
   //saque de valores de cédulas
   do {
      for (i = 0; i < 8; i++) {
         if (saqueHolder - indexNota(i) >= 0 && cedulas[i] - saqueCedulas[i] - 1 >= 0) {
            saqueHolder -= indexNota(i);
            saqueCedulas[i]++;
            break;
         }
      }
   } while (saqueHolder > 0);

   for (i = 0; i < sizeof(cedulas)/sizeof(cedulas[0]); i++) {
      cedulas[i] -= saqueCedulas[i];
      if (saqueCedulas[i] != 0){
         if(saqueCedulas[i] == 1)
            printf("(%d) cedula de R$ %d\n", saqueCedulas[i], indexNota(i));
         else
            printf("(%d) cedulas de R$ %d\n", saqueCedulas[i], indexNota(i));
      }
   }

   valorExtenso(saque, txt);
   if (saque > 0){
      if (saque > 1) printf("\nValor sacado: %s reais\n\n", txt);
      else printf("\nValor sacado: %s real\n\n", txt);

      saques_clientes[index][0]++; //adicionar um saque
      saques_clientes_total[index][0] += saque; //adiciona o valor do saque ao já sacado no total de cada cliente (apção "Mostrar")
      saques_clientes[index][saques_clientes[index][0]] = saque; //adiciona o valor sacado em seu respectivo index
      calcularSaldo();
   } else errorMsg("Operacao nao realizada!\n"); //Sacar 0 reais não é possível

   return 0;
}

//display de saque
void handlerSaque(){
   system("cls");
   char conta[11];
   int index;
   int info = validar_informacao(conta, "Insira a conta");
   int sucesso = 0;
   
   switch (info){
      case -1:
         index = indexConta(conta);
         if (index != -1) 
            sucesso = realizar_saque(index);
         else errorMsg("Esta conta nao existe!\n");
      break;
      default:
         errorMsg("Use sua CONTA para realizar saques!\n"); //tem que ser um número de conta
   }

   system("pause");
}

//montante total sacado
int calcularTotalSacado(int index){
   int total = 0;
   for (int i = 1; i < saques_clientes[index][0] + 1; i++){
      total += saques_clientes[index][i];
   }
   return total;
}

//gera uma conta e cpf aleatórios e insere
void inserir_cliente(){
   if(clientes_contador < 50){ //até o limite (50)
      char cpf[15] = {};
      char conta[10] = {};
      gera_cpf_valido(cpf);
      geraContaCorrente(conta);
      int resposta = 0;
  
      printf("Voce deseja adicionar a conta %s e o CPF %s?\n1. SIM\n2. NAO\n --> ", conta, cpf);
      scanf("%d", &resposta);
  
      if(resposta == 1) { //adicionar cliente
         strcpy(cpf_clientes[clientes_contador], cpf);
         strcpy(contas_clientes[clientes_contador], conta);
         saques_clientes[clientes_contador][0] = 0;
         saques_clientes[clientes_contador][1] = 0;
         clientes_contador++;
      }
   } 
   else {
      errorMsg("Numero maximo de clientes (50) atingido!\n");
      system("pause");
   }
}

//exibe a lista de clientes cadastrados
void mostrar_clientes(){
   system("cls");

   if(clientes_contador > 0){
      for (int i = 0; i < clientes_contador; i++) {
         printf("-----------------------------\n");
         printf("Cliente %d\n", i + 1);
         printf("-----------------------------\n");
         printf("Conta: %s\n", contas_clientes[i]);
         printf("CPF: %s\n", cpf_clientes[i]);
         printf("Saques realizados: %d\n", saques_clientes[i][0]);
         printf("Valor total sacado: R$ %d\n", saques_clientes_total[i][0]);
         printf("-----------------------------\n\n");
      }
   } else printf("Nenhum cliente cadastrado no sistema!\n\n"); //0 clientes
   system("pause");
}

//altera o número de conta e/ou de cpf de clientes
void alterar_cliente(){
   system("cls");

   if(clientes_contador > 0) { //se houver 1 ou mais clientes cadastrados...
      char val[15];
      char newVal[15];
      int index;
      int alteracao = validar_informacao(val, "Insira a CONTA/CPF a alterar");

      //ALTERAR O CPF (14 DIGITOS)
      if (alteracao == 1){
         index = indexCPF(val);

         if (index == -1)
            errorMsg("CPF nao existente no banco de dados!\n");
         else if (saques_clientes[index][0])
            errorMsg("Nao e possivel alterar o CPF depois de ter realizado saques!\n");
         else {
            validar_informacao(newVal, "\nInsira o novo CPF"); //deu certo
            
            if(!verifica_cpf_valido(newVal))
               errorMsg("CPF invalido!\n");
            else if(indexCPF(newVal) != -1)
               errorMsg("O CPF ja existe no sistema!\n");
            else if(!alterar_cpf(val, newVal))
               errorMsg("Nao foi possivel alterar o CPF!\n");
            else 
               printf("\n[OK] Alteracao concluida!\nDE: %s\nPARA: %s\n", val, newVal);
         }
      }
      //ALTERAR CONTA
      else if (alteracao == -1) {
         index = indexConta(val);

         if (index == -1)
            errorMsg("Conta inexistente no banco de dados!\n");
         else if (saques_clientes[index][0])
            errorMsg("Nao e possivel alterar a conta depois de ter realizado saques!\n");
         else {
         validar_informacao(newVal, "\nInsira a nova CONTA"); //deu certo

            if(!verifica_conta_valida(newVal))
               errorMsg("\nConta invalida!\n");
            else if(indexConta(newVal) != -1)
               errorMsg("A Conta ja existe no sistema!\n");
            else if(!alterar_conta(val, newVal))
               errorMsg("Nao foi possivel alterar a conta!\n");
            else 
               printf("\n[OK] Alteracao concluida!\nDE: %s\nPARA: %s\n", val, newVal);
         }
      } else errorMsg("Conta/CPF invalida(o)!\n");

   } else printf("Nenhum cliente cadastrado no sistema!\n\n");
   
   system("pause");
}

//exclusão de clientes do sistema
void excluir_cliente(){

   if(clientes_contador > 0){ // se houver 1 ou mais clientes cadastrados... 
      char val[15];
      int index;
      switch(validar_informacao(val, "Insira a CONTA que deseja excluir")){
         case 1: //tem que fornecer uma CONTA
            errorMsg("Voce precisa fornecer a CONTA para exclui-la!\n");
         break;

         case -1: //CONTA
            index = indexConta(val);
            if (index != -1)
               if (!saques_clientes[index][0]){
                  if(index == clientes_contador - 1) //é o ultimo valor da array
                     strcpy(cpf_clientes[index], "");
                  else {
                     for (int i = 0; i < (clientes_contador - index) + 1; i++) {
                        strcpy(cpf_clientes[index+i], cpf_clientes[index+i+1]);
                        strcpy(contas_clientes[index+i], contas_clientes[index+i+1]);
                     }
                     printf("[OK] Conta excluida com sucesso!\n");
                  } 
                  clientes_contador--; //menos um cliente :(
            }
            else errorMsg("Nao e possivel excluir a conta depois de ter realizado saques!\n");
         break;

         default:
            errorMsg("Conta inexistente no banco de dados!\n");
      }
   } else printf("Nenhum cliente cadastrado no sistema!\n\n");
   
   system("pause");
}

//Relatórios

//Saques
void relatorio_saques(){
   int totalGeral = 0;
   char valExtenso[80];
   system("cls");
   criarInterface("Relatorio | Valores sacados");

   for (int i = 0; i < clientes_contador; i++){
      totalGeral += calcularTotalSacado(i);
      printf("%s %s     ", contas_clientes[i], cpf_clientes[i]);
      for (int j = 1; j < saques_clientes[i][0] + 1; j++) {
         printf("R$ %d\n                             ", saques_clientes[i][j]);
      }
      printf("                             R$ %d\n", calcularTotalSacado(i));
   }

   valorExtenso(totalGeral, valExtenso);
   printf("-----------------------------------------------------------------------\n");
   if (totalGeral == 1)
      printf("Valor total geral: R$ %d (%s real)\n", totalGeral, valExtenso);
   else
      printf("Valor total geral: R$ %d (%s reais)\n", totalGeral, valExtenso);
   printf("-----------------------------------------------------------------------\n\n");

   system("pause");
}

//Saldo
void relatorio_saldo(){
   calcularSaldo();
   char valExtenso[80];
   valorExtenso(saldo, valExtenso);
   system("cls");
   criarInterface("Relatorio | Valor do saldo existente");

   if (saldo == 1)
      printf("R$ %d (%s real)\n", saldo, valExtenso);
   else
      printf("R$ %d (%s reais)\n", saldo, valExtenso);
   printf("-----------------------------------------------------------------------\n\n");

   system("pause");
}

//Quantidade de cédulas
void relatorio_cedulas(){
   char valExtenso[80];
   system("cls");
   criarInterface("Relatorio | Quantidade de cedulas existentes");

   for(int i = 0; i < sizeof(cedulas)/sizeof(cedulas[0]); i++){
      valorExtenso(cedulas[i], valExtenso);
   
      printf("Cedulas de R$ %d : %d (%s)\n", indexNota(i), cedulas[i], valExtenso);
   }
   printf("-----------------------------------------------------------------------\n\n");

   system("pause");
}

//Escolha de relatórios
void handler_relatorios(int escolha){
   switch (escolha){
      case 1:
         relatorio_saques();
      break;

      case 2:
         relatorio_saldo();
      break;

      case 3:
         relatorio_cedulas();
      break;
   }
}

//MENUS
void gerar_menu_principal(){
   system("cls");
   printf("MENU PRINCIPAL\n\n1. Cliente\n2. Saque\n3. Relatorios\n4. Finalizar\n --> ");
}

void gerar_menu_cliente(){
   system("cls");
   printf("MENU CLIENTE\n\n1. Incluir\n2. Mostrar\n3. Alterar\n4. Excluir\n5. Voltar\n --> ");
}

void gerar_menu_relatorios(){
   system("cls");
   printf("RELATORIOS\n\n1. Valores sacados\n2. Valor do saldo existente\n3. Quantidade de cedulas existentes\n4. Voltar ao menu principal\n --> ");
}

//Escolhas
int escolha_principal(){
   int escolha;
   do {
      gerar_menu_principal();
   //esse while serve pra otimizar o scanf e não crashar quando colocar um char.
   } while ((escolha < 1 && escolha > 4) || (!scanf("%d", &escolha) && getchar()));
   return escolha;
}

int escolha_cliente(){
   char escolha;
   do {
      gerar_menu_cliente();
   } while ((escolha < 1 && escolha > 5) || (!scanf("%d", &escolha) && getchar()));
   return escolha;
}

int escolha_relatorios(){
   int escolha;
   do {
      gerar_menu_relatorios();
   } while ((escolha < 1 && escolha > 4) || (!scanf("%d", &escolha) && getchar()));
   return escolha;
}

void handler_cliente(int escolha){ //menu cliente
   system("cls");
   switch(escolha){
      case 1:
         inserir_cliente();
      break;

      case 2:
         mostrar_clientes();
      break;

      case 3:
         alterar_cliente();
      break;

      case 4:
         excluir_cliente();
      break;

   }
}

//main
int main(){
   int escolha, escolhaCliente, escolhaRelatorio;

   do {
      //menu principal
      escolha = escolha_principal();

      switch (escolha){
         //menu cliente
         case 1:
            do {
               escolhaCliente = escolha_cliente();

               handler_cliente(escolhaCliente);

            } while (escolhaCliente != 5);
         break;

         //saques
         case 2:
            handlerSaque();
         break;

         //menu relatorios
         case 3:
            do {
               escolhaRelatorio = escolha_relatorios();

               handler_relatorios(escolhaRelatorio);

            } while (escolhaRelatorio != 4);
         break;

      }
   } while (escolha != 4);

   return 0;
}
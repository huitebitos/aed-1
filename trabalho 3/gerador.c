#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>




/* 
   seria possível fazer uma única array tridimensional clientes[50][2][16]
   mas seria desperdício de memória, já que alguns bytes seriam reservados sem necessidade
*/
char cpf_clientes[50][15] = {};
char contas_clientes[50][10] = {};
int saques_clientes[50][10] = {};
int clientes_contador = 0;

int cedulas[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800};
int limite[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800};
int saqueCedulas[] = {0, 0, 0, 0, 0, 0, 0, 0};

int saldo;

//geradores aleatorios
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

//digitos verificadores
int obtem_primeiro_digito_verificador(char cpf[]) {
   int digito;

   for (int i = 0; i < 9; i++) {
      digito += (cpf[i] - '0') * (10 - i);
   }
   digito = 11 - (digito % 11) >= 10 ? 0 : 11 - (digito % 11);
   return (digito);
}
int obtem_segundo_digito_verificador(char cpf[]) {
   int digito;

   for (int i = 0; i < 10; i++) {
      digito += (cpf[i] - '0') * (11 - i);
   }
   digito = 11 - (digito % 11) >= 10 ? 0 : 11 - (digito % 11);
   return (digito);
}



//formato 999.999.999-99
//retorna 1 se cpf for válido e 0 se for inválido
int verifica_cpf_valido(char cpf[]) {
   int valido = 1;
   char _cpf[11] = {cpf[0], cpf[1], cpf[2], cpf[4], cpf[5], cpf[6], cpf[8], cpf[9], cpf[10], cpf[12], cpf[13]};
   if (_cpf[0] == _cpf[1] && 
      _cpf[1] == _cpf[2] && 
      _cpf[2] == _cpf[3] &&
      _cpf[3] == _cpf[4] &&
      _cpf[4] == _cpf[5] &&
      _cpf[5] == _cpf[6] &&
      _cpf[6] == _cpf[7] &&
      _cpf[7] == _cpf[8] &&
      _cpf[8] == _cpf[9] &&
      _cpf[9] == _cpf[10])
         valido = 0;
   
   if (obtem_primeiro_digito_verificador(_cpf) != _cpf[9] || obtem_segundo_digito_verificador(_cpf) != _cpf[10])
      valido = 0;
   
   if (!(isdigit(cpf[0]) &&
   isdigit(cpf[1]) &&
   isdigit(cpf[2]) &&
   cpf[3] == '.' &&
   isdigit(cpf[4]) &&
   isdigit(cpf[5]) &&             //não está no formato certo 999.999.999-99
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

//retorna o index da conta (se existir), caso não exista retorna -1
int indexConta(char conta[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(conta, contas_clientes[i]) == 0)
         return i;
   }
   return -1;
}

//retorna o index do CPF ou -1, caso não exista
int indexCPF(char cpf[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(cpf, cpf_clientes[i]) == 0)
         return i;
   }
   return -1;
}

//
int alterar_cpf(char valor[], char novoValor[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(valor, cpf_clientes[i]) == 0) {
         strcpy(cpf_clientes[i], novoValor);
         return 1;
      }
   }
   return 0;
}

int alterar_conta(char valor[], char novoValor[]){
   for(int i = 0; i < clientes_contador; i++){
      if (strcmp(valor, contas_clientes[i]) == 0) {
         strcpy(contas_clientes[i], novoValor);
         return 1;
      }
   }
   return 0;
}


//transformar um CPF de 99999999999 para 999.999.999-99
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

//Objetivo: transformar uma conta de 999999X para 999.999-X e deixar a ultima letra em maiusculo
//
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


//objetivo:gera aleatoriamente um numero de conta corrente no formato 999.999-X
//parametros: c onde armazera a conta gerada
//retorno:nenhum
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

   if(strlen(val) == 7) //conta sem pontuação (ainda não validada)
      insere_pontuacao_conta(val, destino);
   else if (strlen(val) == 11) //cpf sem pontuação (não validado)
      insere_pontuacao_cpf(val, destino);
   else strcpy(val, destino);

   if(verifica_cpf_valido(destino)) //retorna 1 se for um CPF válido
      return 1;
   else if (verifica_conta_valida(destino)) //retorna -1 se for uma CONTA válida
      return -1;
   else //retorna 0 se nennhum dos dois
      return 0;
 }


//funções de saque

//transforma um index no seu respectivo valor
//parâmetros: index
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

void calcularSaldo(){
   saldo = 0;
   for (int i = 0; i < (sizeof(cedulas)/sizeof(cedulas[0])); i++){
      saldo += cedulas[i] * indexNota(i);
   }
}

int realizar_saque(int index){ //checar etc
   calcularSaldo();
   int saque, i;
   printf("Valor a ser sacado > ");
   scanf("%d", &saque);
   int saqueHolder = saque;

   if (saque > saldo) //erro
      return -1;

   for (i = 0; i < sizeof(saqueCedulas)/sizeof(saqueCedulas[0]); i++){
      saqueCedulas[i] = 0;
   }
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
      printf("%d cedulas de %d\n", saqueCedulas[i], indexNota(i));
   }
   saques_clientes[index][0]++; //adicionar um saque
   saques_clientes[index][saques_clientes[index][0]] = saque; //adiciona o valor sacado em seu respectivo index;
   calcularSaldo();
   system("pause");
   return 0;
}

void handlerSaque(){ //bug estranho que crasha sempre que a conta não existe
   system("cls");
   char conta[10];
   int index;
   int info = validar_informacao(conta, "Insira a conta");
   int sucesso = 0;

   if (info == -1) {
      index = indexConta(conta);
      if (index != -1) 
         sucesso = realizar_saque(index);
      else printf("Conta nao existe");
      system("pause");
   }
}

int calcularTotalSacado(int index){
   int total = 0;
   for (int i = 1; i < saques_clientes[index][0] + 1; i++){
      total += saques_clientes[index][i];
   }
   return total;
}


//gera uma conta e cpf aleatorios e insere
void inserir_cliente(){
   if(clientes_contador < 50){
      char cpf[15] = {};
      char conta[10] = {};
      gera_cpf_valido(cpf);
      geraContaCorrente(conta);
      printf("Voce deseja adicionar a conta %s e o CPF %s?\n1. SIM\n2. NAO\n --> ", conta, cpf);

      int resposta;
      scanf("%d", &resposta);
      if(resposta == 1) {
         strcpy(cpf_clientes[clientes_contador], cpf);
         strcpy(contas_clientes[clientes_contador], conta);
         saques_clientes[clientes_contador][0] = 0;
         saques_clientes[clientes_contador][1] = 0;
         clientes_contador++;
      }
   } else printf("Limite");
}

void mostrar_clientes(){
   system("cls");
   for (int i = 0; i < clientes_contador; i++) {
      printf("-----------------------------\n");
      printf("Cliente %d\n", i + 1);
      printf("-----------------------------\n");
      printf("Conta: %s\n", contas_clientes[i]);
      printf("CPF: %s\n", cpf_clientes[i]);
      printf("Saques realizados: %d\n", saques_clientes[i][0]);
      printf("Valor total sacado: %d\n", saques_clientes[i][1]);
      printf("-----------------------------\n\n");
   }
   system("pause");
}

void alterar_cliente(){
   char val[15];
   char newVal[15];
   int index;

   system("cls");
   int alteracao = validar_informacao(val, "Insira a CONTA/CPF a ser alterado");

   //ALTERAR O CPF (14 DIGITOS)
   if(alteracao == 1){
      index = indexCPF(val);

      if (index == -1)
         printf("\nCPF nao existe no banco de dados\n");
      else if (saques_clientes[index][0])
         printf("\nNao e possivel alterar o CPF depois de ter realizado saques\n");
      else {
         validar_informacao(newVal, "\nInsira o novo CPF");
         
         if(!verifica_cpf_valido(newVal))
            printf("\nERRO! CPF invalido\n ");
         else if(indexCPF(newVal) != -1)
            printf("\nERRO! CPF ja consta no sistema\n ");
         else if(!alterar_cpf(val, newVal))
            printf("\nErro!! Nao foi possivel\n ");
         else 
            printf("\nAlteracao concluida");
      }
   }

   else if (alteracao == -1) {
      index = indexConta(val);
       if (index == -1)
         printf("\nCONTA nao existe no banco de dados\n");
      else if (saques_clientes[index][0])
         printf("\nNao e possivel alterar a CONTA depois de ter realizado saques\n");
      else{
        validar_informacao(newVal, "\nInsira a nova CONTA");

         if(!verifica_conta_valida(newVal))
            printf("\nERRO! CONTA invalida\n ");
         else if(indexConta(newVal) != -1)
            printf("ERRO! CONTA ja consta no sistema\n ");
         else if(!alterar_conta(val, newVal))
            printf("Erro!! Nao foi possivel\n ");
         else 
            printf("\nAlteracao concluida\nDE: %s\nPARA: %s", val, newVal);
      }
   }
   system("pause");
}

void excluir_cliente(){
   char val[15];
   int index;
   switch(validar_informacao(val, "Insira a CONTA/CPF que deseja excluir")){
      case 1: //CPF
         printf("Voce precisa fornecer a CONTA para excluir.");
      break;

      case -1: //CONTA
         index = indexConta(val);
         if (index == -1)
            printf("Nao existe");
         //checagem de saque TODO
         else {
            if(index == clientes_contador - 1) //é o ultimo valor da array
               strcpy(cpf_clientes[index], "");
            else {
               for (int i = 0; i < (clientes_contador - index) + 1; i++) {
                  strcpy(cpf_clientes[index+i], cpf_clientes[index+i+1]);
                  strcpy(contas_clientes[index+i], contas_clientes[index+i+1]);
               }
            } 
            clientes_contador--;
         }
      break;

      default:
         printf("Numero da conta nao existe no sistema.");
   }
system("pause");
}



//relatorios
void relatorio_saques(){
   system("cls");
   printf("---------------------------\n");
   printf("Valores Sacados\n");
   printf("---------------------------\n");
   for (int i = 0; i < clientes_contador; i++){
      printf("%s %s", contas_clientes[i], cpf_clientes[i]);
      for (int j = 1; j < saques_clientes[i][0] + 1; j++) {
         printf("                          %d\n", saques_clientes[i][j]);
      }
      printf("                       %d reais\n", calcularTotalSacado(i));
   }
   system("pause");
}
void relatorio_saldo(){

}
void relatorio_cedulas(){

}

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



//menus
void gerar_menu_principal(){
   system("cls");
   printf("MENU PRINCIPAL\n1. Cliente\n2. Saque\n3. Relatorios\n4. Finalizar\n --> ");
}

void gerar_menu_cliente(){
   system("cls");
   printf("MENU CLIENTE\n1. Incluir\n2. Mostrar\n3. Alterar\n4. Excluir\n5. Voltar\n --> ");
}

void gerar_menu_relatorios(){
   system("cls");
   printf("1-Valores sacados\n2. Valor do saldo existente\n3. Quantidade de cedulas existentes\n4. Voltar ao menu principal\n --> ");
}





int escolha_principal(){
   int escolha;
   do {
      gerar_menu_principal();
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

void handler_cliente(int escolha){
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* 
Implementações feitas:

 * Contador de cedulas
 * Menus
 * Revarga de Cedulas (com checagem para 0 e numeros negativos) (limite de cedulas)
 * Total sacado e saldo existente
 * Checagem de saque (se o saldo < saque avisar o usuario)
 * Contagem de cedulas
 * Caso for impossivel dar o valor com as notas atuais, exibe mensagem de erro e não é descontado do saldo nem entregue nota alguma
 * Identificadores de SAIDA e ERRO

TODO:

 * Escrever numeros por extenso
 * Checar se é possivel dar o valor (com as notas disponiveis)

*/


int main(){
    int escolha, escolhaGerente, escolhaCedulas, qntCedulas; //escolhas
    
    //saque
    int saque, saque_holder;
    long long int cpf;
    int c1, d1, u1, c2, d2, u2, c3, d3, u3, dig_1, dig_2, soma_mod, v_dig1, v_dig2;
    
    //numero extenso
    char e1, e2, e3, e4, e5, e6;

    int totalSacado = 0; //o valor é acumulativo
    char valExtenso[80];

    //contador de cedulas
    int cedulas450, cedulas250, cedulas50, cedulas20, cedulas10, cedulas5, cedulas2, cedulas1;
    cedulas450 = 100;
    cedulas250 = 200;
    cedulas50 = 400;
    cedulas20 = 800; 
    cedulas10 = 1600;
    cedulas5 = 3200;
    cedulas2 = 6400;
    cedulas1 = 12800;

    //o valor máximo de cédulas que pode existir de cada tipo.
    int limite450, limite250, limite50, limite20, limite10, limite5, limite2, limite1;
    limite450 = 100;
    limite250 = 200;
    limite50 = 400;
    limite20 = 800; 
    limite10 = 1600;
    limite5 = 3200;
    limite2 = 6400;
    limite1 = 12800;

    int saque450, saque250, saque50, saque20, saque10, saque5, saque2, saque1;

    //o saldo maximo é 188600
    int saldo = cedulas450 * 450 + cedulas250 * 250 + cedulas50 * 50 + cedulas20 * 20 + cedulas10 * 10 + cedulas5 * 5 + cedulas2 * 2 + cedulas1;

    do {
        system("cls");
        printf("-------<[ Menu ]>-------\n(1) Saque\n(2) Gerente\n(3) Finalizar\n\n -> Escolha sua opcao: ");
        scanf("%d", &escolha);
        switch(escolha){
            case 1: // saque
                system("cls");
                printf("----------Saque----------\n");
                strcpy(valExtenso, ""); //resetar o valor extenso
                printf(" -> Informe o valor a ser sacado: ");
                scanf("%d", &saque);
                printf(" -> Informe seu CPF: ");
                scanf("%lld", &cpf);

                //Validador de cpf
                c1 = (cpf/10000000000) % 10;
                d1 = (cpf/1000000000) % 10;
                u1 = (cpf/100000000) % 10;
                c2 = (cpf/10000000) % 10;
                d2 = (cpf/1000000) % 10;
                u2 = (cpf/100000) % 10;
                c3 = (cpf/10000) % 10;
                d3 = (cpf/1000) % 10;
                u3 = (cpf/100) % 10;
                dig_1 = (cpf/10) % 10;
                dig_2 = cpf % 10;

                //1. DIGITO
                soma_mod = c1*10 + d1*9 + u1*8 + c2*7 + d2*6 + u2*5 + c3*4 + d3*3 + u3*2;

                v_dig1 = 11 - (soma_mod % 11);
                if(v_dig1>=10)
                    v_dig1 = 0;

                //2. DIGITO
                soma_mod = c1*11 + d1*10 + u1*9 + c2*8 + d2*7 + u2*6 + c3*5 + d3*4 + u3*3 + v_dig1*2;

                v_dig2 = 11 - (soma_mod % 11);
                if(v_dig2>=10)
                    v_dig2 = 0;

                //VALIDACAO
                if((v_dig1!=dig_1)||(v_dig2!=dig_2)){
                    printf("\nCPF invalido!\n\n");
                    break;
                }
                
                if(saque > saldo) {  //impossivel sacar mais dinheiro do que a maquina tem
                    printf("[ERRO!] A maquina nao possui saldo suficiente!\n");
                    break;
                }
                saque_holder = saque;
                saque450 = 0;
                saque250 = 0;
                saque50 = 0;
                saque20 = 0; 
                saque10 = 0;
                saque5 = 0;
                saque2 = 0;
                saque1 = 0;

                while (saque_holder > 0) { // saque_holder != 0 testar dps
                    if (saque_holder - 450 >= 0 && cedulas450 > 0) {
                        saque_holder -= 450;
                        saque450++;
                    }
                    else if (saque_holder - 250 >= 0 && cedulas250 > 0) {
                        saque_holder -= 250;
                        saque250++;
                    }
                    else if (saque_holder - 50 >= 0 && cedulas50 > 0) {
                        saque_holder -= 50;
                        saque50++;
                    }
                    else if (saque_holder - 20 >= 0 && cedulas20 > 0) {
                        saque_holder -= 20;
                        saque20++;
                    }
                    else if (saque_holder - 10 >= 0 && cedulas10 > 0) {
                        saque_holder -= 10;
                        saque10++;
                    }
                    else if (saque_holder - 5 >= 0 && cedulas5 > 0) {
                        saque_holder -= 5;
                        saque5++;
                    }
                    else if (saque_holder - 2 >= 0 && cedulas2 > 0) {
                        saque_holder -= 2;
                        saque2++;
                    }
                    else if (saque_holder - 1 >= 0 && cedulas1 > 0) {
                        saque_holder -= 1;
                        saque1++;
                    }
                    else { //talvez esse caso nunca ocorra, mas é bom se precaver
                        printf("[ERRO!] Impossivel dar o valor com as notas atuais!\n");
                        saque450 = 0;
                        saque250 = 0;
                        saque50 = 0;
                        saque20 = 0; 
                        saque10 = 0;    //zerar o saque, já que nenhuma nota será dada.
                        saque5 = 0;
                        saque2 = 0;
                        saque1 = 0;
                        break;
                    }
                }

                cedulas450 -= saque450;
                cedulas250 -= saque250;
                cedulas50  -= saque50;
                cedulas20  -= saque20; 
                cedulas10  -= saque10;
                cedulas5   -= saque5;
                cedulas2   -= saque2;
                cedulas1   -= saque1;
                if (saque_holder == 0 ) { //foi possivel retirar o dinheiro
                    //converter pra texto
                    e6 = saque % 10;
                    e5 = (saque % 100) / 10;
                    e4 = (saque % 1000) / 100;
                    e3 = (saque % 10000) / 1000;
                    e2 = (saque % 100000) / 10000;
                    e1 = (saque % 1000000) / 100000;
                    if (e1 == 1 && e2 != 0 && e3 != 0) //primeiro dígito [0] 0 0 0 0 0 só pode ser 0 ou 1
                        strcat(valExtenso, "cento e ");
                    else if (e1 == 1 && e2 == 0 && e3 == 0) 
                        strcat(valExtenso, "cem ");

                    if(e2 != 0) { //segundo dígito 0 [0] 0 0 0 0
                        if(e2 == 1 && e3 == 0) //onze, doze, etc
                            strcat(valExtenso, "dez ");
                        else if(e2 == 1 && e3 == 1) 
                            strcat(valExtenso, "onze ");
                        else if(e2 == 1 && e3 == 2) 
                            strcat(valExtenso, "doze ");
                        else if(e2 == 1 && e3 == 3) 
                            strcat(valExtenso, "treze "); 
                        else if(e2 == 1 && e3 == 4) 
                            strcat(valExtenso, "quatorze "); 
                        else if(e2 == 1 && e3 == 5) 
                            strcat(valExtenso, "quize "); 
                        else if(e2 == 1 && e3 == 6) 
                            strcat(valExtenso, "dezesseis "); 
                        else if(e2 == 1 && e3 == 7) 
                            strcat(valExtenso, "dezessete "); 
                        else if(e2 == 1 && e3 == 8) 
                            strcat(valExtenso, "dezoito "); 
                        else if(e2 == 1 && e3 == 9) 
                            strcat(valExtenso, "dezenove "); 
                        else if (e2 == 2)
                            strcat(valExtenso, "vinte ");
                        else if (e2 == 3)
                            strcat(valExtenso, "trinta ");
                        else if (e2 == 4)
                            strcat(valExtenso, "quarenta ");
                        else if (e2 == 5)
                            strcat(valExtenso, "cinquenta ");
                        else if (e2 == 6)
                            strcat(valExtenso, "sessenta ");
                        else if (e2 == 7)
                            strcat(valExtenso, "setenta ");
                        else if (e2 == 8)
                            strcat(valExtenso, "oitenta ");
                        else if (e2 == 9)
                            strcat(valExtenso, "noventa ");            
                    }
                    if(e3 != 0 && e2 != 1) {
                        if(e2 != 0 || e1 != 0)
                            strcat(valExtenso, "e ");

                        if(e3 == 1 && (e2 != 0 || e1 != 0)) 
                            strcat(valExtenso, "um ");
                        else if(e3 == 2) 
                            strcat(valExtenso, "dois ");
                        else if(e3 == 3) 
                            strcat(valExtenso, "tres "); 
                        else if(e3 == 4) 
                            strcat(valExtenso, "quatro "); 
                        else if(e3 == 5) 
                            strcat(valExtenso, "cinco "); 
                        else if(e3 == 6) 
                            strcat(valExtenso, "seis "); 
                        else if(e3 == 7) 
                            strcat(valExtenso, "sete "); 
                        else if(e3 == 8) 
                            strcat(valExtenso, "oito "); 
                        else if(e3 == 9) 
                            strcat(valExtenso, "nove ");
                    }
                    if((e1 != 0 || e2 != 0 || e3 != 0) && (e4 != 0 || e5 != 0 || e6 != 0))
                        strcat(valExtenso, "mil e ");
                    else if(e1 != 0 || e2 != 0 || e3 != 0)
                        strcat(valExtenso, "mil ");
                    
                    //acabou a casa dos milhares, agora da pra repetir o codigo e mudar as variaveis
                    if (e4 != 0){
                        if(e4 == 1 && e5 == 0 && e6 == 0)
                            strcat(valExtenso, "cem ");
                        else if(e4 == 1)
                            strcat(valExtenso, "cento ");
                        else if(e4 == 2)
                            strcat(valExtenso, "duzentos ");  
                        else if(e4 == 3)
                            strcat(valExtenso, "trezentos ");  
                        else if(e4 == 4)
                            strcat(valExtenso, "quatrocentos ");  
                        else if(e4 == 5)
                            strcat(valExtenso, "quinhentos ");  
                        else if(e4 == 6)
                            strcat(valExtenso, "seiscentos ");  
                        else if(e4 == 7)
                            strcat(valExtenso, "setecentos ");
                        else if(e4 == 8)
                            strcat(valExtenso, "oitocentos ");
                        else if(e4 == 9)
                            strcat(valExtenso, "novecentos ");       
                    }

                    if(e5 != 0) { //quinto dígito 0 0 0 0 [0] 0
                        if (e4 != 0)
                           strcat(valExtenso, "e ");

                        if(e5 == 1 && e6 == 0) //onze, doze, etc
                            strcat(valExtenso, "dez");
                        else if(e5 == 1 && e6 == 1) 
                            strcat(valExtenso, "onze");
                        else if(e5 == 1 && e6 == 2) 
                            strcat(valExtenso, "doze");
                        else if(e5 == 1 && e6 == 3) 
                            strcat(valExtenso, "treze"); 
                        else if(e5 == 1 && e6 == 4) 
                            strcat(valExtenso, "quatorze"); 
                        else if(e5 == 1 && e6 == 5) 
                            strcat(valExtenso, "quize"); 
                        else if(e5 == 1 && e6 == 6) 
                            strcat(valExtenso, "dezesseis"); 
                        else if(e5 == 1 && e6 == 7) 
                            strcat(valExtenso, "dezessete"); 
                        else if(e5 == 1 && e6 == 8) 
                            strcat(valExtenso, "dezoito"); 
                        else if(e5 == 1 && e6 == 9) 
                            strcat(valExtenso, "dezenove"); 
                        else if (e5 == 2)
                            strcat(valExtenso, "vinte ");
                        else if (e5 == 3)
                            strcat(valExtenso, "trinta ");
                        else if (e5 == 4)
                            strcat(valExtenso, "quarenta ");
                        else if (e5 == 5)
                            strcat(valExtenso, "cinquenta ");
                        else if (e5 == 6)
                            strcat(valExtenso, "sessenta ");
                        else if (e5 == 7)
                            strcat(valExtenso, "setenta ");
                        else if (e5 == 8)
                            strcat(valExtenso, "oitenta ");
                        else if (e5 == 9)
                            strcat(valExtenso, "noventa ");             
                    }
                    if(e6 != 0 && e5 != 1) {
                        if(e5 != 0 || e4 != 0)
                            strcat(valExtenso, "e ");

                        if(e6 == 1) 
                            strcat(valExtenso, "um");
                        else if(e6 == 2) 
                            strcat(valExtenso, "dois");
                        else if(e6 == 3) 
                            strcat(valExtenso, "tres"); 
                        else if(e6 == 4) 
                            strcat(valExtenso, "quatro"); 
                        else if(e6 == 5) 
                            strcat(valExtenso, "cinco"); 
                        else if(e6 == 6) 
                            strcat(valExtenso, "seis"); 
                        else if(e6 == 7) 
                            strcat(valExtenso, "sete"); 
                        else if(e6 == 8) 
                            strcat(valExtenso, "oito"); 
                        else if(e6 == 9) 
                            strcat(valExtenso, "nove");  
                    }

                    printf("%s\n\n", valExtenso);
                    printf("[SAIDA] Saque %d:\n%d notas de 450\n%d notas de 250\n%d notas de 50\n%d notas de 20\n%d notas de 10\n%d notas de 5\n%d notas de 2\n%d notas de 1\n", saque, saque450, saque250, saque50, saque20, saque10, saque5, saque2, saque1);
                    saldo -= saque; //o saldo PRECISA ser calculado aqui
                    totalSacado += saque;
                }
            break;
            case 2: // menu gerente
                do {
                    system("cls");
                    printf("--------<[ Menu gerente ]>--------\n(1) Valor total sacado\n(2) Valor do saldo existente\n(3) Quantidade de cedulas existentes\n(4) Abastecer o caixa eletronico\n(5) Voltar ao menu principal\n\n -> Sua escolha: ");
                    scanf("%d", &escolhaGerente);
                    switch(escolhaGerente){
                        case 1: //valor total sacado
                            printf(" [SAIDA] O valor total sacado nesse caixa eletronico foi de %d reais\n\n", totalSacado);
                        break;
                        case 2: //Valor do saldo existente
                            //não se calcula o saldo aqui, já que o saldo só atualizaria quando se escolhesse essa opção
                            printf(" [SAIDA] Saldo existente: %d\n\n", saldo);
                        break;
                        case 3: //quantidade de cedulas existentes
                            printf(" [SAIDA] Quantidade de cedulas:\nCedulas de 450: %d\nCedulas de 250: %d\nCedulas de 50: %d\nCedulas de 20: %d\nCedulas de 10: %d\nCedulas de 5: %d\nCedulas de 2: %d\nCedulas de 1: %d\n\n", cedulas450, cedulas250, cedulas50, cedulas20, cedulas10, cedulas5, cedulas2, cedulas1);
                        break;
                        case 4: //Abastecer caixa eletronico
                            do {
                                system("cls");
                                printf("-------<[ Menu abastecer o caixa eletronico ]>-------\n(450) Cedulas de 450\n(250) Cedulas de 250\n(50) Cedulas de 50\n(20) Cedulas de 20\n(10) Cedulas de 10\n(5) Cedulas de 5\n(2) Cedulas de 2\n(1) Cedulas de 1\n(0) Voltar para o menu gerente\n\n -> Sua escolha: ");
                                scanf("%d", &escolhaCedulas);
                                switch(escolhaCedulas){
                                    case 450:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite450 < qntCedulas + cedulas450) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 450 reais!\n", qntCedulas, limite450);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas450 += qntCedulas;
                                    break;
                                    case 250:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite250 < qntCedulas + cedulas250) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 250 reais!\n", qntCedulas, limite250);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas250 += qntCedulas;
                                    break;
                                    case 50:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite50 < qntCedulas + cedulas50) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 50 reais!\n", qntCedulas, limite50);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas50 += qntCedulas;
                                    break;
                                    case 20:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite20 < qntCedulas + cedulas20) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 20 reais!\n", qntCedulas, limite20);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas20 += qntCedulas;
                                    break;
                                    case 10:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite10 < qntCedulas + cedulas10) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 10 reais!\n", qntCedulas, limite10);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas10 += qntCedulas;
                                    break;
                                    case 5:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite5 < qntCedulas + cedulas5) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 5 reais!\n", qntCedulas, limite5);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas5 += qntCedulas;
                                    break;
                                    case 2:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite2 < qntCedulas + cedulas2) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 2 reais!\n", qntCedulas, limite2);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas2 += qntCedulas;
                                    break;
                                    case 1:
                                        printf(" -> Quantidade de cedulas de %d: ", escolhaCedulas);
                                        scanf("%d", &qntCedulas);
                                        if(limite1 < qntCedulas + cedulas1) {
                                            printf(" [ERRO!] A quantidade (%d) ultrapassa o limite de %d cedulas de 1 real!\n", qntCedulas, limite1);
                                            break;
                                        }
                                        if (qntCedulas <= 0) {
                                            printf(" [ERRO!] Impossivel inserir valores negativos ou neutros.\n");
                                            break;
                                        }
                                        cedulas1 += qntCedulas;
                                    break;
                                    case 0:
                                        printf("Retornando ao menu gerente...\n\n");
                                    break;
                                    default:
                                        printf(" [ERRO!] Escolha uma opcao valida!\n");
                                }
                                saldo = cedulas450 * 450 + cedulas250 * 250 + cedulas50 * 50 + cedulas20 * 20 + cedulas10 * 10 + cedulas5 * 5 + cedulas2 * 2 + cedulas1;
                                //atualizar o saldo depois do abastecimento
                                if(escolhaCedulas != 0)
                                    system("pause");
                            } while (escolhaCedulas != 0);
                        break;
                        case 5: //sair
                            printf("Voltando ao menu principal...\n\n");
                        break;
                        default:
                            printf(" [ERRO!] Escolha uma opcao valida!\n\n");
                    }
                    if(escolhaGerente != 5)
                        system("pause");
                } while (escolhaGerente != 5);


            break;
            case 3:
                printf("Finalizado...\n\n");
            break;
            default:
                printf(" [ERRO!] Escolha um valor valido!\n");
        }
        system("pause");
    } while (escolha != 3);
}
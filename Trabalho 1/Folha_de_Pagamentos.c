//Folha de Pagamentos
#include <stdio.h>
#include <stdlib.h>

int main(){
    //checagem e inicialização padrão.
    int qntFunc;
    int matricula, salario;

    do{
        printf("Informe a quantidade de funcionarios: ");
        scanf("%d", &qntFunc);
        if(qntFunc > 10000 || qntFunc < 1) printf("A quantidade de funcionarios deve estar entre 1 e 10000!\n");
    } while (qntFunc > 10000 || qntFunc < 1);

    for(int i = 1; i <= qntFunc; i++){
        do {
            printf("Insira a matricula do funcionario %d: ", i);
            scanf("%d", &matricula);
            if(matricula < 1 || matricula > 30000) printf("O valor da matricula precisa estar entre 1 e 30000!\n");
        } while (matricula < 1 || matricula > 30000);

        salario = matricula; //um numero é divisível por ele mesmo. wow

        //poupar recursos, pois sabe-se que não há divisor inteiro maior que N/2 além do próprio número que já foi somado.
        for(int divisor = 1; divisor <= matricula/2; divisor++){
            if(matricula % divisor == 0) salario += divisor;
        }
        printf("Salario reajustado do funcionario %d: %d\n\n", i, salario);
    }
}

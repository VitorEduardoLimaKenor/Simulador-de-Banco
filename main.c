#include "operacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    infoConta conta;
    int opcaoTelaInicial;
    int opcaoTelaConta;
    int sairDoMenu = 0;
    char *contaAtual;
    float qtdDeposito;
    float qtdSaque;

    do{
        telaInicial();
        scanf("%d", &opcaoTelaInicial);

        if(opcaoTelaInicial == 1){
            telaLogin(&contaAtual);

            do{
                contaCliente(contaAtual, &conta, &opcaoTelaConta);

                if(opcaoTelaConta == 0){
                    system("cls");
                    printf("Crie uma conta primeiro\n");
                    system("pause");
                }else if(opcaoTelaConta == 1){
                    system("cls");
                    printf("Quantidade do deposito: ");
                    scanf("%f", &qtdDeposito);
                    depositar(contaAtual, &conta, qtdDeposito);
                }else if(opcaoTelaConta == 2){
                    system("cls");
                    printf("Quantidade do saque: ");
                    scanf("%f", &qtdSaque);
                    sacar(contaAtual, &conta, qtdSaque);
                }
            }while(opcaoTelaConta != 3 && opcaoTelaConta != 0);

            free(contaAtual);
        }else if(opcaoTelaInicial == 2){
            telaCadastro(&conta);
            criarContaCliente(&conta);
        }else if(opcaoTelaInicial == 3){
            sairDoMenu++;
        }
    }while(sairDoMenu == 0);

        return 0;
}

#include "operacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void telaInicial(){
    system("cls");
    printf("_______________________________\n");
    printf("| Simulador de Conta Bancaria |\n");
    printf("|_____________________________|\n");
    printf("| 1 - Fazer Login             |\n");
    printf("| 2 - Cadastrar-se            |\n");
    printf("| 3 - Sair                    |\n");
    printf("|_____________________________|\n");
    printf("        >>> ");
}

void telaCadastro(infoConta *conta){
    int escolha;

    system("cls");
    printf("_____________________________________\n");
    printf("| Digite seus dados para o cadastro |\n");
    printf("|___________________________________|\n");
    printf(" Nome (sem espacos): ");
    scanf(" %[^\n]", conta->cliente.nome);
    printf(" CPF (sem espacos): ");
    scanf(" %[^\n]", conta->cliente.cpf);
    do{
        printf(" Criar conta poupanca(1) ou corrente(2): ");
        scanf("%d", &escolha);
    }while(escolha > 2 || escolha < 1);
    if(escolha == 1){
        conta->tpct.id = 1;
        strcpy(conta->tpct.tipo,"Poupanca");
    }else{
        conta->tpct.id = 2;
        strcpy(conta->tpct.tipo,"Corrente");
    }
}

void criarContaCliente(infoConta *conta){
    FILE *arquivo;
    char nomeArquivo[24];

    sprintf(nomeArquivo,"%s.txt",conta->cliente.cpf);

    arquivo = fopen(nomeArquivo,"w");
    if(arquivo == NULL){
        printf("\nErro ao abrir a sua conta, seu CPF nao foi aceito\n");
    }else{
        printf("\nConta criada com sucesso\n");

        fprintf(arquivo,"%s\n",conta->cliente.nome);
        fprintf(arquivo,"%d\n",conta->tpct.id);
        fprintf(arquivo,"%s\n",conta->tpct.tipo);
        fprintf(arquivo,"0");
        fclose(arquivo);
    }
    system("pause");
}

void telaLogin(char **contaAtual){
    FILE *arquivo;
    char cpf[20];
    char nomeArquivo[24];

    system("cls");
    printf("_______________________________________\n");
    printf("| Digite seu CPF para entrar na conta |\n");
    printf("|_____________________________________|\n");
    printf(" CPF (sem espacos): ");
    scanf(" %s", cpf);

    sprintf(nomeArquivo,"%s.txt",cpf);

    arquivo = fopen(nomeArquivo,"r");

    if(arquivo == NULL){
        printf("\nConta nao existe\n");
        system("pause");
    }else{
        *contaAtual = malloc(strlen(nomeArquivo) + 1);
        if(*contaAtual == NULL){
            printf("\nERRO AO ALOCAR\n");
            system("pause");
        }else{
            strcpy(*contaAtual, nomeArquivo);
        }
    }
}

void contaCliente(char *contaAtual, infoConta *conta, int *opcaoTelaConta){
    FILE *arquivo;

    arquivo = fopen(contaAtual,"r");
    if(arquivo == NULL){
        *opcaoTelaConta = 0;
        return;
    }
    fscanf(arquivo,"%s", conta->cliente.nome);
    fscanf(arquivo,"%d", &conta->tpct.id);
    fscanf(arquivo,"%s", conta->tpct.tipo);
    fscanf(arquivo,"%f", &conta->saldo);
    fclose(arquivo);

    do{
        system("cls");
        printf("_______________________________\n");
        printf("  OLA, %s\n",conta->cliente.nome);
        printf("  Bem vindo a sua conta %s\n",conta->tpct.tipo);
        printf("  SALDO: %.2f R$\n",conta->saldo);
        printf("_______________________________\n");
        printf("| 1 - Depositar               |\n");
        printf("| 2 - Sacar                   |\n");
        printf("| 3 - Sair                    |\n");
        printf("|_____________________________|\n");
        printf("        >>> ");
        scanf("%d",opcaoTelaConta);
    }while(*opcaoTelaConta > 3 || *opcaoTelaConta < 1);
}

void depositar(char *contaAtual, infoConta *conta, float qtd_dinheiro){
    FILE *arquivo;
    float deposito;

    arquivo = fopen(contaAtual,"w");

    deposito = conta->saldo + qtd_dinheiro;

    fprintf(arquivo,"%s\n",conta->cliente.nome);
    fprintf(arquivo,"%d\n",conta->tpct.id);
    fprintf(arquivo,"%s\n",conta->tpct.tipo);
    fprintf(arquivo,"%.2f",deposito);
    fclose(arquivo);
}

void sacar(char *contaAtual, infoConta *conta, float qtd_dinheiro){
    FILE *arquivo;
    float saque;

    arquivo = fopen(contaAtual,"w");
    if(conta->tpct.id == 1){
        if(conta->saldo < qtd_dinheiro){
            printf("\nSaldo insuficiente\n");
            printf("Crie uma conta corrente para poder ter limite\n");
            system("pause");
            fprintf(arquivo,"%s\n",conta->cliente.nome);
            fprintf(arquivo,"%d\n",conta->tpct.id);
            fprintf(arquivo,"%s\n",conta->tpct.tipo);
            fprintf(arquivo,"%.2f",conta->saldo);
            fclose(arquivo);
            return;
        }else{
            saque = conta->saldo - qtd_dinheiro;
            fprintf(arquivo,"%s\n",conta->cliente.nome);
            fprintf(arquivo,"%d\n",conta->tpct.id);
            fprintf(arquivo,"%s\n",conta->tpct.tipo);
            fprintf(arquivo,"%.2f",saque);
            fclose(arquivo);
            }
    }else{
            if(conta->saldo + 200 < qtd_dinheiro){
            printf("\nSaldo insuficiente\n");
            system("pause");
            fprintf(arquivo,"%s\n",conta->cliente.nome);
            fprintf(arquivo,"%d\n",conta->tpct.id);
            fprintf(arquivo,"%s\n",conta->tpct.tipo);
            fprintf(arquivo,"%.2f",conta->saldo);
            fclose(arquivo);
            return;
        }else{
            saque = conta->saldo - qtd_dinheiro;
            fprintf(arquivo,"%s\n",conta->cliente.nome);
            fprintf(arquivo,"%d\n",conta->tpct.id);
            fprintf(arquivo,"%s\n",conta->tpct.tipo);
            fprintf(arquivo,"%.2f",saque);
            fclose(arquivo);
        }
    }
}

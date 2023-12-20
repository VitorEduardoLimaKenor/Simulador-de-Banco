#ifndef OPERACOES_H_INCLUDED
#define OPERACOES_H_INCLUDED

typedef struct{
    char nome[50];
    char cpf[20];
}infoCliente;

typedef struct{
    int id;
    char tipo[10];
}tipoConta;

typedef struct{
    infoCliente cliente;
    tipoConta tpct;
    float saldo;
}infoConta;

void telaInicial();
void telaCadastro(infoConta *conta);
void criarContaCliente(infoConta *conta);
void telaLogin(char **contaAtual);
void contaCliente(char *contaAtual, infoConta *conta, int *opcao);
void depositar(char *contaAtual, infoConta *conta, float qtd_dinheiro);
void sacar(char *contaAtual, infoConta *conta, float qtd_dinheiro);

#endif // OPERACOES_H_INCLUDED

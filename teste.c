#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[30];
  char cpf[11];
  char dataDeNascimento [10];
  float salarioBase ;
  float totalVendido;
} vendedor;

int cadastroNovos (vendedor *cadastroVendedores, int quantTotal);

int main(void) {
  int opcao=0,quantTotal=0;
  vendedor *cadastroVendedores;

  cadastroVendedores = (vendedor *) malloc (1*sizeof(vendedor));
  if(cadastroVendedores == NULL){
    printf("ERRO DE ALOCACAO!");
    exit(1);
  }
  
  do {
    printf("--------------------MENU--------------------");
    printf("\nEscolha uma opcao:");

    printf("\n1 - Cadastrar Novos Vendedores.");
    printf("\n2 - Mostrar os dados de todos os Vendedores Cadastrados.");
    printf("\n3 - Calcular comissoes.");
    printf("\n4 - Mostrar dados de um vendedor especifico.");
    printf("\n0 - Sair do Programa.\n\n");

    scanf("%d", &opcao);
    
    switch(opcao){
      case 1:
      cadastroNovos(cadastroVendedores, quantTotal);
      // case 2:
      // listarVendedores(cadastroVendedores, quantTotal);
    }
    
  }while(opcao!=0);
  
  return 0;
}

int cadastroNovos (vendedor *cadastroVendedores, int quantTotal){
  int quantCadastros,i=0;
  
  printf("Quantos vendedores deseja cadastrar?: ");
  scanf("%d",&quantCadastros);

  cadastroVendedores = (vendedor *) realloc(cadastroVendedores, quantCadastros * sizeof(vendedor));

  for(i=0; i<quantCadastros; i++){
    printf("Informe o nome do funcionario:");
    fflush(stdin);
    scanf ( "%[^\n]%*c", cadastroVendedores[i].nome);
    printf("Informe o cpf do vendedor:");
    scanf("%s%*c", cadastroVendedores[i].cpf);
    printf("Informe a data de nascimento do vendedor, no formato dd/mm/aaaa\n");
    scanf("%s%*c", cadastroVendedores[i].dataDeNascimento);
    printf("Informe o salario base do vendedor: ");
    scanf("%f%*c",&cadastroVendedores[i].salarioBase);
    printf("Informe o total de vendas do vendedor: ");
    scanf("%f%*c",&cadastroVendedores[i].totalVendido);
    system("cls");
  }
  quantTotal = quantTotal + quantCadastros;
  return quantTotal;
}

// void listarVendedores (vendedor *cadastrovendedores, int quantTotal){

// }
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

int cadastroNovos (vendedor *cadastroVendedores, int *quantTotal, int *j);
void ordenaVendedores(vendedor *cadastroVendedores, vendedor auxiliar, int quantTotal);
void listarVendedores (vendedor *cadastroVendedores, int quantTotal);
void calcularComissoes ( vendedor *cadastroVendedores, int quantTotal);

int main(void) {
  int opcao = 0,quantTotal = 0, j = 0;
  vendedor *cadastroVendedores, auxiliar;

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
        cadastroVendedores = cadastroNovos(cadastroVendedores, &quantTotal, &j);
        ordenaVendedores(cadastroVendedores, auxiliar, quantTotal);
        break;
      case 2:
        listarVendedores(cadastroVendedores, quantTotal);
        break;
      case 3:
        calcularComissoes(cadastroVendedores, quantTotal);
    }
  }while(opcao!=0);
  
  return 0;
}

int  cadastroNovos (vendedor *cadastroVendedores, int *quantTotal, int *j){
  int quantCadastros, i;

  printf("Quantos vendedores deseja cadastrar?: ");
  scanf("%d",&quantCadastros);
  *quantTotal = *quantTotal + quantCadastros;

  cadastroVendedores = (vendedor *) realloc(cadastroVendedores, *quantTotal * sizeof(vendedor));

  for(i=*j; i<(*quantTotal); i++){
    printf("Informe o nome do funcionario:");
    fflush(stdin);
    scanf ("%[^\n]%*c", cadastroVendedores[i].nome);
    fflush(stdin);
    printf("Informe o cpf do vendedor:");
    scanf("%s%*c", cadastroVendedores[i].cpf);
    fflush(stdin);
    printf("Informe a data de nascimento do vendedor, no formato dd/mm/aaaa\n");
    scanf("%s%*c", cadastroVendedores[i].dataDeNascimento);
    fflush(stdin);
    printf("Informe o salario base do vendedor: ");
    scanf("%f%*c", &cadastroVendedores[i].salarioBase);
    fflush(stdin);
    printf("Informe o total de vendas do vendedor: ");
    scanf("%f%*c", &cadastroVendedores[i].totalVendido);
    fflush(stdin);
    system("cls");
    *j+=1;
  }
  
  return cadastroVendedores;
}

void ordenaVendedores(vendedor *cadastroVendedores, vendedor auxiliar, int quantTotal){
  int i, j;

  for(i=0; i<quantTotal-1; i++){
    for(j=i+1; j<quantTotal; j++){
      if(strcmp(cadastroVendedores[i].nome, cadastroVendedores[j].nome) < 0)
        auxiliar = cadastroVendedores[i];
        cadastroVendedores[i] = cadastroVendedores[j];
        cadastroVendedores[j] = auxiliar;
    }
  }
}

 void listarVendedores (vendedor *cadastroVendedores, int quantTotal){
  int i;

  for(i=0; i<quantTotal; i++){
   printf("\n\nNome: %s", cadastroVendedores[i].nome);
   printf("\nCPF: %s", cadastroVendedores[i].cpf);
   printf("\nData de nascimento: %s", cadastroVendedores[i].dataDeNascimento);
   printf("\nSalario base: %.2f", cadastroVendedores[i].salarioBase);
   printf("\ntotal vendido: %.2f\n", cadastroVendedores[i].totalVendido);
  }
}

void calcularComissoes ( vendedor *cadastroVendedores, int quantTotal){

  int i;
  
  for(i=0; i<quantTotal; i++){
    printf("\n%s R$ ", cadastroVendedores[i].nome);
    printf("%.2f\n\n", cadastroVendedores[i].totalVendido*0.03);
  }
}

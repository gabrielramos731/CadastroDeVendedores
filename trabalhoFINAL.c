#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura de cadastro dos vendedores
typedef struct{
  char nome[30];
  char cpf[11];
  char dataDeNascimento [10];
  float salarioBase ;
  float totalVendido;
} vendedor;

//inicialização de funções
vendedor * cadastroNovos (vendedor *cadastroVendedores, int *quantTotal, int *j);
void ordenaVendedores(vendedor *cadastroVendedores, int quantTotal);
void listarVendedores (vendedor *cadastroVendedores, int quantTotal);
void calcularComissoes ( vendedor *cadastroVendedores, int quantTotal);
void buscaEspecifica (vendedor *cadastroVendedores, int opcaoCase4, int quantTotal);

//função principal
int main(void) {
  int opcao, quantTotal = 0, j = 0, opcaoCase4 = 0;
  vendedor *cadastroVendedores;

  cadastroVendedores = (vendedor *) malloc (1*sizeof(vendedor));
  if(cadastroVendedores == NULL){
    printf("ERRO DE ALOCACAO!");
    exit(1);
  }

  //Menu
  do {
    printf("--------------------MENU--------------------");
    printf("\nEscolha uma opcao:\n");
    printf("\n1 - Cadastrar Novos Vendedores.");
    printf("\n2 - Mostrar os dados de todos os Vendedores Cadastrados.");
    printf("\n3 - Calcular comissoes.");
    printf("\n4 - Mostrar dados de um vendedor especifico.");
    printf("\n0 - Sair do Programa.\n\n");

    scanf("%d", &opcao);
    
    switch(opcao){
        case 1:
          cadastroVendedores = cadastroNovos(cadastroVendedores, &quantTotal, &j);
          ordenaVendedores(cadastroVendedores, quantTotal);
          break;
        case 2:
          listarVendedores(cadastroVendedores, quantTotal);
          break;
        case 3:
          calcularComissoes(cadastroVendedores, quantTotal);
          break;
        case 4:
          printf("Como deseja fazer a busca?\n1 - Por nome\n2 - Por CPF\n3 - Por data de nascimento\n4 - Por salario base\n5 - Por total de vendas\n0 - Para voltar ao menu principal\n");
          scanf("%d",&opcaoCase4);
          buscaEspecifica(cadastroVendedores,opcaoCase4,quantTotal);
        case 0:
          break;
        default:
          printf("Opcao inexistente!\n\n");
    }
  }while(opcao!=0);

  return 0;
}

vendedor * cadastroNovos (vendedor *cadastroVendedores, int *quantTotal, int *j){
  int quantCadastros, i;

  printf("Quantos vendedores deseja cadastrar?: ");
  scanf("%d%*c",&quantCadastros);
  fflush(stdin);
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

void listarVendedores (vendedor *cadastroVendedores, int quantTotal){
  int i;

  for(i=0; i<quantTotal; i++){
   printf("\n\nNome: %s", cadastroVendedores[i].nome);
   printf("\nCPF: %s", cadastroVendedores[i].cpf);
   printf("\nData de nascimento: %s", cadastroVendedores[i].dataDeNascimento);
   printf("\nSalario base: %.2f", cadastroVendedores[i].salarioBase);
   printf("\ntotal vendido: %.2f\n", cadastroVendedores[i].totalVendido);
  }
  printf("\n");
}

void ordenaVendedores(vendedor *cadastroVendedores, int quantTotal){
  int i, j;
  vendedor auxiliar;

  for(i=1; i<quantTotal; i++){
    auxiliar = cadastroVendedores[i];
      for(j=i; (j>0) && (strcmp(auxiliar.nome, cadastroVendedores[j-1].nome)<0); j--){
        cadastroVendedores[j] = cadastroVendedores[j-1];
      }
      cadastroVendedores[j] = auxiliar;
  }
}

void calcularComissoes ( vendedor *cadastroVendedores, int quantTotal){

  int i;
  
  for(i=0; i<quantTotal; i++){
    printf("\n%s R$ ", cadastroVendedores[i].nome);
    printf("%.2f\n\n", cadastroVendedores[i].totalVendido*0.03);
  }
}

void buscaEspecifica (vendedor *cadastroVendedores, int opcaoCase4, int quantTotal){
  char buscaChar[30];
  float buscaFloat=0;
  int existe=1, ativado=0;

  switch (opcaoCase4){
    case 1:
      printf("Informe o nome do funcionario: ");
      fflush(stdin);
      scanf ("%[^\n]", buscaChar);
      //funcao de busca binaria de nome
      for(int i=0;i<quantTotal;i++){
        existe = strcmp(buscaChar,cadastroVendedores[i].nome);
        if(existe==0){
          printf("\nVendedor encontrado!");
          printf("\n\nNome: %s", cadastroVendedores[i].nome);
          printf("\nCPF: %s", cadastroVendedores[i].cpf);
          printf("\nData de nascimento: %s", cadastroVendedores[i].dataDeNascimento);
          printf("\nSalario base: %.2f", cadastroVendedores[i].salarioBase);
          printf("\ntotal vendido: %.2f\n", cadastroVendedores[i].totalVendido);
          ativado=1;
        }
      }
      if(ativado!=1){
          printf("\nVendedor nao encontrado!\n\n");
        }
      break;

    case 2:
      printf("Informe o CPF do funcionario:");
      fflush(stdin);
      scanf ("%[^\n]", buscaChar);
      //funcao de busca binarai de cpf
      for(int i=0;i<quantTotal;i++){
        existe = strcmp(buscaChar,cadastroVendedores[i].cpf);
        if(existe==0){
          printf("\nVendedor encontrado!");
          printf("\n\nNome: %s", cadastroVendedores[i].nome);
          printf("\nCPF: %s", cadastroVendedores[i].cpf);
          printf("\nData de nascimento: %s", cadastroVendedores[i].dataDeNascimento);
          printf("\nSalario base: %.2f", cadastroVendedores[i].salarioBase);
          printf("\ntotal vendido: %.2f\n", cadastroVendedores[i].totalVendido);
          ativado=1;
        }
      }
      if(ativado!=1){
          printf("\nVendedor nao encontrado!\n\n");
        }
      break;

    case 3:
      printf("Informe a data de nascimento do funcionario:");
      fflush(stdin);
      scanf ("%[^\n]", buscaChar);
      //funcao de busca binaria de data de nascimento
      for(int i=0;i<quantTotal;i++){
        existe = strcmp(buscaChar,cadastroVendedores[i].dataDeNascimento);
        if(existe==0){
          printf("\nVendedor encontrado!");
          printf("\n\nNome: %s", cadastroVendedores[i].nome);
          printf("\nCPF: %s", cadastroVendedores[i].cpf);
          printf("\nData de nascimento: %s", cadastroVendedores[i].dataDeNascimento);
          printf("\nSalario base: %.2f", cadastroVendedores[i].salarioBase);
          printf("\ntotal vendido: %.2f\n", cadastroVendedores[i].totalVendido);
          ativado=1;
        }
      }
      if(ativado!=1){
          printf("\nVendedor nao encontrado!\n\n");
        }
      break;

    case 4:
      printf("Informe o salario do funcionario:");
      fflush(stdin);
      scanf("%f", &buscaFloat);
      //funcao de busca binaria de salario base
      for(int i=0;i<quantTotal;i++){
        if(cadastroVendedores[i].salarioBase==buscaFloat){
          printf("\nVendedor encontrado!");
          printf("\n\nNome: %s", cadastroVendedores[i].nome);
          printf("\nCPF: %s", cadastroVendedores[i].cpf);
          printf("\nData de nascimento: %s", cadastroVendedores[i].dataDeNascimento);
          printf("\nSalario base: %.2f", cadastroVendedores[i].salarioBase);
          printf("\ntotal vendido: %.2f\n", cadastroVendedores[i].totalVendido);
          ativado=1;
        }
      }
      if(ativado!=1){
          printf("\nVendedor nao encontrado!\n\n");
        }
      break;

    case 5:
      printf("Informe o total de vendas do funcionario:");
      fflush(stdin);
      scanf("%f", &buscaFloat);
      //funcao de busca binaria de total de vendas
      for(int i=0;i<quantTotal;i++){
        if(cadastroVendedores[i].totalVendido==buscaFloat){
          printf("\nVendedor encontrado!");
          printf("\n\nNome: %s", cadastroVendedores[i].nome);
          printf("\nCPF: %s", cadastroVendedores[i].cpf);
          printf("\nData de nascimento: %s", cadastroVendedores[i].dataDeNascimento);
          printf("\nSalario base: %.2f", cadastroVendedores[i].salarioBase);
          printf("\ntotal vendido: %.2f\n", cadastroVendedores[i].totalVendido);
          ativado=1;
        }
      }
      if(ativado!=1){
          printf("\nVendedor nao encontrado!\n\n");
        }
      break;

    case 0:
      printf("Encerrando processo!\n\n");
      break;
    default:
      printf("Funcao inexistente!\n\n");
      break;
  }
}
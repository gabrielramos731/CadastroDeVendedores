#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contadorCadastros = 0;

typedef struct{
  char nome[30];
  char cpf[11];
  char dataDeNascimento [10];
  float salarioBase;
  float totalVendido;
} vendedor;

vendedor * cadastroNovos (vendedor *cadastroVendedores, int *quantTotal, int *j);
void ordenaVendedores(vendedor *cadastroVendedores, int quantTotal);
void listarVendedores (vendedor *cadastroVendedores, int quantTotal);
void calcularComissoes ( vendedor *cadastroVendedores, int quantTotal);
int buscarVendedor(vendedor *cadastroVendedores, int quantTotal, char *nomeBuscado);

int main(void) {
  int opcao = 0, quantTotal = 0, j = 0, i = 0, indiceBusca, indiceInicial = 0;
  char nomeBuscado[30];
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
        cadastroVendedores = cadastroNovos(cadastroVendedores, &quantTotal, &j);
        printf("\n%d\n", quantTotal);
        ordenaVendedores(cadastroVendedores, quantTotal);
        break;
      case 2:
        if(contadorCadastros == 0){
          printf("\nNenhum vendedor cadastrado!\n\n");
          break;
        }
        listarVendedores(cadastroVendedores, quantTotal);
        break;
      case 3:
        if(contadorCadastros == 0){
          printf("\nNenhum vendedor cadastrado!\n\n");
          break;
        }
        calcularComissoes(cadastroVendedores, quantTotal);
        break;
      case 4:
        if(contadorCadastros == 0){
          printf("\nNenhum vendedor cadastrado!\n\n");
          break;
        }
        printf("Digite o nome do vendedor que deseja buscar: ");
        fflush(stdin);
        scanf ("%[^\n]%*c", nomeBuscado);
        indiceBusca = buscarVendedor(cadastroVendedores, quantTotal, nomeBuscado);
        if(indiceBusca == -1){
          printf("\nVendedor nao cadastrado!\n\n");
          break;
        }
        i = 1;   
        indiceInicial = indiceBusca;
        while(strcmp(cadastroVendedores[indiceBusca].nome, cadastroVendedores[indiceBusca-i].nome) == 0){   //retorna para o índice do primeiro valor repetido
          indiceInicial--;
          i++;
        }
        i = 0;
        while(strcmp(cadastroVendedores[indiceInicial].nome, cadastroVendedores[indiceInicial+i].nome) == 0){
          printf("\nNome: %s", cadastroVendedores[indiceInicial+i].nome);
          printf("\nCPF: %s", cadastroVendedores[indiceInicial+i].cpf);
          printf("\nData de nascimento: %s", cadastroVendedores[indiceInicial+i].dataDeNascimento);
          printf("\nSalario base: %.2f", cadastroVendedores[indiceInicial+i].salarioBase);
          printf("\ntotal vendido: %.2f\n\n", cadastroVendedores[indiceInicial+i].totalVendido);
          i++;
        }
        break;
      case 0:
        free(cadastroVendedores);
        printf("\nEncerrando processo!");
        break;
      default:
        printf("Opcao invalida!\n");
    }
  }while(opcao!=0);
  
  return 0;
}

vendedor * cadastroNovos (vendedor *cadastroVendedores, int *quantTotal, int *j){
  contadorCadastros = 1;
  int quantCadastros, i, k, cont;
  
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
    cont = 0;
    for(k=0; k<i; k++){
      if(strcmp(cadastroVendedores[k].cpf, cadastroVendedores[i].cpf) == 0){
        cont++;
      }
    }
    if(cont == 0){
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
    else{
      printf("\nCPF ja existente! Por favor cadastre novamente.\n\n");
      i--;
    }
    
  }
  return cadastroVendedores;
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

//buscar até o primeiro repetido e dps ir até o último

int buscarVendedor(vendedor *cadastroVendedores, int quantTotal, char *nomeBuscado){
  int meio, ini = 0;

  meio = (ini+quantTotal)/2;
  while(ini<quantTotal+1){
    meio = (ini+quantTotal)/2;
    if(strcmp(cadastroVendedores[meio].nome, nomeBuscado) == 0){
      return meio;
    }
    else if(strcmp(cadastroVendedores[meio].nome, nomeBuscado) < 0)
      ini = meio+1;
    else{
      quantTotal = meio-1;
      printf("%d", meio);
    }
  }
  printf("%d", meio);
  return -1;
}

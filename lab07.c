/*
  Luccas Delgado Targa
  2019011503

  README: Professor, como não foi especificado a maneira que nós tínhamos que fazer,
  eu utilizei ponteiros, dessa forma, não foi necessário a implementação das funções
  inicializaPilha() e resisDisponivel().

*/



#include <stdio.h>
#include <stdlib.h>

typedef enum{false, true} bool; //Somente ANSI C

typedef struct no{
   int valor;
   int quant;
   struct no* prox;
} noResis; //estrutura dos resistores

noResis *pilha[7]; //pilhas de resistores
//Lista de valores de resistor
int valorResis[7] = {2,3,5,10,20,50,100};

noResis *prim = NULL;
noResis *ult = NULL;

//void inicializaPilha();
void abastecePilha(int quant, int valor);
void imprimeTudo();
void imprimeSoma();
//bool resisDisponivel(int valor);
bool entrega(int valor);

int main(int argc, char ** argv){
  int i;
  //inicializaPilha();
  abastecePilha(55, 2);
  abastecePilha(42, 3);
  abastecePilha(61, 5);
  abastecePilha(28, 10);
  abastecePilha(35, 20);
  abastecePilha(64, 50);
  abastecePilha(14, 100);

  printf("    Valor Inicial do Almoxarifado   \n");
  printf("====================================\n");
  imprimeTudo();
  imprimeSoma();

  int pedidos[4] = {43,75,123,256};
  for(i=0;i<4;i++){
	  printf("______________________________\n");
	  printf("Pedido de = %d ohms\n",pedidos[i]);
	  printf("Verificando almoxarifado: ");
	  if (entrega(pedidos[i])){
		  printf(" disponível!\n");
		  imprimeTudo();
		  imprimeSoma();
	  }
	  else{
		  printf(" indisponível!\n");
	  }
  }

  printf("     Valor Final do Almoxarifado   \n");
  printf("====================================\n");
  imprimeTudo();
  imprimeSoma();

  return 0;
}

void abastecePilha(int quant, int valor){
  noResis *novo = (noResis*)malloc(sizeof(noResis));
  if(prim == NULL){
    ult = novo;
  }//fim if
  //atualizando os valores do nó
  novo->valor = valor;
  novo->quant = quant;
  novo->prox = prim;
  //atualizando o topo
  prim = novo;
}

void imprimeTudo(){
  noResis *atual = prim;
  while (atual != NULL) {
    printf("Valor: %d\nQuantidade: %d\n", atual->valor, atual->quant);
    atual = atual->prox;
  }
  printf("\n");
}

bool entrega(int valor){
  noResis *atual = prim;
  int aux = valor;
  //atualiza a última posição
  if (prim->prox == NULL) {
    ult = NULL;
  }

  while (aux > 0) {
    if ((aux >= atual->valor) && (atual->quant > 0)) {
      aux = aux - atual->valor;
      atual->quant = atual->quant - 1;
    }else{
      if(atual->quant <= 0){
        prim = prim->prox;
        free(atual);
      }//fim if
      atual = atual->prox;
    }//fim else
    if((atual->valor == 2) && (atual->quant <= 0)){
        return false;
    }
  }
  return true;
}

void imprimeSoma(){
  noResis *atual = prim;
  int valorTotal = 0;
  while (atual != NULL) {
    valorTotal += atual->quant * atual->valor;
    atual = atual->prox;
  }
  printf("Soma total dos resistores: %d\n", valorTotal);
}

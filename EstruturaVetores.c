#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 10
#define MAX 15

#include "EstruturaVetores.h"

typedef struct Vetor {
  int *comeco;
  int tamanho;
  int cont;
} Vetor;

Vetor vetorPrincipal[TAM];

void printList(No *n) {
  printf("\n\nLista\n");
  while (n != NULL) {
    printf("[%d]->", n->conteudo);
    n = n->prox;
  }
  printf("\n\n");

  return;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
  int retorno = 0;
  // se posição é um valor válido {entre 1 e 10}
  if (posicao > 10 || posicao < 1) {
    retorno = POSICAO_INVALIDA;
  }
  // a posicao pode já existir estrutura auxiliar
  else if (vetorPrincipal[posicao - 1].comeco != NULL) {
    retorno = JA_TEM_ESTRUTURA_AUXILIAR;
  }
  // o tamanho ser muito grande
  else if (tamanho > MAX) {
    retorno = SEM_ESPACO_DE_MEMORIA;
  }
  // o tamanho nao pode ser menor que 1
  else if (tamanho < 1) {
    retorno = TAMANHO_INVALIDO;
  }
  // deu tudo certo, crie
  else {
    int *estrutura = (int *)malloc(tamanho * sizeof(int));
    vetorPrincipal[posicao - 1].comeco = estrutura;
    vetorPrincipal[posicao - 1].tamanho = tamanho;
    vetorPrincipal[posicao - 1].cont = 0;
    retorno = SUCESSO;
  }

  return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
  int retorno = 0;
  bool existeEstruturaAuxiliar = true;
  bool temEspaco = true;
  bool posicao_invalida = true;

  if (vetorPrincipal[posicao - 1].comeco == NULL) {
    existeEstruturaAuxiliar = false;
  }
  if (vetorPrincipal[posicao - 1].cont >= vetorPrincipal[posicao - 1].tamanho) {
    temEspaco = false;
  }
  if (posicao >= 1 && posicao <= 10) {
    posicao_invalida = false;
  }

  if (posicao_invalida)
    retorno = POSICAO_INVALIDA;
  else {
    // testar se existe a estrutura auxiliar
    if (existeEstruturaAuxiliar) {
      if (temEspaco) {
        // insere
        vetorPrincipal[posicao - 1].comeco[vetorPrincipal[posicao - 1].cont] =
            valor;
        vetorPrincipal[posicao - 1].cont++;
        retorno = SUCESSO;
      } else {
        retorno = SEM_ESPACO;
      }
    } else {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar
da seguinte forma [3, 8, 7,  ,  ,  ]. Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
  int retorno = SUCESSO;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else if (vetorPrincipal[posicao - 1].comeco == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
  } else if (vetorPrincipal[posicao - 1].cont == 0) {
    retorno = ESTRUTURA_AUXILIAR_VAZIA;
  } else {
    vetorPrincipal[posicao - 1].cont--;
  }

  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições
anteriores ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o
valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ] Obs. Esta é
uma exclusão lógica Rertono (int) SUCESSO - excluido com sucesso 'valor' da
estrutura na posição 'posicao' ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
  int retorno = SUCESSO;
  int aux = 0;
  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else if (vetorPrincipal[posicao - 1].comeco == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
  } else if (vetorPrincipal[posicao - 1].cont == 0) {
    retorno = ESTRUTURA_AUXILIAR_VAZIA;
  } else {
    for (int i = 0; i < vetorPrincipal[posicao - 1].cont; i++) {
      if (vetorPrincipal[posicao - 1].comeco[i] == valor) {
        for (int j = i; j < vetorPrincipal[posicao - 1].cont; j++) {
          vetorPrincipal[posicao - 1].comeco[j] =
              vetorPrincipal[posicao - 1].comeco[j + 1];
        }
        vetorPrincipal[posicao - 1].cont--;
        retorno = SUCESSO;
        break;
      } else {
        retorno = NUMERO_INEXISTENTE;
      }
    }
  }

  return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao) {
  int retorno = 0;
  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else
    retorno = SUCESSO;

  return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar POSICAO_INVALIDA -
Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  int retorno = SUCESSO;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else if (vetorPrincipal[posicao - 1].comeco == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
  } else {
    for (int i = 0; i < vetorPrincipal[posicao - 1].cont; i++) {
      vetorAux[i] = vetorPrincipal[posicao - 1].comeco[i];
    }
  }

  return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao
(1..10)'. os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao
(1..10)' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar POSICAO_INVALIDA -
Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  int retorno = 0;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else if (vetorPrincipal[posicao - 1].comeco == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
  } else {
    for (int i = 0; i < vetorPrincipal[posicao - 1].cont; i++) {
      vetorAux[i] = vetorPrincipal[posicao - 1].comeco[i];
    }
    retorno = insertion_sort(vetorPrincipal[posicao - 1].cont, vetorAux);
  }

  return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
  int retorno = SUCESSO, troca[MAX];
  int aux = 0, cont = 0, i = 0, j = 0;

  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].cont == 0) {
      cont++;
    }
  }

  if (cont == TAM) {
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  } else {
    while (i < TAM) {
      for (j = 0, aux = aux; j < vetorPrincipal[i].cont; j++, aux++) {
        vetorAux[aux] = vetorPrincipal[i].comeco[j];
      }
      i++;
    }
    retorno = SUCESSO;
  }

  return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
  int retorno = 0, troca[MAX];
  int aux = 0, cont = 0, i = 0, j = 0;

  for (int k = 0; k < TAM; k++) {
    if (vetorPrincipal[k].cont == 0) {
      cont++;
    }
  }

  if (cont == TAM) {
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  } else {
    while (i < TAM) {
      for (j = 0, aux = aux; j < vetorPrincipal[i].cont; j++, aux++) {
        vetorAux[aux] = vetorPrincipal[i].comeco[j];
      }
      i++;
    }
    retorno = insertion_sort(aux, vetorAux);
  }

  return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o
novo tamanho 'novoTamanho' + tamanho atual Suponha o tamanho inicial = x, e novo
tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser
sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
  int retorno = 0;
  int *novoEndereco;
  int antigoTamanho = vetorPrincipal[posicao - 1].tamanho;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else if (antigoTamanho + novoTamanho < 1) {
    retorno = NOVO_TAMANHO_INVALIDO;
  } else if (vetorPrincipal[posicao - 1].comeco == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
  } else {
    novoEndereco = (int *)realloc(vetorPrincipal[posicao - 1].comeco,
                                  (antigoTamanho + novoTamanho) * sizeof(int));
    if (novoEndereco == NULL) {
      retorno = SEM_ESPACO_DE_MEMORIA;
    } else {
      vetorPrincipal[posicao - 1].comeco = novoEndereco;
      vetorPrincipal[posicao - 1].tamanho = antigoTamanho + novoTamanho;
      // printf("\n%d",vetorPrincipal[posicao-1].tamanho);
      if (vetorPrincipal[posicao - 1].cont >
          vetorPrincipal[posicao - 1].tamanho) {
        vetorPrincipal[posicao - 1].cont = vetorPrincipal[posicao - 1].tamanho;
      }
      // printf("\n%d\n\n",vetorPrincipal[posicao-1].cont);
      retorno = SUCESSO;
    }
  }

  return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da
posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da
estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
  int retorno = 0;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else if (vetorPrincipal[posicao - 1].comeco == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
  } else if (vetorPrincipal[posicao - 1].cont == 0) {
    retorno = ESTRUTURA_AUXILIAR_VAZIA;
  } else {
    retorno = vetorPrincipal[posicao - 1].cont;
  }

  return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes
em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() {
  Lista *l = criarLista();
  No *novo;
  int i, j;
  for (i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].comeco != NULL) {
      for (j = 0; j < vetorPrincipal[i].cont; j++) {
        addList(l, criarNo(vetorPrincipal[i].comeco[j]));
      }
    }
  }
  // printList(l->inicio);
  if (i == TAM) {
    return l->inicio;
  }
  return NULL;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em
vetorAux. Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
  No *p;
  int i = 0, j, k;

  // printList(inicio);
  for (p = inicio; p != NULL; p = p->prox) {
    vetorAux[i] = p->conteudo;
    i++;
    // printf("%d->",vetorAux[i-1]);
  }
  // printf("\n%d\n",i);
  int aux[i];
  for (j = 0, k = i - 1; j < i; j++, k--) {
    aux[j] = vetorAux[k];
    // printf("%d->", aux[j]);
  }
  // printf("\n%d\n",j);
  for (i = 0; i < j; i++) {
    vetorAux[i] = aux[i];
    // printf("%d->", aux[i]);
  }
  // printf("\n%d\n",i);
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
  No *atual = (*inicio)->prox;
  No *prox;
  while (atual != NULL) {
    prox = atual->prox;
    free(atual);
    atual = prox;
  }
  *inicio = atual;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

void inicializar() {
  for (int i = 0; i < TAM; i++)
    vetorPrincipal[i].comeco = NULL;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar() {
  for (int i = 0; i < TAM; i++)
    free(vetorPrincipal[i].comeco);
}

int insertion_sort(int size, int vet[]) {
  for (int j = 1; j < size; j++) {
    int key = vet[j];
    int i = j - 1;
    while (i > -1 && vet[i] > key) {
      vet[i + 1] = vet[i];
      i--;
    }
    vet[i + 1] = key;
  }
  return SUCESSO;
}

// Criar Lista
Lista *criarLista() {
  Lista *lista = malloc(sizeof(Lista));
  lista->inicio = NULL;

  return lista;
}

// Criar Nó para inserir na lista
No *criarNo(int valor) {
  No *no = malloc(sizeof(No));
  if (no == NULL) {
    return NULL;
    exit(1);
  }
  no->conteudo = valor;
  no->prox = NULL;
  return no;
}

void addList(Lista *l, No *novo) {
  if (l->inicio == NULL) {
    l->inicio = novo;
  } else {
    novo->prox = l->inicio;
    l->inicio = novo;
  }
}
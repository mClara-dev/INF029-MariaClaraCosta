#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *dados;
    int tamMaximo;
    int qtdElementos;
} EstruturaAuxiliar;

EstruturaAuxiliar vetorPrincipal[TAM];

//FUNCOES AUXILIARES:

int ehPosicaoValida(int posicao){
    return (posicao >= 0 && posicao < TAM) ? 1 : 0;
}

int existeEstrutura(int posicao)
{
    if (ehPosicaoValida(posicao) == 0)
        return 0;
    return (vetorPrincipal[posicao].dados != NULL) ? 1 : 0;
}

void ordenaVetor(int vetor[], int N) {
    selectionSort(vetor, N);
}

void selectionSort(int vetor[], int N){
    int min, aux, i, j;

    for(i = 0; i < N; i ++){
        min = i;
        for( j = i + 1; j < N; j++){
            if(vetor[j] < vetor[min]{
                min = j; 
            }
        }   
        aux = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = aux;
    }
}

//FUNCOES PRINCIPAIS

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
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (ehPosicaoValida(posicao) == 0) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao; 

    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    if (vetorPrincipal[indice].dados != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    vetorPrincipal[indice].dados = (int *) malloc(tamanho * sizeof(int));
   
    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[indice].tamanhoMaximo = tamanho;
    vetorPrincipal[indice].quantidadeElementos = 0;
    
    return SUCESSO;
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
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) == 0) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao; 
    
    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    if (vetorPrincipal[indice].quantidadeElementos < vetorPrincipal[indice].tamanhoMaximo) {
        
        int posInsercao = vetorPrincipal[indice].quantidadeElementos;
        vetorPrincipal[indice].dados[posInsercao] = valor;
        vetorPrincipal[indice].quantidadeElementos++;
        
        return SUCESSO;
    }
    else {
        return SEM_ESPACO;
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (ehPosicaoValida(posicao) == 0)
        return POSICAO_INVALIDA;

    if (existeEstrutura(posicao) == 0)
        return SEM_ESTRUTURA_AUXILIAR;
  
    if (vetorPrincipal[posicao].qtdElementos == 0) 
        return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao].qtdElementos--; 
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) == 0)
        return POSICAO_INVALIDA;

    if (existeEstrutura(posicao) == 0)
        return SEM_ESTRUTURA_AUXILIAR;
    
    int quantidade = vetorPrincipal[posicao].qtdElementos;

    if (quantidade == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
        
    int *vetor = vetorPrincipal[posicao].dados; 

    for (int i = 0; i < quantidade; i++) 
    {
        if (vetor[i] == valor)
        {
            for (int j = i; j < quantidade - 1; j++)
            {
                vetor[j] = vetor[j + 1];
            }
            vetorPrincipal[posicao].qtdElementos--;
            return SUCESSO;
        }
    }
    
    return NUMERO_INEXISTENTE;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == 0) {
        return POSICAO_INVALIDA;
    }
    
    if (existeEstrutura(posicao) == 0) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int quantidade = vetorPrincipal[posicao].qtdElementos;
    
    for (int i = 0; i < quantidade; i++) {
        vetorAux[i] = vetorPrincipal[posicao].dados[i];
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == 0) {
        return POSICAO_INVALIDA;
    }
    
    if (existeEstrutura(posicao) == 0) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int quantidade = vetorPrincipal[posicao].qtdElementos;

    for (int i = 0; i < quantidade; i++) {
        vetorAux[i] = vetorPrincipal[posicao].dados[i];
    }
    
    ordenaVetor(vetorAux, quantidade); 
    
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int i, j;
    int totalElementos = 0;
   
    for (i = 0; i < TAM; i++) {
        if (existeEstrutura(i) && vetorPrincipal[i].qtdElementos > 0) {
            
            for (j = 0; j < vetorPrincipal[i].qtdElementos; j++) {
                
                vetorAux[totalElementos] = vetorPrincipal[i].dados[j];
                totalElementos++;
            }
        }
    }

    if (totalElementos == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int i, j;
    int totalElementos = 0;
   
    for (i = 0; i < TAM; i++) {
        if (existeEstrutura(i) && vetorPrincipal[i].qtdElementos > 0) {
            for (j = 0; j < vetorPrincipal[i].qtdElementos; j++) {
                vetorAux[totalElementos] = vetorPrincipal[i].dados[j];
                totalElementos++;
            }
        }
    }

    if (totalElementos == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    ordenaVetor(vetorAux, totalElementos);
    
    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (ehPosicaoValida(posicao) == 0) {
        return POSICAO_INVALIDA;
    }

    if (existeEstrutura(posicao) == 0) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (novoTamanho < 0) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int novoTamanhoTotal = vetorPrincipal[posicao].tamMaximo + novoTamanho;
   
    if (novoTamanhoTotal < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novoPonteiro = (int *) realloc(vetorPrincipal[posicao].dados, novoTamanhoTotal * sizeof(int));
    
    if (novoPonteiro == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao].dados = novoPonteiro;
    vetorPrincipal[posicao].tamMaximo = novoTamanhoTotal;
    
    if (vetorPrincipal[posicao].qtdElementos > vetorPrincipal[posicao].tamMaximo) {
        vetorPrincipal[posicao].qtdElementos = vetorPrincipal[posicao].tamMaximo;
    }

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (ehPosicaoValida(posicao) == 0) {
        return POSICAO_INVALIDA;
    }
    
    if (existeEstrutura(posicao) == 0) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    int quantidade = vetorPrincipal[posicao].qtdElementos;

    if (quantidade == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    
    return quantidade;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    // 1. Cria o nó cabeçote
    No *cabecote = (No *) malloc(sizeof(No));
    if (cabecote == NULL) {
        return NULL;
    }
    
    cabecote->conteudo = 0; 
    cabecote->prox = NULL;
    
    No *atual = cabecote; 
    int totalElementos = 0;

    for (int i = 0; i < TAM; i++) {
        if (existeEstrutura(i) && vetorPrincipal[i].qtdElementos > 0) {
            for (int j = 0; j < vetorPrincipal[i].qtdElementos; j++) {
                No *novoNo = (No *) malloc(sizeof(No));
                if (novoNo == NULL) {
                    destruirListaEncadeadaComCabecote(&cabecote); 
                    return NULL;
                }
                
                novoNo->conteudo = vetorPrincipal[i].dados[j];
                novoNo->prox = NULL;
                
                atual->prox = novoNo;
                atual = novoNo;
                totalElementos++;
            }
        }
    }

    if (totalElementos == 0) {
        free(cabecote); 
        return NULL;
    }
    cabecote->conteudo = totalElementos; 

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if (inicio == NULL || inicio->prox == NULL) {
        return;
    }
    
    No *ptr = inicio->prox; 
    int i = 0;
    
    while (ptr != NULL) {
        vetorAux[i] = ptr->conteudo;
        ptr = ptr->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio == NULL || *inicio == NULL) {
        return;
    }
    
    No *atual = *inicio;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox; 
        free(atual);           
        atual = proximo;       
    }
    
    *inicio = NULL; 
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i].dados = NULL;
        vetorPrincipal[i].tamMaximo = 0;
        vetorPrincipal[i].qtdElementos = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            free(vetorPrincipal[i].dados);
            vetorPrincipal[i].dados = NULL; 
            vetorPrincipal[i].tamMaximo = 0;
            vetorPrincipal[i].qtdElementos = 0;
        }
    }
}

// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Maria Clara Costa Santos
//  email: 20251160006@ifba.edu.br
//  Matrícula: 20251160006
//  Semestre: 2025.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################
#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

#define ANO_ATUAL 25
#define LINHAS 8
#define COLUNAS 10
#define MAX_PALAVRA 5

DataQuebrada quebraData(char data[]);
int ehBissexto(int ano);
int DataMaior(DataQuebrada dqInicial, DataQuebrada dqFinal);
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
	int valida = 1;
	DataQuebrada dq = quebraData(data);
  
    
	if(!dq.valido) valida = 0;
    int dias_meses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(ehBissexto(dq.iAno)) dias_meses[1]++;
    if(dq.iAno < 100) dq.iAno += (dq.iAno > ANO_ATUAL) ? 1900 : 2000;
    
    if(dq.iAno < 1900 || dq.iAno > (ANO_ATUAL + 2000)) valida = 0;
    if(dq.iMes < 1 || dq.iMes > 12) valida = 0;
    if(dq.iDia < 1 || dq.iDia > dias_meses[dq.iMes - 1]) valida = 0;
        
    return valida;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
        DataQuebrada dqInicial = quebraData(datainicial);
        DataQuebrada dqFinal = quebraData(datafinal);
        if (!DataMaior(dqInicial, dqFinal)){
            dma.retorno = 4;
            return dma;
        }
        
        dma.qtdDias = dqFinal.iDia - dqInicial.iDia;
        dma.qtdMeses = dqFinal.iMes - dqInicial.iMes;
        dma.qtdAnos = dqFinal.iAno - dqInicial.iAno;

        if(dma.qtdDias < 0){
            int ano_e = (dqFinal.iMes == 1) ? dqFinal.iAno - 1 : dqFinal.iAno; //se o mes final for 1, o ano do emprestimo eh o anterior
            int mes_e = (dqFinal.iMes == 1) ? 12 : dqFinal.iMes - 1; //se o mes final for 1, o mes do emprestimo eh o anterior - dezembro
            dma.qtdDias += DiasNoMes(mes_e, ano_e);
            dma.qtdMeses--;
        }
        if(dma.qtdMeses < 0){
            dma.qtdAnos--;
            dma.qtdMeses += 12;
        }
        
        dma.retorno = 1;
        return dma;
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    
    if (isCaseSensitive != 1) {
        NormalizarString(texto);
    }
    
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isCaseSensitive == 1) {
            if (texto[i] == c) {
                qtdOcorrencias++;
            }
        } else {
            char c_lower = c;
            char c_upper = c;

            if (c >= 'a' && c <= 'z') {
                c_upper = c - 32;
            } else if (c >= 'A' && c <= 'Z') {
                c_lower = c + 32;
            }
            
            if (texto[i] == c || texto[i] == c_lower || texto[i] == c_upper) {
                qtdOcorrencias++;
            }
        }
    }
    
    return qtdOcorrencias;
}
/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    NormalizarString(strTexto);
    NormalizarString(strBusca);
    
    int qtdOcorrencias = 0;
    
    int lenBusca = 0;
    for(lenBusca = 0; strBusca[lenBusca] != '\0'; lenBusca++);
    
    for (int i = 0; i < 30; i++) {
        posicoes[i] = -1;
    }
    
    for (int i = 0; strTexto[i] != '\0'; i++) {
        int encontrou = 1;
        
        for (int j = 0; j < lenBusca; j++) {
            if (strTexto[i + j] == '\0') {
                encontrou = 0;
                break;
            }
            
            if (strTexto[i + j] != strBusca[j]) {
                encontrou = 0;
                break;
            }
        }
        
        if (encontrou && lenBusca > 0) {
            posicoes[qtdOcorrencias * 2] = i + 1;
            posicoes[qtdOcorrencias * 2 + 1] = i + lenBusca;
            
            qtdOcorrencias++;
            
            if (qtdOcorrencias * 2 >= 30) {
                break;
            }
        }
    }
    
    return qtdOcorrencias;
}
/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int numInvertido = 0;
  int negativo = 0;
  if (num == 0)
    return 0;
  if (num < 0)
  {
    negativo = 1;
    num = -num;
  }
  while (num > 0)
  {
    int digito = num % 10;
    numInvertido = numInvertido * 10 + digito;
    num = num / 10;
  }
  if (negativo)
    numInvertido = -numInvertido;
  return numInvertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int digitosBase[50];
    int digitosBusca[50];
    int tamBase = 0;
    int tamBusca = 0;

    tamBase = separaDigitos(numerobase, digitosBase);
    tamBusca = separaDigitos(numerobusca, digitosBusca);

    if (tamBusca == 0 || tamBusca > tamBase) {
        return 0;
    }

    for (int i = 0; i <= tamBase - tamBusca;) {
        int encontrado = 1;
        for (int j = 0; j < tamBusca; j++) {
            if (digitosBase[i + j] != digitosBusca[j]) {
                encontrado = 0;
                break;
            }
        }
        if (encontrado) {
            qtdOcorrencias++;   
            i = i + tamBusca;
        } else {
            i++;
        }
    }
    return qtdOcorrencias;
}
/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5])
{
    int lenPalavra = strlen(palavra);

    int direcoes[8][2] = {
        {0, 1},   
        {-1, 1},  
        {-1, 0},  
        {-1, -1}, 
        {0, -1},  
        {1, -1},  
        {1, 0},   
        {1, 1}    
    };

    if (lenPalavra == 0) {
        return 0;
    }

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (matriz[i][j] == palavra[0]) {
                for (int d = 0; d < 8; d++) {
                    int di = direcoes[d][0];
                    int dj = direcoes[d][1];
                    
                    int encontrou = 1;
                    
                    for (int k = 1; k < lenPalavra; k++) {
                        int ci = i + k * di;
                        int cj = j + k * dj;
                        
                        if (ci < 0 || ci >= LINHAS || cj < 0 || cj >= COLUNAS) {
                            encontrou = 0;
                            break;
                        }

                        if (matriz[ci][cj] != palavra[k]) {
                            encontrou = 0;
                            break;
                        }
                    }

                    if (encontrou) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

DataQuebrada quebraData(char data[]){
    DataQuebrada dq;
    char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ 
		sDia[i] = '\0';  
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

int ehBissexto(int ano){
    if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
        return 1;
    } else return 0;
}

int DiasNoMes(int mes, int ano){
    int dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(mes == 2 && ehBissexto(ano)){
        return 29;
    } else return dias[mes - 1];
}

int DataMaior(DataQuebrada dqInicial, DataQuebrada dqFinal){
    if (dqFinal.iAno > dqInicial.iAno){
        return 1;
    }else if (dqFinal.iAno == dqInicial.iAno && dqFinal.iMes > dqInicial.iMes){
        return 1;
    }else if (dqFinal.iAno == dqInicial.iAno && dqFinal.iMes == dqInicial.iMes && dqFinal.iDia > dqInicial.iDia){
        return 1;
    }else{
        return 0;
    }
}

//funções auxiliares p q4 >>> ainda incompletas
char ConvertepMinusculo(char c){
    if(c >= 'A' && c <= 'Z'){
        return c + 32;
    }
    return c;
}

void NormalizarString(char *texto) {
    int i, j, tam;
    char cacento[] = "ÄÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛÙüúûù";
    char sacento[] = "AAAAAAAAAAaaaaaaaaaaEEEEEEEEeeeeeeeeIIIIIIIIiiiiiiiiOOOOOOOOOOooooooooooUUUUUUUUuuuuuuuu";
	
    for(tam = 0; texto[tam] != '\0'; tam++);
	
    for(i = 0; texto[i] != '\0'; i++){
        for(j = 0; cacento[j] != '\0'; j++) {
            if(texto[i] == cacento[j] && texto[i+1] == cacento[j+1]) {
                texto[i] = sacento[j];
                for (int k = i + 1; k < tam - 1; k++) {
                    texto[k] = texto[k+1];
                }
                texto[tam - 1] = '\0';
                tam--;
                break;
            }
        }
    }
}

int separaDigitos(int numero, int digitos[]) {
    if (numero == 0) {
        digitos[0] = 0;
        return 1;
    }
    
    int quantidade = 0;
    int numeroTemporario = numero;
    
    while (numeroTemporario > 0) {
        quantidade++;
        numeroTemporario = numeroTemporario / 10;
    }
    
    numeroTemporario = numero;
    for (int posicao = quantidade - 1; posicao >= 0; posicao--) {
        digitos[posicao] = numeroTemporario % 10; 
        numeroTemporario = numeroTemporario / 10;  
    }
    
    return quantidade;
}

// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Victor Gabriel da Silva Nogueira
//  email: victor@smartbusiness1.com.br
//  Matrícula: 20242160005
//  Semestre: 2025.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "VictorNogueira20242160005.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>


DataQuebrada quebraData(char data[]);

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
  int datavalida = 1;

  //quebrar a string data em strings sDia, sMes, sAno
	char sAno[5], sMes[3], sDia[3];
	int ano, mes, dia, i;
    	int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    
    	for( int i = 0; i != '/'; i++){
		sDia[i] = data [i];
	} 

	if(i == 1 || i == 2){
		sDia[i] = '\0'; 
	} 
	else {
		datavalida = 0; 
	}

	int j = i + 1;
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ 
		sMes[i] = '\0';
	}
	else
		datavalida = 0;
  
	

	j = j + 1;
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ 
		sAno[i] = '\0';
	}
	else 
		datavalida = 0;
	
	dia = atoi(sDia);
	mes = atoi(sMes);
	ano = atoi(sAno); 

	
    	if(dia < 1 || dia > 31)
    		datavalida = 0;
    
    	if(mes < 1 || mes > 12)
    		datavalida = 0;

    
    	if((ano % 4 == 0) && (ano % 100 != 0) || (ano % 400 == 0))
    		meses[1] = 29;
    
    	if(dia > meses[mes - 1])
    		datavalida = 0;

  //printf("%s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
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
	int ano, mes, dia;
	int anoF, mesF, diaF;


    sscanf(datainicial, "%d/%d/%d", &dia, &mes, &ano);
    
    sscanf(datafinal, "%d/%d/%d", &diaF, &mesF, &anoF);
    
    
    int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if((anoF % 4 == 0 && anoF % 100 != 0) || (anoF % 400 == 0))
        meses[1] = 29;


    if(diaF < dia) {
        diaF += meses[(mesF - 2 + 12) % 12];
        mesF--;
    }

    if(mesF < mes) {
        mesF += 12;
        anoF--;
    }

    dma.qtdDias = diaF - dia;
    dma.qtdMeses = mesF - mes;
    dma.qtdAnos = anoF - ano;
    
    if((dma.qtdMeses == 11) && (dma.
        qtdDias == 30)){
    	dma.qtdAnos = 1;
    	dma.qtdMeses = 0;
    	dma.qtdDias = 0;
    }

      //calcule a distancia entre as datas


      //se tudo der certo
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
    int qtdOcorrencias = -1;

	char remover_acento(unsigned char c) {
    switch (c) {
        case 225: case 224: case 226: case 227:  
        case 193: case 192: case 194: case 195:  
            return 'a';
        case 233: case 232: case 234: 
        case 201: case 200: case 202: 
            return 'e';
        case 237: case 236: case 238:  
        case 205: case 204: case 206: 
            return 'i';
        case 243: case 242: case 244: case 245: 
        case 211: case 210: case 212: case 213: 
            return 'o';
        case 250: case 249:
        case 218: case 217:  
            return 'u';
        
        default:
            return c;
    }
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}
    
    char caractere_texto, caractere_buscado;
    int cont;
	
	for (cont = 0; texto[cont] != '\0'; cont++) {
        caractere_texto = remover_acento((unsigned char)texto[cont]);
        caractere_buscado = remover_acento((unsigned char)c);

        if (isCaseSensitive == 0) {
            caractere_texto = to_lower(caractere_texto);
            caractere_buscado = to_lower(caractere_buscado);
        }

        if (caractere_texto == caractere_buscado) {
            qtdOcorrencias++;
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
    int tam_texto = strlen(strTexto);
    int tam_busca = strlen(strBusca);
    int i = 0, j, k = 0;
    int qtdOcorrencias = 0;

    while (i <= tam_texto - tam_busca) {
        for (j = 0; j < tam_busca; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                break;
            }
        }

        if (j == tam_busca) {
            posicoes[k] = i + 1;                   
            posicoes[k + 1] = i + tam_busca;
            qtdOcorrencias++;
            i += tam_busca;
        } else {
            i++;
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
    int digito, invertido;
	
    while (num != 0) {
        digito = num % 10;
        invertido = invertido * 10 + digito;
        num /= 10;
    }


    return invertido;
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
    int qtdOcorrencias;
    char strBase[50], strBusca[20];

    
    sprintf(strBase, "%d", numerobase);
    sprintf(strBusca, "%d", numerobusca);

    int tam_numbase = strlen(strBase);
    int tam_numbusca = strlen(strBusca);

    for (int i = 0; i <= tam_numbase - tam_numbusca;) {
    	int igual = 1;
    	for (int j = 0; j < tam_numbusca; j++) {
        	if (strBase[i + j] != strBusca[j]) {
            	igual = 0;
            	break;
        }
    }
    if (igual) {
        qtdOcorrencias++;
        i += tam_numbusca;
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
     	int achou;
	int dx[8] = {-1, -1, -1,  0, 0, 1, 1, 1};
	int dy[8] = {-1,  0,  1, -1, 1, -1, 0, 1};

	int buscaDirecao(char matriz[8][10], int i, int j, char palavra[5], int dir) {
    		int len = strlen(palavra);

    		for (int k = 0; k < len; k++) {
        		int ni = i + k * dx[dir];
        		int nj = j + k * dy[dir];

       		if (ni < 0 || nj < 0 || ni >= 8 || nj >= 10)
            		return 0;

        	if (matriz[ni][nj] != palavra[k])
            		return 0;
    }
    	return 1;
}
	for (int i = 0; i < 8 && !achou; i++) {
        for (int j = 0; j < 10 && !achou; j++) {
            for (int dir = 0; dir < 8; dir++) {
                if (buscaDirecao(matriz, i, j, palavra, dir)) {
                    achou = 1;
                    break;
                }
            }
        }
    }

     return achou;
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
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
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


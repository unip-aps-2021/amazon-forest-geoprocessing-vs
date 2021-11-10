#define MYSQL_STATICLIB
#include "include/mysql.h"
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "libmariadb.lib")

clock_t* StartTimer();
clock_t StopTimer();
void Stop();
int lat[99713];
int	lon[99713];
int contadorTrocas;
int contadorVerificações;//local

int getSql();
int trocaElementos();
int arvore();
int ordenacao();
int imprimiOrdenacao();
int newN();
int combSort();
int FunQuickSort();
int swap();
int partition();
int quickSort();
int printArray();

int main()
{
	int escolha = 0;
	int subescolha = 0;

	do
	{
		system("cls");
		printf("############## Sistema de controle do Geoprocessamento da Floresta Amazonica ##############\n\n");
		printf("Este programa tem como objetivo utilizar as imagens geradas pelos satelites da floresta \nAmazonica ja catalogadas e ordena-las. Para isso sao utilizados tres metodos de ordenacao, \nonde cada um tem sua singularidade. Tambem e possivel comparar o desempenho dos tres \npara melhor analise.\n\n\n");

		printf("Selecione o tipo de programa a ser iniciado:\n | 1 | Iniciar Ordenacao dos dados \n | 2 | Comparar os tipos de ordenacao de dados \n | 3 | Sair\n   ");
		scanf_s("%d", &escolha);
		
		switch (escolha)
		{
			case 1:
				printf("Obtendo dados catalogados das imagens capturadas dos satelites...\n");
				getSql();
				Stop(3000);
				do
				{
					system("cls");
					printf("Escolha o tipo de ordenacao a ser usada:\n |1| Quick Sort\n |2| Heap Sort\n |3| Comb Sort\n\n |4| Voltar para o menu\n  ");
					scanf_s("%d", &subescolha);
					
					switch (subescolha)
					{
						// QUICK SORT
						case 1:
							system("cls");
							contadorVerificações = 0;
							int menuQuick = 0;
								
							do
							{
								printf("\t#### QUICK SORT ####\n\n");

								printf("Escolha o que deseja realizar:\n");
								printf(" |1| - Realizar ordenacao\n");
								printf(" |2| - Voltar\n  ");
								scanf_s("%d", &menuQuick);

								switch (menuQuick)
								{
									case 1:
										printf("LATE");
										clock_t * timerQuick = StartTimer();
										int n = sizeof(lat) / sizeof(lat[0]);
										quickSort(lat, 0, n - 1);
										printf("\n\nNumero de verificacoes: %d\nNumero de trocas: %d", contadorVerificações, contadorTrocas);
										contadorVerificações = 0;
										contadorTrocas = 0;
										quickSort(lon, 0, n - 1);
										printf("\n\nNumero de verificacoes: %d\nNumero de trocas: %d", contadorVerificações, contadorTrocas);
										clock_t totalQuick = StopTimer(timerQuick);
										
										printf("\nTempo total = %d segundos e %d milissegundos.\n\n", totalQuick / CLOCKS_PER_SEC, totalQuick % 1000);
									break;
									case 2:
										printf("Encerrando sistema de ordenacao...\n");
										Stop(1000);
									break;
								}

							} while (menuQuick != 2);

						break;

						// HEAP SORT
						case 2:
							contadorVerificações = 0;
							int vetor[] = { 1, 6, 7, 9, 55, 2, 10 }; // elementos n�o ordenados internos
							int vet[5]; // elementos n�o ordenados externos
							int elemento = sizeof(vetor) / sizeof(vetor[0]); // realizando as divis�es para an�lises da direita e da esquerda
							int tamanhoLatHeap = sizeof(lat) / sizeof(lat[0]); // realizando as divis�es para an�lises da direita e da esquerda

							int menuHeap = 0;
							int i;

							system("cls");
							printf("\t#### HEAP SORT - Ordenação baseada em Árvore ####\n\n", setlocale(LC_ALL, "Portuguese"));

							do {
								printf("\nEscolha como deseja realizar\n");
								printf(" |1| Gerar valores aleatórios\n", setlocale(LC_ALL, "Portuguese")); // m�todo externo recebido do bd
								printf(" |2| Pegar valores definidos\n"); // método interno
								printf(" |3| Sair\n  ");
								scanf_s("%d", &menuHeap);

								switch (menuHeap)
								{
									case 1:
										printf("\nGerando valores aleaat�rios\n", setlocale(LC_ALL, "Portuguese"));

										srand(time(NULL));

										for (i = 0; i < 5; i++) {
											vet[i] = rand();
										}

										clock_t * timerHeap1 = StartTimer();

										// apresentando a ordena��o
										ordenacao(vet, elemento);
										imprimiOrdenacao(vet, elemento);

										clock_t totalHeap1 = StopTimer(timerHeap1);

										printf("Tempo total = %d segundos e %d milissegundos.\n\n", totalHeap1 / CLOCKS_PER_SEC, totalHeap1 % 1000);
									break;
									case 2:
										clock_t * timerHeap2 = StartTimer();

										// apresentando a ordena��o
										ordenacao(lat, tamanhoLatHeap);
										printf("LAT: \n");
										printf("\n\nNumero de verificacoes: %d\nNumero de trocas: %d", contadorVerificações, contadorTrocas);
										contadorTrocas = 0;
										contadorVerificações = 0;
										ordenacao(lon, tamanhoLatHeap);
										printf("\n\nLON: ");
										printf("\n\nNumero de verificacoes: %d\nNumero de trocas: %d", contadorVerificações, contadorTrocas);

										clock_t totalHeap2 = StopTimer(timerHeap2);

										printf("\nTempo total = %d segundos e %d milissegundos.\n", totalHeap2 / CLOCKS_PER_SEC, totalHeap2 % 1000);
									break;
									case 3:
										printf("Encerrando sistema de ordenacao...\n");
										Stop(1000);
									break;
								}
							} while (menuHeap != 3);

						break;

						// COMB SORT
						case 3:
							system("cls");
							int menuComb = 0;

							do
							{
								printf("\t#### COMB SORT ####\n\n");

								printf("Escolha o que deseja realizar:\n");
								printf(" |1| - Realizar ordenacao\n");
								printf(" |2| - Voltar\n  ");
								scanf_s("%d", &menuComb);

								switch (menuComb)
								{
									case 1:
										clock_t * timerComb = StartTimer();

										int veto[] = { 84, 2, 42, 4, 5, 98, 7, -35 };
										int* v = veto;
										int s, k;
										s = 99713;

										// printf("baguncadinho:\n");
										// for (k = 0;k < s;k++)
										// {
										// 	printf("%d ", lon[k]);
										// }
										combSort(lat, s);
										printf("\n\n\n\n\narrumadinho LAAAAAAAAAAAAAATITUDEEEEEEEEEEEEEEEEEEEEE:\n");        
										for (k = 0;k < s;k++)
										{
											printf("%d ", (lat[k]));
										}

										combSort(lon, s);
										printf("\n\n\n\n\n\narrumadinho LOOOOOOOOOONGITUDEEEEEEEEEEEEEEEEEEEEEE:\n");        
										for (k = 0;k < s;k++)
										{
											printf("%d ", (lon[k]));
										}

										clock_t totalComb = StopTimer(timerComb);
										
										printf("\n\nTempo total = %d segundos e %d milissegundos.\n\n", totalComb / CLOCKS_PER_SEC, totalComb % 1000);
									break;
									case 2:
										printf("Encerrando sistema de ordenacao...\n");
										Stop(1000);
									break;
								} 
							} while (menuComb != 2);
							
						break;
						case 4:
							escolha = 0;
							break;
						break;
						default:
							printf("Opcao invalida...\n");
							Stop(1000);
						break;
					}
				} while (subescolha != 4);
			break;
			case 2:
				printf("Obtendo dados catalogados das imagens capturadas dos satelites...\n");
				// GetData();
				printf("O protocolo de comparacao dos algoritmos fara a ordenacao dos dados com 3 algoritmos de ordenacao e \nmostrara alguns dados de performance que podem ser utilizados como criterio para um uso mais objetivo.\n\n");
				printf("Tem q ve isso aí ainda\n");
				// Compare();
			break;
			case 3:
				exit(0);
			break;
		}
	} while (escolha != 3);
	
	return 0;
}

// Usado para pausar a execu��o do programa por um determinado tempo em milissegundos (passado como par�metro)
void Stop(int duracao)
{
	int msec = 0;
	clock_t before = clock();

	do
	{
		clock_t difference = clock() - before;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < duracao);
}

// Usado para iniciar um temporizador. Retorna um n�mero do tipo clock_t* que deve ser armazenado para o uso da fun��o StopTimer().
clock_t* StartTimer()
{
	clock_t* tempo = malloc(sizeof(clock_t));
	*tempo = clock();
	return tempo;
}

// Usado para finalizar a contagem de um temporizador. Retorna um n�mero do tipo clock_t que pode ser usado para calcular o tempo passado em segundos e milissegundos.
clock_t StopTimer(clock_t* timer)
{
	clock_t total = clock() - *timer;
	return total;
	free(timer);
	// Para obter os segundos usados, usa-se 'total / CLOCKS_PER_SEC'   ___  Para obter os milisseundos, usa-se 'total%1000'
}


int getSql()
{
	//  Iniciando vari�veis de conex�o, resultado e linha
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	unsigned int num_fields;
	MYSQL_FIELD* fields;
	int i = 0;
	int index = 0;
	//  Preenchendo dados do banco
	char* server = "20.121.202.26";
	char* user = "usuarioc";
	char* password = "145902";
	char* database = "dados";
	//  Inicia conex�o com banco
	conn = mysql_init(NULL);
	mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0);
	//  Executa Query
	mysql_query(conn, "SELECT lat AS latitude, lon AS longitude FROM dados_geo;");
	//  Usa e printa resultado
	res = mysql_use_result(conn);
	num_fields = mysql_num_fields(res);
	fields = mysql_fetch_fields(res);
	for (i = 0; i < num_fields; i++)
	{
		//printf("Field %u is %s\n", i, fields[i].name);
		while ((row = mysql_fetch_row(res))) {

			lat[index] = atoi(row[i]);
			lon[index] = atoi(row[i + 1]);
			//printf("%d\n", lat[i]);
			//printf("%d\n", lon[i+1]);
			//printf("%s: %s\n",fields[i].name, row[i]);
			//printf("%s: %s\n",fields[i + 1].name, row[i + 1]);
			index++;
		}
	}
	//  Fecha conex�o e limpa o resultado
	//mysql_free_result(conn);
	//mysql_close(conn);
}

//come�o codigo jacque
/* Realiza a troca dos elementos */
int trocaElementos(int* a, int* b) {
	// troca os elementos
	int aux = *a;
	*a = *b;
	*b = aux;
	contadorTrocas++;
}

/* Cria��o da �rvore e dividindo os lado direito e esquerdo*/
int arvore(int vetor[], int elemento, int i) {
	int maiorElemento = i;
	int direita = 2 * i + 1;  // a direita sempre se realiza a soma 2 * i + 1
	int esquerda = 2 * i + 2; // a esquerda sempre se realiza a soma 2 * i + 2

	contadorVerificações++;

	if (esquerda < elemento && vetor[esquerda] > vetor[maiorElemento]) {  // divis�o para esquerda
		maiorElemento = esquerda;
	}
	if (direita < elemento && vetor[direita] > vetor[maiorElemento]) {  // divis�o para direita
		maiorElemento = direita;
	}
	if (maiorElemento != i) {  // troca os elementos e verifica se � maior
		trocaElementos(&vetor[i], &vetor[maiorElemento]);
		arvore(vetor, elemento, maiorElemento);
	}
}

/* Constru��o do HeapSort */
int ordenacao(int vetor[], int elemento) {
	// cria a ordena��o
	int contador;
	for (contador = (elemento / 2) - 1; contador >= 0; contador--) { // realiza o decremento para ordenar de tr�s para frente
		arvore(vetor, elemento, contador);
	}

	// faz a ordena��o para adicionar nos �ndices do vetor
	for (contador = elemento - 1; contador >= 0; contador--) {
		trocaElementos(&vetor[0], &vetor[contador]);
		arvore(vetor, contador, 0);
	}
}

int imprimiOrdenacao(int vetor[], int elemento) {
	int cont;

	for (cont = 0; cont < elemento; ++cont) {
		printf("%d ", vetor[cont]);
	}

	printf("\n");
}
//fim codigo jacque

int newN(int n) {
	n = (n * 10) / 13;
	if (n == 9 || n == 10) {
		n = 11;
	}
	if (n < 1) {
		n = 1;
	}
	return n;
}

int combSort(int array[], int aSize) {
	printf("\ntamo executano, perai....\n");
	int n = aSize;
	int autemp;
	int i;
	int verificacoesComb = 0;
	int trocasComb = 0;
	for (;;) {
		n = newN(n);
		int swapped = 0;
		// n�mero de vezes que vai passar por tudo fazendo as troca la
		for (i = 0; i < aSize - n; i++) {
			verificacoesComb++;
			int j = i + n;
			if (array[i] > array[j]) {
				autemp = array[i];
				array[i] = array[j];
				array[j] = autemp;
				swapped = 1;
				trocasComb++;
			}
		}
		if (n == 1 && !swapped) {
			break;
		}
	}
	printf("\nta na mao patrao:\n");
	printf("\nVerificacoes: %d\nNumero de Trocas: %d\n", verificacoesComb, trocasComb);
}

int partition(int array[], int baixo, int cima) {

	int pivo = array[cima];

	int i = (baixo - 1);

	for (int j = baixo; j < cima; j++) {
		if (array[j] <= pivo) {
			i++;
			trocaElementos(&array[i], &array[j]);
		}
	}

	trocaElementos(&array[i + 1], &array[cima]);

	return (i + 1);
}

int quickSort(int array[], int baixo, int cima) {
	if (baixo < cima) {
		contadorVerificações++;
		int pi = partition(array, baixo, cima);
		quickSort(array, baixo, pi - 1);
		quickSort(array, pi + 1, cima);
	}
}

int printArray(int array[], int tamanho) {
	for (int i = 0; i < tamanho; ++i) {
		printf("%d  ", array[i]);
	}
	printf("\n");
}
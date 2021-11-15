#define MYSQL_STATICLIB
#include "include/mysql.h"
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#pragma comment(lib, "libmariadb.lib")

clock_t* StartTimer();
clock_t StopTimer();
void Stop();
int lat[99713];
int	lon[99713];
int contadorTrocas;
int contadorVerificações;

int getSql();
int trocaElementos();
int arvore();
int ordenacao();
int newN();
int combSort();
int partition();
int quickSort();
int printArray();

int main()
{
	int escolha = 0;
	int subescolha = 0;
	setlocale(LC_ALL, "");

	int listaInterna[11] = {1, -57, 2, -64, 5, -74, 7, -10, 8, -39, 25};

	do
	{
		system("cls");
		wprintf(L"############## Sistema de controle do Geoprocessamento da Floresta Amazonica ##############\n\n");
		wprintf(L"Este programa tem como objetivo utilizar as imagens geradas pelos satelites da floresta \nAmazonica ja catalogadas e ordena-las. Para isso sao utilizados tres metodos de ordenacao, \nonde cada um tem sua singularidade. Tambem e possivel comparar o desempenho dos tres \npara melhor analise.\n\n\n");

		wprintf(L"Selecione o tipo de programa a ser iniciado:\n | 1 | Iniciar Ordenacao dos dados \n | 2 | Comparar os tipos de ordenacao de dados \n | 3 | Sair\n   ");
		scanf_s("%d", &escolha);
		
		switch (escolha)
		{
			case 1:
				wprintf(L"Obtendo dados catalogados das imagens capturadas dos satelites...\n");
				getSql();
				Stop(3000);
				do
				{
					system("cls");
					wprintf(L"########### Ordenação de Dados ###########\n\n");
					wprintf(L"Pegaremos uma variedade de números e aplicaremos os algoritmos de ordenação neles. \nVale ressaltar que o usuário poderá escolher ordenar 2 tipos de conjunto de dados:\n   Interno: cujos números foram estabelecidos pelos programadores no código do programa.\n   Externos: Dados reais de latitude e longitude de queimadas que aconteceram na floresta amazônica e\n   foram registrados por satélites e distribuídos no site queimadas.dgi.inpe.br.\n\n");
					
					wprintf(L"Escolha o tipo de ordenacao a ser usada:\n |1| Quick Sort\n |2| Heap Sort\n |3| Comb Sort\n\n |4| Voltar para o menu\n  ");
					scanf_s("%d", &subescolha);
					
					switch (subescolha)
					{
						
/* QUICK SORT */		case 1:
							system("cls");
							contadorVerificações = 0;
							contadorTrocas = 0;
							int menuQuick = 0;
								
							do
							{
								wprintf(L"\t#### QUICK SORT ####\n\n");

								wprintf(L"Escolha o que deseja realizar:\n");
								wprintf(L" |1| - Realizar ordenacao com números externos (Dados do satélite)\n");
								wprintf(L" |2| - Realizar ordenacao con números internos (Dados predefinidos)\n");
								wprintf(L" |3| - Voltar\n  ");
								scanf_s("%d", &menuQuick);

								switch (menuQuick)
								{
									case 1:
										clock_t * timerQuick1 = StartTimer();
										
										int tamanhoLat = sizeof(lat) / sizeof(lat[0]);
										quickSort(lat, 0, tamanhoLat - 1);
										quickSort(lon, 0, tamanhoLat - 1);

										printf("\n\nDados ordenados de latitude:\n\n");
										Stop(2000);
										printArray(lat, tamanhoLat);
										
										printf("\n\nDados ordenados de longitude:\n\n");
										Stop(2000);
										printArray(lon, tamanhoLat);

										clock_t totalQuick1 = StopTimer(timerQuick1) - 4000;
										wprintf(L"\nTempo total = %d segundos e %d milissegundos.\n\n", totalQuick1 / CLOCKS_PER_SEC, totalQuick1 % 1000);
									break;
									case 2:
										clock_t * timerQuick2 = StartTimer();
										
										int tamanhoLista = sizeof(listaInterna) / sizeof(listaInterna[0]);
										quickSort(listaInterna, 0, tamanhoLista - 1);

										printf("\n\nDados ordenados da lista:\n\n");
										Stop(1000);
										printArray(listaInterna, tamanhoLista);

										clock_t totalQuick2 = StopTimer(timerQuick2) - 1000;
										wprintf(L"\nTempo total = %d segundos e %d milissegundos.\n\n", totalQuick2 / CLOCKS_PER_SEC, totalQuick2 % 1000);
									break;
									case 3:
										wprintf(L"Encerrando sistema de ordenação...\n");
										Stop(1000);
									break;
								}

							} while (menuQuick != 3);

						break;

/* HEAP SORT */			case 2:
							contadorVerificações = 0;
							contadorTrocas = 0;

							int menuHeap = 0;
							int i;

							system("cls");
							wprintf(L"\t#### HEAP SORT - Ordenação baseada em Árvore Binária ####\n\n");

							do {
								wprintf(L"Escolha o que deseja realizar:\n");
								wprintf(L" |1| - Realizar ordenacao com números externos (Dados do satélite)\n");
								wprintf(L" |2| - Realizar ordenacao con números internos (Dados predefinidos)\n");
								wprintf(L" |3| - Voltar\n  ");
								scanf_s("%d", &menuHeap);

								switch (menuHeap)
								{
									case 1:
										int tamanhoLat = sizeof(lat) / sizeof(lat[0]);

										clock_t * timerHeap1 = StartTimer();

										ordenacao(lat, tamanhoLat);
										ordenacao(lon, tamanhoLat);

										printf("\n\nDados ordenados de latitude:\n\n");
										Stop(2000);
										printArray(lat, tamanhoLat);
										
										printf("\n\nDados ordenados de longitude:\n\n");
										Stop(2000);
										printArray(lon, tamanhoLat);
										
										clock_t totalHeap1 = StopTimer(timerHeap1) - 4000;

										wprintf(L"\nTempo total = %d segundos e %d milissegundos.\n", totalHeap1 / CLOCKS_PER_SEC, totalHeap1 % 1000);
									break;
									case 2:
										int tamanhoLista = sizeof(listaInterna) / sizeof(listaInterna[0]);

										clock_t * timerHeap2 = StartTimer();

										ordenacao(listaInterna, tamanhoLista);

										printf("\n\nDados ordenados da lista:\n\n");
										Stop(1000);
										printArray(listaInterna, tamanhoLista);

										clock_t totalHeap2 = StopTimer(timerHeap2) - 1000;
										wprintf(L"Tempo total = %d segundos e %d milissegundos.\n\n", totalHeap2 / CLOCKS_PER_SEC, totalHeap2 % 1000);
									break;
									case 3:
										wprintf(L"Encerrando sistema de ordenacao...\n");
										Stop(1000);
									break;
								}
							} while (menuHeap != 3);

						break;

/* COMB SORT */			case 3:
							contadorVerificações = 0;
							contadorTrocas = 0;

							system("cls");
							int menuComb = 0;

							do
							{
								wprintf(L"\t#### COMB SORT ####\n\n");

								wprintf(L"Escolha o que deseja realizar:\n");
								wprintf(L" |1| - Realizar ordenacao com números externos (Dados do satélite)\n");
								wprintf(L" |2| - Realizar ordenacao con números internos (Dados predefinidos)\n");
								wprintf(L" |3| - Voltar\n  ");
								scanf_s("%d", &menuComb);

								switch (menuComb)
								{
									case 1:
										clock_t * timerComb1 = StartTimer();
										
										int tamanhoLat = sizeof(lat) / sizeof(lat[0]);
										combSort(lat, tamanhoLat);
										combSort(lon, tamanhoLat);

										printf("\n\nDados ordenados de latitude:\n\n");
										Stop(2000);
										printArray(lat, tamanhoLat);
										
										printf("\n\nDados ordenados de longitude:\n\n");
										Stop(2000);
										printArray(lon, tamanhoLat);

										clock_t totalComb1 = StopTimer(timerComb1) - 4000;
										wprintf(L"\nTempo total = %d segundos e %d milissegundos.\n\n", totalComb1 / CLOCKS_PER_SEC, totalComb1 % 1000);
									break;
									case 2:
										clock_t * timerComb2 = StartTimer();
										
										int tamanhoLista = sizeof(listaInterna) / sizeof(listaInterna[0]);
										combSort(listaInterna, tamanhoLista);

										printf("\n\nDados ordenados da lista:\n\n");
										Stop(1000);
										printArray(listaInterna, tamanhoLista);

										clock_t totalComb2 = StopTimer(timerComb2) - 1000;
										wprintf(L"\nTempo total = %d segundos e %d milissegundos.\n\n", totalComb2 / CLOCKS_PER_SEC, totalComb2 % 1000);
									break;
									case 3:
										wprintf(L"Encerrando sistema de ordenacao...\n");
										Stop(1000);
									break;
								} 
							} while (menuComb != 3);
						break;

						case 4:
							escolha = 0;
							break;
						break;

						default:
							wprintf(L"Opcao invalida...\n");
							Stop(1000);
						break;
					}
				} while (subescolha != 4);
			break;

			case 2:
				wprintf(L"O protocolo de comparação dos algoritmos fara a ordenação dos dados com 3 algoritmos de ordenação e \nmostrara alguns dados de performance que podem ser utilizados como critério para um uso mais objetivo.\n\n");
				subescolha=0;
				do
				{
					//timer, comparações e trocas.
					int tamanhoLat = sizeof(lat) / sizeof(lat[0]);

					wprintf(L" |1| - Valores Externos\n");
					wprintf(L" |2| - Valores Internos\n");
					wprintf(L" |3| - Voltar\n  ");
					scanf("%d", &subescolha);

					switch (subescolha)
					{
					case 1:
						getSql();
						contadorTrocas = 0;
						contadorVerificações = 0;

						printf("QUICK: ");

						quickSort(lat, 0, tamanhoLat);
						quickSort(lon, 0, tamanhoLat);
						wprintf(L"\n\nNúmero de verificações: %d\nNúmero de trocas: %d\n\n", contadorVerificações, contadorTrocas);


						getSql();
						contadorTrocas = 0;
						contadorVerificações = 0;

						printf("HEAP: ");
						ordenacao(lat, tamanhoLat);
						ordenacao(lon, tamanhoLat);
						wprintf(L"\n\nNúmero de verificações: %d\nNúmero de trocas: %d\n\n", contadorVerificações, contadorTrocas);


						getSql();
						contadorTrocas = 0;
						contadorVerificações = 0;

						printf("COMB: ");
						combSort(lat, tamanhoLat);
						combSort(lon, tamanhoLat);
						wprintf(L"\n\nNúmero de verificações: %d\nNúmero de trocas: %d\n\n", contadorVerificações, contadorTrocas);
						break;
					case 2:
						int tamanhoLista = sizeof(listaInterna) / sizeof(listaInterna[0]);

						getSql();
						contadorTrocas = 0;
						contadorVerificações = 0;

						printf("QUICK: ");
						quickSort(listaInterna, 0, tamanhoLista - 1);
						wprintf(L"\n\nNúmero de verificações: %d\nNúmero de trocas: %d\n\n", contadorVerificações, contadorTrocas);


						getSql();
						contadorTrocas = 0;
						contadorVerificações = 0;

						printf("HEAP: ");
						ordenacao(listaInterna, tamanhoLista);
						wprintf(L"\n\nNúmero de verificações: %d\nNúmero de trocas: %d\n\n", contadorVerificações, contadorTrocas);

						getSql();
						contadorTrocas=0;
						contadorVerificações=0;

						printf("COMB: ");
						combSort(listaInterna, tamanhoLista);
						wprintf(L"\n\nNúmero de verificações: %d\nNúmero de trocas: %d\n\n", contadorVerificações, contadorTrocas);

					default:
						break;
					}
				} while (subescolha!=3);
			break;
			case 3:
				exit(0);
			break;
		}
	} while (escolha != 3);
	
	return 0;
}

// Usado para pausar a execução do programa por um determinado tempo em milissegundos (passado como par�metro)
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

// Usado para iniciar um temporizador. Retorna um número do tipo clock_t* que deve ser armazenado para o uso da função StopTimer().
clock_t* StartTimer()
{
	clock_t* tempo = malloc(sizeof(clock_t));
	*tempo = clock();
	return tempo;
}

// Usado para finalizar a contagem de um temporizador. Retorna um número do tipo clock_t que pode ser usado para calcular o tempo passado em segundos e milissegundos.
clock_t StopTimer(clock_t* timer)
{
	clock_t total = clock() - *timer;
	return total;
	free(timer);
	// Para obter os segundos usados, usa-se 'total / CLOCKS_PER_SEC'   ___  Para obter os milisseundos, usa-se 'total%1000'
}


int getSql()
{
	//  Iniciando variáveis de conexão, resultado e linha
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

	//  Inicia conexão com banco
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
		while ((row = mysql_fetch_row(res))) {

			lat[index] = atoi(row[i]);
			lon[index] = atoi(row[i + 1]);

			index++;
		}
	}

}

// Realiza a troca dos números passados como parâmetros
int trocaElementos(int* a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;
	contadorTrocas++;
}

// Criação da árvore e dividindo os lado direito e esquerdo
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

// Construção do HeapSort
int ordenacao(int vetor[], int elemento) {
	// Cria a ordenação
	int contador;
	for (contador = (elemento / 2) - 1; contador >= 0; contador--) { // Realiza o decremento para ordenar de três para frente
		arvore(vetor, elemento, contador);
	}

	// Faz a ordenação para adicionar nos índices do vetor
	for (contador = elemento - 1; contador >= 0; contador--) {
		trocaElementos(&vetor[0], &vetor[contador]);
		arvore(vetor, contador, 0);
	}
}

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
	contadorVerificações=0;
	contadorTrocas=0;

	int n = aSize;
	int autemp;
	int i;
	int verificacoesComb = 0;
	int trocasComb = 0;

	for (;;) {
		n = newN(n);
		int swapped = 0;

		// número de vezes que vai passar por tudo fazendo as troca la
		for (i = 0; i < aSize - n; i++)
		{
			contadorVerificações++;

			int j = i + n;

			if (array[i] > array[j]) {
				trocaElementos(&array[i], &array[j]);
				swapped = 1;
			}
		}
		if (n == 1 && !swapped) {
			break;
		}
	}
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
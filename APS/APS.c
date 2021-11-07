#define MYSQL_STATICLIB
#include <mysql.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

clock_t* StartTimer();
clock_t StopTimer();
void Stop();
int lat[10];
int	lon[10];

int main()
{
	int escolha = 0;
	int subescolha = 0;

	//     system("cls");
	printf("############## Sistema de controle do Geoprocessamento da Floresta Amazonica ##############\n\n");
	printf("Este programa tem como objetivo utilizar as imagens geradas pelos satelites da floresta \nAmazonica ja catalogadas e ordena-las. Para isso sao utilizados tres metodos de ordenacao, \nonde cada um tem sua singularidade. Tambem e possivel comparar o desempenho dos tres \npara melhor analise.\n\n\n");

	printf("Selecione o tipo de programa a ser iniciado:\n | 1 | Iniciar Ordenacao dos dados \n | 2 | Comparar os tipos de ordenacao de dados \n | 3 | Sair\n   ");
	scanf_s("%d", &escolha);
	
	switch (escolha)
	{
	case 1:
		getSql();
		printf("Obtendo dados catalogados das imagens capturadas dos satelites...\n");
		// GetData();
		printf("Escolha o tipo de ordenacao a ser usada:\n |1| Quick Sort\n |2| Heap Sort\n |3| Comb Sort\n\n |4| Voltar para o menu\n  ");
		scanf_s("%d", &subescolha);
		switch (subescolha)
		{
			// Seria legal se o usu·rio pudesse escolher entre ordenar de forma crescente ou decrescente em cada sort e cada sort mostrar uma coisa ˙nica (tem q pensar no quÍ)
		case 1:
			clock_t * temporizador1 = StartTimer();

			Stop(1050); // Est· interrompendo o programa por 1 segundo e 50 milissegundos

			clock_t tempoTotal = StopTimer(temporizador1);

			printf("Tempo total = %d segundos e %d milissegundos.\n", tempoTotal / CLOCKS_PER_SEC, tempoTotal % 1000);
			FunQuickSort();
			break;
		case 2:
			// HeapSort();
			int vetor[] = { 1, 6, 7, 9, 55, 2, 10 }; // elementos n„o ordenados internos
			int vet[5]; // elementos n„o ordenados externos
			int elemento = sizeof(vetor) / sizeof(vetor[0]); // realizando as divisıes para an·lises da direita e da esquerda

			int menu = 0;
			int i;

			printf("\t#### HEAP SORT - Ordena√ß√£o baseada em √Årvore ####\n\n", setlocale(LC_ALL, "Portuguese"));

			do {
				printf("\nEscolha como deseja realizar\n");
				printf("1- Gerar valores aleat√≥rios\n", setlocale(LC_ALL, "Portuguese")); // mÈtodo externo recebido do bd
				printf("2- Pegar valores definidos\n"); // m√©todo interno
				printf("0- Sair\n");
				printf("\n\nFaÁa a sua escolha: ", setlocale(LC_ALL, "Portuguese"));
				scanf_s("%d", &menu);

				switch (menu) {
				case 0:
					printf("\nAplicaÁ„o Encerrada", setlocale(LC_ALL, "Portuguese"));
					break;

				case 1:
					printf("\nGerando valores aleaatÛrios\n", setlocale(LC_ALL, "Portuguese"));

					srand(time(NULL));

					for (i = 0; i < 5; i++) {
						vet[i] = rand();
					}

					// apresentando a ordenaÁ„o
					ordenacao(vet, elemento);
					imprimiOrdenacao(vet, elemento);
					break;

				case 2:
					// apresentando a ordenaÁ„o
					ordenacao(vetor, elemento);
					imprimiOrdenacao(vetor, elemento);
					break;
				}
			} while (menu != 0);

			Stop();
			break;
		case 3:
			int veto[] = { 84, 2, 42, 4, 5, 98, 7, -35 };
			int* v = veto;
			int s, k;
			s = 10;
			printf("\nbaguncadinho:\n");
			for (k = 0;k < s;k++)
			{
				printf("%d ", lon[k]);
			}
			combSort(lon, s);
			printf("\narrumadinho:\n");        
			for (k = 0;k < s;k++)
			{
				printf("%d ", (lon[k]));
			}
			break;
		case 4:
			escolha = 0;
			subescolha = 0;
			break;
		default:
			printf("Opcao invalida...");
			break;
		}
		break;
	case 2:
		printf("Obtendo dados catalogados das imagens capturadas dos satelites...\n");
		// GetData();
		printf("O protocolo de comparacao dos algoritmos fara a ordenacao dos dados com 3 algoritmos de ordenacao e \nmostrara alguns dados de performance que podem ser utilizados como criterio para um uso mais objetivo.\n\n");
		printf("Tem q ve em grupo como q a gente vai fazer a comparacao (se vai ser os 3 algoritmos trabalhando ao msm tempo, se vai ser 1 de cada vez; oq q vai mostrar pro usuario, etc)\n");
		// Compare();
		break;
	case 3:
		exit(0);
		break;
	}
	return 0;
}

// Usado para pausar a execuÁ„o do programa por um determinado tempo em milissegundos (passado como par‚metro)
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

// Usado para iniciar um temporizador. Retorna um n˙mero do tipo clock_t* que deve ser armazenado para o uso da funÁ„o StopTimer().
clock_t* StartTimer()
{
	clock_t* tempo = malloc(sizeof(clock_t));
	*tempo = clock();
	return tempo;
}

// Usado para finalizar a contagem de um temporizador. Retorna um n˙mero do tipo clock_t que pode ser usado para calcular o tempo passado em segundos e milissegundos.
clock_t StopTimer(clock_t* timer)
{
	clock_t total = clock() - *timer;
	return total;
	free(timer);
	// Para obter os segundos usados, usa-se 'total / CLOCKS_PER_SEC'   ___  Para obter os milisseundos, usa-se 'total%1000'
}


int getSql()
{
	//  Iniciando vari·veis de conex„o, resultado e linha
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
	//  Inicia conex„o com banco
	conn = mysql_init(NULL);
	mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0);
	//  Executa Query
	mysql_query(conn, "SELECT lat AS latitude, lon AS longitude FROM dados_geo LIMIT 10;");
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
	//  Fecha conex„o e limpa o resultado
	//mysql_free_result(conn);
	//mysql_close(conn);
}

//comeÁo codigo jacque
/* Realiza a troca dos elementos */
int trocaElementos(int* a, int* b) {
	// troca os elementos
	int aux = *a;
	*a = *b;
	*b = aux;
}

/* CriaÁ„o da ·rvore e dividindo os lado direito e esquerdo*/
int arvore(int vetor[], int elemento, int i) {
	int maiorElemento = i;
	int direita = 2 * i + 1;  // a direita sempre se realiza a soma 2 * i + 1
	int esquerda = 2 * i + 2; // a esquerda sempre se realiza a soma 2 * i + 2

	if (esquerda < elemento && vetor[esquerda] > vetor[maiorElemento]) {  // divis„o para esquerda
		maiorElemento = esquerda;
	}
	if (direita < elemento && vetor[direita] > vetor[maiorElemento]) {  // divis„o para direita
		maiorElemento = direita;
	}
	if (maiorElemento != i) {  // troca os elementos e verifica se È maior
		trocaElementos(&vetor[i], &vetor[maiorElemento]);
		arvore(vetor, elemento, maiorElemento);
	}
}

/* ConstruÁ„o do HeapSort */
int ordenacao(int vetor[], int elemento) {
	// cria a ordenaÁ„o
	int contador;
	for (contador = (elemento / 2) - 1; contador >= 0; contador--) { // realiza o decremento para ordenar de tr·s para frente
		arvore(vetor, elemento, contador);
	}

	// faz a ordenaÁ„o para adicionar nos Ìndices do vetor
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
		// n˙mero de vezes que vai passar por tudo fazendo as troca la
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
int FunQuickSort() {
	int dados[] = { 8, 7, 2, 1, 0, 9, 6, 10, 11, 6 };
	int n = sizeof(dados) / sizeof(dados[0]);
	//printf("Dados n„o ordenados\n");
	//printArray(data, n);
	quickSort(dados, 0, n - 1);
	printf("Dados em ordem crescente: \n");
	printArray(dados, n);
}

int swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int array[], int baixo, int cima) {

	int pivo = array[cima];

	int i = (baixo - 1);

	for (int j = baixo; j < cima; j++) {
		if (array[j] <= pivo) {
			i++;
			swap(&array[i], &array[j]);
		}
	}

	swap(&array[i + 1], &array[cima]);

	return (i + 1);
}

int quickSort(int array[], int baixo, int cima) {
	if (baixo < cima) {
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
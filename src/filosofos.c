/*
 ============================================================================
 Name        : filosofos.c
 Author      : Dayanne, Juan, Roberto, Radamés
 Version     :
 Copyright   : 
 Description : Sistemas Operacionais I - Trabalho 2: Jantar dos Filósofos (N-1 Tokens)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int pega_talheres(int num_esquerdo, int num_direito);
void devolve_talheres(int num_esquerdo, int num_direito);
void comendo();
void pensando();
void pega_token();
void devolve_token();
void *filosofo(void *num);

#define FALHA 0;
#define SUCESSO 1;


//Globais
int NUM_FILOSOFOS;
unsigned TMP_COMENDO;
unsigned TMP_PENSANDO;
int NUM_TOKENS;
int COMIDA_NA_MESA;
pthread_mutex_t LOCK_NUM_TOKENS;
pthread_mutex_t *TALHERES;


void pega_token() {
	int ret = 0;
	while (!ret) {
		pthread_mutex_lock(&LOCK_NUM_TOKENS);
		if (NUM_TOKENS > 0) {
			NUM_TOKENS--;
			ret = 1;
		}
		else {
			ret = 0;
		}
		pthread_mutex_unlock(&LOCK_NUM_TOKENS);
	}
}

void devolve_token(){
	pthread_mutex_lock(&LOCK_NUM_TOKENS);
	NUM_TOKENS++;
	pthread_mutex_unlock(&LOCK_NUM_TOKENS);
}

int pega_talheres(int num_esquerdo, int num_direito) {
	if (pthread_mutex_trylock(&TALHERES[num_esquerdo])) {
		sleep(1);
		if (pthread_mutex_trylock(&TALHERES[num_direito])) {
			sleep(1);
			return SUCESSO;
		}
		//pthread_mutex_unlock(&TALHERES[num_esquerdo]); //desiste de segurar o talher caso não conseguiu ambos
	}
	return FALHA;
}

void devolve_talheres(int num_esquerdo, int num_direito) {
	pthread_mutex_unlock(&TALHERES[num_esquerdo]);
	pthread_mutex_unlock(&TALHERES[num_direito]);
}

void comendo() {
	//unsigned int seed = time(NULL);
	//unsigned int variante = rand_r(&seed) * 10;
	//printf(" Comendo (%d ms).", variante);
	usleep(TMP_COMENDO);
}

void pensando() {
	unsigned int seed = time(NULL);
	int variante = rand_r(&seed) * 10;
	usleep(TMP_PENSANDO);
}

void *filosofo(void *num) {
	int id = (int)num;
	int talher_esquerdo, talher_direito;

	talher_esquerdo = id;
	talher_direito = id+1;

	if (talher_direito == NUM_FILOSOFOS) { //talheres dão a volta na mesa
		talher_direito = 0;
	}

	while(COMIDA_NA_MESA) {
		printf("\nFilósofo %d está pronto pra comer.", id);
		pega_token();
		printf("\nFilósofo %d sentou-se à mesa. (token %d)", id, NUM_TOKENS);
		while (!pega_talheres(talher_esquerdo, talher_direito) && COMIDA_NA_MESA) {
			usleep(1000); //caso não consiga pegar ambos talheres
		}
		printf("\nFilósofo %d começou a comer. (talheres %d, %d)", id, talher_esquerdo, talher_direito);
		comendo();
		devolve_talheres(talher_esquerdo, talher_direito);
		printf("\nFilósofo %d terminou de comer. (talheres %d, %d)", id, talher_esquerdo, talher_direito);
		devolve_token();
		printf("\nFilósofo %d levantou-se para pensar.", id);
		pensando();
	}

	printf("\nFilósofo %d acabou de comer.", id);
	return (void *) 0;
}


int main(void) {
	int i;

	printf("\n*** Problema do Jantar dos Filosofos ***\n"
			"*** Trabalho 2 de SO1 ***\n"
			"Solucao de N-1 Tokens\n");
	printf("\nNumero filosofos: ");
	scanf("%d", &NUM_FILOSOFOS);
	printf("\nTempo comendo (ms): ");
	scanf("%d", &TMP_COMENDO);
	TMP_COMENDO = TMP_COMENDO * 1000;
	printf("\nTempo pensando (ms): ");
	scanf("%d", &TMP_PENSANDO);
	TMP_PENSANDO = TMP_PENSANDO * 1000;

	srand(100); //fator variante

	COMIDA_NA_MESA = 1;
	pthread_t filosofos[NUM_FILOSOFOS];
	NUM_TOKENS = NUM_FILOSOFOS-1;
	TALHERES = malloc(sizeof(pthread_mutex_t) * NUM_FILOSOFOS); //inicializa mutexes de talheres
	pthread_mutex_init(&LOCK_NUM_TOKENS, NULL);

	for (i=0; i < NUM_FILOSOFOS; i++) {
		pthread_mutex_init(&TALHERES[i], NULL);
	}

	for (i=0; i < NUM_FILOSOFOS; i++) {
		pthread_create(&filosofos[i], NULL, filosofo, (void *) i);
		printf("%d", i);
	}

	for (i=0; i < NUM_FILOSOFOS; i++) {
		pthread_join(filosofos[i], NULL);
	}

	return EXIT_SUCCESS;
}

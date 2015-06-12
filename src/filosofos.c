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


void *filosofo(void *num);
void pega_talheres();
void devolve_talheres();
void comendo();
void pensando();
void pega_token();
void devolve_token();


//Globais
unsigned int NUM_FILOSOFOS;
unsigned int TMP_COMENDO;
unsigned int TMP_PENSANDO;
unsigned int NUM_TOKENS;
pthread_mutex_t LOCK_NUM_TOKENS;


//Comer requer disponibilidade de recursos ou senão espera
void comendo() {
	sleep(TMP_COMENDO);
}

void pensando() {
	sleep(TMP_PENSANDO);
}

void *filosofo(void *num) {
	//pthread_mutex_t garfo_esq;
	//pthread_mutex_t garfo_dir;
	comendo();
	pensando();
	return (void *) 0;
}


int main(void) {
	printf("\n*** Problema do Jantar dos Filosofos ***\n"
			"*** Trabalho 2 de SO1 ***\n"
			"Solucao de N-1 Tokens\n");
	printf("\nNumero filosofos: ");
	scanf("%d", &NUM_FILOSOFOS);
	printf("\nTempo comendo (ms): ");
	scanf("%d", &TMP_COMENDO);
	printf("\nTempo pensando (ms): ");
	scanf("%d", &TMP_PENSANDO);

	pthread_t filosofos[NUM_FILOSOFOS];
	pthread_mutex_t talheres[NUM_FILOSOFOS];
	NUM_TOKENS = NUM_FILOSOFOS-1;
	pthread_mutex_init(&LOCK_NUM_TOKENS, NULL);

	for (int i=0; i < NUM_FILOSOFOS; i++) {
		pthread_mutex_init(&talheres[i], NULL);
	}

	for (int i=0; i < NUM_FILOSOFOS; i++) {
		pthread_create(&filosofos[i], NULL, filosofo, (void *) i);
	}

	for (int i=0; i < NUM_FILOSOFOS; i++) {
		pthread_join(&filosofos[i], NULL);
	}

	return EXIT_SUCCESS;
}

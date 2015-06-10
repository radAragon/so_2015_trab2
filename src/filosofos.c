/*
 ============================================================================
 Name        : filosofos.c
 Author      : Dayanne, Juan, Roberto, Radames
 Version     :
 Copyright   : 
 Description : Sistemas Operacionais - Trabalho 2: Jantar dos filósofos (n-1 tokens)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *filosofo(void *num);
void pega_talheres();
void devolve_talheres();
void comendo();
void pensando();
void pega_token();
void devolve_token();

//Constantes
#define LIVRE 0;
#define OCUPADO 1;

//Globais
int num_filosofos;
int tmp_comendo;
int tmp_pensando;
unsigned int tokens;
pthread_mutex_t tokens_lock;


//Comer requer disponibilidade de recursos ou senão espera
void comendo() {
	sleep(tmp_comendo);
}

void pensando() {
	sleep(tmp_pensando);
}

void *filosofo(void *num) {
	pthread_mutex_t garfo_esq;
	pthread_mutex_t garfo_dir;
	comendo();
	pensando();
}


int main(void) {

	return EXIT_SUCCESS;
}

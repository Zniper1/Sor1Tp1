#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t a;
sem_t b;
sem_t c;
sem_t d;
sem_t e;
sem_t auxB;
sem_t auxC;

void *ImprimirCanto1 ()
{
   	sem_wait(&a);
    	printf("%s", "Ole ole ole, \n");
    	sem_post(&auxB);
	sem_post(&auxC);
}

void *ImprimirCanto2 ()
{
    	sem_wait(&aux);
	sem_wait(&b);	
    	printf("%s", "Ole ole ole olá, \n");
	sem_post(&a);
	sem_post(&c);
}

void *ImprimirCanto3 ()
{
    	sem_wait(&c);
	sem_wait(&auxy);
    	printf("%s", "cada dia te quiero más. \n");
    	sem_post(&d);
}

void *ImprimirCanto4 ()
{
   	sem_wait(&d);
    	printf("%s", "Ooooooh, Argentina \n");
   	sem_post(&e);
}

void *ImprimirCanto5 ()
{
    	sem_wait(&e);
    	printf("%s", "es un sentimiento, ¡No puedo parar! \n");
    	printf("%s", "\n");
   	sem_post(&a);
	sem_post(&b);
}


int main() {

    int NumRepeticiones = 10;

    	sem_init(&a,0,1);
	sem_init(&b,0,1);
	sem_init(&c,0,0);
	sem_init(&d,0,0);
	sem_init(&e,0,0);
	sem_init(&auxy,0,0);

    while(NumRepeticiones>0)
    {
    	pthread_t Proceso1;
    	pthread_create(&Proceso1,NULL, &ImprimirCanto1,NULL);

    	pthread_t Proceso2;
    	pthread_create(&Proceso2,NULL, &ImprimirCanto2,NULL);

    	pthread_t Proceso3;
    	pthread_create(&Proceso3,NULL, &ImprimirCanto3,NULL);
	
	pthread_t Proceso4;
    	pthread_create(&Proceso4,NULL, &ImprimirCanto4,NULL);
	
	pthread_t Proceso5;
    	pthread_create(&Proceso5,NULL, &ImprimirCanto5,NULL);

    	pthread_join(Proceso1,NULL);
    	pthread_join(Proceso2,NULL);
    	pthread_join(Proceso3,NULL);
	pthread_join(Proceso4,NULL);
	pthread_join(Proceso5,NULL);

    	NumRepeticiones--;
    }
   	sem_destroy(&a);
    	sem_destroy(&b);
   	sem_destroy(&c);
 	sem_destroy(&d);
 	sem_destroy(&e);
 	sem_destroy(&auxy);

    return 0;
}

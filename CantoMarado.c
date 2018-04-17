#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t a;
sem_t b;
sem_t c;

void *ImprimirCantoMa ()
{
    sem_wait(&a);
    	printf("%s", "Ma");
    sem_post(&b);
}

void *ImprimirCantoRa ()
{
    sem_wait(&b);
    	printf("%s", "ra");
    sem_post(&c);
}

void *ImprimirCantoDo ()
{
    sem_wait(&c);
    	printf("%s", "dooo...");
    	printf("%s", "\n");
    sem_post(&a);
}


int main() {

    int NumRepeticiones = 10;

    	sem_init(&a,0,1);
	sem_init(&b,0,0);
	sem_init(&c,0,0);

    while(NumRepeticiones>0)
    {
    	pthread_t Proceso1;
    	pthread_create(&Proceso1,NULL, &ImprimirCantoMa,NULL);

    	pthread_t Proceso2;
    	pthread_create(&Proceso2,NULL, &ImprimirCantoRa,NULL);

    	pthread_t Proceso3;
    	pthread_create(&Proceso3,NULL, &ImprimirCantoDo,NULL);

    	pthread_join(Proceso1,NULL);
    	pthread_join(Proceso2,NULL);
    	pthread_join(Proceso3,NULL);

    	NumRepeticiones--;
    }
   	 sem_destroy(&a);
    	 sem_destroy(&b);
   	 sem_destroy(&c);

    return 0;
}

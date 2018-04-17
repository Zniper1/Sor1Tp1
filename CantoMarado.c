#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t a;
sem_t b;
sem_t c;

pthread_mutex_t mi_mutex;


void *ImprimirCantoMa ()
{
    sem_wait(&a);
	pthread_mutex_lock(&mi_mutex);
    printf("%s", "Ma");
    sem_post(&b);
    pthread_mutex_unlock(&mi_mutex);
    pthread_exit(NULL);

}

void *ImprimirCantoRa ()
{
    sem_wait(&b);
	pthread_mutex_lock(&mi_mutex);
    printf("%s", "Ra");
    sem_post(&c);
    pthread_mutex_unlock(&mi_mutex);
    pthread_exit(NULL);
}

void *ImprimirCantoDo ()
{
    sem_wait(&c);
	pthread_mutex_lock(&mi_mutex);
    printf("%s", "Do");
    printf("%s", "\n");
    sem_post(&a);
    pthread_mutex_unlock(&mi_mutex);
    pthread_exit(NULL);


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

	pthread_exit(NULL);
    sem_destroy(&a);
    sem_destroy(&b);
    sem_destroy(&c);
    pthread_mutex_destroy(&mi_mutex);


    return 0;
}

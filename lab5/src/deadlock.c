#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
int A = 0;
int B = 0;

void F1(int *a)
{
    
    pthread_mutex_lock(&mut1);//Шаг выполнения 1
    
    printf("\nthread1 takes the mut1_1");
    sleep(2);
    
    pthread_mutex_lock(&mut2); //Выполнение шага 3 DEADLOCK !!!
    A+=1;
    printf("\nA = %d", A);
    /*if (pthread_mutex_trylock (& mut2))
    {
        A+=1;
        printf("\nA = %d", A);
        pthread_mutex_unlock (& mut2);
    }*/
    
    printf("\nthread1 takes the mut2_1");
    B+=A;
    printf("\nB +A(%d)= %d",A, B);
    printf("\nthread1 is finishing...");
    pthread_mutex_unlock(&mut2);
    pthread_mutex_unlock(&mut1);
 
    

}

void F2(int *a)
{
    
    pthread_mutex_lock(&mut2); //Шаг выполнения 2
    
    printf("\nthread2 takes the mut2_2");
    sleep(2);
    
    pthread_mutex_lock(&mut1);
    B+=1;
    printf("\nB = %d", B);
    printf("\nthread2 takes the mut1_2");

    A+=B;

    printf("\nA +B(%d)= %d",B, A);
    printf("\nthread2 is finishing...");
    pthread_mutex_unlock(&mut1);
    pthread_mutex_unlock(&mut2);
    //pthread_mutex_unlock(&mut1);
   

    

}

int main()
{
    printf("\na");
    pthread_t Threads_mass[2];
    int a = 1;
    int b = 1;

        if (pthread_create(Threads_mass, NULL, (void *)F1,
			  NULL) != 0) {
        perror("pthread_create");
        exit(1);
              }

        if (pthread_create(Threads_mass + 1, NULL, (void *)F2,
			  NULL) != 0) {
        perror("pthread_create");
        exit(1);
              }
    
    for(int i = 0; i < 2; i++)
        if (pthread_join(Threads_mass[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
printf("\nb\n");
    return 0;
}
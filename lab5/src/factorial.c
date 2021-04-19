#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
int res = 1;
int k = 0, pnum = 0, mod = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void thread_factorial(int* number)
{
    int n = k/pnum;
    int i = n * *number + 1;
    int end = (*(number) + 1)==pnum?(k + 1):(n * (*number + 1) + 1);

    for(i = i; i < end; i++)
    {   
        pthread_mutex_lock(&mut);
        res = (res * (i % mod)) % mod;
        pthread_mutex_unlock(&mut);
    }
    printf("\n\n %d %d %d %d %d",pnum,*number,k,mod,res);
}

int main(int argc, char **argv) {

    static struct option options[] =    {{"k",        required_argument, 0, 0},
                                        {"mod",       required_argument, 0, 0},
                                        {"pnum",      required_argument, 0, 0},
                                        {0, 0,                          0, 0}};
    int option_index = 0;

    while (true) {
        
        int c = getopt_long(argc, argv, "", options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 0: {
                switch (option_index) {
                    case 0: {
                        k = atoi(optarg);
                        if (k < 0) {
                            printf("The factorial argument must be a positive number or 0. Now factorial argument = %d\n", k);
                            return -1;
                        }
                        break;
                    }

                    case 1:
                        mod = atoi(optarg);
                        if (mod < 0) {
                            printf("The factorial modul's must be a positive number. Now modul = %d\n", mod);
                            return -1;
                        }
                        break;

                    case 2: {
                        pnum = atoi(optarg);
                        if (pnum <= 0) {
                            printf("Threads_num must be 1 or more. Now threads_num = %d\n", pnum);
                            return -1;
                        }
                         
                        break;
                    }
                }
                break;
            }

            case '?':
                break;

            default:
                printf("getopt returned character code 0%o?\n", c);
        }
    }
    

    if (optind < argc) {
        printf("Has at least one no option argument\n");
        return 1;
    }

    if (k == -1 || mod == -1 || pnum == -1 ) {
        printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
            argv[0]);
        return 1;
    }
 
    pthread_t Threads_mass[pnum];
    int num[pnum];

    printf("\nmih %d %d %d",k,mod,pnum);
    for(int i = 0; i < pnum; i++)
    {    
        *(num+i)=i;
        printf("\nmh %d",*(num+i));
        if (pthread_create(Threads_mass + i, NULL, (void *)thread_factorial,
              (void *)(num+i)) != 0) {
        perror("pthread_create");
        exit(1);
        }
    }
    
    for(int i = 0; i < pnum; i++){
        if (pthread_join(*(Threads_mass + i), NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }
    printf("\n%d!mod(%d) = %d\n", k, mod, res);

    return 0;
} 

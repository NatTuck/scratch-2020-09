#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#define NN 500

// .data
int stack[5];
int stptr = 0;  // the next empty slot
               
pthread_mutex_t lock;
pthread_cond_t  cond;

// (4096 - sizeof(int)) / 4 = 1023

void
stack_push(int xx)
{
    // precondition: there's a free slot on the stack
    //   true if stptr < 5
    pthread_mutex_lock(&lock);
    while (stptr >= 5) {
        pthread_cond_wait(&cond, &lock);
    }
    stack[stptr++] = xx;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

int
stack_pop()
{
    // precondition: there's data on the stack
    //   true if stptr > 0

    pthread_mutex_lock(&lock);
    while (stptr <= 0) {
        pthread_cond_wait(&cond, &lock);
    }
    int yy = stack[--stptr];
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
    return yy;
}

void*
producer_thread(void* _arg)
{
    usleep(1);
    for (int ii = 0; ii < NN; ++ii) {
        stack_push(ii);
    }

    return 0;
}

int
main(int _ac, char* _av[])
{
    int rv;
    pthread_t threads[2]; // producer threads

    pthread_mutex_init(&lock, 0);
    pthread_cond_init(&cond, 0);

    for (int ii = 0; ii < 2; ++ii) {
        rv = pthread_create(&(threads[ii]), 0, producer_thread, 0);
        assert(rv == 0);
    }

    for (int ii = 0; ii < (2 * NN); ++ii) {
        int yy = stack_pop();
        printf("%d\n", yy);
    }

    return 0;
}

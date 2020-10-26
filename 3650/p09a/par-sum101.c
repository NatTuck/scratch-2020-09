#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct sum_job {
    long r0;
    long r1;
    long sum;
} sum_job;

const int NN = 10;

// a billion
const long TOP = 1000000000;
const long NPT = TOP / NN;

void*
sum_range_thread(void* arg)
{
    sum_job* job = (sum_job*)arg;
    long sum = 0;

    for (long ii = job->r0; ii < job->r1; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }

    job->sum = sum;
    return job;
}

pthread_t
start_sum_job(long r0, long r1)
{
    sum_job* job = malloc(sizeof(job));
    job->r0 = r0;
    job->r1 = r1;

    pthread_t thr;
    int rv = pthread_create(&thr, 0, sum_range_thread, job);
    assert(rv == 0);
    return thr;
}

int
main(int _ac, char* _av[])
{
    pthread_t threads[NN];

    long rv;


    for (long tt = 0; tt < NN; ++tt) {
        threads[tt] = start_sum_job(tt*NPT, (tt+1)*NPT);
    }

    long sum = 0;

    for (long tt = 0; tt < NN; ++tt) {
        sum_job* job;
        rv = pthread_join(threads[tt], (void**)&job);
        assert(rv == 0);

        sum += job->sum;
        free(job);
    }

    printf("Sum = %ld\n", sum);

    return 0;
}

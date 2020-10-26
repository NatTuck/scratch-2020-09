#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#include <stdatomic.h>

// Number of  threads
const int PP = 10;

// A billion
const long TOP = 1000000000;
const long NPT = TOP/PP;

long sum;

typedef struct sum_job {
    long r0;
    long r1;
} sum_job;

typedef struct task {
    pthread_t thread;
    sum_job* job;
} task;


void*
sum_range_thread(void* arg)
{
    sum_job* job = (sum_job*)arg;

    for (long ii = job->r0; ii < job->r1; ++ii) {
        if (ii % 101 == 0) {
            //sum += ii;
            long _old_sum = atomic_fetch_add(&sum, ii);
        }
    }

    return 0;
}

task
create_job_thread(long r0, long r1)
{
    sum_job* job = malloc(sizeof(sum_job));
    job->r0 = r0;
    job->r1 = r1;
   
    int rv; 
    task tt;
    tt.job = job;

    rv = pthread_create(&(tt.thread), 0, sum_range_thread, job);
    assert(rv == 0);

    return tt;
}

int
main(int _ac, char* _av[])
{
    task tasks[PP];
    int rv;

    sum = 0;

    for (long tt = 0; tt < PP; ++tt) {
        tasks[tt] = create_job_thread(tt*NPT, (tt+1)*NPT);
    }
    
    for (long tt = 0; tt < PP; ++tt) {
        rv = pthread_join(tasks[tt].thread, 0);
        assert(rv == 0);
        free(tasks[tt].job);
    }

    printf("sum = %ld\n", sum);

    return 0;
}


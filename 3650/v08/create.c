#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define NN 10

void*
thread_main(void* thread_arg)
{
    int xx = *((int*)thread_arg);
    printf("Thread %d: We're in a thread.\n", xx);
    *((int*)thread_arg) += xx;
    return thread_arg;
}

int
main(int _ac, char* _av[])
{
    int rv;
    pthread_t threads[NN];
    int nums[NN];

    printf("main: starting %d thread.\n", NN);

    for (int ii = 0; ii < NN; ++ii) {
        nums[ii] = ii;
        rv = pthread_create(&(threads[ii]), 0, thread_main, (void*)(&(nums[ii])));
        assert(rv == 0);
    }

    printf("main: started %d threads\n", NN);

    for (int ii = 0; ii < NN; ++ii) {
        void* ret;
        rv = pthread_join(threads[ii], &ret);
        assert(rv == 0);

        int yy = *((int*) ret);
        printf("main: Joined thread %d, yy = %d\n", ii, yy);
    }

    printf("main: all threads joined.\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <alloca.h>

long
sqrt_up(long xx)
{
    return (long)ceil(sqrt(xx));
}

int
is_prime(long primes[], long xx)
{
    for (long ii = 0; ii[primes] <= sqrt_up(xx); ++ii) {
        long pp = *(primes + ii);
        if ((xx % pp) == 0) {
            return 0;
        }
    }
    return 1;
}

long
prime(long nn)
{
    long* primes = alloca(nn * sizeof(long));
    for (long ii = 0; ii < nn; ++ii) {
        primes[ii] = 0;
    }

    // pointer + integer = pointer + (integer * sizeof(pointer_type))

    primes[0] = 2;   // primes[0] => *(primes + 0)
    *(primes + 1) = 3;  // <- this is the real mechanic
    2[primes] = 5;   // 2[primes] => *(2 + primes)

    for (long ii = 3; ii < nn; ++ii) {
        long guess = *(primes + (ii - 1)) + 2;
        while (!is_prime(primes, guess)) {
            guess += 2;
        }
        primes[ii] = guess;
    }
    return (nn-1)[primes];
}

int
main(int argc, char* argv[])
{
    if (argc != 2) { abort(); }

    long nn = atol(argv[1]);
    long pp = prime(nn);

    printf("Prime %ld is %ld\n", nn, pp);
    return 0;
}

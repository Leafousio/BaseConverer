
include <bitset>
#include <iostream>

using namespace std;
 
bitset<500001> Primes;

void SieveOfEratosthenes(int n)
{

    Primes[0] = 1;

    for (int i = 3; i*i <= n; i += 2) {

        if (Primes[i / 2] == 0) {

            for (int j = 3 * i; j <= n; j += 2 * i)

                Primes[j / 2] = 1;

        }

    }
}

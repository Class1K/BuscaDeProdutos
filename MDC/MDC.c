#include <stdio.h>
#include <stdlib.h>

// SOMENTE complete essa função
int MDC(int m, int n)
{

    int mdc;
    if (n > m)
        mdc = MDC(n, m);
    if (n == 0)
        mdc = m;
    if (n > 0)
        mdc = MDC(n, m % n);

    return mdc;
}

int main()
{

    int m, n;
    printf("Digite dois numeros inteiros: ");
    scanf("%i", &m);
    scanf("%i", &n);
    printf("MDC(%i,%i) = %i\n", m, n, MDC(m, n));
    return 0;
}
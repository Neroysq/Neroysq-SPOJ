#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int nmax = 40000, pmax = 100000;

int t, n, m;
bool ed[pmax + 18];
int prim[nmax + 18];

void prepare ()
{
    for (int i = 2, j; i <= nmax; ++i)
	if (!ed[i])
	    for (prim[++prim[0]] = i, j = i << 1; j <= nmax; j <<= 1)
		ed[j] = true;
}

void pri (int n, int m)
{
    memset (ed, 0, sizeof (ed));
    if (n == 1) ed[1] = true;
    for (int i = 1; i <= prim[0]; ++i)
    {
	int l = n / prim[i], r = m / prim[i];
	if (n % prim[i]) ++l;
	if (l == 1) l = 2;
	for (int j = l; j <= r; ++j)
	    ed[j * prim[i] - n + 1] = true;
    }
    for (int i = 1; i <= m - n + 1; ++i)
	if (!ed[i])
	    printf ("%d\n", i + n - 1);
}

int main()
{
    freopen ("test.in", "r", stdin);
    freopen ("test.out", "w", stdout);
    scanf ("%d", &t);
    prepare ();
    for (int i = 1; i <= t; ++i, printf ("\n"))
	scanf ("%d%d", &n, &m), pri (n ,m);
    return 0;
}

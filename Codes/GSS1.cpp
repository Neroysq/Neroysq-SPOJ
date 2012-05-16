#include <stdio.h>
#include <memory.h>
const int nmax = 50000;

int lmax[(1 << 17) + 18], rmax[(1 << 17) + 18], sum[(1 << 17) + 18], smax[(1 << 17) + 18];
int n, m, l, r, M = 1;
int i, lrans, rlans, subans;

int max (int a, int b)
{
    return a > b ? a : b;
}

int query (int l, int r)
{
    subans = lrans = rlans = -nmax;
    for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	    if (~l & 1)
	    {
           subans = max (subans, max (smax[l ^ 1], lrans + lmax[l ^ 1]));
	       lrans = max (rmax[l ^ 1], lrans + sum[l ^ 1]);
        }
	    if ( r & 1)
	    {
	       subans = max (subans, max (smax[r ^ 1], rlans + rmax[r ^ 1]));
	       rlans = max (lmax[r ^ 1], rlans + sum[r ^ 1]);
        }
    }
    return max (subans, lrans + rlans);
}

int main ()
{
    freopen ("GSS1.in", "r", stdin);
    freopen ("GSS1.out", "w", stdout);
    scanf ("%d", &n);
    memset (lmax, 0xEF, sizeof (lmax));
    memset (rmax, 0xEF, sizeof (rmax));
    memset (sum, 0xEF, sizeof (sum));
    memset (smax, 0xEF, sizeof (smax));
    while (M < n) M <<= 1;
    for (i = 1; i <= n; ++i)
	    scanf ("%d", &lmax[i + M]), sum[i + M] = rmax[i + M] = smax[i + M] = lmax[i + M];
    for (i = M - 1; i; --i)
    {
	    lmax[i] = max (lmax[i << 1], sum[i << 1] + lmax[(i << 1) + 1]);
	    rmax[i] = max (rmax[(i << 1) + 1], rmax[i << 1] + sum[(i << 1) + 1]);
	    sum[i] = sum[i << 1] + sum[(i << 1) + 1];
	    smax[i] = max (max (smax[i << 1], smax[(i << 1) + 1]), rmax[i << 1] + lmax[(i << 1) + 1]);
    }
    scanf ("%d", &m);
    for (i = 1; i <= m; ++i)
	    scanf ("%d%d", &l, &r), printf ("%d\n", query (l, r));
    return 0;
}

	

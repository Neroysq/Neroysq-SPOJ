#include <stdio.h>
const int nmax = 50000, tmax = 1 << 17;

int n, m, M = 1;
int sum_t[tmax + 18], lmax_t[tmax + 18], rmax_t[tmax + 18], sub_t[tmax + 18];

int max(int a, int b) {return a > b ? a : b;}

void give(int i, int l, int r)
{
    sum_t[i] = sum_t[l] + sum_t[r];
    lmax_t[i] = max(lmax_t[l], sum_t[l] + lmax_t[r]);
    rmax_t[i] = max(rmax_t[r], sum_t[r] + rmax_t[l]);
    sub_t[i] = max(sub_t[l], max(sub_t[r], rmax_t[l] + lmax_t[r]));
}

void change(int i, int x)
{
    for (i += M, sum_t[i] = sub_t[i] = lmax_t[i] = rmax_t[i] = x; i >>= 1; )
	give(i, i << 1, i << 1 | 1);
}

int getmax(int l, int r)
{
    int subans, lrans, rlans;
    for (subans = lrans = rlans = -nmax, l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1)
	{
	    subans = max(subans, max(sub_t[l ^ 1], lrans + lmax_t[l ^ 1]));
	    lrans = max(lrans + sum_t[l ^ 1], rmax_t[l ^ 1]);
	}
	if ( r & 1)
	{
	    subans = max(subans, max(sub_t[r ^ 1], rlans + rmax_t[r ^ 1]));
	    rlans = max(rlans + sum_t[r ^ 1], lmax_t[r ^ 1]);
	}
    }
    return max(subans, lrans + rlans);
}

int main()
{
    freopen("GSS3.in", "r", stdin);
    freopen("GSS3.out", "w", stdout);
    scanf("%d", &n);
    while (n >= M) M <<= 1;
    for (int i = 1; i <= n; ++i) scanf("%d", sum_t + M + i), lmax_t[M + i] = rmax_t[M + i] = sub_t[M + i] = sum_t[M + i];
    for (int i = M - 1; i; --i)
	give(i, i << 1, i << 1 | 1);
    scanf("%d", &m);
    for (int k, x, y; m--;)
	if (scanf("%d%d%d", &k, &x, &y), k)
	    printf("%d\n", getmax(x, y));
	else
	    change(x, y);
    return 0;
}

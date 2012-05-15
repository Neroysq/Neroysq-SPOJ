#include <stdio.h>
const int nmax = 10000, tmax = 1 << 16;

int maxl[tmax + 18], maxr[tmax + 18], sum[tmax + 18], sub[tmax + 18];
int n, m, t, M;

int max(int a, int b) {return a > b ? a : b;}

int getmax(int l, int r, int mode)
{
    if (l > r) return 0;
    int lans = -nmax, rans = -nmax, sans = mode == 4 ? -nmax : 0;
    for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1)
	    if (mode == 0 || mode == 4) 
	    {
		if (mode == 4) sans = max(sub[l ^ 1], max(sans, lans + maxl[l ^ 1]));
		lans = max(maxr[l ^ 1], lans + sum[l ^ 1]);	    
	    }
	    else if (mode == 2) 
		lans = max(lans, sans + maxl[l ^ 1]), sans += sum[l ^ 1];
	    else sans += sum[l ^ 1];
	if ( r & 1)
	    if (mode == 2 || mode == 4)
	    {
		if (mode == 4) sans = max(sub[r ^ 1], max(sans, rans + maxr[r ^ 1]));
		rans = max(maxl[r ^ 1], rans + sum[r ^ 1]);
	    }
	    else if (mode == 0)
		rans = max(rans, sans + maxr[r ^ 1]), sans += sum[r ^ 1];
	    else sans += sum[r ^ 1];
    }
    return mode ? (mode == 1 ? sans : (mode == 2 ? max(rans + sans, lans) : max(sans, rans + lans))) : max(lans + sans, rans);
}

int main()
{
    freopen("GSS5.in", "r", stdin);
    freopen("GSS5.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	scanf("%d", &n);
	for (M = 1; n >= M; M <<= 1);
	for (int i = 1; i <= n; ++i) scanf("%d", sum + M + i), maxl[M + i] = maxr[M + i] = sub[M + i] = sum[M + i];
	for (int i = M - 1; i; --i)
	{
	    maxl[i] = max(maxl[i << 1], sum[i << 1] + maxl[i << 1 | 1]);
	    maxr[i] = max(maxr[i << 1 | 1], sum[i << 1 | 1] + maxr[i << 1]);
	    sum[i] = sum[i << 1] + sum[i << 1 | 1];
	    sub[i] = max(sub[i << 1], max(sub[i << 1 | 1], maxr[i << 1] + maxl[i << 1 | 1]));
	}
	scanf("%d", &m);
	for (int l1, r1, l2, r2; m--;)
	    if (scanf("%d%d%d%d", &l1, &r1, &l2, &r2), r1 < l2)
		printf("%d\n", getmax(l1, r1, 0) + getmax(r1 + 1, l2 - 1, 1) + getmax(l2, r2, 2));
	    else
		printf("%d\n", max(getmax(l1, l2 - 1, 0) + getmax(l2, r2, 2), max(getmax(l2, r1, 4), getmax(l2, r1, 0) + getmax(r1 + 1, r2, 2))));
    }
    return 0;
}

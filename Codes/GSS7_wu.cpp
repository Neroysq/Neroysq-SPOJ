#include <stdio.h>
const int nmax = 100000, tmax = 1 << 18;

int lmax[tmax + 18], rmax[tmax + 18], submax[tmax + 18], sum[tmax + 18], flag[tmax + 18];
int n, m, M = 1, H = 1;
bool ed[tmax + 18];

int max(int a, int b) {return a > b ? a : b;}
void update(int i)
{
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    submax[i] = max(rmax[i << 1] + lmax[i << 1 | 1], max(submax[i << 1], submax[i << 1 | 1]));
    lmax[i] = max(lmax[i << 1], rmax[i << 1] + sum[i << 1 | 1]);
    rmax[i] = max(rmax[i << 1 | 1], lmax[i << 1 | 1] + sum[i << 1]);
}

void pd(int i)
{
    for (int h = H - 1, j; h; --h)
	if (ed[j = i >> h])
	{
	    lmax[j << 1] = rmax[j << 1] = submax[j << 1] = max(flag[j << 1] = sum[j << 1] = flag[j] >> 1, 0);
	    lmax[j << 1 | 1] = rmax[j << 1 | 1] = submax[j << 1 | 1] = max(flag[j << 1 | 1] = sum[j << 1 | 1] = flag[j] >> 1, 0);
	    ed[j << 1] = ed[j << 1 | 1] = 1, ed[j] = 0;
	}
}

int getmax(int l, int r)
{
    int lans = 0, rans = 0, sans = 0;
    for (pd(l += M - 1), pd(r += M + 1); l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1)
	{
	    lans = max(lans + sum[l ^ 1], rmax[l ^ 1]);
	    sans = max(sans, max(lans, submax[l ^ 1]));
	}
	if ( r & 1)
	{
	    rans = max(rans + sum[r ^ 1], lmax[r ^ 1]);
	    sans = max(sans, max(rans, submax[r ^ 1]));
	}
    }
    return max(sans, lans + rans);
}

void change(int l, int r, int c)
{
    for (pd(l += M - 1), pd(r += M + 1); l ^ r ^ 1; update(l >>= 1), update(r >>= 1), c <<= 1)
    {
	if (~l & 1)
	    lmax[l ^ (ed[l ^ 1] = 1)] = rmax[l ^ 1] = submax[l ^ 1] = max(flag[l ^ 1] = sum[l ^ 1] = c, 0);
	if ( r & 1)
	    lmax[r ^ (ed[r ^ 1] = 1)] = rmax[r ^ 1] = submax[r ^ 1] = max(flag[r ^ 1] = sum[r ^ 1] = c, 0);
    }
    for (; l >>= 1;) update(l);
}

int main()
{
    freopen("GSS7.in", "r", stdin);
    freopen("GSS7.out", "w", stdout);
    scanf("%d", &n);
    while (n <= M) M <<= 1, ++H;
    for (int i = 1; i <= n; ++i) scanf("%d", sum + M + i), lmax[M + i] = rmax[M + i] = submax[M + i] = max(0, sum[M + i]);
    for (int i = M - 1; i; --i) update(i);
    for (int k, a, b, c; m--;)
	if (scanf("%d%d%d", &k, &a, &b), k == 1)
	    printf("%d\n", getmax(a, b));
	else
	    scanf("%d", &c), change(a, b, c);
    return 0;
}    

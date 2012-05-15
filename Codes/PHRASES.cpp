#include <stdio.h>
#include <string.h>
const int nmax = 10, lmax = 10000, smax = (lmax + 1) * nmax, shift = 100;

int sw[smax + 18], sv[smax + 18], who[smax + 18], xx[smax + 18], wre[smax + 18];
int a[smax + 18], height[smax + 18], ind[smax + 18];
int sl[nmax + 18], sr[nmax + 18], ed[nmax + 18], wdt;
int i, j, k, p, fdt, tot;
int n, l, r, t, nl, mid;
char str[lmax + 18];

int cmp(int *a, int i, int j, int l)
{
    return a[i] == a[j] && a[i + l] == a[j + l];
}

void da(int n, int m)
{
    int *x = xx, *y = wre, *t;
    for (i = 0; i <= m; ++i) sw[i] = 0;
    for (i = 1; i <= n; ++i) ++sw[x[i] = a[i]];
    for (i = 1; i <= m; ++i) sw[i] += sw[i - 1];
    for (i = n; i; --i) who[sw[x[i]]--] = i;
    for (j = p = 1; p < n; j <<= 1, m = p)
    {
	for (p = 0, i = n - j + 1; i <= n; ++i) y[++p] = i;
	for (i = 1; i <= n; ++i) if (who[i] > j) y[++p] = who[i] - j;
	for (i = 0; i <= m; ++i) sw[i] = 0;
	for (i = 1; i <= n; ++i) ++sw[sv[i] = x[y[i]]];
	for (i = 1; i <= m; ++i) sw[i] += sw[i - 1];
	for (i = n; i; --i) who[sw[sv[i]]--] = y[i];
	for (t = x, x = y, y = t, p = x[who[1]] = 1, i = 2; i <= n; ++i)
	    x[who[i]] = cmp(y, who[i - 1], who[i], j) ? p : ++p;
    }
}

void calch()
{
    for (i = 2; i <= tot; ++i) wre[who[i]] = i;
    for (k = 0, i = 1; i < tot; height[wre[i++]] = k)
	for (k ? --k : 0, j = who[wre[i] - 1]; a[i + k] == a[j + k]; ++k);
}

void update(int &a, int b){if (a < b) a = b;}
void downdate(int &a, int b){if (a > b) a = b;}

bool check(int k)
{
    int i, j, s;
    bool suc;
    for (i = 1; i <= n; ++i) sl[i] = lmax + 1, sr[i] = 0;
    for (i = 2, s = 0; i <= tot; ++i)
    {
	if (height[i] < k)
	{
	    s = 1, ++wdt;
	    sl[ind[who[i]]] = sr[ind[who[i]]] = who[i];
	    ed[ind[who[i]]] = wdt;
	}
	else
	{
	    if (ed[ind[who[i]]] !=  wdt)
	    {
		++s;
		sl[ind[who[i]]] = sr[ind[who[i]]] = who[i];
		ed[ind[who[i]]] = wdt;
	    }
	    else
		update(sr[ind[who[i]]], who[i]), downdate(sl[ind[who[i]]], who[i]);
	    if (s >= n)
	    {
		for (suc = 1, j = 1; j <= n; ++j)
		    if (sr[j] - sl[j] < k) 
		    {
			suc = 0;
			break;
		    }
		if (suc) return 1;
	    }
	}
    }
    return 0;
}

int main()
{
    freopen("PHRASES.in", "r", stdin);
    freopen("PHRASES.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	scanf("%d", &n);
	for (i = 1, fdt = tot = 0; i <= n; ++i)
	{
	    scanf("%s", str + 1);
	    nl = strlen(str + 1);if (nl > r) r = nl;
	    for (j = 1; j <= nl; ++j) a[++tot] = shift + str[j], ind[tot] = i;
	    a[++tot] = ++fdt, ind[tot] = i;
	}
	a[tot] = 0;
	da(tot, 280);
	calch();
	for (l = 0, r >>= 1; l < r; )
	    if (check(mid = (l + r + 1) >> 1))
		l = mid;
	    else
		r = mid - 1;
	printf("%d\n", r);
    }
    return 0;
}

	

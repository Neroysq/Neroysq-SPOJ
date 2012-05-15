#include <stdio.h>
const int nmax = 50000;

int sv[nmax + 18], sw[nmax + 18], who[nmax + 18];
int xx[nmax + 18], yy[nmax + 18], wre[nmax + 18];
int a[nmax + 18], segtree[1 << 17];
int n, t, M, l, tmp;
int i, j, k, p, ans;
char c;

int min(int a, int b)
{
    return a > b ? b : a;
}

void downdate(int &a, int b)
{
    if (a > b) a = b;
}

int cmp(int *a, int i, int j, int l)
{
    return a[i] == a[j] && a[i + l] == a[j + l];
}

void da(int n, int m)
{
    int *x = xx, *y = yy, *t;
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
	    x[who[i]] = cmp(y, who[i - 1], who[i], j) ? p: ++p;
    }
}

void calch(int *height)
{
    for (i = 2; i <= n; ++i) wre[who[i]] = i;
    for (k = 0, i = 1; i < n; height[wre[i++]] = k)
	for (k ? --k : 0, j = who[wre[i] - 1]; a[i + k] == a[j + k]; ++k);
}

int getrmq(int l, int r)
{
    int rnt;
    l = wre[l], r = wre[r];
    if (l > r) rnt = r, r = l, l = rnt;
    for (rnt = n, l += M, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1) downdate(rnt, segtree[l ^ 1]);
	if ( r & 1) downdate(rnt, segtree[r ^ 1]);
    }
    return rnt;
}

int main()
{
    freopen("REPEATS.in", "r", stdin);
    freopen("REPEATS.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	M = 1;ans = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) scanf("\n%c", &c), a[i] = c == 'a' ? 1 : 2;
	a[++n] = 0;
	da(n, 2);
	while (M <= n) M <<= 1;
	calch(segtree + M);
	for (i = M - 1; i; --i) segtree[i] = min(segtree[i << 1], segtree[i << 1 | 1]);
	--n;
	for (i = 1; i < n; ++i)
	    for (j = 1; j + i <= n; j += i)
	    {
		p = (k = getrmq(j, j + i)) / i;
		if ((l = j - (tmp = i - k % i)) && getrmq(l, l + i) >= tmp) ++p;
		if (p > ans) ans = p;
	    }
	printf("%d\n", ans + 1);
    }
    return 0;
}

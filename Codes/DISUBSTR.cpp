#include <stdio.h>
#include <string.h>
const int nmax = 50000;

int sw[nmax + 18], sv[nmax + 18], who[nmax + 18];
int xx[nmax + 18], wre[nmax + 18], height[nmax + 18];
int i, j, k, p;
int n, ans, t;
char str[nmax + 18];

int cmp(int *a, int i, int j, int l)
{
    return a[i] == a[j] && a[i + l] == a[j + l];
}

void da(int n, int m)
{
    int *x = xx, *y = wre, *t;
    for (i = 0; i <= m; ++i) sw[i] = 0;
    for (i = 1; i <= n; ++i) ++sw[x[i] = str[i]];
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
    for (i = 2; i <= n; ++i) wre[who[i]] = i;
    for (k = 0, i = 1; i < n; height[wre[i++]] = k)
	for (k ? --k : 0, j = who[wre[i] - 1]; str[i + k] == str[j + k]; ++k);
}

int main()
{
    freopen("DISUBSTR.in", "r", stdin);
    freopen("DISUBSTR.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	str[++n] = 0;
	da(n, 180);
	calch();
	for (i = 2, ans = 0; i <= n; ++i) 
	    ans += n - who[i] - height[i];
	printf("%d\n", ans);
    }
    return 0;
}

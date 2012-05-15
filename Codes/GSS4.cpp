#include <stdio.h>
#include <math.h>
typedef long long ll;
const int nmax = 100000;

int f[nmax + 18], n, m, tot;
ll s[nmax + 18], a[nmax + 18], tmp;

int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}

void add(int i, ll x)
{
    for (; i <= n; i += i & -i) s[i] += x;
}

ll gets(int l, int r)
{
    ll rnt = 0;
    for (--l; l; l -= l & -l) rnt -= s[l];
    for (; r; r -= r & -r) rnt += s[r];
    return rnt;
}

int main()
{
    freopen("GSS4.in", "r", stdin);
    freopen("GSS4.out", "w", stdout);
    while (scanf("%d", &n) != EOF)
    {
	printf("Case #%d:\n", ++tot);
	for (int i = 1; i <= n; ++i) scanf("%I64d", a + i), s[f[i] = a[i] == 1 ? i + 1 : i] = 0;
	for (int i = 1; i <= n; ++i) add(i, a[i]);
	scanf("%d", &m), f[n + 1] = n + 1;
	for (int i = 1, k, x, y; i <= m; ++i)
	    if (scanf("%d%d%d", &k, &x, &y), k)
		printf("%I64d\n", x < y ? gets(x, y) : gets(y, x));
	    else
	    {
		if (x > y) k = x, x = y, y = k;
		for (int i = find(x); i <= y; i = find(i + 1))
		{
		    tmp = a[i], a[i] = (long long)sqrt(a[i]);
		    add(i, a[i] - tmp);
		    if (a[i] == 1) f[i] = i + 1;
		}
	    }
	printf("\n");
    }
    return 0;
}

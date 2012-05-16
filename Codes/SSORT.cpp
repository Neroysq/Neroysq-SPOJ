#include <stdio.h>
const int nmax = 1000;

int num[nmax + 18], mininall, pnum[nmax + 18], ed[nmax + 18];
int n, ans, wdt, ord[nmax + 18], no, minofcyc;

void downdate(int &a, int b) {if (a > b) a = b;}
int min(int a, int b) {return a > b ? b : a;}

int main()
{
    freopen("SSORT.in", "r", stdin);
    freopen("SSORT.out", "w", stdout);
    while (scanf("%d", &n), n)
    {
	int i, j, k;
	ans = 0;++wdt;
	mininall = nmax;
	for (i = 1; i <= n; ++i) scanf("%d", &num[i]), pnum[num[i]] = wdt, ans += num[i], downdate(mininall, num[i]);
	for (no = 0, i = 1; i <= nmax; ++i)
	    if (pnum[i] == wdt)
		ord[i] = ++no;
	for (i = 1; i <= n; ++i)
	    if (ed[ord[num[i]]] != wdt)
	    {
		for (ed[j = ord[minofcyc = num[i]]] = wdt, k = 1; j != i; ++k)
		    downdate(minofcyc, num[j]), ed[ord[num[j]]] = wdt, j = ord[num[j]];
		ans += min((k - 2) * minofcyc, (k + 1) * mininall + minofcyc);
	    }
	printf("Case %d: %d\n\n", wdt, ans);
    }
    return 0;
}

	

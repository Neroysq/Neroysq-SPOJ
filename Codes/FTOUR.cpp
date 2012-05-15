//WAing....  for later
#include <stdio.h>
#include <string.h>
const int nmax = 8000, mmax = 10000 << 1, oo = ~0U >> 1;

int t, n, m, tot, ans, ansl, ansr, f[nmax + 18];
int fst[nmax + 18], nxt[mmax + 18], pnt[mmax + 18];
int ed[mmax/2 + 18], wdt, tmp, d[nmax + 18];

void add(int s, int t) {pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot;}
void dfs(int x)
{
    for (int i = fst[x], p; i; i = nxt[i])
	if (ed[i >> 1] != wdt)
	    if (ed[i >> 1] = wdt, !d[p = pnt[i]])
		d[p] = d[f[p] = x] + 1, dfs(p);
	    else
		if (!((tmp = d[x] - d[p] + 1) & 1) && ans > tmp)
		    ans = tmp, ansl = x, ansr = p;
}

int main()
{
    freopen("FTOUR.in", "r", stdin);
    freopen("FTOUR.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	scanf("%d%d", &n, &m);
	memset(fst, 0, sizeof(fst));
	memset(d, 0, sizeof(d));
	ans = oo, tot = 1, ++wdt, d[1] = 1;
	for (int i = 1, ss, tt; i <= m; ++i)
	    scanf("%d%d", &ss, &tt), add(ss, tt), add(tt, ss);
	dfs(1);
	if (ans < oo)
	    for (printf("%d\n%d", ans, ansr); ;)
		if (printf(" %d", ansl), ansl == ansr)
		    break;
		else ansl = f[ansl];
	else printf("-1");
	printf("\n");
    }
    return 0;
}


#include <stdio.h>
#include <string.h>
const int nmax = 50000 * 2, mmax = 150000 * 2;

int n, m, ans, tot = 1, deg[nmax + 18], e;
int fst[nmax + 18], pnt[mmax + 18], nxt[mmax + 18], now;
int head[nmax + 18], l[nmax / 2 * 3+ 18], r[nmax / 2 * 3 + 18], mind;
bool ed[mmax / 2 + 18];

void add(int s, int t) {pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot, ++deg[s];}
inline void dellist(int k) {r[l[k]] = r[k], l[r[k]] = l[k];}
inline void addlist(int k, int x) {l[r[k] = r[x]] = k, l[r[x] = k] = x;}

void clear(int j)
{
    for (int i = fst[j]; i; i = nxt[i])
	if (!ed[i >> 1])
	    if (dellist(pnt[i]), ed[i >> 1] = 1, --now, --deg[pnt[i]])
		if (addlist(pnt[i], head[deg[pnt[i]]]), mind > deg[pnt[i]]) 
		    mind = deg[pnt[i]];
}

int main()
{
          freopen("matching.in", "r", stdin);
          freopen("matching.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1, ss, tt; i <= e; ++i)
	scanf("%d%d", &ss, &tt), tt += n, add(ss, tt), add(tt, ss);
    e = m > n ? n : m;
    for (int i = 1; i <= e; ++i) head[i] = n + m + i;
    for (int i = 1; i <= n + m; ++i) if (deg[i]) addlist(i, head[deg[i]]);
    for (now = tot >> 1, mind = 1; now; ++ans)
    {
	int i, minnei, minneid = n + m, minind, j;
	while (!r[head[mind]])
	    ++mind;
	for (i = fst[r[head[mind]]]; i; i = nxt[i])
	    if (!ed[i >> 1] && deg[pnt[i]] < minneid)
		minneid = deg[minnei = pnt[minind = i]];
	dellist(j = r[head[mind]]), dellist(minnei);
	ed[minind >> 1] = 1, --now, clear(j), clear(minnei);
    }
    printf("%d\n", ans);
    return 0;
}

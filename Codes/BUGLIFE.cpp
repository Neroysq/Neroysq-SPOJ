#include <stdio.h>
const int nmax = 2000 << 1, mmax = 1000000 << 2;

int n, m, fst[nmax + 18], nxt[mmax + 18], pnt[mmax + 18];
int stack[nmax + 18], st, dfn[nmax + 18], low[nmax + 18];
int tot;
bool lancer[nmax + 18];

void add(int s, int t)
{
    pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot;
    pnt[++tot] = s, nxt[tot] = fst[t], fst[t] = tot;
}

void del(int x)
{
    if (lancer[x ^ 1]) return; else lancer[x ^ 1] = 1;
    for (int i = fst[x]; i; i = nxt[i]) del(pnt[i]);
}

void dfs(int x)
{
    stack[dfn[x] = low[x] = ++st] = x;
    for (int i = fst[x]; i; i = nxt[i])
	if (dfn[pnt[i]] > 0)
	    low[x] > low[pnt[i]] ? low[x] = low[pnt[i]] : 0;
	else
	    if (!dfn[pnt[i]])
		dfs(pnt[i]), low[x] > low[pnt[i]] ? low[x] = low[pnt[i]] : 0;
    if (low[x] == dfn[x]) {
	int nt = dfn[x];
	while (st >= nt) dfn[stack[st--]] = -1;
	if (!lancer[x]) del(x);
    }
}

int main()
{
    int t;
    freopen("BUGLIFE.in", "r", stdin);
    freopen("BUGLIFE.out", "w", stdout);
    scanf("%d", &t);
    for(int cases = 1; cases <= t; ++cases) {
	for (int i = n << 1 | 1; i; --i) dfn[i] = fst[i] = lancer[i] = 0;
	scanf("%d%d", &n, &m);
	tot = 0;
	for (int i = 1, ss, tt; i <= m; ++i)
	    scanf("%d%d", &ss, &tt), add(ss << 1, tt << 1 | 1), add(tt << 1, ss << 1 | 1);
	for (int i = 1; i <= n; ++i) {
	    if (!dfn[i << 1]) dfs(i << 1);
	    if (!dfn[i << 1 | 1]) dfs(i << 1 | 1);
	}
	bool suc = 1; 
	for (int i = 1; i <= n; ++i)
	    if (lancer[i << 1] && lancer[i << 1 | 1]) {
		suc = 0;
		break;
	    }
	printf("Scenario #%d:\n", cases);
	if (!suc)
	    printf("Suspicious bugs found!\n");
	else
	    printf("No suspicious bugs found!\n");
    }
    return 0;
}

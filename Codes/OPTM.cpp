/*
    We solve this problem one bit by one bit like the classic 2-sat problem
    network maxflow
    O(log2(n) * maxflow(n, m))
*/
#include <stdio.h>
const int nmax = 500, mmax = 3000, emax = (mmax + nmax*2) << 1, oo = ~0U >> 1, Woo = oo >> 1;

int t, n, m, tot, S, T, k, K;
int fst[nmax + 18], nxt[emax + 18], pnt[emax + 18], cty[emax + 18];
int mark[nmax + 18], ans[nmax + 18], num[nmax + 18];
int gap[nmax + 18], dis[nmax + 18], pre[nmax + 18], cur[nmax + 18];
int next[nmax + 18], head, tail, ed[nmax + 18], wdt;

void add(int s, int t)
{
    pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot;
    pnt[++tot] = s, nxt[tot] = fst[t], fst[t] = tot;
}

void bfs()
{
    gap[dis[head = tail = T] = 0] = 1;
    for (int i, now, p; head; head = next[now], next[now] = 0)
	for (i = fst[now = head]; i; i = nxt[i])
	    if (cty[i ^ 1] && dis[p = pnt[i]] > dis[now] + 1) 
		++gap[dis[p] = dis[now] + 1], next[tail] = p, tail = p;
}

void sap(int num)
{
    for (int i = 1; i <= num; ++i) dis[i] = Woo, gap[i] = 0, cur[i] = fst[i];
    bfs();
    for (int i, u = S, min, p, del = oo; dis[S] <= num; ) {
	for (bool flag = 1; flag; )
	    for (flag = 0, i = cur[u]; i && !flag; i = nxt[i])
		if (cty[i] && dis[p = pnt[i]] + 1 == dis[u]) {
		    if (del > cty[i]) del = cty[i];
		    flag = 1;
		    pre[u = p] = i;
		    if (p == T) {
			for (; p != S; p = pnt[u ^ 1])
			    cty[u = pre[p]] -= del, cty[u ^ 1] += del;
			del == oo, u = S;
		    }
		}
		else cur[u] = i;
	for (i = fst[u], min = num; i; i = nxt[i])
	    if (cty[i] && min > dis[pnt[i]]) min = dis[pnt[i]];
	if (!(--gap[dis[u]])) break;
	++gap[dis[u] = min + 1];
	cur[u] = fst[u];
	if (u != S) u = pnt[pre[u] ^ 1];
    }
}

void dfs(int x)
{
    ed[x] = wdt, ans[x] |= 1 << K;
    for (int i = fst[x]; i; i = nxt[i])
	if (ed[pnt[i]] != wdt && cty[i])
	    dfs(pnt[i]);
}

bool work()
{
    bool over = 0;
    for (int i = 1; i <= n; ++i)
	cty[i << 1] = cty[(i + n) << 1] = 1, cty[i << 1 | 1] = cty[(i + n) << 1 | 1] = 0;
    for (int i = (n << 2) + 2; i <= tot; ++i) cty[i] = 1;
    for (int i = 1; i <= k; ++i) {
	(mark[i] & 1) ? cty[num[i] << 1] = oo : cty[(n + num[i]) << 1] = oo;
	if (mark[i] >>= 1) over = 1;
    }
    sap(T), ++wdt, dfs(S);
    return over;
}

int main()
{
    freopen("OPTM.in", "r", stdin);
    freopen("OPTM.out", "w", stdout);
    scanf("%d", &t);
    while (t--) {
	tot = 1;
	scanf("%d%d", &n, &m);
	S = n + 1, T = S + 1;
	fst[S] = fst[T] = 0;
	for (int i = 1; i <= n; ++i) ans[i] = fst[i] = 0, add(S, i);
	for (int i = 1; i <= n; ++i) add(i, T);
	for (int i = 1, ss, tt; i <= m; ++i)
	    scanf("%d%d", &ss, &tt), add(ss, tt);
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i)
	    scanf("%d%d", num + i, mark + i);
	for (K = 0; K < 31 && work(); ++K);
	for (int i = 1; i <= n; ++i)
	    printf("%d\n", ans[i]);
    }
    return 0;
}

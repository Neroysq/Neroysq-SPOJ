#include <stdio.h>
#include <string.h>
const int vmax = 5000, emax = 30000, oo = ~0U >> 1, Emax = emax * 2;

int n, m, S = 0;

int s, t, tot = 1;
int gap[vmax + 18], pre[vmax + 18], cur[vmax + 18], fst[vmax + 18], dis[vmax + 18];
int pnt[Emax + 18], nxt[Emax + 18], cty[Emax + 18];

void addedge (int s, int t, int c)
{
    pnt[++tot] = t;
    nxt[tot] = fst[s];
    fst[s] = tot;
    cty[tot] = c;
}

int next[vmax + 18], head, tail;

void bfs ()
{
    gap[dis[head = tail = t] = 0] = 1;
    for (int p, i, now; head; head = next[now], next[now] = 0)
        for (i = fst[now = head]; i; i = nxt[i])
            if (cty[i ^ 1] && dis[p = pnt[i]] > dis[now] + 1)
	    {
                ++gap[dis[p] = dis[now] + 1];
		if (!next[p] && tail != p)
		    next[tail] = p, tail = p;
	    }
}

long long sap (int num)
{
    memset(dis, 0x3F, sizeof (dis));
    memset(gap, 0, sizeof (gap));
    for (int i = 1; i <= num; ++i) cur[i] = fst[i];
    bfs ();
    long long ans = 0;
    for (int u = s, del = oo, i, min, p; dis[s] <= num; )
    {
        for (bool flag = 1; flag;)
            for (i = cur[u], flag = 0; i && !flag; i = nxt[i])
                if (cty[i] && dis[u] == dis[p = pnt[i]] + 1)
                {
                    if (del > cty[i]) del = cty[i];
                    pre[u = p] = i; flag = 1;
                    if (p == t)
                    {
                        for (ans += del; p != s; p = pnt[u ^ 1]) cty[u = pre[p]] -= del, cty[u ^ 1] += del;
                        u = s, del = oo;
                    }
                }
		else cur[u] = i;
        for (min = num, i = fst[u]; i; i = nxt[i])
            if (cty[i] && dis[p = pnt[i]] < min) min = dis[p];
        if (!(--gap[dis[u]])) break;
        ++gap[dis[u] = min + 1];
	cur[u] = fst[u];
        if (u != s) u = pnt[pre[u] ^ 1];
    }
    return ans;
}

int main()
{
    freopen("FASTFLOW.in", "r", stdin);
    freopen("FASTFLOW.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset (fst, 0, sizeof(fst));
    for (int i = 1, ss, tt, cc; i <= m; ++i)
    {
	scanf("%d%d%d", &ss, &tt, &cc);
	addedge(ss, tt, cc);addedge(tt, ss, cc);
    }
    s = 1;t = n;
    printf("%I64d", sap(n));
    return 0;
}

// Copyright @ Neroysq

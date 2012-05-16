/*
  Just a point-divide_and_conquer the hard part is how to calc the answer of a subtree in O(n) time
  O(nlogn)
*/
#include <stdio.h>
const int nmax = 200000, mmax = nmax << 1;

int n, m, K, d[nmax + 18], sze[nmax + 18], sta[nmax + 18], bl[nmax + 18], globemaxd;
int fst[nmax + 18], pnt[mmax + 18], nxt[mmax + 18], cst[mmax + 18];
int ed[nmax + 18], wdt, ans, globen, globek, tot, ms[nmax + 18], st, c[nmax + 18], f[nmax + 18];
bool bla[nmax + 18], dead[nmax + 18];

void add(int s, int t, int c) {pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot, cst[tot] = c;}
void conflict_prince(int &a, int b) {if (ms[a] > ms[b]) a = b;}
void update(int &a, int b) {if (a < b) a = b;}

int dfs_centroid(int x)
{
    ed[x] = wdt, sze[x] = 1;
    int prince = ms[x] = 0;
    for (int i = fst[x], p; i; i = nxt[i])
	if (!dead[p = pnt[i]] && ed[p] != wdt)
	    conflict_prince(prince, dfs_centroid(pnt[i])), sze[x] += sze[p], update(ms[x], sze[p]);
    update(ms[x], globen - sze[x]);
    return ms[prince] > ms[x] ? x : prince;
}

void dfs_depth(int x, int tot)
{
    ed[x] = wdt;
    if (tot > globek) return;
    update(globemaxd, tot), update(c[tot], d[x]);
    for (int i = fst[x]; i; i = nxt[i])
	if (!dead[pnt[i]] && ed[pnt[i]] != wdt)
	    d[pnt[i]] = d[x] + cst[i], dfs_depth(pnt[i], tot + bla[pnt[i]]);
}

void dfs_ans(int x)
{
    dead[x] = 1, d[x] = 0, ++wdt, globek = K - bla[x], f[0] = 0;
    int nmaxd = 0;
    for (int i = fst[x]; i; i = nxt[i])
	if (!dead[pnt[i]])
	{
	    d[pnt[i]] = d[x] = cst[i], globemaxd = 0, dfs_depth(pnt[i], bla[pnt[i]]);
	    for (int j = 1; j <= globemaxd; ++j) update(c[j], c[j - 1]);
	    for (int j = 0; j <= globemaxd; ++j)
		update(ans, c[j] + f[(globek - j) > nmaxd ? nmaxd : globek - j]);
	    if (globemaxd > nmaxd)
	    {
		for (int j = nmaxd + 1; j <= globemaxd; ++j) f[j] = c[j];
		nmaxd = globemaxd;
	    }
	    for (int j = 0; j <= globemaxd; ++j)
		update(f[j], c[j]), c[j] = 0;
	}
    for (int i = fst[x]; i; i = nxt[i])
	if (!dead[pnt[i]])
	    globen = sze[pnt[i]], ++wdt, dfs_ans(dfs_centroid(pnt[i]));
}

int main()
{
    freopen("FTOUR2.in", "r", stdin);
    freopen("FTOUR2.out", "w", stdout);
    scanf("%d%d%d", &n, &K, &m);
    ms[0] = n;
    for (int i = 1, id; i <= m; ++i) scanf("%d", &id), bla[id] = 1;
    for (int i = 1, ss, tt, cc; i < n; ++i) 
	scanf("%d%d%d", &ss, &tt, &cc), add(ss, tt, cc), add(tt, ss, cc);
    globen = n, wdt = 1, dfs_ans(dfs_centroid(1));
    printf("%d", ans);
    return 0;
}

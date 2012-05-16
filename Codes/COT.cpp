/*
   idea of functional programming 
   let seg[i] = a segment tree maintaining the every element's apprear time from root to v[i]
   O(nlogn)
*/
#include <stdio.h>
#include <stdlib.h>
const int nmax = 100000, mmax = nmax << 2;

struct tps {
    tps *l, *r;
    int s;
}*st[nmax + 18], TMP, *null = &TMP, pool[nmax * 20];

int ind[nmax + 18], idt, p[nmax + 18], fp[nmax + 18];
int n, m, f[nmax + 18], base, pot;
int fst[nmax + 18], Fst[nmax + 18], nxt[mmax + 18], pnt[mmax + 18], tot;
int q[nmax + 18], a[nmax + 18], b[nmax + 18], c[nmax + 18];
bool ed[nmax + 18];

inline tps *newp(tps *b) {tps *a = &pool[++pot]; return *a = *b, a;}
inline int cmpor(const void *i, const void *j) {return a[*(int *)i] - a[*(int *)j];}
inline int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}

inline void add(int *fst, int s, int t)
{
    pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot;
    pnt[++tot] = s, nxt[tot] = fst[t], fst[t] = tot;
}

inline tps *build(int l, int r)
{
    tps *a = newp(null);
    if (l < r) {
	int mid = (l + r) >> 1;
	a->l = build(l, mid);
	a->r = build(mid + 1, r);
    }
    return a;
}

inline void add(tps *&a, int l, int r, int x)
{
    a = newp(a);
    ++a->s;
    if (l == r) return;
    else {
	int mid = (l + r) >> 1;
	if (x <= mid) add(a->l, l, mid, x);
	else add(a->r, mid + 1, r, x);
    }
}

inline void dfs(int x)
{
    ed[f[x] = x] = 1, add(st[x], 1, idt, ind[x]);
    for (int i = Fst[x]; i; i = nxt[i])
	if (ed[pnt[i]])
	    c[(i - base) >> 1] = find(pnt[i]);
    for (int i = fst[x]; i; i = nxt[i])
	if (!ed[pnt[i]])
	    st[pnt[i]] = st[x], dfs(pnt[i]), f[find(pnt[i])] = x;
}

inline int ask(tps *a, tps *b, tps *c, int k, int A)
{
    int l = 1, r = idt;
    for (int tmp, mid; l < r; )
	if ((tmp = a->l->s + b->l->s - (c->l->s << 1) + (A <= (mid = (l + r) >> 1) && A >= l)) >= k)
	    a = a->l, b = b->l, c = c->l, r = mid;
	else
	    k -= tmp, a = a->r, b = b->r, c = c->r, l = mid + 1;
    return fp[l];
}

int main()
{
    freopen("COT.in", "r", stdin);
    freopen("COT.out", "w", stdout);
    null->l = null->r = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), p[i] = i;
    qsort(p + 1, n, sizeof(p[0]), cmpor);
    for (int i = 1, last = a[p[1]] - 1; i <= n; ++i)
	if (a[p[i]] == last)
	    ind[p[i]] = idt;
	else
	    fp[ind[p[i]] = ++idt] = last = a[p[i]];
    for (int i = 1, ss, tt; i < n; ++i)
	scanf("%d%d", &ss, &tt), add(fst, ss, tt);
    base = tot - 1;
    for (int i = 1; i <= m; ++i)
	scanf("%d%d%d", a + i, b + i, q + i), add(Fst, a[i], b[i]);
    st[1] = st[0] = build(1, n);
    dfs(1);
    for (int i = 1; i <= m; ++i) 
	printf("%d\n", ask(st[a[i]], st[b[i]], st[c[i]], q[i], ind[c[i]]));
    return 0;
}

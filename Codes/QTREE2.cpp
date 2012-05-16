#include <stdio.h>
#include <string.h>
const int nmax = 10000, mmax = nmax * 2;

int t, n, tot, l, r, k, q[nmax + 18], qh, qt, d[nmax + 18];
int fst[nmax + 18], nxt[mmax + 18], pnt[mmax + 18], cst[mmax + 18];
char str[10];
bool ed[nmax + 18];

inline void add(int s, int t, int c){pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot, cst[tot] = c;}

struct Spode
{
    int k, s, sze, who;
    Spode *chi[2], *p;
    inline bool dir(){return this == p->chi[1];}
    inline bool pcs(){return p->chi[1] == this || p->chi[0] == this;}
    inline void update(){s = chi[0]->s + chi[1]->s + k, sze = chi[0]->sze + chi[1]->sze + 1;}
}pe[nmax + 18], *null;

inline void rotate(Spode *a)
{
    Spode *b = a->p;
    bool d = !a->dir();
    if (b->pcs()) b->p->chi[b->dir()] = a;
    a->p = b->p, b->p = a, b->chi[!d] = a->chi[d], a->chi[d]->p = b, a->chi[d] = b;
    b->update();
}

inline void splay(Spode *a)
{
    while (a->p != null && a->pcs())
	if (a->p->p == null || !a->p->pcs()) rotate(a);
	else
	    a->dir() == a->p->dir() ? (rotate(a->p), rotate(a)) : (rotate(a), rotate(a));
    a->update();
}

inline Spode *access(Spode *a)
{
    Spode *b;
    for (b = null; a != null; a = a->p)
	splay(a), a->chi[1] = b, (b = a)->update();
    return b;
}

inline void bfs()
{

    memset(ed, 0, sizeof(ed));
    ed[q[qh = qt = 1] = 1] = 1;pe[1].p = null;
    for (int i, p; qh <= qt; ++qh)
	for (pe[q[qh]].sze = 1, pe[q[qh]].chi[0] = pe[q[qh]].chi[1] = null, i = fst[q[qh]]; i; i = nxt[i])
	    if (!ed[p = pnt[i]])
		d[p] = d[q[qh]] + 1, ed[p] = 1, q[++qt] = p, pe[p].k = pe[p].s = cst[i], pe[p].p = &pe[q[qh]];
}

int find(Spode *a, int k)
{
    for (;;)
	if (a->chi[0]->sze + 1 == k) return a->who;
	else
	    if (a->chi[0]->sze < k) k-=a->chi[0]->sze + 1, a = a->chi[1];
	    else a = a->chi[0];
}

int main()
{
    freopen("QTREE2.in", "r", stdin);
    freopen("QTREE2.out", "w", stdout);
    null = new Spode;
    null->s = null->k = null->sze = 0;
    for (int i = 1; i <= nmax; ++i) pe[i].who = i, pe[i].sze = 1;
    for (scanf("%d", &t); t--;)
    {
	scanf("%d", &n);tot = 1;
	memset(fst, 0, sizeof(fst));
	for (int i = 1, ss, tt, cc; i < n; ++i) scanf("%d%d%d", &ss, &tt, &cc), add(ss, tt, cc), add(tt, ss, cc);
	bfs();
	for (Spode *a, *b, *c; scanf("%s", str), str[1] != 'O';)
	    if (str[1] == 'I')
	    {
		scanf("%d%d", &l, &r);
		d[l] > d[r] ? (a = &pe[l], b = &pe[r]) : (a = &pe[r], b = &pe[l]);
		access(a);
		c = access(b);
		splay(a);
		printf("%d\n", l == r ? 0 : a->s + c->chi[1]->s);
	    }
	    else
	    {
		scanf("%d%d%d", &l, &r, &k);
		a = &pe[l], b = &pe[r];
		access(a), c = access(b);
		splay(a);
		if (a == c) splay(c), printf("%d\n", find(c, c->chi[0]->sze + k));
		else
		    if (a->sze >= k) printf("%d\n", find(a, a->sze - k + 1));
		    else splay(c), printf("%d\n", find(c, k - a->sze + c->chi[0]->sze));
	    }
    }
    return 0;
}

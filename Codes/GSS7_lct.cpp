#include <stdio.h>
const int nmax = 100000, mmax = nmax << 1;

int fst[nmax + 18], nxt[mmax + 18], pnt[mmax + 18], tot;
int a[nmax + 18], n, m, next[nmax + 18], head, tail, dep[nmax + 18];
bool ed[nmax + 18];
char com;

int max(int a, int b) {return a > b ? a : b;}
void add(int s, int t) {pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot;}
struct Spode
{
    Spode *c[2], *f;
    int x, ml, mr, ms, sum, sze;
    bool ed;
    inline bool dir() {return this == f->c[1];}
    inline bool pcs() {return this == f->c[1] || this == f->c[0];}
    inline void update()
	{
	    sum = c[0]->sum + x + c[1]->sum;
	    ml = max(c[0]->ml, c[0]->sum + x + c[1]->ml);
	    mr = max(c[1]->mr, c[1]->sum + x + c[0]->mr);
	    ms = max(c[0]->ms, max(c[1]->ms, c[0]->mr + x + c[1]->ml));
	    sze = c[0]->sze + 1 + c[1]->sze;
	}
}pe[nmax + 18], *null;

void give(Spode *a, int z)
{
    if (a == null) return;
    a->ed = 1, a->x = z;
    a->ml = a->mr = a->ms = max(a->sum = z * a->sze, 0);
}

void pd(Spode *a)
{
    if (a->ed)
	give(a->c[0], a->x), give(a->c[1], a->x), a->ed = 0;
}

void rot(Spode *a)
{
    Spode *b = a->f;
    bool m = a->dir();
    a->f = b->f, b->c[m] = a->c[!m];
    if (b->pcs()) a->f->c[b->dir()] = a;
    if (a->c[!m] != null) a->c[!m]->f = b;
    a->c[!m] = b, b->f = a;
    b->update();
}

void splay(Spode *a)
{
    pd(a);
    while (a->pcs())
	if (!a->f->pcs()) pd(a->f), pd(a), rot(a);
	else pd(a->f->f), pd(a->f), pd(a), a->dir() == a->f->dir() ? rot(a->f) : rot(a), rot(a);
    a->update();
}

Spode *access(Spode *a)
{
    Spode *b = null;
    for (; a != null; a = b->f)
	splay(a), a->c[1] = b, (b = a)->update();
    return b;
}

void bfs()
{
    pe[dep[1] = ed[head = tail = 1] = 1].f = null;
    for (int now, i, p; head; head = next[now], next[now] = 0)
	for (pe[now = head].c[0] = pe[now].c[1] = null, pe[now].ml = pe[now].mr = pe[now].ms = max(pe[now].sum = pe[now].x, 0), i = fst[now]; i; i = nxt[i])
	    if (!ed[p = pnt[i]])
		ed[p] = 1, pe[p].f = &pe[now], next[tail] = p, dep[tail = p] = dep[now] + 1;
}

int main()
{
    freopen("GSS7.in", "r", stdin);
    freopen("GSS7.out", "w", stdout);
    null = new Spode;
    null->ml = null->mr = null->ms = null->sum = null->ed = null->sze = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &pe[i].x);
    for (int i = 1, ss, tt; i < n; ++i)
	scanf("%d%d", &ss, &tt), add(ss, tt), add(tt, ss);
    bfs();
    scanf("%d", &m);
    Spode *a, *b, *d;
    for (int x, y, z; m--; )
    {
	scanf("\n%c%d%d", &com, &x, &y);
	if (dep[x] < dep[y]) z = x, x = y, y = z;
	a = &pe[x], b = &pe[y];
	access(a), d = access(b), splay(a);
	if (com == '1')
	{
	    z = a == b ? max(0, a->x) : a->ms;
	    if (d != a) 
		if (d->c[1] != null) z = max(z, max(d->c[1]->ms, a->ml + d->x + d->c[1]->ml));
		else z = max(z, d->x + a->ml);
	    else if (d->c[1] != null) z = max(z, a->x + a->c[1]->ml);
	    printf("%d\n", z);
	}
	else
	{
	    scanf("%d", &z);
	    if (a != b) give(a, z), give(d->c[1], z);
	    d->x = z, d->update();
	}
    }
    return 0;
}

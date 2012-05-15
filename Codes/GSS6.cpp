#include <stdio.h>
#define d(i) ((i) > 0 ? (i) : 0)
const int nmax = 100000;

int max(int a, int b) {return a > b ? a : b;}
struct Spode
{
    int x, msub, ml, mr, sum, sze;
    Spode *c[2], *f;
    inline bool dir() {return this == f->c[1];}
    inline void update()
    {
	msub = max(d(c[0]->mr) + x + d(c[1]->ml), max(c[0]->msub, c[1]->msub));
	ml = max(c[0]->ml, c[0]->sum + x + d(c[1]->ml));
	mr = max(c[1]->mr, c[1]->sum + x + d(c[0]->mr));
	sum = c[0]->sum + x + c[1]->sum;
	sze = c[0]->sze + 1 + c[1]->sze;
    }
}pe[nmax * 2 + 18], *null, *l, *r, *root;
int n, m, p[nmax * 2 + 18], tot, a[nmax + 18];
char com;

inline void rotate(Spode *a)
{
    Spode *b = a->f;
    bool m = a->dir();
    a->f = b->f, b->c[m] = a->c[!m];
    if (b->f != null) b->f->c[b->dir()] = a;
    if (a->c[!m] != null) a->c[!m]->f = b;
    a->c[!m] = b, b->f = a;
    b->update();
}

inline void splay(Spode *a, Spode *b)
{
    while (a->f != b)
	if (a->f->f == b) rotate(a);
	else a->dir() == a->f->dir() ? rotate(a->f) : rotate(a), rotate(a);
    a->update();
    if (b != null) b->update();
    if (b == null) root = a;
}

inline Spode *find_rank(int x)
{
    Spode *a = root;
    while (a->c[0]->sze + 1 != x)
	if (a->c[0]->sze + 1 == x) break;
	else if (a->c[0]->sze < x)
	    x -= a->c[0]->sze + 1, a = a->c[1];
	else
	    a = a->c[0];
    return a;
}

inline Spode *build(int l, int r)
{
    int mid = (l + r + 1) >> 1;
    Spode *b = &pe[++tot];
    b->x = a[mid];
    b->msub = b->ml = b->mr = b->sum = a[mid];
    b->sze = 1;
    if (l < mid) b->c[0] = build(l, mid - 1), b->c[0]->f = b; 
    else b->c[0] = null;
    if (r > mid) b->c[1] = build(mid + 1, r), b->c[1]->f = b;
    else b->c[1] = null;
    b->update();
    return b;
}

int main()
{
    freopen("GSS6.in", "r", stdin);
    freopen("GSS6.out", "w", stdout);
    scanf("%d", &n);
    null = new Spode;
    null->x = null->ml = null->mr = null->msub = -nmax;
    null->sze = null->sum = 0;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    (root = build(0, n + 1))->f = null;
    scanf("%d", &m);
    for (int x, y; m--;)
	if (scanf("\n%c%d", &com, &x), com == 'D')
	{
	    l = find_rank(x), r = find_rank(x + 2);
	    splay(l, null), splay(r, l);
	    r->c[0] = null;
	    r->update(), l->update();
	}
	else
	{
	    scanf("%d", &y);
	    if (com == 'I')
	    {
		l = find_rank(x), r = find_rank(x + 1);
		splay(l, null), splay(r, l);
		pe[++tot].x = y;
		pe[tot].ml = pe[tot].mr = pe[tot].msub = pe[tot].sum = y;
		pe[tot].sze = 1;
		r->c[0] = &pe[tot];
		pe[tot].c[0] = pe[tot].c[1] = null;
		pe[tot].f = r;
		r->update(), l->update();
	    }
	    else if (com == 'R')
		splay(l = find_rank(x + 1), null), l->x = y, l->update();
	    else if (com == 'Q')
	    {
		splay(l = find_rank(x), null);
		splay(r = find_rank(y + 2), l);
		printf("%d\n", r->c[0]->msub);
	    }
	}
    return 0;
}

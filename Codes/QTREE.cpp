#include <stdio.h>
#include <string.h>
const int nmax = 10000, mmax = nmax * 2, oo = ~0U >> 1;

int n, tot = 1, t;
int fst[nmax + 18], pnt[mmax + 18], cst[mmax + 18], nxt[mmax + 18];
char com[10];
int k, l, r, ans, q[nmax + 18], qh, qt;
bool ed[nmax + 18];

void add(int s, int t, int c){pnt[++tot] = t, nxt[tot] = fst[s], cst[tot] = c, fst[s] = tot;}
void update(int &a, int b){if (a < b) a = b;}
int max(int a, int b){return a > b ? a : b;}

struct Splaynode
{
    Splaynode *chi[2], *p;
    int k, m;
    inline void sc(Splaynode *k, int d){chi[d] = k, k->p = this;}
    inline bool dir(){return this == p->chi[1];}
    inline void update(){m = max(k, max(chi[0]->m, chi[1]->m));}
}*pe[nmax + 18], *ep[nmax + 18], *null;

inline void rotate(Splaynode *t)
{
    Splaynode *p = t->p;
    bool d = !t->dir();
    if (p->p != null && (p->p->chi[0] == p || p->p->chi[1] == p)) p->p->sc(t, p->dir());else t->p = p->p;
    p->sc(t->chi[d], !d);
    t->sc(p, d);
    p->update();
}

inline void splay(Splaynode *t)
{
    while (t->p != null && (t->p->chi[0] == t || t->p->chi[1] == t))
	if (t->p->p == null || (t->p->p->chi[0] != t->p && t->p->p->chi[1] != t->p)) rotate(t);
	else
	    t->dir() == t->p->dir() ? (rotate(t->p), rotate(t)) : (rotate(t), rotate(t));
    t->update();
}

inline Splaynode *access(Splaynode *a)
{
    Splaynode *b;
    for (b = null; a != null; a = a->p)
	splay(a), a->chi[1] = b, (b = a)->update();
    return b;
}

inline void bfs()
{
    memset(ed, 0, sizeof(ed));
    pe[1]->chi[0] = pe[1]->chi[1] = pe[1]->p = null, pe[1]->k = pe[1]->m = -oo;
    ed[1] = q[qh = qt = 1] = 1;
    for (int i; qh <= qt; ++qh)
	for (i = fst[q[qh]]; i; i = nxt[i])
	    if (!ed[pnt[i]])
	    {
		ed[pnt[i]] = 1;
		pe[pnt[i]]->chi[0] = pe[pnt[i]]->chi[1] = null;
		pe[pnt[i]]->k = pe[pnt[i]]->m = cst[i];pe[pnt[i]]->p = pe[q[qh]];
                ep[i >> 1] = pe[pnt[i]], q[++qt] = pnt[i];
            }
}

int main()
{
    freopen("qtree.in", "r", stdin);
    freopen("qtree.out", "w", stdout);
    null = new Splaynode;
    null->m = null->k = -oo;
    for (int i = 1; i <= nmax; ++i) pe[i] = new Splaynode;
    scanf("%d", &t);
    while (t--)
    {
        memset(fst, 0, sizeof(fst));
        scanf("%d", &n);tot = 1;
        for (int i = 1, ss, tt, cc; i < n; ++i)
	    scanf("%d%d%d", &ss, &tt, &cc), add(ss, tt, cc), add(tt, ss, cc);
        for (bfs(); ;)
        {
	    scanf("%s", com);
	    if (com[0] == 'D') break;
	    if (com[0] == 'C')
	    {
                scanf("%d%d", &k, &l);
	        splay(ep[k]);
	        ep[k]->k = l;
	        ep[k]->update();
            }
	    else
	    {
	        scanf("%d%d", &l, &r);
	        Splaynode *a = pe[l], *b = pe[r], *c;
	        if (a == b) {printf("0\n");continue;}
	        access(a);
	        c = access(b);
	        ans = 1 << 31;
	        update(ans, c->chi[1]->m);
	        if (a != c) splay(a), update(ans, a->m);
	        printf("%d\n", ans);
            }
        }
    }
    return 0;
}

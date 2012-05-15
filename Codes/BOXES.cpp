#include <stdio.h>
#include <memory.h>
const int nmax = 1000, oo = ~0U >> 1;

int n, T, s, t, tot, cf;
int fst[nmax + 18], d[nmax + 18], pre[nmax + 18], q[nmax + 18];
bool ed[nmax + 18];

struct typedge
{
    int pnt, nxt, cty, cst;
}e[(nmax * 8) + 18];

void addedge (int s, int t, int ct, int cs)
{
    e[++tot].pnt = t;
    e[tot].nxt = fst[s];
    e[tot].cty = ct;
    e[tot].cst = cs;
    fst[s] = tot;

    e[++tot].pnt = s;
    e[tot].nxt = fst[t];
    e[tot].cty = 0;
    e[tot].cst = -cs;
    fst[t] = tot;
}

bool spfa ()
{
    memset (d, 0x3F, sizeof (d));
    int tt = d[0];
    memset (q, 0, sizeof (q));
    memset (ed, 0, sizeof (ed));
    d[s] = 0;
    int now = s, nxt = s, dt;
    for (int i, pos, p; now; now = q[pos], q[pos] = 0)
	for (ed[pos = now] = false,  i = fst[pos], p = e[i].pnt; i; i = e[i].nxt, p = e[i].pnt)
	    if (e[i].cty && (dt = d[pos] + e[i].cst) < d[p])
	    {
		d[p] = dt;
		pre[p] = i;
		if (!ed[p])
		{
		    q[nxt] = p;
		    ed[p] = true;
		    nxt = p;
		}
	    }
    return d[t] != tt;
}

void aug ()
{
    int del = oo;
    for (int i = t; i != s; i = e[pre[i] ^ 1].pnt)
	if (e[pre[i]].cty < del) del = e[pre[i]].cty;
    for (int i = t; i != s; i = e[pre[i] ^ 1].pnt)
    {
	e[pre[i]].cty -= del;
	e[pre[i] ^ 1].cty += del;
	cf += e[pre[i]].cst * del;
    }
}

int main ()
{
    freopen ("Boxes.in", "r", stdin);
    freopen ("Boxes.out", "w", stdout);
    scanf ("%d", &T);
    while (T--)
    {

    memset (fst, 0, sizeof (fst));
	tot = 1, cf = 0;
	scanf ("%d", &n);
	s = n + 1, t = s + 1;
	for (int i = 1, c; i <= n; ++i)
	{
	    scanf ("%d", &c);
	    if (i > 1) addedge (i, i - 1, oo, 1); else addedge (i, n, oo, 1);
	    if (i < n) addedge (i, i + 1, oo, 1); else addedge (i, 1, oo, 1);
	    addedge (s, i, c, 0);
	    addedge (i, t, 1, 0);
	}
	while (spfa ()) aug ();
	printf ("%d\n", cf);
    }
    return 0;
}


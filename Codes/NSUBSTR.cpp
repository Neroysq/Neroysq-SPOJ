/*
  Suffix_Automaton
  O(n)
*/
#include <stdio.h>
#include <string.h>
const int nmax = 250000, cmax = 26;

struct sanode {
    sanode *f, *ch[cmax + 8];
    int ml;
}pool[nmax*2 + 18], *init, *tail;

int n, k, F[nmax + 18], c[nmax*2 + 18], tot, q[nmax*2 + 18], v[nmax + 18];
char str[nmax + 18];

void update(int &a, int b)
{
    if (a < b) a = b;
}

void add(int c, int len)
{
    sanode *p = tail, *np = &pool[++tot];
    np->ml = len;
    for (; p && !p->ch[c]; p = p->f) p->ch[c] = np;
    tail = np;
    if (!p) np->f = init;
    else
	if (p->ch[c]->ml == p->ml + 1) np->f = p->ch[c];
	else {
	    sanode *q = p->ch[c], *r = &pool[++tot];
	    *r = *q;
	    r->ml = p->ml + 1;
	    q->f = np->f = r;
	    for (; p && p->ch[c] == q; p = p->f) p->ch[c] = r;
	}
}

int main()
{
    freopen("NSUBSTR.in", "r", stdin);
    freopen("NSUBSTR.out", "w", stdout);
    scanf("%s", str + 1);
    n = strlen(str + 1);
    init = tail = &pool[tot = 1];
    for (int i = 1; i <= n; ++i)
	add(str[i] - 'a', i);
    sanode *a = init;
    for (int i = 1; i <= tot; ++i) ++v[pool[i].ml];
    for (int i = 1; i <= n; ++i) v[i] += v[i - 1];
    for (int i = 1; i <= tot; ++i) q[v[pool[i].ml]--] = i;
    for (int i = 1; i <= n; ++i)
	++c[(a = a->ch[str[i] - 'a']) - pool];
    for (int i = tot; i; --i) {
	update(F[pool[q[i]].ml], c[q[i]]);
	if (pool[q[i]].f) c[pool[q[i]].f - pool] += c[q[i]];
    }
    for (int i = n; i > 1; --i) update(F[i - 1], F[i]);
    for (int i = 1; i <= n; ++i) printf("%d\n", F[i]);
    return 0;
}

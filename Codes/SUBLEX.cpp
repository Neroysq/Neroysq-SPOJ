/*
  Suffix_Automaton
  O(n)
*/
#include <stdio.h>
#include <string.h>
const int nmax = 90000, cmax = 26, SZE = sizeof(int) * cmax;

struct sanode {
    sanode *f, *ch[cmax];
    int l, k;
}pool[nmax*2 + 18], *init, *tail;

int n, m, q[nmax*2 + 18], qh, qt, v[nmax + 18], p[nmax*2 + 18], tot;
int pt, hash[nmax*2 + 18][cmax+2];
char a[nmax + 18], ch[nmax*2 + 18][cmax+2];

inline void addhash(int a, int j, int k)
{
    pool[a].k += pool[a].ch[j]->k;
    hash[a][k] = pool[a].ch[j] - pool;
    ch[a][k] = j + 'a';
}

void add(int c)
{
    sanode *q = pool + (++tot), *p = tail;
    q->l = p->l + 1, q->k = 1;
    for (; p && !p->ch[c]; p = p->f) p->ch[c] = q;
    tail = q;
    if (!p) q->f = init;
    else
	if (p->ch[c]->l == p->l + 1) q->f = p->ch[c];
	else {
	    sanode *u = p->ch[c], *r = pool + (++tot);
	    memcpy(r->ch, u->ch, SZE), r->k = 1, r->f = u->f;
	    r->l = p->l + 1;
	    q->f = u->f = r;
	    for (; p && p->ch[c] == u; p = p->f) p->ch[c] = r;
	}
}

void solve(int k, int A)
{
    pt = 0;
    while (k) 
	for (int i = 0, tmp; hash[A][i]; ++i)
	    if (k > pool[tmp = hash[A][i]].k)
		k -= pool[tmp].k;
	    else {
		a[++pt] = ch[A][i], A = tmp, --k;
		break;
	    }
    a[pt + 1] = '\0';
    puts(a + 1);
}

int main()
{
    freopen("SUBLEX.in", "r", stdin);
    freopen("SUBLEX.out", "w", stdout);
    scanf("%s", a + 1);
    n = strlen(a + 1);
    init = tail = pool + (++tot);
    init->k = 1, init->l = 0;
    for (int i = 1; i <= n; ++i) add(a[i] - 'a');
    for (int i = 1; i <= tot; ++i) ++v[pool[i].l];
    for (int i = 1; i <= n; ++i) v[i] += v[i - 1];
    for (int i = 1; i <= tot; ++i) p[v[pool[i].l]--] = i;
    for (int i = tot, j, now; i; --i) {
	for (now = j = 0; j < cmax; ++j)
	    if (pool[p[i]].ch[j]) 
		addhash(p[i], j, now++);
	hash[p[i]][now] = 0;
    }
    scanf("%d", &m);
    for (int k; m--; ) 
	scanf("%d", &k), solve(k, init - pool);
    return 0;
}

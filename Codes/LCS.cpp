/*
  Suffix_Automaton
  O(n)
*/
#include <stdio.h>
#include <string.h>
const int nmax = 250000, cmax = 26;

struct sanode {
    sanode *f, *ch[cmax];
    int l;
}pool[nmax*2 + 18], *init = pool, *tail = init;

int n, tot, ans;
char str[nmax + 18];

void add(int c)
{
    sanode *q = pool + (++tot), *p = tail;
    q->l = p->l + 1;
    for (; p && !p->ch[c]; p = p->f) p->ch[c] = q;
    tail = q;
    if (!p) q->f = init;
    else
	if (p->ch[c]->l == p->l + 1) q->f = p->ch[c];
	else {
	    sanode *r = pool + (++tot), *u = p ->ch[c];
	    *r = *u;
	    r->l = p->l + 1;
	    u->f = q->f = r;
	    for (; p && p->ch[c] == u; p = p->f) p->ch[c] = r;
	}
}

int main()
{
    freopen("LCS.in", "r", stdin);
    freopen("LCS.out", "w", stdout);
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n; ++i) add(str[i] - 'a');
    sanode *a = init;
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1, nl = 0; i <= n; ans < nl ? ans = nl : 0, ++i)
	if (a->ch[str[i] -= 'a'])
	    a = a->ch[str[i]], ++nl;
	else {
	    while (a && !a->ch[str[i]]) a = a->f;
	    a ? nl = a->l + 1, a = a->ch[str[i]], 0 : (a = init, nl = 0);
	}
    printf("%d", ans);
    return 0;
}

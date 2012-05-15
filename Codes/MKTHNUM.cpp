#include <stdio.h>
#include <stdlib.h>
const int nmax = 100000;

struct tps 
{
    tps *l, *r;
    int s;
}*st[nmax + 18], TMP, *null = &TMP;
int n, m, idt;
int a[nmax + 18], ind[nmax + 18], p[nmax + 18], fp[nmax + 18];

int cmpor(const void *i, const void *j)
{
    return a[*(int *)i] - a[*(int *)j];
}

tps *newp(tps *b)
{
    tps *a = new tps;
    return *a = *b, a;
}

tps *build(int l, int r)
{
    tps *A = newp(null);
    if (l == r) return A;
    else {
	int mid = (l + r) >> 1;
	if (l <= mid) A->l = build(l, mid);
	if (r > mid) A->r = build(mid + 1, r);
    }
    return A;
}

void add(tps *&a, int l, int r, int x)
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

int ask(tps *L, tps *R, int l, int r, int k)
{
    while (l < r)
	if (R->l->s - L->l->s < k)
	    k -= R->l->s - L->l->s, l = ((l + r) >> 1) + 1, R = R->r, L = L->r;
	else
	    r = (l + r) >> 1, L = L->l, R = R->l;
    return fp[l];
}

int main()
{
    freopen("MKTHNUM.in", "r", stdin);
    freopen("MKTHNUM.out", "w", stdout);
    null->l = null->r = null;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), p[i] = i;
    qsort(p + 1, n, sizeof(p[0]), cmpor);
    for (int i = 1, last = a[p[i]] - 1; i <= n; ++i)
	if (last != a[p[i]])
	    fp[ind[p[i]] = ++idt] = last = a[p[i]];
	else
	    ind[p[i]] = idt;
    st[0] = build(1, n);
    for (int i = 1; i <= n; ++i)
	add(st[i] = st[i - 1], 1, idt, ind[i]);
    for (int l, r, x; m--; )
	scanf("%d%d%d", &l, &r, &x), printf("%d\n", ask(st[l - 1], st[r], 1, idt, x));
    return 0;
}

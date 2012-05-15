#include <stdio.h>
#include <stdlib.h>
const int nmax = 100000, tmax = 18;

int A[tmax + 2][nmax + 18], p[nmax + 18], f[tmax + 2][nmax + 18], n, m, H;

int cmpor(const void *i, const void *j) {return *(int *)i - *(int *)j;}
void build(int l, int r, int *a, int *b, int h)
{
    int lp = l - 1, rp = ((l + r + 1) >> 1) - 1, mp = rp + 1, mid = p[mp], mn = 0;
    for (int i = l; i <= r; ++i) if (a[i] >= mid) ++mn;
    for (int i = l; i <= r; ++i)
	if (a[i] < mid)
	    b[++lp] = a[i], f[h][i] = f[h][i - 1] + 1;
	else
	    if (a[i] == mid && rp + mn > r)
		b[++lp] = a[i], f[h][i] = f[h][i - 1] + 1, --mn;
	    else
		b[++rp] = a[i], f[h][i] = f[h][i - 1], --mn;
    if (h < H) build(l, mp - 1, b, A[h + 1], h + 1), build(mp, r, b, A[h + 1], h + 1);
}

int getkth(int l, int r, int k)
{
    int h = 1;
    for (int nl = 1, nr = n, tmp; l < r; ++h)
	if ((tmp = f[h][r] - f[h][l - 1]) >= k)
	    l = f[h][l - 1] - f[h][nl - 1] + nl, r = l + tmp - 1, nr = ((nl + nr + 1) >> 1) - 1;
	else
	{
	    k -= tmp, r -= l + tmp;
	    l = (l - nl - f[h][l - 1] + f[h][nl - 1]) + (tmp = (nl + nr + 1) >> 1), r += l, nl = tmp;
	}
    return A[h - 1][l];
}

int main()
{
    freopen("MKTHNUM.in", "r", stdin);
    freopen("MKTHNUM.out", "w", stdout);
    scanf("%d%d", &n, &m);
    while (n > (1 << H)) ++H;++H;
    for (int i = 1; i <= n; ++i) scanf("%d", A[0] + i), p[i] = A[0][i];
    qsort(p + 1, n, sizeof(p[0]), cmpor);
    build(1, n, A[0], A[1], 1);
    for (int l, r, k; m--;)
	scanf("%d%d%d", &l, &r, &k), printf("%d\n", getkth(l, r, k));
    return 0;
}

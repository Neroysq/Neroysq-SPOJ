/*
    Maintain two stacks that the height is monotonically decreasing to find the position i's widest rectangle whose height is a[i]
    */
#include <stdio.h>
#define update(i,j) {long long tmp = (j);i < tmp ? i = tmp : 0;}
const int nmax = 100000;

int l[nmax + 18], r[nmax + 18], a[nmax + 18], q[nmax + 18], qt, yn;
long long ans;

int main()
{
    freopen("HISTOGRA.in", "r", stdin);
    freopen("HISTOGRA.out", "w", stdout);
    a[0] = -1;
    while (scanf("%d", &n), n)
    {
	ans = q[qt = 1] = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i)
	{
	    while (a[q[qt]] >= a[i]) --qt;
	    l[i] = i - q[qt], q[++qt] = i;
	}
	a[q[qt = 1] = n + 1] = -1;
	for (int i = n; i; --i)
	{
	    while (a[q[qt]] >= a[i]) --qt;
	    r[i] = q[qt] - i, q[++qt] = i;
	}
	for (int i = 1; i <= n; ++i)
	    update(ans, (l[i] + r[i] - 1) *1LL* a[i]);
	printf("%lld\n", ans);
    }
    return 0;
}

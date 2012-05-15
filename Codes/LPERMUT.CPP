#include <stdio.h>
const int nmax = 100000;

int q[nmax + 18], qh, qt, ans, pnt;
bool ed[nmax + 18];
int a[nmax + 18], n;

void update(int &a, int b)
{
    if (a < b) a = b;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    scanf("%d", &n);
    qh = pnt = 1;
    for (int i = 1, tmp; i <= n; ++i)
    {
	scanf("%d", &tmp);
	a[i] = tmp;
	if (ed[tmp])
	{
	    while (pnt <= i && ed[tmp]) ed[a[pnt++]] = false;
	    while (q[qh] < pnt && qh <= qt) ++qh;
	}
	if (a[q[qh]] == i - pnt) update(ans, i - pnt);
	while (qh <= qt && a[q[qt]] < tmp) --qt;
	q[++qt] = i;
	if (a[q[qh]] == i - pnt + 1) update(ans, i - pnt + 1);
	ed[tmp] = true;
    }
    printf("%d", ans);
    return 0;
}

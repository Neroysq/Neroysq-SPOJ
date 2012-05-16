#include <stdio.h>
const int nmax = 200;

int t, n, m, sc[nmax + 18][nmax + 18], sr[nmax + 18][nmax + 18];
int a[nmax + 18][nmax + 18], ans, w;
int u[nmax + 18], v[nmax + 18];

void update(int a, int k)
{
    if (a > ans) ans = a, w = k;
    else
	if (a == ans) w += k;
}

int main()
{
    freopen("MATRIX.in", "r", stdin);
    freopen("MATRIX.out", "w", stdout);
    scanf("%d", &t);u[0] = 1 << 31;
    while (t--)
    {
	scanf("%d%d", &n, &m);
	ans = -n * m;
	for (int i = 1; i <= n; ++i)
	    for (int j = 1; j <= m; ++j) 
		scanf("%d", a[i] + j), update(a[i][j] ? a[i][j] : --a[i][j], 1);
	for (int i = 1; i <= n; ++i)
	    for (int j = 1; j <= m; ++j)
		sc[i][j] = sc[i][j - 1] + a[i][j], sr[i][j] = sr[i - 1][j] + a[i][j];
	for (int j = 1; j <= n; ++j)
	    for (int i = j + 1; i <= n; ++i)
	    {
		for (int k = 1; k <= m; update(sr[i][k] - sr[j - 1][k++], 1)) 
		    u[k] = sr[i - 1][k] - sr[j][k] - sc[i][k - 1] - sc[j][k - 1],v[k] = sc[i][k] + sc[j][k] + sr[i - 1][k] - sr[j][k];
		for (int k = 0, l = 2, s = 1; l <= m; update(u[k] + v[l++], s))
		    if (u[l - 1] > u[k]) k = l - 1, s = 1;
		    else if (u[l - 1] == u[k]) ++s;
	    }
	for (int i = 1; i <= m; ++i)
	    for (int j = i + 1; j <= m; ++j)
		for (int k = 1; k <= n; ++k)
		    update(sc[k][j] - sc[k][i - 1], 1);
	printf("%d %d\n", ans, w);
    }
    return 0;
}

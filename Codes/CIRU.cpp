/*
  com_geo 
  O(n^2*logn)
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef double db;
const int nmax = 1000;
const db PI = 3.1415926535897, BP = PI * 2;

int x[nmax + 18], y[nmax + 18], r[nmax + 18], rr[nmax + 18];
bool ed[nmax + 18];
int n, p[nmax*4 + 18], qt, q[nmax*4 + 18], tmp;
db ans, alp[nmax*4 + 18];

inline db sqr(int x) {return (db)x * x;}
inline int eps(db x) {return x < 1e-8 ? -1 : x > 1e-8;}
inline int cmpor(const void *i, const void *j) {return r[*(int *)i] - r[*(int *)j];}
inline int cmpor2(const void *i, const void *j)
{
    return (tmp = eps(alp[*(int *)i] - alp[*(int *)j])) ? tmp : q[*(int *)j] - q[*(int *)i];
}

inline void inter(int a, int b, db &a0, db &a1)
{
    db dx = x[b] - x[a], dy = y[b] - y[a], d = dx*dx + dy*dy, da = acos((d + rr[a] - rr[b]) * 0.5 / (sqrt(d) * r[a]));
    db ba = atan2(dy, dx);
    a0 = ba - da, a1 = ba + da;
    if (a0 < 0) a0 += BP;
    if (a1 < 0) a1 += BP;
}

inline db calcarea(int a, db a0, db a1)
{
    db da = a1 - a0;
    db x0 = x[a] + r[a] * cos(a0), y0 = y[a] + r[a] * sin(a0);
    db x1 = x[a] + r[a] * cos(a1), y1 = y[a] + r[a] * sin(a1);
    return ((da - sin(da)) * rr[a] + (x0 * y1 - x1 * y0));
}

db calc(int X)
{
    db rnt = 0;
    qt = 0;
    for (int i = 1; i <= n; ++i)
	if (i != X && eps(sqrt(sqr(x[X] - x[i]) + sqr(y[X] - y[i])) - r[X] - r[i]) < 0) {
	    inter(X, i, alp[qt + 1], alp[qt + 2]);
	    q[++qt] = 1, p[qt] = qt;
	    q[++qt] =-1, p[qt] = qt;
	    if (eps(alp[qt - 1] - alp[qt]) > 0)
		q[++qt] = 1, p[qt] = qt, alp[qt] = 0, q[++qt] = -1, p[qt] = qt, alp[qt] = BP;
	}
    if (!qt) return BP * r[X] * r[X];
    qsort(p + 1, qt, sizeof(p[0]), cmpor2);
    rnt += calcarea(X, 0, alp[p[1]]) + calcarea(X, alp[p[qt]], BP);
    for (int i = 1, now = 0; i < qt; ++i)
	if (!(now += q[p[i]]))
	    rnt += calcarea(X, alp[p[i]], alp[p[i + 1]]);
    return rnt;
}

int main()
{
    freopen("CIRU.in", "r", stdin);
    freopen("CIRU.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
	scanf("%d%d%d", x + i, y + i, r + i), p[i] = i;
    qsort(p + 1, n, sizeof(p[0]), cmpor);
    for (int i = 1; i <= n; ++i)
	if (!r[p[i]])
	    ed[p[i]] = 1;
	else
	    for (int j = i + 1; j <= n; ++j)
		if (eps(sqrt(sqr(x[p[i]] - x[p[j]]) + sqr(y[p[i]] - y[p[j]])) + r[p[i]] - r[p[j]]) <= 0) {ed[p[i]] = 1;break;}
    for (int i = 1; i <= n; ++i)
	if (!ed[i]) x[++qt] = x[i], y[qt] = y[i], r[qt] = r[i], rr[qt] = r[i]*r[i];
    n = qt;
    for (int i = 1; i <= n; ++i) ans += calc(i);
    printf("%.3f", ans*0.5);
    return 0;
}

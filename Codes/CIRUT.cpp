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

int x[nmax + 18], y[nmax + 18], r[nmax + 18], tot;
int n, p[nmax*4 + 18], q[nmax*4 + 18], qt, ttmp;
db ans[nmax + 18], alp[nmax*4 + 18];

int eps(db x)
{
    return x < -1e-8 ? -1 : x > 1e-8;
}

int cmpor(const void *i, const void *j)
{
    return (ttmp = eps(alp[*(int *)i] - alp[*(int *)j])) ? ttmp : q[*(int *)j] - q[*(int *)i];
}

int judge(db d, int r0, int r1)
{
    if (eps(d - r0 - r1) >= 0) return -1;
    if (eps(d + r1 - r0) <= 0) return 0;
    if (eps(d + r0 - r1) <= 0) return 1;
    return 2;
}

void inter(int a, int b, int dx, int dy, db d, db &a0, db &a1)
{
    db da = acos((r[a]*r[a] + d*d - r[b]*r[b]) *0.5 / (r[a]*d));
    db ba = atan2(dy, dx);
    a0 = ba - da, a1 = ba + da;
    if (a0 < 0) a0 += BP;
    if (a1 < 0) a1 += BP;
}

db calcarea(int a, db a0, db a1)
{
    db da = a1 - a0;
    if (!eps(da)) return 0;
    db x0 = x[a] + r[a] * cos(a0), y0 = y[a] + r[a] * sin(a0);
    db x1 = x[a] + r[a] * cos(a1), y1 = y[a] + r[a] * sin(a1);
    return r[a] * r[a] * (da - sin(da)) + (x0 * y1 - x1 * y0);
}

void calc(int X)
{
    int covered = 1, dx, dy;
    db d;
    qt = 0;
    for (int i = 1, tmp; i <= n; ++i)
	if (X != i && (dx = x[i] - x[X], dy = y[i] - y[X], tmp = judge(d = sqrt(dx*dx + dy*dy), r[X], r[i])) > 0) 
	    if (tmp == 1)
		++covered;
	    else {
		inter(X, i, dx, dy, d, alp[qt + 1], alp[qt + 2]);
		q[++qt] = 1, p[qt] = qt;
		q[++qt] =-1, p[qt] = qt;
		if (eps(alp[qt - 1] - alp[qt]) > 0) {
		    alp[++qt] = 0, q[qt] = 1, p[qt] = qt;
		    alp[++qt] =BP, q[qt] =-1, p[qt] = qt;
		}
	    }
    if (!qt) {ans[covered] += r[X] * r[X] * BP; return;}
    qsort(p + 1, qt, sizeof(p[0]), cmpor);
    ans[covered] += calcarea(X, 0, alp[p[1]]) + calcarea(X, alp[p[qt]], BP);
    for (int i = 1; i < qt; ++i) 
	covered += q[p[i]], ans[covered] += calcarea(X, alp[p[i]], alp[p[i + 1]]);
}

int main()
{
    freopen("CIRUT.in", "r", stdin);
    freopen("CIRUT.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1, xx, yy, rr; i <= n; ++i)
	if (scanf("%d%d%d", &xx, &yy, &rr), rr)
	    x[++tot] = xx, y[tot] = yy, r[tot] = rr;
    n = tot;
    for (int i = 1; i <= n; ++i) calc(i);
    for (int i = 1; i <= n; ++i) ans[i] -= ans[i + 1];
    for (int i = 1; i <= n; ++i) printf("[%d] = %.3f\n", i, ans[i] * 0.5);
    return 0; 
}

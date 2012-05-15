#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef double db;
const int nmax = 50;

int n, x[nmax + 18], y[nmax + 18], r[nmax + 18], ml, mr;
int rr[nmax + 18], qt, p[nmax*2 + 18], q[nmax*2 + 18], tmp, P[nmax + 18];
db ans, Y[nmax*2 + 18];
bool ed[nmax + 18];

inline db sqr(int a)
{
    return a * a;
}

inline int eps(db x)
{
    return (x < -1e-8) ? -1 : (x > 1e-8);
}

inline int cmpor(const void *i, const void *j)
{
    return (tmp = eps(Y[*(int *)i] - Y[*(int *)j])) ? tmp : q[*(int *)j] - q[*(int *)i];
}

inline int cmpor3(const void *i, const void *j)
{
    return r[*(int *)i] - r[*(int *)j];
}

inline int cmpor2(const void *i, const void *j)
{
    return x[*(int *)i] - x[*(int *)j] - r[*(int *)i] + r[*(int *)j];
}

inline db f(db X)
{
    db d = 0, rnt = 0, l;
    qt = 0;
    for (int i = 1; i <= n; ++i)
	if ((d = fabs(X - x[i])) < r[i]) {
	    q[++qt] = -1, p[qt] = qt, Y[qt] = y[i] + (d = sqrt(rr[i] - d*d));
	    q[++qt] =  1, p[qt] = qt, Y[qt] = y[i] - d;
	}
    qsort(p + 1, qt, sizeof(p[0]), cmpor);
    for (int i = 1, now = 0, ed = 0; i <= qt; ++i) 
	if (!(now += q[p[i]]))
	    rnt += Y[p[i]] - l, ed = 0;
	else
	    if (!ed) l = Y[p[i]], ed = 1;
    return rnt;
}

inline db s(db fl, db fm, db fr, db l, db r)
{
    return (fl + fr + 4 * fm) * (r - l);
}

inline db S(db l, db m, db r, db Ss, db fl, db fm, db fr)
{
    db lm = (l + m) *0.5, rm = (m + r) *0.5, flm = f(lm), frm = f(rm);
    db Sl = s(fl, flm, fm, l, m), Sr = s(fm, frm, fr, m, r);
    return !eps(Ss - Sl - Sr) ? Ss : S(l, lm, m, Sl, fl, flm, fm) + S(m, rm, r, Sr, fm, frm, fr);
}

int main()
{
    freopen("VCIRCLES.in", "r", stdin);
    freopen("VCIRCLES.out", "w", stdout);
    scanf("%d", &n);
    for (int i= 1; i <= n; ++i) 
	scanf("%d%d%d", x + i, y + i, r + i), P[i] = i;
    qsort(P + 1, n, sizeof(P[0]), cmpor3);
    for (int i = 1; i <= n; ++i) {
	if (!r[P[i]]) {ed[P[i]] = 1; break;}
	for (int j = i + 1; j <= n; ++j)
	    if (eps(sqrt(sqr(x[P[i]] - x[P[j]]) + sqr(y[P[j]] - y[P[i]])) + r[P[i]] - r[P[j]]) <= 0) {ed[P[i]] = 1;break;}
    }
    int tot = 0;
    for (int i = 1; i <= n; ++i)
	if (!ed[i]) x[++tot] = x[i], y[tot] = y[i], r[tot] = r[i], rr[tot] = r[tot] * r[tot], P[tot] = tot;
    n = tot;
    qsort(P + 1, n, sizeof(P[0]), cmpor2);
    ml = -10010, mr = -10010;
    for (int i = 1; i <= n; ++i) 
	if (eps(mr - x[P[i]] + r[P[i]]) <= 0) {
	    db fl = f(ml), fr = f(mr), fm = f((ml + mr) *0.5);
	    ans += S(ml, (ml + mr) *0.5, mr, s(fl, fm, fr, ml, mr), fl, fm, fr);
	    ml = x[P[i]] - r[P[i]], mr = x[P[i]] + r[P[i]];
	}
	else
	    if (eps(mr - x[P[i]] - r[P[i]]) < 0) mr = x[P[i]] + r[P[i]];
    db fl = f(ml), fr = f(mr), fm = f((ml + mr) *0.5);
    ans += S(ml, (ml + mr) *0.5, mr, s(fl, fm, fr, ml, mr), fl, fm, fr);
    printf("%.5f", ans/6);
    return 0;
}

#include <stdio.h>
const int tmax = 1 << 19, nmax = 10000, mmax = nmax * 2;

int segc[tmax + 18], l[nmax + 18], M[nmax + 18], S[nmax + 18], Fot, st, tot = 1;
int fst[nmax + 18], nxt[mmax + 18], pnt[mmax + 18], p[nmax + 18];
int n, m, color[nmax + 18], q[nmax + 18], qh, qt, s[nmax + 18];
int f[nmax + 18], fa[nmax + 18], F[nmax + 18], k, c, d[nmax + 18];
bool ed[nmax + 18];

inline void add(int s, int t){pnt[++tot] = t, nxt[tot] = fst[s], fst[s] = tot;}
inline int spmax(int a, int b){return color[a] == color[b] ? (d[a] > d[b] ? b : a) : ( color[a] ? a : b);}
inline void update(int &a, int b)
{
    if (!b || b == -1 || !color[b]) return;
    if (a == -1 || !a || !color[a] || d[a] > d[b]) a = b;
}

inline void bfs()
{
    for (d[1] = ed[q[qh = qt = 1] = 1] = 1; qh <= qt; ++qh)
	for (int i = fst[q[qh]]; i; i = nxt[i])
	    if (!ed[pnt[i]])
		ed[q[++qt] = pnt[i]] = 1, fa[pnt[i]] = q[qh], d[pnt[i]] = d[q[qh]] + 1;
    for (int i, m, mp; qt; --qt)
    {
	for (i = fst[q[qt]], m = 0; i; i = nxt[i])
	    if (s[pnt[i]] > m) m = s[mp = pnt[i]];
	if (m) p[q[qt]] = ++S[F[q[qt]] = (F[pnt[i]] ? F[pnt[i]] : (S[pnt[i]] = 1, F[pnt[i]] = ++Fot))];
    }
    for (int i = 1; i <= Fot; l[i] = st, st += M[i++] << 1)
	for (M[i] = 1; M[i] <= S[i]; M[i] <<= 1);
    for (int i = 1; i <= n; ++i)
	if (F[i])
	{
	    segc[l[F[i]] + M[F[i]] + (S[F[i]] - p[i] + 1)] = i;
	    if ((p[i] = S[F[i]] - p[i] + 1) == 1) f[F[i]] = i;
	    p[i] += M[F[i]];
	}
    for (int i = 1; i <= Fot; ++i)
	for (int j = M[i] - 1; j; --j)
	    segc[l[F[i]] + j] = spmax(segc[l[F[i]] + (j << 1)], segc[l[F[i]] + (j << 1 | 1)]);
}

int getnear(int *a, int l, int r)
{
    int ans = -1;
    for (--l, ++r; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1) update(ans, segc[l ^ 1]);
	if ( r & 1) update(ans, segc[r ^ 1]);
    }
    return ans;
}

inline void change(int *a, int k)
{
    for (color[k] = !color[k], k = p[k] >> 1; k; k >>= 1) segc[k] = spmax(segc[k << 1], segc[k << 1 | 1]);
}

inline int getpos(int k)
{
    int ans = -1, tmp;
    while (k)
	if (F[k])
	    (ans = (tmp = getnear(segc + l[F[k]], p[f[F[k]]], p[k])) != -1 ? tmp : ans), k = fa[f[F[k]]];
	else
	    (ans = color[k] ? k : ans), k = fa[k];
    return ans;
}

int main()
{
    freopen("QTREE3.in", "r", stdin);
    freopen("QTREE3.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1, ss, tt; i < n; ++i)
	scanf("%d%d", &ss, &tt), add(ss, tt), add(tt, ss);
    for (bfs(); m--;)
	if (scanf("%d%d", &c, &k), c)
	    printf("%d\n", getpos(k));
	else
	    if (F[k]) change(segc + l[F[k]], k); else color[k] = !color[k];
    return 0;
}


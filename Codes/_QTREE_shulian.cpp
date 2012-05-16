#include <stdio.h>
#include <string.h>
const int nmax = 10000, tmax = 1 << 15, emax = nmax << 1;

int segm[tmax + 18], l[nmax + 18], st, d[nmax + 18], p[nmax + 18], M[nmax + 18];
int q[nmax + 18], qh, qt, s[nmax + 18], f[nmax + 18], F[nmax + 18], Fot, fa[nmax + 18];
int fst[nmax + 18], nxt[emax + 18], pnt[emax + 18], cst[emax + 18], w[nmax + 18];
int n, t, a, b, pe[emax + 18], ans, S[nmax + 18], tot, ttt;
char str[10];
bool ed[nmax + 18];

inline void update(int &a, int b){if (a < b) a = b;}
inline int max(int a, int b){return a > b ? a : b;}
inline void add(int s, int t, int c){pnt[++tot] = t;nxt[tot] = fst[s];cst[tot] = c;fst[s] = tot;}

void bfs()
{
    memset(ed, 0, sizeof(ed));
    memset(F, 0, sizeof(F));Fot = st = 0;
    memset(S, 0, sizeof(S));
    d[ed[q[qh = qt = 1] = 1] = 1] = 1;
    for (int i;qh <= qt; ++qh)
	for (i = fst[q[qh]]; i; i = nxt[i])
	    if (!ed[pnt[i]]) ed[q[++qt] = pnt[i]] = 1, fa[pnt[i]] = q[qh], d[pnt[i]] = d[q[qh]] + 1, w[pnt[i]] = cst[i], pe[i >> 1] = pnt[i];
    for (int i, m, mp; qt; --qt)
    {
	for (i = fst[q[qt]], s[q[qt]] = 1, m = 0; i; s[q[qt]] += s[pnt[i]], i = nxt[i])
	    if (m < s[pnt[i]]) m = s[pnt[i]], mp = pnt[i];
	if (m) p[q[qt]] = ++S[F[q[qt]] = (F[mp] ? F[mp] : (S[Fot + 1] = p[mp] = 1, F[mp] = ++Fot))];
    }
    for (int i = 1; i <= Fot; l[i] = st, st += M[i++] << 1)
	for (M[i] = 1; M[i] <= S[i]; M[i] <<= 1);
    for (int i = 1; i <= n; ++i)
	if (F[i]) 
	{
	    segm[l[F[i]] + M[F[i]] + (S[F[i]] - p[i] + 1)] = w[i];
	    if (S[F[i]] - p[i] + 1 == 1) f[F[i]] = i;
	    p[i] = M[F[i]] + (S[F[i]] - p[i] + 1);
	}
    for (int i = 1; i <= Fot; ++i)
	for (int j = M[i] - 1; j; --j)
	    segm[l[i] + j] = max(segm[l[i] + (j << 1)], segm[l[i] + (j << 1 | 1)]);
}

inline void change(int *a, int i, int k)
{
    for (a[i] = k, i >>= 1; i; i >>= 1) a[i] = max(a[i << 1], a[i << 1 | 1]);
}

inline int getmax(int *a, int l, int r)
{
    int ans = 1 << 31;
    for (--l, ++r; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1) update(ans, a[l ^ 1]);
	if ( r & 1) update(ans, a[r ^ 1]);
    }
    return ans;
}

inline void work(int a, int c)
{  
    while (d[a] > d[c])
	if (F[a])
	    if (d[f[F[a]]] > d[c]) update(ans, getmax(segm + l[F[a]], p[f[F[a]]], p[a])), a = fa[f[F[a]]];
	    else {update(ans, getmax(segm + l[F[a]], p[c] + 1, p[a]));return;}
	else update(ans, w[a]), a = fa[a];
}

inline int lca(int a, int b)
{
    if (a == b) return a;
    if (!F[a]) a = fa[a];
    if (!F[b]) b = fa[b];
    while (1)
	if (F[a] == F[b]) return d[a] > d[b] ? b : a;
	else
	    d[f[F[a]]] < d[f[F[b]]] ? (b = fa[f[F[b]]]) : (a = fa[f[F[a]]]);	
}

int main()
{
    freopen("QTREE.in", "r", stdin);
    freopen("QTREE.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	scanf("%d", &n);tot = 1;
	memset(fst, 0, sizeof(fst));
	for (int i = 1, ss, tt, cc; i < n; ++i) scanf("%d%d%d", &ss, &tt, &cc), add(ss, tt, cc), add(tt, ss, cc);
	for (bfs(); scanf("%s", str), str[0] != 'D';)
	{
            scanf("%s", str);
	    if (str[0] == 'Q')
	    {
		scanf("%d%d", &a, &b);
		int c = lca(a, b);ans = 1 << 31;
		work(a, c), work(b, c);
		printf("%d\n", a == b ? 0 :ans);
	    }
	    else
		scanf("%d%d", &a, &b), (F[a = pe[a]] ? (change(segm + l[F[a]], p[a], b), 0) : (w[a] = b));
        }
    }
    return 0;
}

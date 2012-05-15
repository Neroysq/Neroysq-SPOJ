/*
    for a query[l,r] we solve the first one and the last one at first ,then the rest is all the complete interval, maintain their maximum by a segment tree
    
    O(qlogn)
*/
#include <stdio.h>
const int nmax = 100000, tmax = 1 << 18;

int seg[tmax + 18], p[nmax + 18], index;
int n, q, l[nmax + 18], r[nmax + 18], M = 1, c[nmax + 18];

inline int max(int a, int b) {return a > b ? a : b;}
inline void update(int &a, int b) {if (a < b) a = b;}

int getmax(int l, int r)
{
    if (l > r) return 0;
    int maxc = 0;
    for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1) update(maxc, seg[l ^ 1]);
	if ( r & 1) update(maxc, seg[r ^ 1]);
    }
    return maxc;
}

int main()
{
    freopen("FREQUENT.in", "r", stdin);
    freopen("FREQUENT.out", "w", stdout);
    while (scanf("%d", &n), n)
    {
	M = 1, index = 0;
	scanf("%d", &q);
	for (int i = 1, last = -nmax - 1, a; i <= n; ++i)
	    if (scanf("%d", &a), a == last)
		++c[p[i] = index];
	    else
		r[index] = i - 1, c[p[i] = ++index] = 1, l[index] = i, last = a;
	r[index] = n;
	while (M <= index) M <<= 1;
	for (int i = 1; i <= index; ++i) seg[M + i] = c[i];
	for (int i = M - 1; i; --i) seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
	for (int nl, nr; q--;)
	{
	    scanf("%d%d", &nl, &nr);
	    printf("%d\n", max(getmax(p[nl] + 1, p[nr] - 1), max((r[p[nl]] >= nr ? nr : r[p[nl]]) - nl + 1, nr - (l[p[nr]] <= nl ? nl : l[p[nr]]) + 1)));
	}
    }
    return 0;
}

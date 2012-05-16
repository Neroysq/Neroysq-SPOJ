#include <stdio.h>
#include <time.h>
const int nmax = 10000000;

int n, a, b, s[nmax + 18];
int prime[1000000 + 18], u[nmax + 18], pt;
bool ed[nmax + 18];

void prepare()
{
    u[1] = 1;
    for (int i = 2; i <= nmax; ++i) {
	if (!ed[i])
	    prime[++pt] = i, u[i] = -1;
	for (int j = 1, tmp; j <= pt; ++j) {
	    if ((tmp = prime[j] * i) > nmax) break;
	    ed[tmp] = 1;
	    if (!(i % prime[j])) {
		u[tmp] = 0;
		break;
	    }
	    else u[tmp] = -u[i];
	}
    }
    for (int i = 1; i <= nmax; ++i) s[i] = s[i - 1] + u[i];
    prime[++pt] = nmax + 1;
}

inline long long calc(int l, int r)
{
    long long rnt = 0;
    int p = 1, nl = 1, nr = 1, lc = l, rc = r;
    while (p <= l) 
	if (nl < nr)
	    rnt += (s[nl] - s[p - 1]) *1LL* lc * rc, lc = l / (p = nl + 1), nl = lc ? l / lc : l;
	else
	    rnt += (s[nr] - s[p - 1]) *1LL* lc * rc, rc = r / (p = nr + 1), nr = rc ? r / rc : r;
    return rnt;
}

long long ans;
int main()
{
    freopen("PGCD.in", "r", stdin);
    freopen("PGCD.out", "w", stdout);
    prepare();
    scanf("%d", &n);
    while (n--) {
        ans = 0;
	scanf("%d%d", &a, &b);
	if (a < b) pt = a, a = b, b = pt;
	for (int i = 1; prime[i] <= a; ++i) ans += calc(a / prime[i], b / prime[i]);
        printf("%I64d\n", ans);
    }
    printf("%d\n", clock());
    return 0;
}

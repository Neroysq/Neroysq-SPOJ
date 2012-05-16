#include <stdio.h>
const int nmax = 1000000, mo = 1000003, pmax = nmax / 10;

int bi[nmax + 18], pot;
int tiny[nmax + 18], euler[nmax + 18];
int t;
int a, b, g;
long long ans;

void init()
{
    bi[0] = euler[1] = 1;
    for (int i = 1; i <= nmax; ++i) bi[i] = (bi[i - 1] << 1) % mo;
    for (int i = 2; i <= nmax; ++i)
	if (!euler[i])
	    for (int j = i; j <= nmax; j += i)
	    {
		if (!euler[j]) euler[j] = i, tiny[j] = i;
		euler[j] = euler[j] / i * (i - 1);
	    }
}

int calc()
{
    ans = 0;
    g = (a + b) / gcd(a, b);
    get(g);
    
}
    
int main()
{
    freopen("TRANSP2.in", "r", stdin);
    freopen("TRANSP2.out", "w", stdout);
    init();
    scanf("%d", &t);
    while (t--)
	scanf("%d%d", &a, &b), printf("%d\n", calc());
    return 0;
}

    

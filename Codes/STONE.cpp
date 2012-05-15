#include <stdio.h>
const int nmax = 1000000;

int t, n, tmpx, tmpy;
double rntx, rnty, total;
int x0, y0, lx, ly;

int main()
{
    freopen("STONE.in", "r", stdin);
    freopen("STONE.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	rntx = rnty = total = 0;
	scanf("%d", &n);
	scanf("%d%d%d%d", &x0, &y0, &lx, &ly);
//	rntx = x0;
//	rnty = y0;
	for (int i = 3; i <= n; ++i)
	{
	    scanf("%d%d", &tmpx, &tmpy);
	    double tmps = (double)((lx - x0) * (tmpy - y0) - (ly - y0) * (tmpx - x0)) / 2;
	    double mx = (double)(x0 + lx + tmpx) / 3, my = (double)(y0 + ly + tmpy) / 3;
	    rntx += tmps * mx;
	    rnty += tmps * my;
	    total += tmps;
	    lx = tmpx;
	    ly = tmpy;
	}
	printf("%.2lf %.2lf\n", rntx / total, rnty / total);
    }
    return 0;
}

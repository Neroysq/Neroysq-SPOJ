#include <stdio.h>
#include <math.h>

int p, q, r, l, m, n, t;

int main()
{
    freopen("PIR.in", "r", stdin);
    freopen("PIR.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
	scanf("%d%d%d%d%d%d", &p, &q, &r, &l, &m, &n);
	double a1 = p * p, b2 = q * q, c3 = r * r;
	double a2 = b2 + c3 - n * n * 1.0, a3 = a1 + c3 - m * m * 1.0, b3 = a1 + b2 - l * l * 1.0;
	printf("%.4f\n", sqrt(a1 * b2 * c3 - (a1 * a2 * a2 + b2 * a3 * a3 + c3 * b3 * b3) / 4 + a3 * a2 * b3 / 4) / 6);
    }
    return 0;
}

//欧拉四面体公式

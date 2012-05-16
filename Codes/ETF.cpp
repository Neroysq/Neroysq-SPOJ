#include <stdio.h>
const int nmax = 1000000;

int n, phi[nmax + 18], prime[nmax + 18], t, pt;

int main()
{
  freopen("ETF.in", "r", stdin);
  freopen("ETF.out", "w", stdout);
  
  phi[1] = 1;
  for (int i = 2; i <= nmax; ++i) {
    if (!phi[i])
      prime[++pt] = i, phi[i] = i - 1;
    for (int j = 1, k; j <= pt; ++j) {
      if ((k = (prime[j] * i)) > nmax) break;
      if (i % prime[j])
	phi[k] = phi[i] * (prime[j] - 1);
      else {
	phi[k] = phi[i] * prime[j];
	break;
      }
    }
  }
  for (scanf("%d", &t); t--; )
    scanf("%d", &n), printf("%d\n", phi[n]);
  
  return 0;
}

#include <stdio.h>
const int nmax = 500000;

int ans[nmax + 18], t, n;

int main()
{

  freopen("DIVSUM.in", "r", stdin);
  freopen("DIVSUM.out", "w", stdout);

  for (int i = 1; i <= nmax; ++i)
    for (int j = i << 1; j <= nmax; j += i)
      ans[j] += i;

  scanf("%d", &t);
  while (t--) scanf("%d", &n), printf("%d\n", ans[n]);
  return 0;
}

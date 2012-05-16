#include <stdio.h>
#ifdef WIN32
#define oll "%I64d"
#else
#define oll "%lld"
#endif

int n, k, t;

inline long long solve(int n, int k)
{
  if ((k << 1) > n) k = n - k;
  long long ans = 1;
  for (int i = 1; i <= k; ++i, --n) ans *= n, ans /= i;
  return ans;
}

int main()
{

  freopen("MARBLES.in", "r", stdin);
  freopen("MARBLES.out", "w", stdout);
  
  for (scanf("%d", &t); t--; )
    scanf("%d%d", &n, &k), printf(oll "\n", solve(n - 1, k - 1));
  
  return 0;
}

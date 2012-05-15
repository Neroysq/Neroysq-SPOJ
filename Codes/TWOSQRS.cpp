#include <stdio.h>
#include <math.h>
#ifdef WIN32
#define ioll "%I64d"
#else
#define ioll "%lld"
#endif

int t;
long long n, l, r, tmp;

int main()
{
  freopen("TWOSQRS.in", "r", stdin);
  freopen("TWOSQRS.out", "w", stdout);
  
  for (scanf("%d", &t); t--; ) {
    scanf(ioll, &n);
    for (l = 0, r = (int)sqrt(n); l <= r && (tmp = l * l + r * r) != n; ) 
        tmp > n ? --r : ++l;
    l <= r ? puts("Yes") : puts("No");
  }
  
  return 0;
}

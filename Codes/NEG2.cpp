#include <stdio.h>

int n;

void solve(int k, int d)
{
  if (!k) return;
  (k & 1) ? solve((k - d) >> 1, -d) : solve(k >> 1, -d);
  printf("%d", k & 1);
}

int main()
{
  freopen("NEG2.in", "r", stdin);
  freopen("NEG2.out", "w", stdout);
  
  scanf("%d", &n);
  if (!n) {printf("0"); return 0;}
  solve(n, 1);

  return 0;
}

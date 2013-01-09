#include <cstdio>
#include <cstring>
const int nmax = 100;

int T, x[nmax + 18][nmax + 18], S, C;

int calc()
{
  int depth = 0;
  for (; ; ) {
    bool same = 1;
    for (int i = 2; i + depth <= S; ++i)
      if (x[depth][i] != x[depth][i - 1]) {
	same = 0;
	break;
      }
    if (same) break;
    ++depth;
    for (int i = 1; i + depth <= S; ++i) 
      x[depth][i] = x[depth - 1][i + 1] - x[depth - 1][i];
  }
  return depth;
}

int main()
{
  freopen("CMPLS.in", "r", stdin);
  freopen("CMPLS.out", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &S, &C);
    memset(x[0], 0, sizeof(x[0]));
    for (int i = 1; i <= S; ++i)
      scanf("%d", x[0] + i);
    int depth = calc();
    memset(x[depth + 1], 0, sizeof(x[depth + 1]));
    for (int i = depth; i >= 0; --i) 
      for (int j = S - i + 1; j <= S + C - i; ++j)
	x[i][j] = x[i][j - 1] + x[i + 1][j - 1];
    for (int i = 1; i <= C; ++i)
      printf("%d ", x[0][S + i]);
    printf("\n");
  }
  return 0;
}


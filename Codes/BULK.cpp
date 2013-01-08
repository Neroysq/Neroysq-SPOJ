#include <cstdio>
#include <algorithm>
using namespace std;
const int nmax = 250, smax = 200;

struct face 
{
  int sze, sgn;
  int x[smax + 18], y[smax + 18], z[smax + 18];
}F[nmax + 18];

int p[nmax + 18], n, T, tot, ans;
int M[smax + 18];

bool cmpor(int i, int j)
{
  return F[i].z[1] > F[j].z[1];
}

int main()
{
  freopen("BULK.in", "r", stdin);
  freopen("BULK.out", "w", stdout);
  scanf("%d", &T);
  while (T--) {

    scanf("%d", &n);
    tot = n;
    for (int k = 1, i = 1; k <= n; ++k, ++i) {
      bool need = 1;
      scanf("%d", &F[i].sze);
      p[i] = i;
      for (int j = 1; j <= F[i].sze; ++j) {
	scanf("%d%d%d", F[i].x + j, F[i].y + j, F[i].z + j);
	if (j > 1 && F[i].z[j] != F[i].z[j - 1]) need = 0;
      }
      // ++F[i].sze;
      if (!need) --i, --tot;
      else {
	for (int j = 1; j <= F[i].sze; ++j) {
	  int lst = j > 1 ? j - 1 : F[i].sze;
	  if (F[i].x[j] != F[i].x[lst]) M[j] = 1;
	  else M[j] = 2;
	}
	int nt = 0;
	for (int j = 1; j <= F[i].sze; ++j)
	  if (j == F[i].sze || M[j] != M[j + 1]) {
	    ++nt;
	    F[i].x[nt] = F[i].x[j];
	    F[i].y[nt] = F[i].y[j];
	  }
	F[i].sze = nt;
      }
    }

    sort(p + 1, p + tot + 1, cmpor);
    
    ans = 0;
    for (int i = 1; i <= tot; ++i) {
      int o = 1, now = p[i];
      for (int j = 2; j <= F[now].sze; ++j)
	if (F[now].y[j] > F[now].y[o] || (F[now].y[j] == F[now].y[o] && F[now].x[j] < F[now].x[o]))
	  o = j;
      int x = F[now].x[o], y = F[now].y[o];
      F[now].sgn = 1;
      for (int jj = i - 1, j; j = p[jj], jj; --jj)
	if (F[now].z[1] < F[j].z[1]) {
	  int num = 0;
	  for (int k = 1; k <= F[j].sze; ++k) {
	    int nxt = k == F[j].sze ? 1 : k + 1;
	    if (F[j].x[k] == F[j].x[nxt] || F[j].y[k] < y) continue;
	    if ((F[j].x[k] <= x || F[j].x[nxt] <= x) && (F[j].x[k] > x || F[j].x[nxt] > x)) ++num;
	  }
	  if (num & 1) {
	    F[now].sgn = -F[j].sgn;
	    break;
	  }
	}
      
      int area = 0, h = F[now].z[1];
      for (int i = 1; i <= F[now].sze; ++i) {
	int nxt = i == F[now].sze ? 1 : i + 1;
	area += F[now].x[i] * F[now].y[nxt] - F[now].y[i] * F[now].x[nxt];
      }
      if (area < 0) area = -area;
      ans += area * h * F[now].sgn / 2;
    }
    printf("The bulk is composed of %d units.\n", ans);
  }
  return 0;
}


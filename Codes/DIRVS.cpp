#include <cstdio>
#include <cstring>
const int nmax = 200, mmax = 200, xmax = nmax, ymax = mmax;
const int dx[] = {1, -1,  0,  0};
const int dy[] = {0,  0,  1, -1};

int d[xmax + 18][ymax + 18];
int z[nmax + 18][mmax + 18], P, Q;
int q[nmax*mmax + 18][2], qh, qt;
int x1, x2, y1, y2, T;
bool ed[nmax + 18][mmax + 18];

void init()
{
  scanf("%d%d", &P, &Q);
  for (int i = 1; i <= P; ++i)
    for (int j = 1; j <= Q; ++j)
      scanf("%d", z[i] + j);
  scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
  memset(d, 0, sizeof(d));
  memset(ed, 0, sizeof(ed));
}

int abs(int x)
{
  return x > 0 ? x : -x;
}

int calc(int dx, int dy, int i)
{
  if (!dx) return 0;
  return (dy * i + dx - 1) / dx / 2;//(dy * dy * i + dx * dx - dx * dy) / dx / dy / 2;
}

int calcc(int dx, int dy, int i)
{
  if (!dx) return 0;
  return (dy * i + dx) / dx / 2;//(dy * dy * i + dx * dx) / dx / dy / 2;
}

bool cans(int lx, int ly, int rx, int ry)
{
  int lz = z[lx][ly]*2+1, dx = (rx-lx)*2, dy = (ry-ly)*2, dz = (z[rx][ry] - z[lx][ly]) * 2, sx = abs(dx), sy = abs(dy), xsgn = dx > 0 ?1 : -1, ysgn = dy > 0 ? 1 : -1;

  if (dx)
    for (int i = 1, ny, ty, nx, nz; i < sx; i += 2) {
      nx = lx + i / 2 * xsgn, ny = ly + calc(sx, sy, i) * ysgn, ty = ly + calcc(sx, sy, i) * ysgn;
      nz = dz * i;
      if (nz < (z[nx][ny] * 2 - lz) * sx || nz < (z[nx + xsgn][ty] * 2 - lz) * sx) return 0;
    }

  if (dy)
    for (int i = 1, ny, tx, nx, nz; i < sy; i += 2) {
      ny = ly + i / 2 * ysgn, nx = lx + calc(sy, sx, i) * xsgn, tx = lx + calcc(sy, sx, i) * xsgn;
      nz = dz * i;
      if (nz < (z[nx][ny] * 2 - lz) * sy || nz < (z[tx][ny + ysgn] * 2 - lz) * sy) return 0;
    }

  return 1;
}

bool can(int x, int y, int dz)
{
  if (dz < -3 || dz > 1) return 0;
  return cans(x, y, x1, y1) || cans(x, y, x2, y2);
}

int bfs()
{
  if (x1 == x2 && y1 == y2) return 0;
  qh = qt = 1;
  q[1][0] = x1, q[1][1] = y1;
  ed[x1][y1] = 1;
  for (int nx, ny, tx, ty; qh <= qt; ) {
    nx = q[qh][0], ny = q[qh][1];
    ++qh;
    for (int i = 0; i < 4; ++i) {
      tx = nx + dx[i];
      if (tx <= 0 || tx > P) continue;
      ty = ny + dy[i];
      if (ty <= 0 || ty > Q) continue;
      if (!ed[tx][ty] && can(tx, ty, -z[nx][ny] + z[tx][ty])) {
	ed[tx][ty] = 1;
	d[tx][ty] = d[nx][ny] + 1;
	if (tx == x2 && ty == y2) return d[tx][ty];
	++qt;
	q[qt][0] = tx, q[qt][1] = ty;
      }
    }
  }
  return -1;
}

void work()
{
  int ans = bfs();
  if (ans >= 0)
    printf("The shortest path is %d steps long.\n", ans);
  else
    printf("Mission impossible!\n");
}

int main()
{
  freopen("DIRVS.in", "r", stdin);
  freopen("DIRVS.out", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    init();
    work();
  }
  return 0;
}



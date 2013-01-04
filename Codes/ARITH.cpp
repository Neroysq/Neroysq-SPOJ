#include <cstdio>
#include <cstring>
const int nmax = 10000, mo = 10;

int max(int a, int b) {return a > b ? a : b;}
char str[nmax + 18], com;
struct BigInt 
{
  int len;
  int a[nmax + 18];
  char read() {
    memset(a, 0, sizeof(a));
    len = 0;
    char c = getchar();
    while (c > '9' || c < '0') c = getchar();
    while (c >= '0' && c <= '9') str[++len] = c - '0', c = getchar();
    for (int i = 1; i <= len; ++i) a[i] = str[len - i + 1];
    return c;
  }
}a, b, c, tmp;

int T;

void print(int len, BigInt &a, char c, int spc)
{
  int k = max(0, len - a.len - spc - 1);
  for (int i = 1; i <= k; ++i) printf(" ");
  if (len - a.len - spc > 0) printf("%c", c);
  for (int i = a.len; i; --i) printf("%d", a.a[i]);
  for (int i = 1; i <= spc; ++i) printf(" ");
  puts("");
}

void add(BigInt &c, BigInt &a, BigInt &b)
{
  memset(c.a, 0, sizeof(c.a));
  c.len = max(a.len, b.len);
  for (int i = 1; i <= c.len; ++i)
    c.a[i] = a.a[i] + b.a[i];
  for (int i = 1; i <= c.len; ++i)
    if (c.a[i] >= 10) {
      c.a[i + 1] += c.a[i] / 10;
      c.a[i] %= 10;
      if (i == c.len) ++c.len;
    }
}

void sub(BigInt &c, BigInt &a, BigInt &b)
{
  memset(c.a, 0, sizeof(c.a));
  c.len = a.len;
  for (int i = 1; i <= c.len; ++i)
    c.a[i] = a.a[i] - b.a[i];
  for (int i = 1; i <= c.len; ++i)
    if (c.a[i] < 0) {
      --c.a[i + 1];
      c.a[i] += 10;
    }
  while (c.a[c.len] == 0 && c.len > 1) --c.len;
}

void mul(BigInt &c, BigInt &a, BigInt &b)
{
  memset(c.a, 0, sizeof(c.a));
  c.len = a.len + b.len - 1;
  for (int i = 1; i <= a.len; ++i)
    for (int j = 1; j <= b.len; ++j)
      c.a[i + j - 1] += a.a[i] * b.a[j];
  for (int i = 1; i <= c.len; ++i)
    if (c.a[i] >= 10) {
      c.a[i + 1] += c.a[i] / 10;
      c.a[i] %= 10;
      if (i == c.len) ++c.len;
    }
  while (c.a[c.len] == 0 && c.len > 1) --c.len;
}

void mul(BigInt &c, BigInt &a, BigInt &b, int d)
{
  memset(c.a, 0, sizeof(c.a));
  c.len = a.len;
  for (int i = 1; i <= a.len; ++i)
    c.a[i] = a.a[i] * b.a[d];
  for (int i = 1; i <= c.len; ++i)
    if (c.a[i] >= 10) {
      c.a[i + 1] += c.a[i] / 10;
      c.a[i] %= 10;
      if (i == c.len) ++c.len;
    }
  while (c.a[c.len] == 0 && c.len > 1) --c.len;
}

void work_add_sub()
{
  if (com == '+') 
    add(c, a, b);
  else 
    sub(c, a, b);
  int width = max(a.len, max(b.len + 1, c.len));
  print(width, a, ' ', 0);
  print(width, b, com, 0);
  int num = max(b.len + 1, c.len);
  for (int i = width; i > num; --i) printf(" ");
  for (int i = 1; i <= num; ++i) printf("-");
  puts("");
  print(width, c, ' ', 0);
}

void worl_mul()
{
  mul(c, a, b);
  int width = max(a.len, max(b.len + 1, c.len));
  print(width, a, ' ', 0);
  print(width, b, '*', 0);
  mul(tmp, a, b, 1);
  int num = max(b.len + 1, tmp.len);
  for (int i = width; i > num; --i) printf(" ");
  for (int i = 1; i <= num; ++i) printf("-");
  puts("");
  if (b.len > 1) {
    for (int i = 0; i < b.len; ++i) {
      mul(tmp, a, b, i + 1);
      print(width, tmp, ' ', i);
    }
    num = c.len;
    for (int i = width; i > num; --i) printf(" ");
    for (int i = 1; i <= num; ++i) printf("-");
    puts("");
  }
  print(width, c, ' ', 0);
}

int main()
{
  freopen("ARITH.in", "r", stdin);
  freopen("ARITH.txt", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    com = a.read();
    b.read();
    if (com == '+' || com == '-') work_add_sub();
    else worl_mul();
    puts("");
  }
  return 0;
}

  

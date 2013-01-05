#include <cstdio>
#include <cstring>
const int nmax = 1000000;

char str[nmax + 18];
int n, T;

int main()
{
  freopen("PALIN.in", "r", stdin);
  freopen("PALIN.txt", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    bool jump = 1;
    for (int i = 1; i <= n; ++i)
      if (str[i] != '9') {
	jump = 0;
	break;
      }
    if (jump) {
      printf("1");
      for (int i = 1; i < n; ++i) printf("0");
      printf("1\n");
    }
    else {
      int pos = 0;
      for (int i = n >> 1; i; --i)
	if (str[i] != str[n - i + 1]) {
	  pos = i;
	  break;
	}
      if (pos && str[pos] > str[n - pos + 1]) 
	for (int i = pos; i; --i)
	  str[n - i + 1] = str[i];
      else {
	int np = 0;
	for (int i = (n + 1) >> 1; i; --i)
	  if (str[i] < '9') {
	    np = i;
	    break;
	  }
	++str[np];
	for (int i = (n + 1) >> 1; i > np; --i)
	  str[i] = str[n - i + 1] = '0';
	for (int i = np; i; --i) str[n - i + 1] = str[i];
      }
      printf("%s\n", str + 1);
    }
  }
  return 0;
}


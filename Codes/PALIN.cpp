#include <stdio.h>
const int nmax = 1000000;

int t, l;
bool get;
char str[nmax + 18];

int main()
{
    freopen("PALIN.in", "r", stdin);
    freopen("PALIN.out", "w", stdout);
    scanf("%d\n", &t);
    while (t--)
    {
	get = false;
	scanf("%s\n", str + 1);
	len = strlen(str);
	if (len == 1)
	{
	    printf("%s", str[1] == '9' ? "11" : str + 1);
	    continue;
	}
	for (int l = 1, r = l, ln, rn; l < r; ++l, --r)
	{
	    ln = str[l] - '0';
	    rn = str[r] - '0';
	    if (ln != 9 || rn != 9) get = true;
	}
	if (!get)
	{
	    printf("1");
	    for (int i = 1; i < len; ++i)
		printf("0");
	    printf("1\n");
	}
	for (int l = len >> 1

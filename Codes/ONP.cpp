#include <stdio.h>
#include <memory.h>
const int lmax = 400;

int p, n, q[100];
char s[lmax + 18], stack[lmax + 18];

int main()
{
    freopen ("ONP.in", "r", stdin);
    freopen ("ONP.out", "w", stdout);
    scanf ("%d", &n);
    q[40] = 0;
    q[43] = 1;
    q[45] = 2;
    q[42] = 3;
    q[47] = 4;
    q[94] = 5;
    while (n--)
    {
	scanf ("\n%s", &s);
	p = 0;
	for (int i = 0, tmp = strlen (s); i < tmp; ++i)
	    if (s[i] >= 'a' && s[i] <= 'z')
		printf ("%c", s[i]);
	    else
		if (s[i] == '(')
		    stack[++p] = s[i];
		else
		    if (s[i] == ')')
		    {
			for (; stack[p] != '('; --p)
			    printf ("%c", stack[p]);
			--p;
		    }
		    else
		    {
			if (q[s[i]] <= q[stack[p]]) printf ("%c", stack[p--]);
			stack[++p] = s[i];
		    }
	printf ("\n");
    }
    return 0;
}

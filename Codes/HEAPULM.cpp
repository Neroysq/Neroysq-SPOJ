/*
     construct a cartesian tree,  remember to sort the label~~~~~~
     O(nlogn + n)
     */

#include <stdio.h>
#include <stdlib.h>
const int nmax = 50000, lmax = 10;

int a[nmax + 18], n, stack[nmax + 18], st, l[nmax + 18], r[nmax + 18], p[nmax + 18];
char name[nmax + 18][lmax + 18], c;

void dfs(int x)
{
    printf("(");
    if (l[x]) dfs(l[x]);
    printf("%s/%d", name[x], a[x]);
    if (r[x]) dfs(r[x]);
    printf(")");
}

int cmpor(const void *i, const void *j)
{
    char *a = name[*(int *)i], *b = name[*(int *)j];
    for (int k = 0; a[k] != '\0' || b[k] != '\0'; ++k)
	if (a[k] != b[k]) return a[k] - b[k];
    return 0;
}

int main()
{
    freopen("HEAPULM.in", "r", stdin);
    freopen("HEAPULM.out", "w", stdout);
    while (scanf("%d", &n), n)
    {
	st = 0;
	for (int i = 1; i <= n; ++i)
	    scanf(" %[^/]/%d", name[i], a + i), l[i] = r[i] = 0, p[i] = i;
	qsort(p + 1, n, sizeof(p[0]), cmpor);
	for (int i = 1, j; i <= n; ++i)
	{
	    for (j = st; j && a[stack[j]] < a[p[i]]; --j);
	    if (j < st) l[p[i]] = stack[j + 1];
	    if (j) r[stack[j]] = p[i];
	    stack[st = j + 1] = p[i];
	}
	dfs(stack[1]);
	printf("\n");
    }
    return 0;
}

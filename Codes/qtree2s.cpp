#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001,oo = ~0U >> 1;
typedef int arr[maxn*3];
arr e,next,head,w,line,sum,fa,cost,top,depth,rank,s,first;
int n,tot,delta,now,last;
void add(int j,int k,int l)
{
    ++tot; e[tot] = k; next[tot] = head[j]; head[j] = tot; w[tot] = l;
}
void original()
{
    int i;
    for (delta = 1; delta < n+2; delta *= 2);
    for (i = 1; i <= n; ++i) line[i+delta] = cost[s[i]];
    for (i = delta; i; --i) line[i] = line[i*2]+line[i*2+1];    
}
void change(int x)
{
    for (x = (x+delta)/2; x; x >>= 1) line[x] = line[x*2]+line[x*2+1];    
}
int ask(int l,int r)
{
    int ans = 0;
    l = l+delta-1; r = r+delta+1;
    while (l+1 < r)   
    {
        if ((l&1) == 0) ans += line[l+1];
        if ((r&1) == 1) ans += line[r-1];
        l >>= 1;
        r >>= 1;
    }
    return ans;
}
void prepare(int x,int deep)
{
    int p,max = 0,mind = 0;
    sum[x] = 1; depth[x] = deep;
    for (p = head[x]; p; p = next[p])
    if (e[p] != fa[x])
    {
        fa[e[p]] = x;
        cost[e[p]] = w[p];
        prepare(e[p],deep+1);
        sum[x] += sum[e[p]];
        if (sum[e[p]] > max) max = sum[e[p]],mind = p;
    }
    if (mind != 0) first[x] = mind; else first[x] = 0;
}
void tarjan(int x)
{
    int p,i;
    s[++now] = x; rank[x] = now;
    if (first[x] == 0)
    {
        for (i = last+1; i <= now; ++i) top[s[i]] = s[last+1];
        last = now;
    }
    else 
    {
        tarjan(e[first[x]]);
        for (p = head[x]; p; p = next[p])
        if (e[p] != fa[x] && p != first[x]) tarjan(e[p]);        
    }    
}
int main()
{
    int i,j,k,l,p,q,x,y,z,rex,rey,nx,ny,lenx,leny,task,ans;
    char st[11];
    freopen("qtree2.in","r",stdin); freopen("qtree2s.out","w",stdout);
    for (scanf("%d",&task); task; --task)
    {
        memset(head,0,sizeof(head));
        memset(line,0,sizeof(line));
        memset(fa,0,sizeof(fa));
        scanf("%d",&n);
        for (i = 1; i < n; ++i) scanf("%d%d%d",&j,&k,&l),add(j,k,l),add(k,j,l);  
        tot = 0; now = 0; last = 0;    
        prepare(1,1); 
        tarjan(1); 
        original();
        for (scanf("%s",st); st[1] != 'O'; scanf("%s",st))
        {
        
            if (st[1] == 'T')
            {
                scanf("%d%d%d",&x,&y,&z);
                rex = x; rey = y; lenx = 0; leny = 0;
                for (; top[x] != top[y];)
                {
                    nx = top[x]; ny = top[y];
                    if (depth[nx] > depth[ny]) lenx += rank[x]-rank[nx]+1,x = fa[nx];               
                    else leny += rank[y]-rank[ny]+1,y = fa[ny];                
                }
                if (depth[x] > depth[y]) lenx += rank[x]-rank[y]+1;
                else leny += rank[y]-rank[x]+1;
                x = rex; y = rey;             
                if (lenx >= z)
                {
                    while (z)   
                    {
                        nx = top[x];
                        if (z > rank[x]-rank[nx]+1) {z -= rank[x]-rank[nx]+1; x = fa[nx];}
                        else {x = s[rank[x]-z+1]; z = 0;}
                    }
                    printf("%d\n",x);
                }
                else 
                {
                    z = leny-(z-lenx)+1;
                    while (z)
                    {
                        ny = top[y];
                        if (z > rank[y]-rank[ny]+1) {z -= rank[y]-rank[ny]+1; y = fa[ny];}
                        else {y = s[rank[y]-z+1]; z = 0;}
                    }
                    printf("%d\n",y);                
                }
            }
            else 
            {
                scanf("%d%d",&x,&y);
                for (ans = 0; top[x] != top[y]; x = fa[nx])
                {
                    nx = top[x]; ny = top[y];
                    if (depth[nx] < depth[ny]) swap(x,y),swap(nx,ny);
                    ans += ask(rank[nx],rank[x]);
                }
                if (depth[x] < depth[y]) swap(x,y);
                ans += ask(rank[y]+1,rank[x]);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}

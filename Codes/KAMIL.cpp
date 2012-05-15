#include<cstdio>
int t=10,c[90],a,i;char s;int main(){
    freopen("KAMIL.in", "r", stdin);
    freopen("KAMIL.out", "w", stdout);
    c[76]=c[70]=c[68]=c[84]=1;
    while(t--){a=0;
    while(scanf("%c",s)!=EOF&&s!=0)
    a+=c[s];
    printf("%d\n",1<<a);}return 0;}

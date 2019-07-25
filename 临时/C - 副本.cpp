#include <bits/stdc++.h>
using namespace std;
int gi(){
    int x=0,w=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')w=0,ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return w?x:-x;
}
const int N=1e6+5;
int n,m,a[N],pre[N],suf[N],nxt[N],vis[N],num;
int get(){
    while(vis[num])++num;
    vis[num]=-1;return num;
}
void del(int l,int r){
    suf[pre[l]]=suf[r];pre[suf[r]]=pre[l];
}
void solve(int l,int r){
    for(int i=l;i<=r;i=suf[i])
        while(nxt[i]){
            solve(suf[i],pre[nxt[i]]);
            del(suf[i],nxt[i]);nxt[i]=nxt[nxt[i]];
        }
    int sum=0,cnt=0,rt=a[pre[l]];
    for(int i=l;i<=r;i=suf[i])++sum,cnt+=a[i]>0;
    sum=(sum+1)>>1;
    for(int i=l;i<=r;i=suf[i])if(!a[i]&&cnt<sum)a[i]=get(),++cnt;
    for(int i=l;suf[i]<=r;i=suf[i]){
        while(i>l&&suf[i]<=r&&!a[pre[i]]&&a[i]&&a[suf[i]])
            a[pre[i]]=a[suf[i]],del(i,suf[i]),i=pre[pre[i]];
        while(i>=l&&suf[suf[i]]<=r&&a[i]&&a[suf[i]]&&!a[suf[suf[i]]])
            a[suf[suf[i]]]=a[i],del(suf[i],suf[suf[i]]),i=pre[i];
    }
    for(int i=l;i<=r;i=suf[i])if(!a[i])a[i]=rt;
}
int main(){
    for (int _=gi();_;_--) {
        n=gi();m=n*2-1; num=1;
        for (int i=0;i<=m+5;i++)
            a[i]=pre[i]=suf[i]=nxt[i]=vis[i]=0;
        for(int i=1;i<=m;++i){
            a[i]=gi();
            if (a[i]==-1) a[i]=0;
        }
        a[1]=a[m]=1;
        for(int i=0;i<=m;++i)pre[i]=i-1,suf[i]=i+1;
        for(int i=m;i;--i)
            if(a[i]){
                if(vis[a[i]])nxt[i]=vis[a[i]];
                vis[a[i]]=i;
            }
        solve(1,m);
        for(int i=1;i<=m;++i)printf("%d ",a[i]);
        puts("");
    }
}

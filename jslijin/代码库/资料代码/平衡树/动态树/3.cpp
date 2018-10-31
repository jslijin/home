#include <cstdio>
#include <algorithm>
#define N 10010
#define lson c[0][x]
#define rson c[1][x]
using namespace std;
int f[N],c[2][N],rev[N],s[N],v[N];
int sum[N];
char str[10];
void push_up(int x) {
	sum[x]=sum[lson]+sum[rson]+v[x];
	s[x]=s[lson]+s[rson]+1;
}
void U(int x,int d,int r){
	if (r) swap(lson,rson),rev[x]^1;
	if (d) sum[x]+=s[x]*d,lazy[x]+=d;
}
void push_down(int x){
	U(lson,lazy[x],rev[x]);
	U(rson,lazy[x],rev[x]);
	lazy[x]=rev[x]=0;
}
bool is_R(int x){ return c[0][f[x]]!=x && c[1][f[x]]!=x; }
void U_P(int x){ if (!is_R(x)) U_P(f[x]); push_down(x); }
void rot(int x){
    int y=f[x],z=f[y],l=(c[1][y]==x),r=l^1;
    if (!is_R(y)) c[c[1][z]==y][z]=x;
    f[x]=z,f[y]=x,f[c[r][x]]=y,c[l][y]=c[r][x],c[r][x]=y;
	push_up(y),push_up(x);
}
void SP(int x){
    U_P(x);
    for(;!is_R(x);rot(x)){
        int y = f[x],z = f[y];
        if(!is_R(y)) if((c[0][y] == x) ^ (c[0][z] == y)) rot(x);
        else rot(y);
    }
}
void AC(int x){ for (int t=0; x; x=f[x]) SP(x),rson=t,push_up(x),t=x; }
void make_R(int x){ AC(x),SP(x),swap(lson,rson),rev[x]^=1; }
void link(int x,int y){ make_R(x),f[x] = y; }
void cut(int x,int y) { make_R(x),AC(y),SP(y),c[0][y]=f[x]=0,push_up(y); }
int find_R(int x){
    AC(x),SP(x);
    while (lson) push_down(x),x=lson; return x;
}
int find_F(int x){
	AC(x); SP(x); for (x=lson; !rson; x=rson); 
	return x;
}
void get_P(int x,int y) { make_R(x); AC(y); SP(y); }
int query(int x,int y) { get_P(x,y); return sum[y]; }
int main(){
    int n , m , x , y;
    scanf("%d%d" , &n , &m);
    while(m -- ){
        scanf("%s%d%d" , str , &x , &y);
        if(str[0] == 'C') link(x , y);
        else if(str[0] == 'D') cut(x , y);
        else printf("%s\n" , find_R(x) == find_R(y) ? "Yes" : "No");
    }
    return 0;
}
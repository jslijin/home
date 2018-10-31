#include <cstdio>
#include <algorithm>
#define N 100010
#define MOD 51061
#define lson c[0][x]
#define rson c[1][x]
using namespace std;
int fa[N] , c[2][N] , si[N] , rev[N];
unsigned w[N] , sum[N] , add[N] , mul[N];
char str[5];

void pushup(int x)
{
    si[x] = si[lson] + si[rson] + 1;
    sum[x] = (sum[lson] + sum[rson] + w[x]) % MOD;
}
void cal(int x , unsigned a , unsigned m , int r)
{
    sum[x] = (sum[x] * m + si[x] * a) % MOD;
    w[x] = (w[x] * m + a) % MOD;
    mul[x] = (mul[x] * m) % MOD;
    add[x] = (add[x] * m + a) % MOD;
    if(r) swap(lson , rson) , rev[x] ^= 1;
}
void pushdown(int x)
{
    cal(lson , add[x] , mul[x] , rev[x]);
    cal(rson , add[x] , mul[x] , rev[x]);
    add[x] = rev[x] = 0 , mul[x] = 1;
}
bool isroot(int x)
{
    return c[0][fa[x]] != x && c[1][fa[x]] != x;
}
void update(int x)
{
    if(!isroot(x)) update(fa[x]);
    pushdown(x);
}
void rotate(int x)
{
    int y = fa[x] , z = fa[y] , l = (c[1][y] == x) , r = l ^ 1;
    if(!isroot(y)) c[c[1][z] == y][z] = x;
    fa[x] = z , fa[y] = x , fa[c[r][x]] = y , c[l][y] = c[r][x] , c[r][x] = y;
    pushup(y) , pushup(x);
}
void splay(int x)
{
    update(x);
    while(!isroot(x))
    {
        int y = fa[x] , z = fa[y];
        if(!isroot(y))
        {
            if((c[0][y] == x) ^ (c[0][z] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
void access(int x)
{
    int t = 0;
    while(x) splay(x) , rson = t , pushup(x) , t = x , x = fa[x];
}
void makeroot(int x)
{
    access(x) , splay(x);
    swap(lson , rson) , rev[x] ^= 1;
}
void link(int x , int y)
{
    makeroot(x) , fa[x] = y;
}
void cut(int x , int y)
{
    makeroot(x) , access(y) , splay(y) , c[0][y] = fa[x] = 0 , pushup(y);
}
void split(int x , int y)
{
    makeroot(y) , access(x) , splay(x);
}
int main()
{
    int n , m , i , x , y;
    unsigned z;
    n = read() , m = read();
    for(i = 1 ; i <= n ; i ++ ) si[i] = w[i] = sum[i] = mul[i] = 1;
    for(i = 1 ; i < n ; i ++ ) x = read() , y = read() , link(x , y);
    while(m -- )
    {
        scanf("%s" , str) , x = read() , y = read();
        switch(str[0])
        {
            case '+': z = (unsigned)read() , split(x , y) , cal(x , z , 1 , 0); break;
            case '-': cut(x , y) , x = read() , y = read() , link(x , y); break;
            case '*': z = (unsigned)read() , split(x , y) , cal(x , 0 , z , 0); break;
            default: split(x , y) , printf("%u\n" , sum[x]);
        }
    }
    return 0;
}
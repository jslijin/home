# include <iostream>
# include <sstream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <string>
# include <cstring>
# include <cmath>
# include <stack>
# include <queue>
# include <vector>
# include <list>
# include <map>
# include <set>
# include <deque>
# include <iterator>
# include <functional>
# include <bitset>
# include <climits>
# include <ctime>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define odd(x) ((x)&1)
#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
#define all(x) (x).begin(),(x).end()
#define mem(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for (int i=(a); i<=(b); ++i)
#define per(i,a,b) for (int i=(a); i>=(b); --i)
#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n) rep(j,0,m) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
const int oo = /*2 * 1000 * 1000 * 1000*/0x3f3f3f3f;
const ll ooo=9223372036854775807ll; 
const int _cnt = 1000 * 1000 + 7;
const int _p = 1000 * 1000 * 1000 + 7;
const int N=200105; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

int n,a[N],b[N],phi[N],fac[N][20],L[N],R[N],fa[21][N],flag[N],d[N],T=0,m=0,x,y,tmp[N],tt=0,S[N],r,c,xx;
ll inv[N],F[N],H[N],ans[N],ans0=0; bool check[N];
vector <int> G[N],E[N],W[N];

bool cmp(int x,int y) { return L[x]<L[y]; }
bool out(int y,int x) { return L[y]<L[x] || L[y]>R[x]; }
void link(int x,int y,int w) {
	if (flag[x]!=T) E[x].clear(),W[x].clear(),flag[x]=T;
	if (flag[y]!=T) E[y].clear(),W[y].clear(),flag[y]=T;
	E[x].pb(y),W[x].pb(w);
}

void dfs(int x,int p) {
	L[x]=++m,fa[0][x]=p,d[x]=d[p]+1;
	rep_it(it,G[x]) {
		if (*it==p) continue;
		dfs(*it,x);
	}
	R[x]=m;
}

int lca(int x,int y) {
	per(i,19,0) if (fa[i][x] && out(y,fa[i][x])) x=fa[i][x];
	return out(y,x) ? fa[0][x]:x;
}

void dp(int x,int k) {
	F[x]=(a[x]%k)?0:phi[a[x]],H[x]=0;
	rep(i,0,(int)E[x].size()-1) {
		int y=E[x][i],w=W[x][i];
		dp(y,k),(H[y]+=F[y]*w)%=_p;
		(ans[k]+=F[x]*H[y])%=_p,(ans[k]+=F[y]*H[x])%=_p;
		(F[x]+=F[y])%=_p,(H[x]+=H[y])%=_p;
	}
}

int main() {
    //file_put();
    
    scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]),b[a[i]]=i;
	inv[1]=1; rep(i,2,n) inv[i]=(_p-_p/i)*inv[_p%i]%_p;
	rep(i,1,n-1) scanf("%d%d",&x,&y),G[x].pb(y),G[y].pb(x);
	dfs(1,0);
	rep(i,1,19) rep(j,1,n) fa[i][j]=fa[i-1][fa[i-1][j]];
	rep(i,1,n) phi[i]=i;
	rep(i,2,n) {
		if (check[i]) continue;
		for (int j=i; j<=n; j+=i) {
			check[j]=1,phi[j]=phi[j]/i*(i-1);
			fac[j][++fac[j][0]]=i;
		}
	}
	rep(i,1,n) {
		++T,tt=0;
		for (int j=i; j<=n; j+=i) tmp[++tt]=b[j],flag[b[j]]=T,E[b[j]].clear(),W[b[j]].clear();
		sort(tmp+1,tmp+tt+1,cmp);
		S[r=1]=tmp[1];
		rep(i,2,tt) {
			c=lca(tmp[i],S[r]),xx=0;
			while (r && d[S[r]]>=d[c]) {
				if (xx) link(S[r],xx,d[xx]-d[S[r]]);
				xx=S[r--];
			}
			if (xx!=c) link(c,xx,d[xx]-d[c]);
			S[++r]=c,S[++r]=tmp[i];
		}
		while (r>1) link(S[r-1],S[r],d[S[r]]-d[S[r-1]]),--r;
		dp(S[1],i);
	}
	per(i,n,1) for (int j=i*2; j<=n; j+=i) (ans[i]-=ans[j])%=_p;
	rep(i,1,n) rep(j,1,fac[i][0]) ans[i]=ans[i]*fac[i][j]%_p*inv[fac[i][j]-1]%_p;
	rep(i,1,n) (ans0+=ans[i])%=_p;
	ans0=ans0*2%_p*inv[n]%_p*inv[n-1]%_p;
	printf("%I64d\n",ans0);
	
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
#define mem(a,x) memset(a,x,sizeof(a))

const int _p=(int)1e9+9, w0=115381398ll;
ll add(ll x,ll y) { x+=y; return x%_p; }
ll mul(ll x,ll y) { return x*y%_p; }
ll Pow(ll x,ll k) {
	ll ret=1;
	for (;k;k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
	return ret;
}

template <int N,int K>
struct FT{
	ll tmp[K<<1],a[N],b[N],w[K]; int t; 
    void Init(ll w0) {
        w[0]=1; rep(i,1,K) w[i]=mul(w[i-1],w0);
    } 
	void FWT(ll a[],int S,int n,int op) {
		if (n==1) return; int L=n/K;
		rep(i,0,K) FWT(a,S+L*i,n/K,op);
		rep(i,0,L) {
			rep(j,0,K) tmp[j]=0;
			rep(j,0,K) rep(k,0,K) {
				t=op*j*k%K,t<0?t+=K:0;
				tmp[j]=add(tmp[j],mul(a[S+L*k+i],w[t])); 
			}
			rep(j,0,K) a[S+L*j+i]=tmp[j];
		}
	}
	void Multiply(ll A[],ll B[],int n,ll C[]) {
	    rep(i,0,n) a[i]=A[i],b[i]=B[i];
	    FWT(a,0,n,1),FWT(b,0,n,1);
	    rep(i,0,n) a[i]=mul(a[i],b[i]);
	    FWT(a,0,n,-1); ll inv=Pow(n,_p-2);
	    rep(i,0,n) C[i]=mul(a[i],inv),C[i]<0?C[i]+=_p:0;
    }
    int get(int x,int y) {
        int ret=0,B=1;
        for (; x||y; x/=K,y/=K,B*=K) ret+=(x%K+y%K)%K*B;
        return ret;
    }
    void Multiply_B(ll A[],ll B[],int n,ll C[]) {
        rep(i,0,n) rep(j,0,n) (C[get(i,j)]+=mul(A[i],B[j]))%=_p;
        rep(i,0,n) C[i]<0?C[i]+=_p:0;
    }
};

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=6561;
FT<N,3> T;
ll inv,a[N],b[N],c[N],d[N];

int main() {
	file_put();
	
	srand(time(0));
	
	//rep(i,0,N) scanf("%lld",&a[i]);
	//rep(i,0,N) scanf("%lld",&b[i]);
	
	rep(i,0,N) a[i]=(rand()<<15)|rand();
	rep(i,0,N) b[i]=(rand()<<15)|rand();
	
	T.Init(w0);
	T.Multiply(a,b,N,c);
	T.Multiply_B(a,b,N,d);
	
	rep(i,0,3) printf("%lld\n",c[i]); printf("\n");
	rep(i,0,3) printf("%lld\n",d[i]); printf("\n");
	
    if (equal(c,c+N,d)) printf("Yes\n"); else printf("No\n");

	return 0;
}


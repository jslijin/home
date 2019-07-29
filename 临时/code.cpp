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

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int P=1e9+7; 

int add(int x,int y) {
    if ((x += y) >= P) x -= P;
    return x < 0 ? x + P : x;
}

int mul(int x,int y) {
    return (ll)x*y%P;
}

ll qpow(ll x,ll k) {
    ll ret=1;
    for (;k; k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
    return ret;
}

// desc : 0^k + 1^k + 2^k + .. + (n-1)^k
// time-ini : O(n^2)
// time-cal : k + log
namespace Bernoulli {
	const int N = 1000;
	int C[N][N], B[N];
	void init() {
		rep(i, 0, N) C[i][0] = 1;
		rep(i, 0, N) rep(j, 1, i + 1) C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
		B[0] = 1;
		rep(i, 1, N) {
			B[i] = 0;
			rep(j, 0, i) B[i] = add(B[i], P - mul(C[i + 1][j], B[j]));
			B[i] = mul(B[i], qpow(C[i + 1][i], P - 2)) % P;
		}
	}
	int cal(int n, int k) { 
		int sum = 0;
		rep(i, 0, k + 1) sum = add(sum, mul(C[k + 1][i], mul(B[i], qpow(n, k + 1 - i))));
		return mul(sum, qpow(k + 1, P - 2));
	}
};

struct Min_25{ 
	// F(i) 要拆成多个完全积性函数的和 
	static const int N = 1e6 + 7;
	int Sqr, m, p[N], id1[N], id2[N], tot, cntp, K, f[N];
	ll g[N], sp[N], h[N], n, w[N];
	bool isp[N];
	// f(p) = p ^ k 
	//ll f(int p) { return qpow(p,K); }
 
	// 假设都是质数的完全积性函数前缀和 去掉 f(1) 
	ll calc(ll n) { return Bernoulli::cal(n+1,K) - 1;}

	void prime(int n, int k){
	    K = k;
    	cntp = 0;isp[1] = 1;
    	rep(i, 2, n+1) {
        	if(!isp[i]) p[++cntp] = i;
        	for(int j = 1; j <= cntp && i * p[j] <= n; j++){
            	isp[i * p[j]] = 1;
            	if(i % p[j] == 0)break;
        	}
    	}
    	rep(i, 1, cntp+1) f[i] = qpow(p[i], K), sp[i] = add(sp[i - 1], f[i]);
    	p[++cntp] = INT_MAX;
	}
	
	void solve(ll _n, int _K) {
	    n = _n, K=_K; if (n == 0) return;
		m = 0;Sqr = sqrt(n);
		tot = upper_bound(p + 1, p + cntp + 1, Sqr) - (p + 1);
		for(ll i = 1, j; i <= n; i = j + 1){
        	j = n / (n / i);
			w[++m] = n / i;
        	g[m] = calc(w[m]);
        	w[m] <= Sqr ? id1[w[m]] = m : id2[j] = m;
    	}
    	rep(j, 1, tot + 1)
        	for(int i = 1; i <= m && 1ll * p[j] * p[j] <= w[i]; i++){
				ll t = w[i] / p[j];
				int k = t <= Sqr ? id1[t] : id2[n / t]; 
        		g[i] = add(g[i], -mul(f[j], (g[k] - sp[j - 1])));
			}
	}
	
	ll get(ll _n) {
	    int t = _n <= Sqr ? id1[_n] : id2[n / _n];
	    return g[t];
    }
} _U;

int n,k;

int main() {
    file_put();
    
    scanf("%d%d",&n,&k);
    Bernoulli::init();
    _U.prime(111111, k);
    _U.solve(n, k);
	return 0;
}


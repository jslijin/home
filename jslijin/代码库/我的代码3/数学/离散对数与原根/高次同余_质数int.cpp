ll kpow(ll a, ll b, ll P) {
    ll r = 1; assert(b>=0);
    for (; b; b>>=1, a = a * a % P) if (b & 1) r = r * a % P;
    return r; 
}

void ex_gcd(int a, int b, int &x, int &y){
	b ? (ex_gcd(b, a % b, y, x), y -= a / b * x) : (x = 1, y = 0);
}

inline int Inv(int a, int P) {
	int x, y; ex_gcd(a, P, x, y);
	return x < 0 ? x + P : x;
}

struct BSGS{
    map<ll, int> M;
    ll bsgs(ll x, ll z, ll P) {
    	if(x % P == 0) return -1;
    	ll res = z % P, sa, t = 1, sq = sqrt(P); M.clear();
    	rep(i, 0, sq+1) { if (M.count(t)) break; M[t] = i, t = t * x % P; }
    	t = P / sq, sa = Inv(kpow(x, sq, P), P);
    	rep(i, 0, t+1) if (M.count(res)) 
            return i * sq + M[res]; else res = res * sa % P;
    	return -1;
    }
    ll ex_bsgs(ll x, ll z, ll P) { //x^y==z(mod P)
    	ll t = 1 % P, w = 1, ans, c = 0; z %= P;
    	rep(i, 0, 51) { if (t == z) return i; t = t * x % P; }
    	for(t = __gcd(x, P); t != 1; t = __gcd(x, P)){
    		if (z % t) return -1;
    		z /= t, P /= t, w = w * x / t % P, c++;
    		if (z == w) return c;
    	}
    	z = z * Inv(w, P) % P, ans = bsgs(x, z, P);
    	return ans + (ans != -1) * c;

    }
};

typedef vector<ll> vll;
typedef pair<ll,ll> pll;
struct Euler{
	vll P,A; ll phi,g,phi_phi; BSGS T;
    inline bool check_g(ll g, ll p) {
    	rep(i,0,sz(P))
    		if (kpow(g, P[i], p) == 1)
    			return 0;
    	return 1;
    }
    inline void factor(ll m) {
        P.clear(),A.clear();
        for (ll k=2; k*k<=m; ++k) if (m%k==0) {
            int cnt=0;
            while (m%k==0) m/=k,cnt++;
            P.pb(k),A.pb(cnt); 
        }
        if (m>1) P.pb(m),A.pb(1);
    }
	inline void norm(ll &x,ll p) { x=(x%p+p)%p; }
    inline ll get_phi(ll p) {
    	ll phi=p;
		for (auto t:P) phi=phi/t*(t-1);
//		rep(i,0,sz(P)) phi=phi/P[i]*(P[i]-1); 
		return phi;
	}
    inline bool check(ll m) {
        //if (m==1 || m==2 || m==4) return 1; 
        factor(m);
        if (sz(P)>2 || sz(P)==1 && P[0]==2) return 0;
        if (sz(P)==1) return 1;
        if (P[0]!=2 || P[0]==2 && A[0]>1) return 0;
        return 1;
    }
    inline ll getRoot(ll p) {
        if (p==1 || p==2 || p==4) return phi=p+1>>1,phi_phi=1,p-1;
        if (!check(p)) return -1;
        phi=p-1;
    	factor(phi),phi_phi=get_phi(phi);
    	for (auto &t:P) t=phi/t;
//		rep(i,0,sz(P)) P[i]=phi/P[i]; 
    	for (g=1; __gcd(g,p)!=1 || !check_g(g,p); ++g);
    	return g;
    }
	// solve equation: ax=b(%p), gcd(a,p)!=1
	pll solve(ll a,ll b,ll p) {
		norm(a,p); norm(b,p); ll g=__gcd(a,p);
		if (b%g) return mp(-1,g);
		a/=g,b/=g,p/=g;
		return mp(kpow(a,phi_phi-1,p)*b%p,g);//note that phi_phi 
	}
	// solve equation: x^a=b(%p), p must be a prime
	vll solve_high(ll a,ll b,ll p) {
		vll ret; norm(b,p); assert(p>0);
		if (!a==b) ret.pb(0);
		if (!b) return ret;
		ll g=getRoot(p);
		if (g==-1) return ret;
		ll _b=T.bsgs(g,b,p);
		if (_b==-1) return ret;
		ll _p=p-1;
		pll t=solve(a,_b,_p);
		if (t.fi==-1) return ret;
		ll _g=t.se,x=t.fi,ans=kpow(g,x,p),d=kpow(g,_p/_g,p);
		ret.pb(ans);
		rep(i,1,_g) ans=ans*d%p,ret.pb(ans);
		sort(all(ret)); 
		return ret;
	}
};

// 注 : 返回所有 [0,p) 中的非负整数解

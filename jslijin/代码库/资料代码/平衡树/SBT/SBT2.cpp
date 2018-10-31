const int maxn = 1 << 18; 
struct SBT{
	int root,L[maxn],R[maxn],s[maxn],idx,val[maxn];
	void init(){root = idx = 0;}
	void RR(int &t){
		int k = L[t];L[t]=R[k];R[k]=t; 
		s[k]=s[t];s[t]=s[L[t]]+s[R[t]] + 1; t = k;
	}
	void LR(int &t){
		int k = R[t];R[t] = L[k];L[k] = t; 
		s[k]=s[t];s[t]=s[L[t]]+s[R[t]] + 1; t = k;
	}
	void MT(int &t){
		if(s[L[L[t]]] > s[R[t]]) RR(t),MT(R[t]),MT(t); else
		if(s[R[L[t]]] > s[R[t]]) LR(L[t]),RR(t),MT(L[t]),MT(R[t]),MT(t);else 
		if(s[R[R[t]]] > s[L[t]]) LR(t),MT(L[t]),MT(t); else
		if(s[L[R[t]]] > s[L[t]]) RR(R[t]),LR(t),MT(L[t]),MT(R[t]),MT(t);
	}
	void Insert(int &t,int x){
		if(! t){
			t = ++ idx; val[t] = x;
			s[t] = 1; L[t] = R[t] = 0;
			return ;
		}
		++ s[t];
		if(x < val[t]) Insert(L[t],x); else Insert(R[t],x); 
		MT(t);
	}
	int Del(int &t,int x){
		int ret;
		-- s[t];
		if(x == val[t] || (x < val[t] && L[t] == 0) || (x > val[t] && R[t] == 0)){ 
			ret = val[t];
			if(L[t] && R[t]) val[t] = Del(L[t],x + 1);else t = L[t] + R[t];
			return ret;
		}
		if(x < val[t]) return Del(L[t],x); else return Del(R[t],x);
	}
};

struct LCT{
	#define lson c[0][x]
	#define rson c[1][x]
	int f[N],c[2][N],rev[N],s[N]; ll v[N],ans[N][2],lazy[N][2];//ans：和/最值; lazy: +/*
	void init(int n,int a[]=NULL){
		mem(f,0); mem(c,0); mem(rev,0); rep(i,1,n) s[i]=1; 
		if (a==NULL) { mem(ans,0); mem(v,0); return; }
		rep(i,1,n) v[i]=ans[i][0]=a[i];
	}
	void push_up(int x) {
		s[x]=s[lson]+s[rson]+1;
		ans[x][0]=ans[lson][0]+ans[rson][0]+v[x];
	}
	void U(int x,int data[],int r){
		ans[x][0]=ans[x][0]*data[1]+s[x]*data[0];
		v[x]=v[x]*data[1]+data[0];
		lazy[x][0]=lazy[x][0]*data[1]+data[0];
		lazy[x][1]=lazy[x][1]*data[1];
		if (r) swap(lson,rson),rev[x]^1;
	}
	void push_down(int x){
		U(lson,lazy[x],rev[x]);
		U(rson,lazy[x],rev[x]);
		lazy[x]=rev[x]=0;
	}
	bool is_r(int x){ return c[0][f[x]]!=x && c[1][f[x]]!=x; }
	void U_P(int x){ if (!is_r(x)) U_P(f[x]); push_down(x); }
	void rot(int x){
		int y=f[x],z=f[y],l=(c[1][y]==x),r=l^1;
		if (!is_r(y)) c[c[1][z]==y][z]=x;
		f[x]=z,f[y]=x,f[c[r][x]]=y,c[l][y]=c[r][x],c[r][x]=y;
		push_up(y),push_up(x);
	}
	void SP(int x){
		U_P(x);
		for(;!is_r(x);rot(x)){
			int y = f[x],z = f[y];
			if(!is_r(y)) if((c[0][y]==x)^(c[0][z]==y)) rot(x); else rot(y);
		}
	}
	void AC(int x){ for (int t=0; x; x=f[x]) SP(x),rson=t,push_up(x),t=x; }
	void make_R(int x){ AC(x),SP(x),swap(lson,rson),rev[x]^=1; }
	void get_P(int x,int y) { make_R(x); AC(y); SP(y); }
	void link(int x,int y){ make_R(x),f[x] = y; }
	void cut(int x,int y) { get_P(x,y),c[0][y]=f[x]=0,push_up(y); }
	int get_dep(int x) { AC(x); SP(x); return s[x]; }
	int get_R(int x){ AC(x),SP(x); for (;lson;x=lson) push_down(x); return x; }
	int get_r(int x){ while (!is_r(x)) x=f[x]; return x; }
	int get_F(int x){ AC(x); SP(x); for (x=lson; !rson; x=rson);  return x; }
	bool is_Home(int x,int y) { return get_R(x)==get_R(y); }
	bool is_home(int x,int y) { return get_r(x)==get_r(y); }
	int get_lca(int x,int y) { AC(x); AC(y); SP(x); return is_home(x,y)?x:f[x]; }
	int* query(int x,int y) { get_P(x,y); return ans[y]; }
	void update(int x,int y,int data[],int r) { get_P(x,y); U(y,data,r); }
	bool LC(int op,int x,int y) { 
		if (is_Home(x,y)==op) return false; 
		if (op==1) link(x,y); else cut(x,y); return true;
	}
	void print_p(int); void print_P(int,int*); void print();
};

LCT::void print_p(int x){
	if (!x) return;
	printf("id=%d   v[%d]=%d   sum[%d]=%d   s[%d]=%d   lazy[%d]=%d  \n",x,x,v[x],x,ans[x],x,s[x],x,lazy[x]);
}

LCT::void print_P(int x,int *y){
	if (!x) return; y[x]=1;
	print_P(lson); print_p(x); printf(rson);
}

LCT::void print(){
	bool check[N]; mem(check,0);
	rep(i,1,n) if (!check[i]) {
		int x=get_r(i);
		printf("\n\n\n*****>>  root=%d   father=%d   size=%d\n",x,f[x],s[x]);
		print_P(x,check);
		cnt+=(!f[x]);
	}
	printf("\n\n\nconnected blocks number: %d \n\n\n",cnt);
}
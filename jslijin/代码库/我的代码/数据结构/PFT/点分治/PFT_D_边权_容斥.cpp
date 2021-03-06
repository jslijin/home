struct PFT{
	struct node { int y,nxt; int v;} e[N<<1];
	int n,tot,k,rt,ans,head[N],f[N],vis[N],sz[N]; int s[N],temp[N];
	void Init(int _n,int _k){ n=_n,tot=0; mem(vis,0),mem(head,0); f[0]=oo; k=_k; }
	void addedge(int x,int y,int v=1){
		e[++tot].nxt=head[x]; head[x]=tot; e[tot].y=y; e[tot].v=v;
	}
	void dfs(int x,int fa) {
		temp[++temp[0]]=s[x];
		for (int i=head[x]; i; i=e[i].nxt) {
			if (vis[e[i].y] || e[i].y==fa) continue;
			s[e[i].y]=s[x]+e[i].v;
			dfs(e[i].y,x);
		}
	}
	void get_rt(int x,int c,int fa=0) {
		sz[x]=1,f[x]=0;
		for (int i=head[x]; i; i=e[i].nxt) {
			if (vis[e[i].y] || e[i].y==fa) continue;
			get_rt(e[i].y,c,x);
			sz[x]+=sz[e[i].y];
			f[x]=max(f[x],sz[e[i].y]);
		}
		f[x]=max(f[x],c-sz[x]);
		if (f[x]<f[rt]) rt=x;
	}
	int cal(int x,int v) {
		//...
		s[x]=v,temp[0]=0; dfs(x,0);
		sort(temp+1,temp+temp[0]+1);
		int l=1,r=temp[0],sum=0;
		while (l<r)
			if (temp[l]+temp[r]<=k) sum+=r-l,l++; 
				else r--;
		return sum;
	}
	void solve(int x,int c,int fa=0) {
		get_rt(x,c,rt=0),x=rt; ans+=cal(x,0); vis[x]=1;
		for (int i=head[x]; i; i=e[i].nxt) {
			if (vis[e[i].y]) continue;
			ans-=cal(e[i].y,e[i].v);
			solve(e[i].y,sz[e[i].y]);
		}
	}
	int Q(){
		//...
		ans=0; solve(1,n); return ans;
	}
}; 

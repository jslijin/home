struct LCT
{
    int ch[maxn][2],pre[maxn],sz[maxn],val[maxn],mx[maxn],add[maxn];
    bool rt[maxn],rev[maxn];
    void init(int s,int t)
    {
        memset(this,0,sizeof(*this));
        for(int i=s;i<=t;++i){rt[i]=true;sz[i]=1;}
    }
    void app_rev(int u){if(u){rev[u]^=true;swap(ch[u][0],ch[u][1]);}}
    void app_add(int u,int a){if(u){mx[u]+=a;val[u]+=a;add[u]+=a;}}
    void up(int u)
    {
        sz[u]=sz[ch[u][0]]+sz[ch[u][1]]+1;
        mx[u]=max(val[u],max(mx[ch[u][0]],mx[ch[u][1]]));//mx初始化与val相同
    }
    void down(int u)
    {
        if(u&&rev[u])app_rev(ch[u][0]),app_rev(ch[u][1]),rev[u]=false;
        if(u&&add[u])app_add(ch[u][0],add[u]),app_add(ch[u][1],add[u]),add[u]=0;
    }
    void rotate(int u)
    {
        int f=pre[u],d=ch[f][1]==u;
        down(f);down(u);
        ch[f][d]=ch[u][!d];pre[ch[f][d]]=f;
        pre[u]=pre[f];
        pre[f]=u;ch[u][!d]=f;
        if(rt[f])rt[f]=false,rt[u]=true;
        else ch[pre[u]][ch[pre[u]][1]==f]=u;
        up(f);
    }
    void splay(int u)
    {
        for(down(u);!rt[u];)
        {
            int f=pre[u];
            if(rt[f])rotate(u);
            else if((ch[f][1]==u)==(ch[pre[f]][1]==f))rotate(f),rotate(u);
            else rotate(u),rotate(u);
        }
        up(u);
    }
    void expose(int u)
    {
        for(int v=0;u;v=u,u=pre[u])
        {
            splay(u);
            rt[ch[u][1]]=true;rt[v]=false;
            ch[u][1]=v;up(u);//注意更新时机
        }
    }
    void make_root(int u)//慎用 会改变部分父子关系
    {
        expose(u);
        splay(u);
        app_rev(u);
    }
    int ancestor(int u)
    {
        while(pre[u])u=pre[u];
        return u;
    }
    void link(int c,int f)//先判断是否在同一子树
    {
        make_root(c);
        pre[c]=f;
    }
    void cut(int f,int c)//先判断是否联通
    {
        make_root(f);
        expose(c);
        splay(c);
        pre[ch[c][0]]=pre[c];
        pre[c]=0;
        rt[ch[c][0]]=true;
        ch[c][0]=0;up(c);
    }
    int query(int u,int v)//慎用 会改变父子关系
    {
        make_root(u);
        expose(v);
        splay(v);
        return mx[v];
    }
    int lca_query(int a,int b)//退出时注意子树状态
    {
        expose(a);
        splay(a);
        for(a=0;b;a=b,b=pre[b])
        {
            splay(b);
            if(!pre[b])return max(mx[ch[b][1]],mx[a]);
            rt[ch[b][1]]=true;
            rt[a]=false;
            ch[b][1]=a;
            up(b);
        }
        return 0;
    }
    void change(int a,int b)
    {
        expose(a);
        splay(a);
        val[a]=b;
        up(a);
    }
}Lct;

int cnt, rt;

struct Tree
{
    int key, size, son[2];
}T[MAXN];

inline void PushUp(int x)
{
    T[x].size=T[T[x].son[0]].size+T[T[x].son[1]].size+1;
}

inline int Newnode(int key)
{
    ++cnt;
    T[cnt].key=key;
    T[cnt].size=1;
    T[cnt].son[0]=T[cnt].son[1]=0;
    return cnt;
}

void Rotate(int p, int &x)
{
    int y=T[x].son[!p];
    T[x].son[!p]=T[y].son[p];
    T[y].son[p]=x;
    PushUp(x);
    PushUp(y);
    x=y;
}

void Maintain(int &x, int p) //维护SBT的!p子树
{
    if(T[T[T[x].son[p]].son[p]].size > T[T[x].son[!p]].size)
        Rotate(!p, x);
    else if(T[T[T[x].son[p]].son[!p]].size > T[T[x].son[!p]].size)
        Rotate(p, T[x].son[p]), Rotate(!p, x);
    else return;
    Maintain(T[x].son[0], 0);
    Maintain(T[x].son[1], 1);
    Maintain(x, 0);
    Maintain(x, 1);
}

inline int Prev() //返回比根值小的最大值 若无返回0
{
    int x=T[rt].son[0];
    if(!x) return 0;
    while(T[x].son[1])
        x=T[x].son[1];
    return x;
}

inline int Succ() //返回比根值大的最小值 若无返回0
{
    int x=T[rt].son[1];
    if(!x) return 0;
    while(T[x].son[0])
        x=T[x].son[0];
    return x;
}

void Insert(int key, int &x)
{
    if(!x) x=Newnode(key);
    else
    {
        T[x].size++;
        Insert(key, T[x].son[key > T[x].key]);
        Maintain(x, key > T[x].key);
    }
}

bool Delete(int key, int &x) //删除值为key的节点 key可以不存在
{
    if(!x) return 0;
    if(T[x].key == key)
    {
        if(!T[x].son[0])
        {
            x=T[x].son[1];
            return 1;
        }
        if(!T[x].son[1])
        {
            x=T[x].son[0];
            return 1;
        }
        int y=Prev();
        T[x].size--;
        return Delete(T[x].key, T[x].son[0]);
    }
    else
        if(Delete(key, T[x].son[key > T[x].key]))
        {
            T[x].size--;
            return 1;
        }
}

int GetPth(int p, int &x) //返回第p小的节点
{
    if(!x) return 0;
    if(p == T[T[x].son[0]].size+1)
        return x;
    if(p > T[T[x].son[0]].size+1)
        return GetPth(p-T[T[x].son[0]].size-1, T[x].son[1]);
    else
        return GetPth(p, T[x].son[0]);
}

int GetRank(int key, int &x) //找出值<=key的节点个数
{
    if(!x) return 0;
    if(T[x].key <= key)
        return T[T[x].son[0]].size+1+GetRank(key, T[x].son[1]);
    else
        return GetRank(key, T[x].son[0]);
}

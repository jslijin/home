#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

using namespace std;

#define szof(x) ((x) ? (x)->sz : 0)

const int N = 200000 + 10;

struct Node *pis;
struct Node {
    int v, sz;
    Node *ch[2];
    
    Node(int v = 0) : v(v) {
        sz = 1;
        ch[0] = ch[1] = 0;
    }
    
    void maintain() {
        sz = szof(ch[0]) + szof(ch[1]) + 1;
    }
    
    int cmp(int x) const {
        if(x == v) return -1;
        return x < v ? 0 : 1;
    }
    
    void *operator new(size_t) {
        return pis++;
    }
}pool[N], *cache[N], *root;
int tot = 0;

void print(Node *o) {
    if(!o) return;
    print(o->ch[0]);
    cache[++tot] = o;
    print(o->ch[1]);
}

void rebuild(Node*& o, int l, int r) {
    if(l > r) return o = 0, void();
    int mid = (l + r) >> 1;
    o = cache[mid];
    rebuild(o->ch[0], l, mid - 1);
    rebuild(o->ch[1], mid + 1, r);
    o->maintain();
}

void insert(Node*& o, int x) {
    if(!o) o = new Node(x);
    else {
        int d = o->cmp(x);
        if(d == -1) d = 0;
        insert(o->ch[d], x);
    }
    o->maintain();
}

void scape(Node*& o, int x) {
    int d = o->cmp(x);
    if(d == -1) return;
    if(o->ch[d]->sz > o->sz * 0.75) {
        tot = 0;
        print(o);
        rebuild(o, 1, tot);
    }else scape(o->ch[d], x);
}

void insert(int x) {
    insert(root, x);
    scape(root, x);
}

void remove(Node*& o, int x) {
    int d = o->cmp(x);
    if(d == -1) {
        if(!o->ch[0] && !o->ch[1]) o = 0;
        else {
            tot = 0;
            print(o->ch[0]);
            print(o->ch[1]);
            rebuild(o, 1, tot);
        }
    }else remove(o->ch[d], x);
    if(o) o->maintain();
}

int kth(Node *o, int k) {
    while(o) {
        int s = szof(o->ch[0]) + 1;
        if(s == k) return o->v;
        if(s < k) k -= s, o = o->ch[1];
        else o = o->ch[0];
    }
    return -1;
}

int rank(Node *o, int x) {
    int res = 0;
    for(int d; o; o = o->ch[d]) {
        d = o->cmp(x);
        if(d == 1) res += szof(o->ch[0]) + 1;
        if(d == -1) d = 0;
    }
    return res + 1;
}

int pre(Node *o, int x) {
    int res = -1;
    for(int d; o; o = o->ch[d]) {
        d = o->cmp(x);
        if(d == 1) res = o->v;
        if(d == -1) d = 0;
    }
    return res;
}

int suf(Node *o, int x) {
    int res = -1;
    for(int d; o; o = o->ch[d]) {
        d = o->cmp(x);
        if(d == 0) res = o->v;
        if(d == -1) d = 1;
    }
    return res;
}

int main() {
    pis = pool;
    int n, opt, x;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &opt, &x);
        if(opt == 1) insert(x);
        else if(opt == 2) remove(root, x);
        else if(opt == 3) printf("%d\n", rank(root, x));
        else if(opt == 4) printf("%d\n", kth(root, x));
        else if(opt == 5) printf("%d\n", pre(root, x));
        else printf("%d\n", suf(root, x));
    }
    
    return 0;
}
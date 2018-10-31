# include <iostream>
# include <sstream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <cstring>
# include <cmath>
# include <stack>
# include <queue>
# include <iterator>
# include <vector>
# include <functional>
# include <map>
# include <set>
# include <ctime>

using namespace std;

struct treetype { long state,key,parent,size,mul,child[2]; };

treetype tree[1000000];
long n,k,root;

void file_put(){
  freopen("splay.in","r",stdin);
  freopen("splay.our","w",stdout);
}

long put(long x,long k,long state){
  tree[x].child[state]=k;
  tree[k].parent=x;
  tree[k].state=state; return 0;
}

long update(long x){ tree[x].size=tree[tree[x].child[0]].size+tree[tree[x].child[1]].size+tree[x].mul; return 0;}

long rot(long x){
  long y=tree[x].parent;
  long state=tree[x].state;
  if (y==root) { root=x; tree[x].parent=0; } else put(tree[y].parent,x,tree[y].state);
  long t=put(y,tree[x].child[state^1],state)+put(x,y,state^1)+update(y); return 0;
}

long splay(long x,long r){
  long p=tree[x].parent;
  while (p!=r){ long t=((tree[p].parent==r)?rot(x):(tree[x].state=tree[p].state)?rot(p)+rot(x):rot(x)+rot(x))+update(x); return 0; }
}

long find(long x){
  long i=root;
  while (true){
	if (tree[i].key==x) break;
	i=tree[i].child[tree[i].key>x];
  }
  return i;
}

long inset(long k){
  if (!root){
	tree[n].size=tree[++n].mul=1;
	root=n;
	return 0;
  }
  long i=root;
  while (true) {
	tree[i].size++;
	if (tree[i].key==k) { tree[i].mul++; splay(i,0); return 0; }
	long j=tree[i].child[k>tree[i].key];
	if (!j) break; else i=j;
	tree[n].size=tree[++n].mul=1;
	put(i,n,k>tree[i].key);
	splay(n,0);
  }
}

long pred_succ(long state){
  long i=tree[root].child[state];
  if (!i) return 0;
  while (tree[i].child[state^1]) i=tree[i].child[state^1];
  return i;
}

long delte(long x){
  if (tree[x].mul>1) { tree[x].mul--; return 0; }
  splay(x,0);
  long y1=pred_succ(1);
  long y2=pred_succ(0);
  if (!y1) { root=tree[x].child[0]; tree[root].parent=0; } else
  if (!y2) { root=tree[x].child[1]; tree[root].parent=0; } else {
	splay(y2,0);
	splay(y1,root);
	tree[x].parent=0;
	tree[y1].child[tree[x].state]=0;
	update(y1);
	update(root);
  }
}

long find_kth(long k){
  long i=root;
  while (true) {
	long s=tree[tree[i].child[0]].size;
	long m=tree[i].mul;
	if (k<=s) i=tree[i].child[0]; else
	if (k<=s+m) return tree[i].key; else{
	  k-=s+m;
	  i=tree[i].child[1];
	}
  }
}

long rank(long x){
  splay(x,0);
  return tree[tree[x].child[0]].size+1;
}

int main()
{
  file_put();

  return 0;
}

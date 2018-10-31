#include <cstdio>
using namespace std;
const int maxint=~0U>>1;

struct node{
	int key,size;
	node *c[2];
	node():key(0),size(0){c[0]=c[1]=this;}
	node(int key_,node* c0_,node* c1_):
	key(key_){c[0]=c0_;c[1]=c1_;}
	node* rz(){return size=c[0]->size+c[1]->size+1,this;}
} Tnull,*null=&Tnull;

struct splay{
	node *root;
	splay(){
		root=(new node(*null))->rz();
		root->key=maxint;
	}

	void zig(bool d){
		node *t=root->c[d];
		root->c[d]=null->c[d];
		null->c[d]=root;
		root=t;
	}

	void zigzig(bool d){
		node *t=root->c[d]->c[d];
		root->c[d]->c[d]=null->c[d];
		null->c[d]=root->c[d];
		root->c[d]=null->c[d]->c[!d];
		null->c[d]->c[!d]=root->rz();
		root=t;
	}

	void finish(bool d){
		node *t=null->c[d],*p=root->c[!d];
		while(t!=null)
		{
			t=null->c[d]->c[d];
			null->c[d]->c[d]=p;
			p=null->c[d]->rz();
			null->c[d]=t;
		}
		root->c[!d]=p;
	}

	void select(int k)
	{
		int t;
		for(;;)
		{
			bool d=k>(t=root->c[0]->size);
			if(k==t||root->c[d]==null)break;
			if(d)k-=t+1;
			bool dd=k>(t=root->c[d]->c[0]->size);
			if(k==t||root->c[d]->c[dd]==null){zig(d);break;}
			if(dd)k-=t+1;
			d!=dd?zig(d),zig(dd):zigzig(d);
		}
		finish(0),finish(1);
		root->rz();
	}

	void search(int x)
	{
		for(;;)
		{
			bool d=x>root->key;
			if(root->c[d]==null)break;
			bool dd=x>root->c[d]->key;
			if(root->c[d]->c[dd]==null){zig(d);break;}
			d!=dd?zig(d),zig(dd):zigzig(d);
		}
		finish(0),finish(1);
		root->rz();
		if(x>root->key)select(root->c[0]->size+1);
	}

	void ins(int x)
	{
		search(x);node *oldroot=root;
		root=new node(x,oldroot->c[0],oldroot);
		oldroot->c[0]=null;
		oldroot->rz();
		root->rz();
	}

	void del(int x)
	{
		search(x);
		node *oldroot=root;
		root=root->c[1];
		select(0);
		root->c[0]=oldroot->c[0];
		root->rz();
		delete oldroot;
	}

	int sel(int k){return select(k-1),root->key;}
	int ran(int x){return search(x),root->c[0]->size+1;}
} sp;

int main()
{
	for(;;)
	{
		char cmd;
		int num;
		scanf(" %c%d",&cmd,&num);
		switch(cmd)
		{
		case'i':sp.ins(num);break;
		case'd':sp.del(num);break;
		case's':printf("%d\n",sp.sel(num));break;
		case'r':printf("%d\n",sp.ran(num));break;
		}
	}
}
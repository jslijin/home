struct LTNode{
	int data,dist; LTNode *l,*r;
	LTNode(int x=0) : l(NULL),r(NULL),data(x),dist(0) {}
};

void print(LTNode *t){
	if (t==NULL) return;
	print(t->l);
	printf("%d\n",t->data);
	print(t->r);
}

LTNode* merge(LTNode* &A,LTNode* &B){
	if(A==NULL || B==NULL) return A==NULL?B:A;
	if(A->data > B->data) swap<LTNode*>(A,B);
	A->r = merge(A->r,B);
	if(A->l==NULL || A->r->dist > A->l->dist) swap<LTNode*>(A->l,A->r);
	if(A->r==NULL) A->dist = 0; else A->dist = A->r->dist + 1;
	return A;
}

void insert(LTNode *&t,int x){
	LTNode *p = new LTNode(x);
	t = merge(t,p);
}

LTNode* ExtractMin(LTNode* &t){  
	LTNode *p = t;
	t = merge(t->l,t->r);
	return p;
}

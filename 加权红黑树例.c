#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//long count=0;
//int flag=0;
typedef struct RBTNode
{
	long key;
	struct RBTNode *parent,*left,*right;
	int color;
	long size;
}RBTNode,*RBTree;

RBTree nil,root;


void InitLeafNode()
{
	nil=(RBTree)malloc(sizeof(RBTNode));
	root=(RBTree)malloc(sizeof(RBTNode));
	nil->color=1;
	nil->parent=nil;
	nil->left=nil;
	nil->right=nil;
	nil->key=-1;
	nil->size=0;
	root=nil;
}

RBTree CreateNode(long key,int color)
{
	RBTree x=(RBTNode*)malloc(sizeof(RBTNode));
	x->color=color;
	x->key=key;
	x->left=nil;
	x->right=nil;
	x->parent=NULL;
	x->size=1;
	return x;
}

void LeftRotate(RBTree T,RBTree x)
{
	RBTree y=(RBTree)malloc(sizeof(RBTNode));
	y=x->right;
	x->right=y->left;
	if(y->left!=nil)
	{
		y->left->parent=x;
	}
	y->parent=x->parent;
	if(x->parent==nil)
	{
		root=y;
	}
	else if (x==x->parent->left)
	{
		x->parent->left=y;
	}
	else
	{
		x->parent->right=y;
	}
	y->left=x;
	x->parent=y;
	y->size=x->size;
	x->size=x->right->size+x->left->size+1;
}

void RightRotate(RBTree T,RBTree x)
{
	RBTree y=(RBTree)malloc(sizeof(RBTNode));
	y=x->left;
	x->left=y->right;
	if(y->right!=nil)
	{
		y->right->parent=x;
	}
	y->parent=x->parent;
	if(x->parent==nil)
	{
		root=y;
	}
	else if (x==x->parent->left)
	{
		x->parent->left=y;
	}
	else
	{
		x->parent->right=y;
	}
	y->right=x;
	x->parent=y;
	y->size=x->size;
	x->size=x->right->size+x->left->size+1;
}

void RBTreeInsertFixup(RBTree T,RBTree z)
{
	RBTree y=(RBTree)malloc(sizeof(RBTNode));
	while(z->parent->color == 0)
	{
		if(z->parent==z->parent->parent->left)
		{
			y=z->parent->parent->right;
			if(y->color==0)
			{
				z->parent->color=1;
				y->color=1;
				z->parent->parent->color=0;
				z=z->parent->parent;
			}
			else
			{if(z==z->parent->right)
			 {
				z=z->parent;
				LeftRotate(T,z);
			 }
			z->parent->color=1;
			z->parent->parent->color=0;
			RightRotate(T,z->parent->parent);
			}
		}
		else
		{
			y=z->parent->parent->left;
			if(y->color==0)
			{
				z->parent->color=1;
				y->color=1;
				z->parent->parent->color=0;
				z=z->parent->parent;
			}
			else
			{
				if(z==z->parent->left)
				{
					z=z->parent;
					RightRotate(T,z);
				}
				z->parent->color=1;
				z->parent->parent->color=0;
				LeftRotate(T,z->parent->parent);
			}
		}
	}
	root->color=1;
}

void TreeInsert(RBTree T,RBTree z)
{
	RBTree x=(RBTree)malloc(sizeof(RBTNode));
	RBTree y=(RBTree)malloc(sizeof(RBTNode));
	y=nil;
	x=root;
	while(x!=nil)
	{
		y=x;
		if(z->key<x->key)
		{
			x=x->left;
		}
		else
		{
			x=x->right;
		}
	}
	z->parent=y;
	if(y==nil)
	{
		root=z;
	}
	else
	{
		if(z->key<y->key)
		{
			y->left=z;
			while(z!=root)
	             {
		          z->parent->size=z->parent->right->size+z->parent->left->size+1;
		          z=z->parent;
	             }
		}
		else
		{
			y->right=z;
			    while(z!=root)
	             {
		          z->parent->size=z->parent->right->size+z->parent->left->size+1;
		          z=z->parent;
	             }
		}
	}
}

void RBTreeInsert(RBTree T,RBTree z)
{
	TreeInsert(T,z); 
	z->left=nil;
	z->right=nil;
	z->color=0;
	RBTreeInsertFixup(T,z);
}

RBTree TreeMinimum(RBTree x)
{
	while(x->left!=nil)
	{
		x=x->left;
	}
	return x;
}

void RBDeleteFixup(RBTree T,RBTree x)
{
	RBTree w=(RBTree)malloc(sizeof(RBTNode));
	while(x!=root&&x->color==1)
	{
		if(x==x->parent->left)
		{
			w=x->parent->right;
			if(w->color==0)
			{
				w->color=1;
				x->parent->color=0;
				LeftRotate(T,x->parent);
				w=x->parent->right;
			}
			if(w->left->color==1&&w->right->color==1)
			{
				w->color=0;
				x=x->parent;
			}
			else{
				if(w->right->color==1)
				{
					w->left->color=1;
					w->color=0;
					RightRotate(T,w);
					w=x->parent->right;
				}
				w->color=x->parent->color;
				x->parent->color=1;
				w->right->color=1;
				LeftRotate(T,x->parent);
				x=root; 
			}
		}
		else{
			w=x->parent->left;
			if(w->color==0)
			{
				w->color=1;
				w->parent->color=0;
				RightRotate(T,x->parent);
				w=x->parent->left;
			}
			if(w->left->color==1&&w->right->color==1)
			{w->color=0;
			 x=x->parent;
			}
			else{
				if(w->left->color==1)
				{
					w->right->color=1;
					w->color=0;
					LeftRotate(T,w);
					w=x->parent->left; 
				}
				w->color=x->parent->color;
				x->parent->color=1;
				w->left->color=1;
				RightRotate(T,x->parent);
				x=root;
			}
		}
	}
	x->color=1; 
}

/*void RBTreesizefixup(RBTree z)
{
	RBTree r=(RBTree)malloc(sizeof(RBTNode));
	RBTree y=(RBTree)malloc(sizeof(RBTNode));
	if(z->left==nil||z->right==nil)
	{
		while(z!=root)
	    {
		z->parent->size=z->parent->size-1;
		z=z->parent;
	    }
	}
	else if (z->right->left==nil)
	{
	    z->right->size=z->right->right->size+z->left->size+1;
		while(z!=root)
	    {
		z->parent->size=z->parent->size-1;
		z=z->parent;
	    }
	}
	else{
		r=z->right;
		y=r->left;
		while(y->left!=nil)
		{y=y->left;}
		y->size=z->left->size+z->right->size;
		while(y!=r)
		{
		y->parent->size=y->parent->size-1;
		y=y->parent;
	    }
	}
}*/ 

void RBTRANSPLANT(RBTree T,RBTree u,RBTree v)
{   
	if(u->parent==nil)
	{
		root=v;
	}
	else if(u==u->parent->left)
	{
		u->parent->left=v;
	}
	else 
	{
	    u->parent->right=v;
	}
	v->parent=u->parent;
}

void RBTreeDelete(RBTree T,RBTree z)
{   
    RBTree x=(RBTree)malloc(sizeof(RBTNode));
	RBTree y=(RBTree)malloc(sizeof(RBTNode));
	RBTree w=(RBTree)malloc(sizeof(RBTNode));
	y=z;
	int y_original_color=y->color;
	if(z->left==nil)
	{
		w=z;
		while(w!=root)
	    {
		w->parent->size=w->parent->size-1;
		w=w->parent;
	    }
		x=z->right;
		RBTRANSPLANT(T,z,z->right);	
	}
	else if(z->right==nil)
	{
		w=z;
		while(w!=root)
	    {
		w->parent->size=w->parent->size-1;
		w=w->parent;
	    }
		x=z->left;
		RBTRANSPLANT(T,z,z->left);
	}
	else{
	    y=TreeMinimum(z->right);
	    w=z;
		while(w->parent!=nil)
		{w->parent->size=w->parent->size-1;
		 w=w->parent;
		}
		y->size=z->left->size+z->right->size;
		if(y->parent!=z){
			z->right->size=z->right->size-1;
			w=y;
			while(w->parent!=z->right)
		   {w->parent->size=w->parent->size-1;
		    w=w->parent;
		   }
		}
		y_original_color=y->color;
		x=y->right;
		if(y->parent==z)
		{x->parent=y;}
		else 
		{RBTRANSPLANT(T,y,y->right);
		 y->right=z->right;
		 y->right->parent=y;
		}
		RBTRANSPLANT(T,z,y);
		y->left=z->left;
		y->left->parent=y;
		y->color=z->color;
	}
	if(y_original_color==1)
	{
		RBDeleteFixup(T,x);
	}
}

RBTree TreeNodeSearch(RBTree x,long key)
{
	while(x!=nil&&key!=x->key)
	{
		if(key<x->key)
		 {x=x->left;} 
		else
		 {x=x->right;}
	}
	//RBTreesizefixup(x);
	return x;
}

RBTree OS_SELECT(RBTree x,long i)
{
 	long r=x->left->size+1;
	if(i==r)
	{return x;}
	else if(i<r)
	{return OS_SELECT(x->left,i);}
	else return OS_SELECT(x->right,i-r); 
}
/*static void inorder(RBTree tree,long b)
{   
    if(tree == nil||flag==1)return ;
        inorder(tree->left,b);
        count++;
		if(count==b)
		{printf("%ld\n",tree->key); flag=1;}
        inorder(tree->right,b);
} */
int main()
{
    RBTree node,find,t;
	long n=0;
	InitLeafNode();
	scanf("%ld",&n);
	long key=0;
	long i;
	char c;
    for(i=0;i<n;i++){ 
    	getchar();
    	c=getchar();
    	if(c=='I') {scanf("%ld",&key);node=CreateNode(key,0);RBTreeInsert(root,node);}
		else if (c=='D') {scanf("%ld",&key); find=TreeNodeSearch(root,key);RBTreeDelete(root,find);}
		else if (c=='K') {/*flag=0;count=0;*/scanf("%ld",&key);t=OS_SELECT(root,key);printf("%ld\n",t->key);/*inorder(root,key);*/}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void initTree(AVLTree *t)
{
	t->p = 0;
	int i;
	for(i=0;i< 32 ;i++)
	{
		t->roadPath[i] = NULL;
	}
};

int searchElem(AVLTree *t,int value)
{
	printf("start to search:\n");
	initTree(t);
	Node *h = t->head;
	int bReturn = 0;
	while(h != NULL)
	{
		t->roadPath[t->p] = h;
		printf("p:%d,value:%d\n",t->p,t->roadPath[t->p]->val);
		if(h->val == value)
	    {
			bReturn = 1;
			break;
		}
		else if(h->val > value)
		 	h = h->lc;
	 	else
			h = h->rc;
		t->p++;
	}
	h = NULL;
	printf("end search\n");
	return bReturn;
};

Node* LL(Node* t)
{
	Node *n = t->lc;
	t->lc->bf = t->bf = n->lc->bf = 0;
	t->lc = n->rc;
	n->rc = t;
	return n;
}

Node* LR(Node* t)
{
	Node *n = t->lc->rc;
	if(n->bf == 1)
	{	
		t->lc->bf = 0;
		t->bf = -1;
	}
	else if(n->bf == -1)
	{
		t->lc->bf = 1;
		t ->bf = 0;
	}
	else
	{
		t->lc->bf = 0;
		t->bf = 0;
	}
	n->bf = 0;
	t->lc->rc = n->lc;
	n->lc = t->lc;
	t->lc = n->rc;
	n->rc = t;
	return n;
}

Node* RR(Node *t)
{
	Node *n = t->rc;
	n->bf = t->bf = n->rc->bf = 0;
	t->rc = n->lc;
	n->lc = t;
	return n;
}


Node* RL(Node* t)
{
	Node *n = t->rc->lc;
	if(n->bf == 1)
	{	
		t->rc->bf = -1;
		t->bf = 0;
	}
	else if(n->bf == -1)
	{
		t->rc->bf = 0;
		t->bf = 1;
	}
	else
	{
		t->rc->bf = 0;
		t->bf = 0;
	}
	n->bf = 0;
	t->rc->lc = n->rc;
	n->rc = t->rc;
	t->rc = n->lc;
	n->lc = t;
	return n;
}

void rotateSubTree(AVLTree *t,int bf,int pos)
{
	Node *n = NULL;
	if(bf == 2)
	{
		if(t->roadPath[pos+1]->bf == 1 || t->roadPath[pos+1]->bf == 0)
			n = LL(t->roadPath[pos]);
		else
			n = LR(t->roadPath[pos]);
	}
	else
	{
		if(t->roadPath[pos+1]->bf == -1 || t->roadPath[pos+1]->bf == 0)
			n = RR(t->roadPath[pos]);
		else
			n = RL(t->roadPath[pos]);
	}
	if(pos == 0)
		t->head = n;
	else
		if(t->roadPath[pos]->val > t->roadPath[pos-1]->val)
			t->roadPath[pos-1]->rc = n;
		else
			t->roadPath[pos-1]->lc = n;
};

void rebuildBf(AVLTree *t,int deleteFlag)
{
	int p = t->p;
	while(p>0){
		printf("value:%d,bf:%d,change bf to:",t->roadPath[p-1]->val,t->roadPath[p-1]->bf);
		if(t->roadPath[t->p]->val > t->roadPath[p-1]->val)
			deleteFlag == 0 ? t->roadPath[p-1]->bf-- : t->roadPath[p-1]->bf++;
		else 
			deleteFlag == 0 ? t->roadPath[p-1]->bf++ : t->roadPath[p-1]->bf--;
		printf("%d\n",t->roadPath[p-1]->bf);
		
		if(deleteFlag == 0)
		{
			if(t->roadPath[p-1]->bf == 0)
				break;
		}
		else
		{
			if(t->roadPath[p-1]->bf == 1 || t->roadPath[p-1]->bf == -1)
				break;
		}
		if(t->roadPath[p-1]->bf == 2 || t->roadPath[p-1]->bf == -2)
		{
			printf("need to rotate tree!\n");
			rotateSubTree(t,t->roadPath[p-1]->bf,p-1);
			break;
		}
		p--;
	}
};

int insertElem(AVLTree *t,int value)
{
	printf("Are you sure to add elem:%d? y/n:",value);
	char c;
    while(scanf("%c",&c))
	{
		if(c == 110)
			exit(0);
		else 
		{
			if(c == 121)
				break;
		}
	}
	/*printf("ready to add value:%d\n",value);*/
	if(searchElem(t,value) == 1)
	{
		printf("this elem is already exist in tree\n\n");
		return 0;
	}
	Node *n = malloc(sizeof(Node));
	n->val = value;
	n->lc = n->rc = NULL;
	n->bf = 0;	

	if(t->len == 0)
	{
		t->head = n;
		printf("the tree is null,add first elem! head value:%d\n\n",t->head->val);
	}
	else
	{
		if(value > t->roadPath[t->p-1]->val)
			t->roadPath[t->p-1]->rc = n;
		else
			t->roadPath[t->p-1]->lc = n;
		t->roadPath[t->p] = n;
		n = NULL;
		rebuildBf(t,0);
		printf("add value success:%d,p:%d\n\n",value,t->p);
	}
	t->len++;
	return 1;
};

int getPreNode(AVLTree *t)
{
	Node *h = t->roadPath[t->p];
	printf("start to get pre node\n");
	if(h->lc != NULL)
	{
		h = h->lc;
		t->p++;
		t->roadPath[t->p] = h;
		printf("has left pre node,left child,p:%d,value:%d\n",t->p,h->val);
		while(h->rc != NULL)
		{
			t->p++;
			t->roadPath[t->p] = h;
			printf("p:%d,value:%d",t->p,h->val);
			h = h->rc;
		}
		return 1;
	}
	else if(h->rc != NULL)
	{
		h = h->rc;
		t->p++;
		t->roadPath[t->p] = h;
		printf("has right pre node,left child,p:%d,value:%d\n",t->p,h->val);
		while(h->lc != NULL)
		{
			t->p++;
			t->roadPath[t->p] = h;
			printf("p:%d,value:%d",t->p,h->val);
			h = h->lc;
		}
		return 2;
	}
	else
		return 0;
}

int deleteElem(AVLTree *t,int value)
{
	printf("Are you sure to delete elem:%d:y/n\n",value);
	char c;
    while(scanf("%c",&c))
	{
		if(c == 110)
			exit(0);
		else 
		{
			if(c == 121)
				break;
		}
	}
	if(searchElem(t,value) == 0)
	{
		printf("delete failed,this elem doesn't exist in the tree!\n\n")		;
		return 0;
	}
	int pos = t->p;
	int flag = getPreNode(t);
	printf("end get pre node\n");
	int p = t->p;
	if(flag == 0)
	{
		printf("can't get pre Node\n");
		if(p == 0)
			t->head = NULL;
		else
		{
			t->roadPath[p]->val > t->roadPath[p-1]->val?(t->roadPath[p-1]->rc = NULL):(t->roadPath[p-1]->lc = NULL);
		}
	}
	else
	{
		printf("get pre Node,value:%d\n",t->roadPath[p]->val);
		if(flag == 1)
		{
			t->roadPath[p-1]->val > t->roadPath[p] ->val?(t->roadPath[p-1]->lc = t->roadPath[p]->lc):(t->roadPath[p-1]->rc = t->roadPath[p]->lc);
		}
		else
		{
			t->roadPath[p-1]->val > t->roadPath[p] ->val?(t->roadPath[p-1]->lc = t->roadPath[p]->rc):(t->roadPath[p-1]->rc = t->roadPath[p]->rc);
		}
	}
	t->len--;
	rebuildBf(t,1);
	if(flag > 0)
		t->roadPath[pos]->val = t->roadPath[p]->val;
	free(t->roadPath[p]);
	printf("delete value:%d success,tree len:%d\n\n",value,t->len);
	return 1;
}

int main()
{
	AVLTree *t = (AVLTree*)malloc(sizeof(AVLTree));
	if(t == NULL){
		printf("out of memory!\n");
		exit(0);
	}
	insertElem(t,8);
	deleteElem(t,8);
	insertElem(t,8);
	insertElem(t,3);
	insertElem(t,1);
	deleteElem(t,3);
	insertElem(t,3);
	insertElem(t,12);
	insertElem(t,10);
	deleteElem(t,12);
	insertElem(t,12);
	insertElem(t,15);
	insertElem(t,10);
	insertElem(t,3);
	insertElem(t,5);
	free(t);
	return 1;
}

#ifndef AVL_H
#define AVL_H

typedef struct Node{
	int val;
	struct Node *lc;
	struct Node *rc;
	int bf;
} Node;

typedef struct AVLTree{
	Node *head;
	int len;
	Node *roadPath[32];
	int p;
} AVLTree;

#endif

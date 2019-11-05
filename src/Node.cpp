#include "Node.h"

Node* NewNode(char c, int f, Node* l, Node* r)
{
	Node* n = new Node();
	n->c = c;
	n->f = f;
	n->left = l;
	n->right = r;
	return n;
}
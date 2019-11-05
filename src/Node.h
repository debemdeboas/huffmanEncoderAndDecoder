#pragma once

/* Struct declarations */

/**
*  A simple Node structure
*/
struct Node
{
	/* The char it represents */
	char c;
	/* Pointer to this Node's left Node */
	Node* left;
	/* Pointer to this Node's rigth Node */
	Node* right;
	/* This Node's char's corresponding frequency of appearance */
	unsigned int f;
};

/* Procedure declarations */

Node* NewNode(char, int, Node*, Node*);
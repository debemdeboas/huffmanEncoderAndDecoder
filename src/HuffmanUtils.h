#pragma once
#include "Node.h"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <algorithm>

/*-----------------------------------------------------------------------------*/
/* Record declarations */

/* Comparison struct used in ordering the heap by frequency (ascending) */
struct Comparator
{
	/* This function returns true if the frequency of the left node is bigger
	   than the frequency of the right node, false otherwise.
	*/
	bool operator()(Node* l, Node* r);
};

/*-----------------------------------------------------------------------------*/
/* Procedure declarations */

/* Prints the Heap */
void PrintHeap(std::priority_queue<Node*, std::vector<Node*>, Comparator>);
#include "HuffmanUtils.h"

using std::priority_queue;
using std::vector;
using std::cout;
using std::endl;

bool Comparator::operator()(Node* l, Node* r) { return l->f > r->f; }

void PrintHeap(priority_queue<Node*, vector<Node*>, Comparator> Heap)
{
	Node* n = nullptr;
	cout << "Heap size: " << Heap.size() << endl;
	while (!Heap.empty())
	{
		n = Heap.top();
		cout << n->c << ": " << n->f << '\n';
		Heap.pop();
	}
}
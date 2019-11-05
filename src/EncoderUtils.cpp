#include "EncoderUtils.h"

using std::ifstream;
using std::ofstream;
using std::priority_queue;
using std::string;
using std::unordered_map;
using std::vector;

void ReadFileData(string filename, unordered_map<char, int>& Dictionary)
{
	ifstream in(filename, std::ios::in);

	char c;
	while (in.get(c))
		Dictionary[c]++;

	in.close();
}

unordered_map<char, int> ReadFileDataEx(const string f)
{
	std::unordered_map<char, int> d;
	ReadFileData(f, d);
	return d;
}

Node* ConstructHuffmanTree(unordered_map<char, int>& Dictionary)
{
	/*
	   MinHeap that holds Nodes ordered by the Comparator struct.
	   The heap was declared in this way because the default priority
	   queue in C++20 is a MaxHeap.
	*/
	priority_queue<Node*, vector<Node*>, Comparator> Heap;

	/* Add all characters to the priority queue as Nodes */
	for (auto pair : Dictionary)
	{
		Heap.push(
			NewNode(
				pair.first,
				pair.second,
				nullptr,
				nullptr
			)
		);
	}

	/* While there is more than one Node in the queue, merge the two lowest priority nodes into one */
	while (Heap.size() > 1)
	{
		/*
		   As there is no native ExtractMin() Heap operation, the way to extract
		   the highest priority member of a queue is by calling .top() followed by .pop().
		*/
		Node* left = Heap.top(); Heap.pop();
		Node* right = Heap.top(); Heap.pop();
		Heap.push(
			NewNode(
				0,
				left->f + right->f,
				left,
				right
			)
		);
	}

	/* Returns the root of the Huffman Tree */
	return Heap.top();
}

Node* ConstructHuffmanTreeWithVector(unordered_map<char, int>& Dictionary)
{
	vector<Node*> Array;

	for (auto pair : Dictionary)
	{
		Array.push_back(
			NewNode(
				pair.first,
				pair.second,
				nullptr,
				nullptr
			)
		);
	}

	std::sort(Array.begin(), Array.end(), Comparator());

	while (Array.size() > 1)
	{
		Node* left = Array.front(); Array.erase(Array.begin());
		Node* right = Array.front(); Array.erase(Array.begin());

		Array.push_back(
			NewNode(
				0,
				left->f + right->f,
				left,
				right
			)
		);

		std::sort(Array.begin(), Array.end(), Comparator());
	}

	return Array.front();
}

unordered_map<char, string> Encode(Node* root)
{
	unordered_map<char, string> HuffmanEncodingTable;
	__encode(root, "", HuffmanEncodingTable);
	return HuffmanEncodingTable;
}

void __encode(Node* n, string code, unordered_map<char, string>& dict)
{
	/* Invalid node -> end recursion */
	if (!n)
		return;
	/* Leaf node -> encode */
	else if (!(n->left) && !(n->right))
		dict[n->c] = code;

	__encode(
		n->left,
		code + '0',
		dict
	);

	__encode(n->right,
		code + '1',
		dict
	);
}

void WriteSymbolTable(std::unordered_map<char, std::string>& HuffmanTable, std::string filename)
{
	filename = "SYMBOLTABLE_" + filename;

	/* Symbol table file (binary) */
	ofstream CompressionTableFile(filename, std::ios::out);

	/* Could not open file! */
	if (!CompressionTableFile)
	{
		std::cerr << "***Error*** WriteSymbolTable: Could not open file. File: " << filename;
		exit(EXIT_FAILURE);
	}

	for (auto&& pair : HuffmanTable)
	{
		CompressionTableFile << (int)pair.first << "=" << pair.second << '\n';
	}

	std::cout << "WriteSymbolTable: Symbol table has been written to " << filename << std::endl;
	CompressionTableFile.close();
}

void CompressFile(unordered_map<char, string>& HuffmanTable, string filename)
{
	/*
		Since the 'WriteSymbolTable' procedure and this procedure are
		independent from each other, 'WriteSymbolTable' can be executed
		by another thread safely.
	*/
	std::thread t(WriteSymbolTable, std::ref(HuffmanTable), filename);

	ofstream CompressedFile("ENC_" + filename + ".bin", std::ios::out | std::ios::binary);
	ifstream OriginalFile(filename);

	/* Could not open file! */
	if (!CompressedFile)
	{
		std::cerr << "***Error*** CompressFile: Could not open file. File: " << "ENC_" + filename + ".binary";
		exit(EXIT_FAILURE);
	}

	/* Could not open file! */
	if (!OriginalFile)
	{
		std::cerr << "***Error*** CompressFile: Could not open file. File: " << filename;
		exit(EXIT_FAILURE);
	}

	/*
		Byte buffer to be written to the file, effectively
		compressing it to around half of its original size.
	*/
	vector<unsigned char> buff;
	string line, code;
	while (getline(OriginalFile, line))
	{
		for (char& c : line)
		{
			code += HuffmanTable[c];
		}
		AddStringToByteBuffer(code, buff);
	}

	if (code.size() % 8)
	{
		code += string(abs((int)code.size() - 8), '0');
		AddStringToByteBuffer(code, buff);
	}

	CompressedFile.write((char*)&buff[0], buff.size());
	CompressedFile.close();
	std::cout << "CompressFile: File compressed." << std::endl;
	t.join();
}

void AddStringToByteBuffer(std::string& str, std::vector<unsigned char>& Buffer)
{
	unsigned char cBytes = 0;
	int s = 0;
	for (unsigned int ByteCount = 1; s < ((int)str.size() / 8) * 8; s++)
	{
		if ((s > 0) && !(s % 8))
		{
			Buffer.push_back(cBytes);
			cBytes = 0;
			++ByteCount;
		}

		if (str[s] == '1')
			cBytes |= (1 << ((8 * ByteCount - 1) - s));
	}
	str = str.substr(str.size() - s, str.size() - s);
	Buffer.push_back(cBytes);
}

void EncodeFile(std::unordered_map<char, std::string>& HuffmanTable, std::string filename)
{
	/*
		Since the 'WriteSymbolTable' procedure and this procedure are
		independent from each other, 'WriteSymbolTable' can be executed
		by another thread safely.
	*/
	std::thread t(WriteSymbolTable, std::ref(HuffmanTable), filename);

	ofstream EncodedFile("ENC_NOT_COMPRESSED_" + filename, std::ios::out);
	ifstream OriginalFile(filename);

	/* Could not open file! */
	if (!EncodedFile)
	{
		std::cerr << "***Error*** EncodeFile: Could not open file. File: " << "ENC_NOT_COMPRESSED_" + filename;
		exit(EXIT_FAILURE);
	}

	/* Could not open file! */
	if (!OriginalFile)
	{
		std::cerr << "***Error*** EncodeFile: Could not open file. File: " << filename;
		exit(EXIT_FAILURE);
	}

	char c;
	while (OriginalFile.get(c))
		EncodedFile << HuffmanTable[c];

	EncodedFile.close();
	std::cout << "EncodeFile: File encoded." << std::endl;
	t.join();
}
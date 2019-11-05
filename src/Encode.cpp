#include "EncoderUtils.h"
#include <string>
#include <chrono>

const std::string filename = "king_james.txt";

using namespace std::chrono;

int main()
{
	auto FrequencyMap = ReadFileDataEx(filename);

	auto startVect = high_resolution_clock::now();
	ConstructHuffmanTreeWithVector(FrequencyMap);
	auto stopVect = high_resolution_clock::now();

	auto startPQ = high_resolution_clock::now();
	auto pqAux = ConstructHuffmanTree(FrequencyMap);
	auto stopPQ = high_resolution_clock::now();

	auto durationVect = duration_cast<microseconds>(stopVect - startVect);
	auto durationPQ = duration_cast<microseconds>(stopPQ - startPQ);

	std::cout << "--- Elapsed execution times for std::vector and std::priority_queue ---" << std::endl
		<< "Vector: " << durationVect.count() << " microseconds" << std::endl
		<< "Priority queue: " << durationPQ.count() << " microseconds" << std::endl;

	/*
		Since I couldn't figure out a way to make this work, this function has been left out.
	*/
	//CompressFile(Table, filename);

	auto Tree = Encode(pqAux);
	EncodeFile(Tree, filename);
	
	return 0;
}
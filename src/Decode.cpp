#include "DecoderUtils.h"
#include <string>

#ifdef __linux__
	std::string filename = "king_james_UNIX.txt";
#else
	std::string filename = "king_james.txt";
#endif

int main()
{
	//UncompressFile(filename);

	DecodeFile(filename);
	return 0;
}
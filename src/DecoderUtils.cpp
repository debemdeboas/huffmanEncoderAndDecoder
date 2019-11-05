#include "DecoderUtils.h"

using std::string;
using std::unordered_map;
using std::ofstream;
using std::ifstream;

unordered_map<string, char> ReadSymbolTable(string f)
{
	unordered_map<string, char> dic;
	f = "SYMBOLTABLE_" + f;

	ifstream sTable(f, std::ios::in | std::ios::binary);

	string line;
	while (getline(sTable, line))
	{
		DecodeLine(line, dic);
	}
	return dic;
}

void DecodeLine(string l, unordered_map<string, char>& dic)
{
#ifdef _WIN32
	int line_end = 2;
#else
	int line_end = 1;
#endif
	string strFirst = l.substr(l.find_last_of('=') + 1, l.length() - l.find_last_of('=') - line_end);
	string strSecond = l.substr(0, l.find_last_of('='));

	dic[strFirst] = (char)std::stoi(strSecond);
}

void UncompressFile(string filename)
{
	unordered_map<string, char> SymbolTable = ReadSymbolTable(filename);

	ifstream encFile("ENC_" + filename + ".bin", std::ios::in | std::ios::binary);

	ofstream outFile("DEC_" + filename, std::ios::out);

	std::vector<unsigned char> buff;
	string line;
	while (getline(encFile, line))
	{
		for (char& c : line)
		{
			buff.push_back(c);
		}
	}

	string code, decodedString;
	for (unsigned char& c : buff)
	{
		code += c;
		TryDecodeChars(code, SymbolTable, decodedString);
	}
}

void TryDecodeChars(string& code, unordered_map<string, char>& dic, string& out)
{
	/* currently not working as intended (or not working at all) */


	string aux;
	for (char& byte : code)
	{
		aux += StringFromByte(byte);

		if (dic.find(aux) != dic.end())
		{
			out += dic[aux];
			code.erase(0);
		}
	}
}

string StringFromByte(char c)
{
	/* currently not working as intended (or not working at all) */


	bool b[8];
	for (int i = 0; i < 8; i++)
	{
		b[i] = (c & (1 << i)) != 0;
	}
	string result;
	for (int i = 0; i < 8; i++)
		result += '1' ? b[i] : '0';
	return result;
}

void DecodeFile(string filename)
{
	/* Huffman Symbol Table used to decode the encoded file */
	unordered_map<string, char> SymbolTable = ReadSymbolTable(filename);

	/* Simple encoded file */
	ifstream EncFile("ENC_NOT_COMPRESSED_" + filename, std::ios::in | std::ios::binary);

	/* Decoded file pointer */
	ofstream DecFile("DEC_2_" + filename, std::ios::out | std::ios::binary);

	string line, key;
	while (getline(EncFile, line))
	{
		for (char& c : line)
		{
			key += c;
			if (SymbolTable.find(key) != SymbolTable.end())
			{
				DecFile << SymbolTable[key];
				key.clear();
			}
		}
	}
	DecFile.close();

	std::cout << "DecodeFile: File " << filename << " decoded successfuly." << std::endl;
}

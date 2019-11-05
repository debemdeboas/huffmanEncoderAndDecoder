#pragma once
#include "HuffmanUtils.h"
#include <fstream>
#include <vector>

/*-----------------------------------------------------------------------------*/
/* Procedure declarations */

/* Reads the SymbolTable file and loads that Huffman table into memory */
std::unordered_map<std::string, char> ReadSymbolTable(std::string);

/* Decodes a line from the SymbolTable file */
void DecodeLine(std::string, std::unordered_map<std::string, char>&);

/* Uncompressed a binary file using a Huffman Symbol Table */
void UncompressFile(std::string);

/* Tries to decode a byte buffer */
void TryDecodeChars(std::string&, std::unordered_map<std::string, char>&, std::string&);

/* Converts a byte to a string of '1's and '0's */
std::string StringFromByte(char);

/* Decodes a simple encoded file (non-binary) */
void DecodeFile(std::string);
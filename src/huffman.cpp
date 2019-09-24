#ifndef __HUFFMAN_UTILS
#define __HUFFMAN_UTILS
#include <iostream>
#include <fstream>
#include <unordered_map>

/* 
g++ -lstdc++fs -Wall -Werror -Wextra -std=c++17 -pedantic main.cpp -o main 
*/

using namespace std;

void ReadFileData(string FileName, unordered_map<char, int> &Dictionary);

int main()
{
    unordered_map<char, int> Frequencies;
    ReadFileData("./king_james.txt", Frequencies);

    for (auto &&item : Frequencies)
        cout << "[ " << item.first << " ] (" << (int)(item.first) << ")" << " : " << item.second << endl;

    return 0;
}

void ReadFileData(string FileName, unordered_map<char, int> &Dictionary)
{
    ifstream in;
    in.open(FileName);
    string str;
    while(getline(in, str))
    {
        for(char& c : str)
            Dictionary[c]++;
    }
}
#endif

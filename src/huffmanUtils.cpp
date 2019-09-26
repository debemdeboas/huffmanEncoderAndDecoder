#include "huffmanUtils.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

/* 
g++ -lstdc++fs -Wall -Werror -Wextra -std=c++17 -pedantic main.cpp -o main 
*/

using namespace std;

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


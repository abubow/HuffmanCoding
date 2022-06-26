#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<bitset>
#include"helper.h"
using namespace std;

int main(){
	ifstream file("input.txt");
	vector<char> input;
	char ch;
	if(!file.is_open())
	{
		cerr << "File did not open";
		return 0;
	}
	while(file>>ch){
		input.push_back(ch);
	}
	auto counts = wordCount(input);
	for(auto i:counts)
		cout << i.first << " : " <<  bitset<sizeof(char)*8>(i.first) << " : " << i.second << endl;
	auto table = createTable(counts);
	return 0;
}

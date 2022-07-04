#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<bitset>
#include"helper.h"
using namespace std;

int main(){
	cout << "Enter FilePath to Compress: ";
	string name;
	cin >> name;
	cout << "Enter Compressed Name: ";
	string resultName;
	cin >> resultName;
	compress(name, resultName);
	
	return 0;
}

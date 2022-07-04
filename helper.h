#pragma once
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
#include<iostream>
#include<bitset>
#include<unordered_map>
#define MAX_NUMBER_OF_CHRACTERS 256
#define CODES_BITS std::bitset<MAX_NUMBER_OF_CHRACTERS + 2>
#define CB_PAIR std::pair<char, CODES_BITS>
#define FULL_TABLE std::vector<CB_PAIR>
struct Node {
	char first;
	unsigned second;
	Node* left;
	Node* right;
	Node() {
		first = NULL;
		second = 0;
		left = nullptr;
		right = nullptr;
	}
	bool operator>(Node& obj) {
		return second > obj.second;
	}
	bool operator<(Node& obj) {
		return second < obj.second;
	}
	bool operator<=(Node& obj) {
		return second <= obj.second;
	}
};
std::vector<Node*> wordCount(std::vector<char> chars){
	std::vector<Node*> counts;
	bool alreadyExists;
	for(auto i:chars){
		alreadyExists=false;
		for(auto& it:counts){
			if(i==it->first){
				it->second+= 1;
				alreadyExists=true;
				break;
			}
		}
		if(alreadyExists == false)
		{
			Node* res = new Node;
			res->first = i;
			res->second = 1;
			counts.push_back(res);
		}	
        }
	return counts;
}
template<typename type>
void swapV(type& a, type& b) {
	type temp = a;
	a = b;
	b = temp;
}
void insertInHeap(std::vector<Node*>& vec, Node* a) {
	vec.push_back(a);
	for (int i = vec.size() - 1; i > 0;)
	{
		if (vec[i / 2] > vec[i]) {
			swapV(vec[i / 2], vec[i]);
			i = (i / 2);
		}
		else
			break;
	}
}
Node* popFromHeap(std::vector<Node*>& vec) {
	if (!(vec.size() > 1))
		return nullptr;
	Node* value = vec[0];
	vec[0] = vec[vec.size() - 1];
	vec.pop_back();
	for (int i = 0; i < (vec.size() - 1) / 2;)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (*vec[i] > *vec[left] && *vec[left] <= *vec[right]) {
			swapV(vec[i], vec[left]);
			i = left;
		}
		else if (*vec[i] > *vec[right] && *vec[right] <= *vec[left]) {
			swapV(vec[i], vec[right]);
			i = right;
		}
		else break;
	}
	return value;
}
void printHCodes(struct Node* root, int arr[], int top) {
	if (root->left) {
		arr[top] = 0;
		printHCodes(root->left, arr, top + 1);
	}

	if (root->right) {
		arr[top] = 1;
		printHCodes(root->right, arr, top + 1);
	}
	if (root->left==nullptr&&root->right==nullptr) {
		std::cout << root->first << "  | ";
		for (int i = 0; i < top; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
}
void getHCodes(struct Node* root, CODES_BITS codes, int top, FULL_TABLE& table) {
	if (root->left) {
		codes.set(top, 0);
		getHCodes(root->left, codes, top + 1, table);
	}

	if (root->right) {
		codes.set(top, 1);
		getHCodes(root->right, codes, top + 1, table);
	}
	if (root->left == nullptr && root->right == nullptr) {
		CB_PAIR myPair;
		myPair.first = root->first;
		codes.set(top, 1);
		myPair.second = codes;
		table.push_back(myPair);
	}
}
Node* createHuffmanTree(std::vector<Node*> counts) {
	std::sort(counts.begin(), counts.end(),
			[](auto& first, auto& second) {
				return first < second;
			});
	int s = counts.size();
	for (int i = 0; i < s-2; i++)
	{
		Node* top1 = popFromHeap(counts);
		Node* top2 = popFromHeap(counts);
		Node* collective = new Node();
		collective->left = top1;
		collective->right = top2;
		collective->second = top1->second + top2->second;
		insertInHeap(counts, collective);
	}
	std::cout << "Size after tree creation" << counts.size() << " \n";
	Node* res = new Node;
	res->left = counts[0];
	res->right = counts[1];
	return res;
}
FULL_TABLE createTable(std::vector <Node*>& counts) 
{
	FULL_TABLE table;
	Node* huffmanTree = createHuffmanTree(counts);
	/*for (const auto& var : counts)
	{
		std::cout << var->first << " : " << var->second << std::endl;
	}*/
	//int arr[256];
	//int top = 0;
	//printHCodes(huffmanTree, arr, 0);
	std::bitset<MAX_NUMBER_OF_CHRACTERS + 2> codes;
	getHCodes(huffmanTree, codes, 0, table);

	for(auto i : table){
		std::cout << i.first << "|" << i.second << std::endl;
	}
	return table;
}
void compress(std::string filename, std::string resultName) {

	std::ifstream file(filename);
	std::vector<char> input;
	char ch;
	if (!file.is_open())
	{
		std::cerr << "File did not open";
		return;
	}
	while (!file.eof()) {
		ch = file.get();
		input.push_back(ch);
	}
	auto counts = wordCount(input);
	
	std::vector<bool> fileBoleanRepresentation;
	
	auto table = createTable(counts);
	std::unordered_map<char, CODES_BITS> hashtable;
	for (auto i : table) {
		hashtable.insert(make_pair(i.first, i.second));
	}

	for (auto i : input) {
		CODES_BITS x = hashtable[i]; // constant complexity since its a hashmap
		int index = MAX_NUMBER_OF_CHRACTERS + 1;
		bool started = x.test(index);
		for (int j = MAX_NUMBER_OF_CHRACTERS + 1; j >=0; j--) // the loop is of O(1) complexity it always runs a constant number of times
		{
			if (!started) {
				x <<= 1; // shit bits left one time
				started = x.test(index); 
			}
			else {
				fileBoleanRepresentation.push_back(x.test(index--));
			}

		}
	}
	int nChars = (fileBoleanRepresentation.size()) / (sizeof(char) * 8);
	std::cout << "Original Size: " << input.size()*8 << " bits" << std::endl;
	std::cout << "Entropy: " << sizeof(char)*8 << " bits/char" << std::endl;
	std::cout << "Compressed Size: " << (nChars+1) << " bits" << std::endl;
	std::ofstream output(resultName);
	std::bitset<8> bitChar;
	std::string outStr = "";
	double progress;
	for (int i = 0; i < nChars; i++)
	{
		char c = 0;
		for (int j = 0; j < 8; j++)
		{
			bitChar.set(7 - j, fileBoleanRepresentation[j]);
		}
		for (int j = 0; j < 8; j++)
		{
			fileBoleanRepresentation.erase(fileBoleanRepresentation.begin()); // remove the first element from the vector
		}
		outStr += (char)bitChar.to_ulong();
		progress = i / (nChars*1.0);
		std::printf("%f\n", progress);
	}
	output << outStr;
	if ((fileBoleanRepresentation.size()) % sizeof(char)) {
		for (int i = 0; i < 8; i++)
		{
			bitChar.reset();
			for (auto j : fileBoleanRepresentation)
				bitChar.set(7 - j, fileBoleanRepresentation[j]);
			output << (char)bitChar.to_ulong();
		}
	}
	
}
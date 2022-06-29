#pragma once
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
#include<iostream>
#include<bitset>

#define MAX_NUMBER_OF_CHRACTERS 256
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
std::vector <Node*> createTable(std::vector <Node*>& counts) {
	std::vector <Node*> table;
	Node* huffmanTree = createHuffmanTree(counts);
	int arr[256];
	int top = 0;
	printHCodes(huffmanTree, arr, 0);
	for (const auto& var : counts)
	{
		std::cout << var->first << " : " << var->second << std::endl;
	}
	return table;
}
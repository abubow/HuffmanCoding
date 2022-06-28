#pragma once
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
#include<iostream>
struct Node {
	char first;
	int second;
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
};
std::vector<Node> wordCount(std::vector<char> chars){
	std::vector<Node> counts;
	bool alreadyExists;
	for(auto i:chars){
		alreadyExists=false;
		for(auto& it:counts){
			if(i==it.first){
				it.second=it.second + 1;
				alreadyExists=true;
				break;
			}
		}
		if(alreadyExists == false)
		{
			Node res;
			res.first = i;
			res.second = 1;
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
void insertInHeap(std::vector<Node>& vec, Node a) {
	vec.push_back(a);
	for (int i = vec.size(); i < 0; i++)
	{

	}
}
Node popFromHeap(std::vector<Node> vec) {

}
Node createHuffmanTree(std::vector<Node> counts) {
	std::sort(counts.begin(), counts.end(),
			[](auto& first, auto& second) {
				return first < second;
			});
	for (int i = 0; i < counts.size(); i++)
	{

	}
}
std::vector <Node> createTable(std::vector <Node>& counts) {
	std::vector <Node> table;
	
	
	for (const auto& var : counts)
	{
		std::cout << var.first << " : " << var.second << std::endl;
	}
	return table;
}
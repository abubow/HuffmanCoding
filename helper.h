#pragma once
#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
std::vector<std::pair<char, int>> wordCount(std::vector<char> chars){
	std::vector<std::pair<char, int>> counts;
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
			std::pair<char, int> res;
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
void heapify(std::vector < std::pair<char, int>> arr) {
	for (int i = 0; i < arr.size()/2; i++)
	{
		if (arr[i] > arr[(2 * i) + 1]) {
			swapV(arr[i], arr[(2 * i) + 1]);
			i = (2 * i) + 1;
		}
		else if (arr[i] > arr[(2 * i) + 2]) {
			swapV(arr[i], arr[(2 * i) + 2]);
		}
	}
}
std::vector < std::pair<char, std::string>> createTable(std::vector < std::pair<char, int>> counts) {
	std::vector < std::pair<char, std::string>> table;
	
	for (auto var : counts)
	{
		std::cout << var.first << " : " << var.second << std::endl;
	}
	return table;
}
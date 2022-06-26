#pragma once
#include<vector>
#include<string>
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


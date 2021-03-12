#ifndef TASK1_TSPALGORITHM_H_
#define TASK1_TSPALGORITHM_H_


#include<vector>
#include<numeric>
#include<limits.h>  
#include<algorithm>


int TspSolution(const std::vector<std::vector<int>>& cities, int pos, int visited, std::vector<std::vector<int>>& state);

void CreatePossibleStates(std::vector<std::vector<int>>& possible_states, int total_node);

void BacktrackPathFromMinimumCost(std::vector<std::vector<int>> & states, int min, const std::vector<std::vector<int>> & cities,std::vector<int>& visited_node_order);

void FindNextNode(std::vector<int>& nodes_remaining, const std::vector<std::vector<int>> & cities, int& min, int& current_node,std::vector<std::vector<int>> & states, std::vector<int> &visited_node_order,int& mask);




#endif /* TASK1_TSPALGORITHM_H_ */
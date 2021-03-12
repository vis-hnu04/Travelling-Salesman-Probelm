#include "tspalgorithm.h"



/**
    \brief Given a complete, undirected, weighted graph in the form of an adjacency matrix,
           returns the smallest tour that visits all nodes and starts and ends at the same
           node. This dynamic programming solution runs in O(n * 2^n).

    \param @ cities        -------> the 2D adjacency matrix of size (TOTAL_NODES * TOTAL_NODES)
           @ int pos       -------> the starting position of tour. (Takken first node as starting position).
           @ int visited   -------> mask of visited nodes or cities. LSB is the first node and MSB is the Final node. If visited set the bit
                                    position. (For example: If First node visited then set LSB (1<<0).)
           @ state         -------> The possibe routes available with the given number of nodes. Array of dimension (Total_Nodes * 2^Total_Nodes).
                                    Initially state has INT_MAX value.
                                    At the function return, state is updated with the cost of taking different path.                        
    \return the minimum cost to complete the tour
*/
int TspSolution(const std::vector<std::vector<int>>& cities, int pos, int visited, std::vector<std::vector<int>>& state)
{
        if(visited == ((1 << cities.size()) - 1))                          //
            return cities[pos][0];                       // return to starting city or start node

        if(state[pos][visited] != INT_MAX)
            return state[pos][visited];

        for(int i = 0; i < cities.size(); ++i)
        {
            // can't visit ourselves unless we're ending & skip if already visited
            if(i == pos || (visited & (1 << i)))
                continue;

            int distance = cities[pos][i] + TspSolution(cities, i, visited | (1 << i), state);
            if(distance < state[pos][visited])
                state[pos][visited] = distance;
        }

        return state[pos][visited];
}


/**
    \brief Given total number of nodes, the function, adds MAXIMUM_INTEGER VALUE to all the position of 2D Matrix. 

    \param @ possible_state   ------->  The possibe routes available with the given number of nodes. 
                                        Array of dimension (Total_Nodes * 2^Total_Nodes). Passed as reference assigns value INT_MAX 
                                        all the positions.
           @ int total_node  --------> total number of nodes.                                                         
    
*/
void CreatePossibleStates(std::vector<std::vector<int>>& possible_states, int total_node){
 
        for(auto& neighbors : possible_states)
        {  
            neighbors = std::vector<int>((1 << total_node)-1, INT_MAX);

        }
 
}


/**
    \brief  Given the Minimum cost from the Tsp fn:, this fn: calculates the route Salesperson travelled from the states array.
            start by looking at the states[startnode] for the minimum cost. 
            The index corresponding to the minimum cost in the states[startnode] will be the second node visited.
             Minimum value is updated everytime a node is visited, by deducting the cities[current_index][min_element_index]
             from the minimum value.

    \param @ states                  -------->  Array has cost of taking from different possible routes.
           @ int min                 -------->  minimum value obtained from TSP algorithm.
           @ cities                  -------->  adjacency matrix with cost.                                                         
           @ visited_node_order      ---------> passed as reference, when returns the vector has elements in the order of node visited.
*/

void BacktrackPathFromMinimumCost(std::vector<std::vector<int>> &states, int min, const std::vector<std::vector<int>> & cities,std::vector<int>& visited_node_order){
   
        // set LSB as 1 for starting from first node
        int mask=1;     
        // remaining nodes has size of (total nodes-1)                                                                
        std::vector<int> nodes_remaining(cities.size()-1);                                 

        if(cities.size() == 2){
            visited_node_order.push_back(1);
            return;
        } 
        // Fill with 1, ..., Total_nodes-1 (except 0) .
        iota (std::begin(nodes_remaining), std::end(nodes_remaining), 1);             
        //start node is 0 , so current_node =0:
        int  current_node = 0;                                                       
        std::vector<int> v = states[current_node] ;      
                    
        // look for minimum cost in states[current_node]
        auto min_element_index = std::min_element(v.begin(), v.end()) - v.begin();
        //pushed next node visited
        visited_node_order.push_back(min_element_index);                              
        //set the bit postion of visited node and updated mask by OR ing
        mask |= 1<<min_element_index;                                                 

        // remove node from nodes_remaining array
        nodes_remaining.erase(std::find(nodes_remaining.begin(),nodes_remaining.end(),min_element_index));  
        //min value updated
        min  = min - cities[current_node][min_element_index];       
        // next visited node is current node.                                       
        current_node = min_element_index;                                                                   

        while(nodes_remaining.size()!= 1){
            FindNextNode(nodes_remaining,cities, min, current_node, states,visited_node_order , mask);
        }
        visited_node_order.push_back(nodes_remaining[0]);
}



/**
    \brief  Function finds the next possible node in the route. This function is called till the nodes_remaining size is greater than 1.
            Checks for the minimum cost in the state matrix, if the minimum cost is found, the node's possibility to be the next node is 
            validated by checking the index of the minimum cost in the states array with the mask value. If passed we pushed the node to 
            the visited_node_order and erased the node from the nodes_remaining also the minimum cost is updated.
            If the validation check is not passed then minimum values is restored by adding the cities[current_index][i].

    \param @ nodes_remaining         -------->  Nodes left to visit.
           @ cities                  -------->  adjacency matrix with cost.                                                         
           @ int min                 ---------> updated minimum values from the BackTrackPathFromMinimumCost.
           @ current_node            ---------> current position of the salesman in terms of node.            
           @ states                  ---------> Array of cost of taking different routes.
           @ visited_node_order      ---------> Elements in vector are in the order of nodes visited.
           @ mask                    ---------> mask value. set 1 if a node is visited. LSB is first node and MSB is Total_node.

*/     

void FindNextNode(std::vector<int>& nodes_remaining, const std::vector<std::vector<int>> & cities, int& min, int& current_node,std::vector<std::vector<int>> & states, std::vector<int> &visited_node_order,int& mask)
{
        for (auto i : nodes_remaining){
               //minimum value is updated
            min = min - cities[current_node][i];                                                                       

            auto iter = states[i].begin();

              //checking if minimum value present in the states[i]
            while ((iter = std::find_if(iter, states[i].end(), [=](int i){return (i == min);} )) != states[i].end()){

            auto element_index = iter - states[i].begin();
            iter++;
            if(element_index == (mask | 1<<i)){                                    
            visited_node_order.push_back(i);
            current_node = i;
            nodes_remaining.erase(std::find(nodes_remaining.begin(),nodes_remaining.end(),i));
            mask |= 1<<i;
            return;
            }

            }

            min = min + cities[current_node][i];
            } 

}


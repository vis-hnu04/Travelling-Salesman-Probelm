#include"addremove.h"


/**
    \brief This function adds a new node to the given input. Function expects the user to input $total_node values. 

    \param @ cities          ------->   Adjacency matrix, It is updated with the new node and the edge values from new node to older nodes  

           @ node_names     --------->  Orignal node names.Starts from 1.
        
*/

void AddNode(std::vector<std::vector<int>>& cities, std::vector<int>&node_names){
    std::cout<<"Enter non-zero distances from new node to the old nodes"<<std::endl;
    int distance;
    int total_nodes = cities.size();
    int total_nodes_after_adding = total_nodes+1;
    cities.resize(total_nodes_after_adding);

    for (int i = 0;i<= node_names.size()-1;i++){
        std::cout<<"Enter distance from new node to node "<<node_names[i]<<std::endl;
        std::cin>> distance;
        cities[total_nodes].push_back(distance);
        cities[i].push_back(distance);
    }
    cities[total_nodes].push_back(0);
}


/**
    \brief This function adds a new node to the given input. Function expects the user to input $total_node values. 

    \param @ cities         -------->   Adjacency matrix, values are updated when a node is deleted from the given nodes.  
                                        If the size of cities is equal to 2, then no nodes will be deleted and function will
                                        return to the helper menu. (Deleting a node will cause cost to be zero.)                                                              
            @node_names     --------->  Vector of orignal names of nodes. Starts with 1.
    
    \return node_to_delete   ---------> The Node which user wants to delete.        
*/

int DeleteNode(std::vector<std::vector<int>>& cities, std::vector<int> &node_names){
    int node_to_delete;
    std::cout<<std::endl;
    
    if(cities.size()==2){
        std::cout<<"Only two nodes are available. Deleting one node will result in zero cost.\n";
        std::cout<<"Enter another choice."<<std::endl;
        return -1;
    } 
   
    std::cout<<"--------------------------------------------------\n";
    std::cout<<"Nodes available to delete are ";
    for (int i = 0;i<=node_names.size()-1;i++){
        std::cout<< node_names[i] <<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Enter the node to delete and press Enter\n";
    std::cout<<"---------------------------------------------------\n";
    std::cin>>node_to_delete;
    
   
   auto iter = find(node_names.begin(),node_names.end(),node_to_delete);
   if(iter == node_names.end()){
       std::cout<<"Entered node does not exist in the graph.\n";
       return -1;
   }
   
    std::cout<< "Node "<<node_to_delete << " is deleted from the input.\n" ;
    std::cout<<"----------------------------------------------------\n";

   //finding row to delete from the adjacency matrix
   int index = iter - node_names.begin();
   cities.erase(cities.begin()+index); 

   
   //deleting column from the adacency matrix
    std::for_each(cities.begin(), cities.end(), 
    [&](std::vector<int>& row) {
        row.erase(std::next(row.begin(), index));
    });
   return node_to_delete; 
   
}

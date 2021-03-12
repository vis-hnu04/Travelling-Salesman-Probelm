#include "addremove.h"
#include "display.h"
#include "tspalgorithm.h"
#include <ctype.h>
#include <string>
#include <fstream>      // std::ofstream
#include <stdio.h>

const std::string result_file_name = "../output/optimum_route.txt";
/**
    \brief This function calls other procedures. The call is in the order

            CreatePossibleStates > TSP > BacktrackPathFromMinimum >
   DisplayFinalRoute.

            Finally the route travesred is printed onto the console.

    \param @ cities         -------->   Adjacency matrix.
            @node_names     --------->  Vector of orignal names of nodes.

*/

void process(const std::vector<std::vector<int>> &cities,
              std::vector<int> node_names) {

  int start_node = 0;

  int total_nodes = cities.size();
  std::vector<std::vector<int>> possible_states(cities.size());
  CreatePossibleStates(possible_states, total_nodes);

  int minimum = TspSolution(cities, 0, 1, possible_states);
  std::cout << "minimum cost of traversing all the given nodes once is: "
            << minimum << std::endl;

  std::vector<int> visited_node_order;
  visited_node_order.push_back(start_node);
  BacktrackPathFromMinimumCost(possible_states, minimum, cities,
                               visited_node_order);
  DisplayFinalRoute(visited_node_order, node_names, std::to_string(minimum));


  std::cout << "---------------------------------------------------------------"
               "--------"
            << std::endl;
  std::cout << "------fastest route possible for the given node is as "
               "follows--------- "
            << std::endl;
  std::cout << std::endl;
  std::ofstream ofs (result_file_name, std::ofstream::out|std::ofstream::app );

  for (auto i : visited_node_order) {
    std::cout << node_names[i] << "-->";
    ofs << node_names[i] << "-->";
  }
  ofs << node_names[0] << "\n";
  std::cout << node_names[0] << std::endl;
  
}

int main() {
 
  int node_deleted;
  int index;
  bool keeprunning = true;
  std::vector<std::vector<int>> cities = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  // Delete the result text file if present already
  remove( result_file_name.c_str() );
  DisplayInputNode();
  std::vector<int> node_names{1, 2, 3, 4};
  // iota (std::begin(node_names), std::end(node_names), 0);
  process(cities, node_names);

  std::cout << "---------------------------------------------------------------"
               "--------"
            << std::endl;

  while (keeprunning) {
    std::string str;
    int  choice;
    std::cout << std::endl;
    std::cout << "Select any of the choice below.\n";
    std::cout << " 1 - Add a node to the input. User must input 4 values for "
                 "the new node.\n";
    std::cout << " 2 - Delete a node from the input.\n";
    std::cout << " 3 - Exit.\n";
    std::cout << " Enter your choice and press return: ";
    std::cin >> str;
    try {
      choice = std::stoi(str);
    }
    catch (std::exception& e) {
      std::cout << "\nNot a Valid Choice. \n"
                << "Choose again.\n";
      continue;
    }
    switch (choice) {

    case 1:

      AddNode(cities, node_names);
      index =
          std::distance(node_names.begin(),
                        std::max_element(node_names.begin(), node_names.end()));
      node_names.push_back(node_names[index] + 1);
      std::cout << "--------------------------------------------------\n";
      std::cout << " New node " << node_names[index] + 1 << " is added."
                << std::endl;
      process(cities, node_names);
      break;

    case 2:

      node_deleted = DeleteNode(cities, node_names);
      if (node_deleted == -1) {
        break;
      }
      node_names.erase(
          std::remove(node_names.begin(), node_names.end(), node_deleted),
          node_names.end());
      process(cities, node_names);
      break;

    case 3:
      std::cout << "End of Program.\n";
      keeprunning = false;
      break;
    default:
      std::cout << "Not a Valid Choice. \n"
                << "Choose again.\n";
      break;
    }

  } 

  return 0;
}
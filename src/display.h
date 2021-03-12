
#ifndef TASK1_DISPLAY_H_
#define TASK1_DISPLAY_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<string.h>
#include <stdlib.h>  
#include<vector>
#include<iostream>
#include<time.h>
#include<numeric>


void DisplayInputNode();

void DisplayFinalRoute(std::vector<int>  visited_node_order, std::vector<int>&node_names,const std::string& minimum_cost);


#endif /* TASK1_DISPLAY_H_ */   
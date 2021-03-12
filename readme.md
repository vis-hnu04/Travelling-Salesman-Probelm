Hi There!!
## TRAVELLING SALESMAN PROBLEM
* * * 
Author: Vishnu Sambasivan Remani
* * *
## Contents
+ Standard Libraries
+ Dependencies
    - OpenCV
    - Installing OpenCV
+ Algorithm
    - acktrackalgorithm for finding Route.
+ Output    
* * *
## Standard Libraries
C++ Standard Library - including STL Containers, STL Aglorithm are used in this project.
* * *
## Dependencies
## OpenCV
OpenCV is used in this project for displaying the nodes and the final route.

## Installing OpenCV
* * *
## Installing OpenCV in Linux

OpenCV can be downloaded from this location: https://opencv.org/releases/

For a more detailed OpenCV installation refer to this tutorial installation, https://docs.opencv.org/4.1.0/d7/d9f/tutorial_linux_install.html 

## Installation Steps
* * *
+ Install the required dependencies
---
> sudo apt-get install build-essential cmake libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

+ Download source archive from https://opencv.org/releases/ and extract it.

>wget https://github.com/opencv/opencv/archive/4.1.0.zip -O  /Destination/opencv_src.zip
cd ~/  
unzip /Destination/opencv_src.zip ; rm /tmp/opencv_src.zip 

+ Navigate to the extracted sources, create a build directory.
>cd ~/opencv-*  
mkdir build  
cd build

+ Run cmake
>cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_JAVA=OFF -DWITH_OPENGL=ON ..


* Execute make.
>make -j$(nproc) 

Runs nproc jobs in parallel.
+ Install the libraries
>sudo make install

* * *

## Algorithm
* * *
## Backtrack algorithm for finding route
+ Calculating the route by finding the minimum cost from the possible_states[0].
>  std::vector<std::vector<int>> possible_states

+ Index of the minimum cost in the possible_states[0] will be the second node visited.
+ minimum cost is updated.
> minimum = minimum - cities[current_node][minimum_cost_index]  
> current_node = Index of minimum_cost

+ Loop through all the unvisited nodes.
> for (auto i : nodes_remaining)

+ >minimum = minimum -cities[current_node][i] 
+ > check if minimum value is present in the states[i]
+ > if yes, validate by comparing the index of minimum value with the mask.

+ > For example, if there are 4 nodes availble in the input and 0 and 1 is already visited then the mask will be 3 (0011) and if next node visited is 2 then, the minimum value should found at the index of 7(0111) in states[2].

+ > if no, keep the minimum value unchanged.

* * *
## Output
output is stored into the "../output" folder as text file "optimum_route.txt"

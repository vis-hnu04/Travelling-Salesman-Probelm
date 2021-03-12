#include "display.h"



/*
  Function to display the given four input nodes and the weights to the other nodes as shown in the below figure:
    https://www.geeksforgeeks.org/wp-content/uploads/Euler12-300x225.png
*/
void DisplayInputNode()
{
 
    int window_size = 800;
    cv::Mat image(window_size,window_size, CV_8UC3, cv::Scalar(0,0,0));
    if( !image.data ){
    std::cout <<  "Could not open or find the image" << std::endl ;
    exit(EXIT_FAILURE);
    }

    cv::Point first_node(400, 200);
    cv::Point second_node(250,600);
    cv::Point third_node(550,600);
    cv::Point fourth_node(400,400);
    int radius_circle = 30;
    cv::Scalar color_circle(255,255,255);
    int thickness_circle = 2;
    cv::Scalar color_line(255,255,255);
    int thickness_line = 2;

            /* First node location in the window*/  
    cv::circle(image, first_node, radius_circle, color_circle, thickness_circle,cv::LINE_AA);            
    cv::putText(image,"1",cv::Point(390,210),cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255,255,255),2);

                /* Second node location in the window*/
    cv::circle(image, second_node, radius_circle, color_circle, thickness_circle,cv::LINE_AA);
    cv::putText(image,"2",cv::Point(240,610),cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255,255,255),2);

    cv::circle(image, third_node, radius_circle, color_circle, thickness_circle,cv::LINE_AA);
    cv::putText(image,"3",cv::Point(540,610),cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255,255,255),2);

    cv::circle(image, fourth_node, radius_circle, color_circle, thickness_circle,cv::LINE_AA);   
    cv::putText(image,"4",cv::Point(390,410),cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255,255,255),2);


    cv::line(image, cv::Point(378,222), cv::Point(241,571), color_line, thickness_line);
    cv::putText(image,"10",cv::Point(265,388),cv::FONT_HERSHEY_PLAIN ,1.5,CV_RGB(255,255,255),1);

    cv::line(image, cv::Point(423,219), cv::Point(547,570), color_line, thickness_line);
    cv::putText(image,"15",cv::Point(500,388),cv::FONT_HERSHEY_PLAIN ,1.5,CV_RGB(255,255,255),1);

    cv::line(image, cv::Point(400,230), cv::Point(400,370), color_line, thickness_line);
    cv::putText(image,"20",cv::Point(360,304),cv::FONT_HERSHEY_PLAIN,1.5,CV_RGB(255,255,255),1);

    cv::line(image, cv::Point(264,574), cv::Point(379,422), color_line, thickness_line);
    cv::putText(image,"25",cv::Point(330,511),cv::FONT_HERSHEY_PLAIN,1.5,CV_RGB(255,255,255),1);

    cv::line(image, cv::Point(425,418), cv::Point(534,576), color_line, thickness_line);
    cv::putText(image,"30",cv::Point(440,511),cv::FONT_HERSHEY_PLAIN,1.5,CV_RGB(255,255,255),1);

    cv::line(image, cv::Point(280,602), cv::Point(520,602), color_line, thickness_line);
    cv::putText(image,"35",cv::Point(386,643),cv::FONT_HERSHEY_PLAIN,1.5,CV_RGB(255,255,255),1);

    /* Create a window for display.  */ 
    cv::imshow( "Press Any key to close", image );                  
    cv::waitKey(0);   

 }

/**
    \brief Displays the final route taken by the salesman. 

    \param @ visited_node_order ------->  vector with elements in the order of path taken by salesman.
           @ node_names         -------->  Vector of names of nodes.
           @ minimum            ---------> Minimum value obtained.                                             
    
*/

void DisplayFinalRoute(std::vector<int>  visited_node_order,std::vector<int> &node_names, const std::string& minimum){
    
    //const int kmultipler = 3;

    int window_size = 1500;
    int first_node_x , first_node_y, other_node_x, other_node_y, temp_x, temp_y;

      /* lower_limit and upper_limit is used with the random number generator to generate values b/w these limit  */
    int lower_limit = 51;
    int upper_limit = 80;
    int red; 
    int green; 

    srand(time(NULL));

    cv::Mat image(window_size,window_size, CV_8UC3, cv::Scalar(0,0,0));

    if( !image.data ){
     std::cout <<  "Could not open or find the image" << std::endl ;
     exit(EXIT_FAILURE);
    }
   
    //keeping first node position constant in the window.
    first_node_x = 500; 
    first_node_y = 200;

    temp_x = first_node_x;
    temp_y = first_node_y;

    std::string text_to_display =  std::to_string(node_names[0]) +" Start Node";
    cv::circle(image, cv::Point(first_node_x,first_node_y), 30, cv::Scalar(255,255,255), 2,cv::LINE_AA);
    cv::putText(image,text_to_display,cv::Point(first_node_x, first_node_y),cv::FONT_HERSHEY_DUPLEX,1, CV_RGB(255,255,255),2);



    while(visited_node_order.size()!=1)
    {
      int temp = visited_node_order.back(); 

      visited_node_order.pop_back();
     
             //randomly assigning x value of node
      other_node_x = temp*(lower_limit + ( std::rand() % ( upper_limit - lower_limit + 1 ) ));     
      other_node_y = temp*(lower_limit + ( std::rand() % ( upper_limit - lower_limit + 1 ) ));
     
          //assigning different red color everytime
      red   = std::min(255, (int)(255 * abs((float(window_size)-other_node_x) / window_size)));          
         //assigning diff: green color everytime 
      green = std::min(255, (int)(255 * (1 - abs((float(window_size)-other_node_x) / window_size))));    

      text_to_display = std::to_string(node_names[temp]);                                                                      
      cv::circle(image, cv::Point(other_node_x,other_node_y), 30, cv::Scalar(255,255,255), 2,cv::LINE_AA);
      cv::putText(image,text_to_display,cv::Point(other_node_x, other_node_y),cv::FONT_HERSHEY_DUPLEX,1,CV_RGB(255,255,255),2);
      cv::arrowedLine(image, cv::Point(other_node_x, other_node_y), cv::Point(first_node_x, first_node_y), cv::Scalar(0, green, red), 2, 4, 0, 0.05);
      
      first_node_x = other_node_x;
      first_node_y = other_node_y;
      lower_limit +=5;

      if(lower_limit >= upper_limit)
      {
      lower_limit = 51;
      }
    }

    cv::circle(image, cv::Point(other_node_x,other_node_y), 30, cv::Scalar(255,255,255), 2,cv::LINE_AA);

    cv::arrowedLine(image, cv::Point(temp_x, temp_y), cv::Point(other_node_x, other_node_y), cv::Scalar(255, 0, 0), 2, 4, 0, 0.05);

    cv::putText(image,"minimum distance :"+minimum, cv::Point(800,50),cv::FONT_HERSHEY_DUPLEX,1,CV_RGB(255,255,255),2);


    // Create a window for display. 
    cv::imshow( "Final path of given input :", image );                  
    //cv::imwrite("graph.png",image);
    cv::waitKey(0);   
    cv::destroyAllWindows();
     
}

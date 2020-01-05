#include <iostream>
#include <array>
#include <vector>
 #include <limits>
 #define __STDC_LIMIT_MACROS
#define BOARD_SIZE 100
bool containsSnakeOrLadder(int row,std::vector<std::pair<int,int>> const & input);

void printvector(std::vector<std::vector<int>> graph){
    for(auto it = graph.begin(); it < graph.end(); ++it){
        for(auto jit = (*it).begin(); jit < (*it).end(); ++jit){
            std::cout<<"["<<(*jit)<<"]";
        }
        std::cout<<"\n";
    }
}

bool filloutshortestpath(int row,int step,std::vector<int> &shortestpatharray,std::vector<std::vector<int>> graph){

   if(step < shortestpatharray[row] ){
       shortestpatharray[row] = step;
   }
   if(row ==99){ //base case

       return true;
   }
   
   // Only look for forward moving jumps
   for(int i = (row +1) ; i < BOARD_SIZE  ; ++i){
       if(graph[row][i] >0){
          auto hitlast= filloutshortestpath(i,step+1,shortestpatharray,graph);
       }
   }
   return true;

}


int main(){
    std::cout<<"Begin project"<<std::endl;
   
    
    std::vector<std::vector<int>> graph;

    for(auto i = 0; i < BOARD_SIZE; ++i){
        std::vector<int> row;
        for(auto j = 0; j < BOARD_SIZE; ++j){
            row.push_back(0);
          
        }
        graph.push_back(row);
        row.clear();
    }
    
     /*
        snakes = {16: 6, 48: 26, 49: 11, 56: 53, 62: 19, 64: 60, 87: 24, 93: 73, 95: 75, 98: 78}
        ladders = {1: 38, 4: 14, 9: 31, 21: 42, 28: 84, 36: 44, 51: 67, 71: 91, 80: 100}
    */

    std::vector<std::pair<int,int>> snakesandladders;
    //define snakes
    snakesandladders.push_back({16,6});
    snakesandladders.push_back({48,26});
    snakesandladders.push_back({49,11});
    snakesandladders.push_back({56,53});
    snakesandladders.push_back({62,19});
    snakesandladders.push_back({64,60});
    snakesandladders.push_back({87,24});
    snakesandladders.push_back({93,73});
    snakesandladders.push_back({95,75});
    snakesandladders.push_back({98,78});

    //define ladders
    snakesandladders.push_back({1,38});
    snakesandladders.push_back({4,14});
    snakesandladders.push_back({9,31});
    snakesandladders.push_back({21,42});
    snakesandladders.push_back({28,84});
    snakesandladders.push_back({36,44});
    snakesandladders.push_back({51,67});
    snakesandladders.push_back({71,91});
    snakesandladders.push_back({80,100});

    for(auto it = snakesandladders.begin(); it < snakesandladders.end(); ++it){
        graph[((*it).first)-1][((*it).second)-1] = 1;
    }
    for(int i = 0; i < BOARD_SIZE; ++i){
        if(!containsSnakeOrLadder(i,snakesandladders)){
            for(int j = 0; j < 6; ++j){
                int spot = i+j;
                if(spot < BOARD_SIZE){
                    graph[i][spot] = 1;
                }
                
            }
        }
    }

    std::vector<int> shortestpatharray;

    for(int i = 0; i < BOARD_SIZE; ++i) {
        shortestpatharray.push_back(INT8_MAX);
    }

   filloutshortestpath(0,0,shortestpatharray,graph);
  
   for(int i =0; i < BOARD_SIZE; ++i){
        std::cout<<"shortest:"<<i<<" :"<<shortestpatharray[i]<<std::endl;
   }
}
bool containsSnakeOrLadder(int row,std::vector<std::pair<int,int>> const & input){
   for(auto it = input.begin(); it < input.end(); ++it){
       if((*it).first == row +1){
           return true;
       }
   }
   return false;
}






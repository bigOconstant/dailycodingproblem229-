#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <unordered_map>
 #define __STDC_LIMIT_MACROS
#define BOARD_SIZE 100
using namespace std;
bool containsSnakeOrLadder(int row,std::vector<std::pair<int,int>> const & input);

void findShortestPath(vector<vector<int>> graph,std::unordered_map<int,std::pair<int,int>> &table,vector<std::pair<int,int>> checked,vector<std::pair<int,int>> &unchecked){
    //Base case

    if(unchecked.size() <1){
        return;//
    }

    //Sort unvisited list by distance from source. 
    
    auto currentitem = unchecked.back();

    for(auto it = unchecked.begin(); it < unchecked.end(); ++it){
        if((*it).second < currentitem.second){
            currentitem = (*it); // set current item to smallest distance from source
        }
    }


    //Remove item we won't look at it again
    auto i = 0;
    auto counter = 0;
    for(auto it = unchecked.begin(); it < unchecked.end(); ++it){
        if((*it).first == currentitem.first){
            counter = i;
        }
        ++i;
    }


    unchecked.erase(unchecked.begin()+counter);

    //Get neighbors of current item

    auto const row = graph[currentitem.first];

    vector<int> neighbors;

    counter = 0;
    for(auto it = row.begin(); it < row.end(); ++it){
        if(counter != currentitem.first && (*it) >0){
            neighbors.push_back(counter);
        }
        ++counter;
    }

    //if neighbors not in checked and not in unchecked put them in unchecked

    for(auto it = neighbors.begin(); it < neighbors.end(); ++it){
        bool found = false;
        for(auto jit = unchecked.begin(); jit < unchecked.end(); ++jit){
            if((*jit).first == (*it)){
                found = true;
                break;
            }
        }
        
        for(auto jit = checked.begin(); jit < checked.end(); ++jit){
            if((*jit).first == (*it)){
                            found = true;
                            break;
              }
        }

        if(!found  ){

            unchecked.push_back({(*it),table[(*it)].second});
        }
    }


    //if distance from current item to each neighbor is less than the neighbor's items's distance, update distance to shorter value

    for(auto it = neighbors.begin(); it < neighbors.end(); ++it){
        auto newdistance =  graph[currentitem.first][(*it)] + table[currentitem.first].first;
        if(newdistance < table[(*it)].first){ //This is what makes it a "Greedy Algorithm"
            table[(*it)].first = newdistance;
            table[(*it)].second = currentitem.first; //Update previous

            
        }
    }

    //Put current item in visited list remove it from unvisted list.
    checked.push_back(currentitem);

    //Update sizes. They have have changed for both
    for(auto it = checked.begin(); it < checked.end(); ++it){
        (*it).second = table[(*it).first].first;
    }
    for(auto it = unchecked.begin(); it < unchecked.end(); ++it){
        (*it).second = table[(*it).first].first;
    }


    // Recurse to finish
     findShortestPath(graph,table,checked,unchecked);
}

void printvector(std::vector<std::vector<int>> graph){
    int counter = 1;
    for(auto it = graph.begin(); it < graph.end(); ++it){
        cout<<counter<<".";
        for(auto jit = (*it).begin(); jit < (*it).end(); ++jit){
            std::cout<<"["<<(*jit)<<"]";
        }
        ++counter;
        std::cout<<"\n";
    }
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

    std::unordered_map<int,std::pair<int,int>> table;
    table.insert({0,{0,0}});

    for(int i = 0; i < BOARD_SIZE; ++i) {
        if(i ==0){
            table.insert({0,{0,0}});
        }else{
         table.insert({i,{INT32_MAX,i}});
        }
    }

    vector<std::pair<int,int>> checked{};
    vector<std::pair<int,int>> unchecked {{0,0}};

    findShortestPath(graph,table,checked,unchecked);

    cout<<"printing table"<<endl;

    for(int i = 0; i < BOARD_SIZE; ++i){
        cout<<"cell "<<i+1 <<":distance from source- "<<(table[i].first)<<" prev:"<<(table[i].second+1)<<endl;
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






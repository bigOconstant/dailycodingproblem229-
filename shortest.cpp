#include <iostream>
#include <vector>
#include <unordered_map> 
using namespace std;
int main(){
    cout<<"starting app"<<endl;


    vector<vector<int>> graph{
        {1,1,6,0,0},//0
        {0,0,2,1,0},//1
        {1,2,1,2,5},//2
        {0,1,2,1,5},//3
        {0,0,5,5,0}//4
    };
    /* |Vertex - shortest distance from start - previous vertex |*/
    std::unordered_map<int,std::pair<int,int>> table;
    table.insert({0,{0,0}});
    table.insert({1,{INT32_MAX,1}});
    table.insert({2,{INT32_MAX,2}});
    table.insert({3,{INT32_MAX,3}});
    table.insert({4,{INT32_MAX,4}});


}
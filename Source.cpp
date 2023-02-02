#include "AdjacencyList.h"
#include <string>
using namespace std;

/*
PROCESS:
1. Keep track of OutDegrees as websites are inserted (DONE)
2. Insert Edges into Adjacency List w/ (1/outdegree of from) as weight (DONE)
*/

int main()
{
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;

    //stores website and outdegree associated
    map<string, float> websites;
    //stores from and to as a pair in a vector (from as first, to as second)
    vector<pair<string, string>> webLinks;
    AdjacencyList worldWideWeb;

    for (int i = 0; i < no_of_lines; i++)
    {
        cin >> from;

        //KEEPS TRACK OF OUT DEGREES
        if (websites.size() == 0 || websites.find(from) == websites.end()) {
            //inserts a new website into map, sets out degree as 1 bc if it is a from it has a to => outdegree is 1
            websites.emplace(from, 1);
        }
        else {
            //increments out degree of website
            auto it = websites.find(from);
            it->second += 1;
        }

        cin >> to;
        //storing from and to as a pair
        webLinks.push_back(pair<string, string>(from, to));
    }
    
    
    //iterate over webLinks to add edges to graph
    //weight is determined from finding the outdegree of the from vertex in websites (from vertex is first element in webLinks pair at i)
    float weight = 0;
    string fromI, toI;
    for (int i = 0; i < webLinks.size(); i++) {
        fromI = webLinks.at(i).first;
        toI = webLinks.at(i).second;
        if (websites[fromI] != 0) {
            weight = (float)(1 / websites[fromI]);
        }
        else { weight = 0; }
        worldWideWeb.addEdge(toI, fromI, weight);
    }
    worldWideWeb.PageRank(power_iterations);
}
#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std; 

class AdjacencyList {
private:
    //stores all websites as first element (to) then stores its links in the vector as pair<from, weight>, weight is 1/out degree of from vertex
    map < string, vector<pair<string, float>>> links;
public:
    AdjacencyList();
    void PageRank(int powerIts);
    void addEdge(string from, string to, float weight);
};

AdjacencyList::AdjacencyList() {
    
}

void AdjacencyList::addEdge(string from, string to, float weight) {
    if (links.size() == 0) {
        vector<pair<string, float>> tos;
        tos.push_back(pair<string, float>(to, weight));
        links.emplace(from, tos);
    }
    else {
        //makes sure "from" is in map
        if (links.find(from) != links.end()) {
            for (auto i = links.begin(); i != links.end(); i++) {
                if (i->first == from) {
                    i->second.push_back(pair<string, float>(to, weight));
                }
            }
        }
        else {
            vector<pair<string, float>> tos;
            tos.push_back(pair<string, float>(to, weight));
            links.emplace(from, tos);
        }
    }
    auto finder = links.find(to);
    vector<pair<string, float>> tos;
    if (finder == links.end()) {
        links.emplace(to, tos);
    }
}

void AdjacencyList::PageRank(int powerIts) { 
    map<string, float> ranks;
    float intialRank = (float) 1 / (float) links.size();
    //initialize ranks to 1/numVertices
    for (auto i = links.begin(); i != links.end(); i++) {
        ranks.insert(pair<string, float>(i->first, intialRank));
    }
    map<string, float> tempRanks = ranks;
    //continues for number of powerIts
    float rankVal = 0.0;
    for (int i = 1; i < powerIts; i++) {
        //cycles through links
        for (auto j = links.begin(); j != links.end(); j++) {
            rankVal = 0;
            //cycles through vector at links value
            for (int h = 0; h < j->second.size(); h++) {
                            //weight                    //old pagerank
                rankVal += j->second.at(h).second * ranks[j->second.at(h).first];
            }
            tempRanks[j->first] = rankVal;
        }
        ranks = tempRanks;
    }


    for (auto i = ranks.begin(); i != ranks.end(); i++) {
        cout << i->first << " ";
        cout << fixed << showpoint;
        cout << setprecision(2);
        cout << i->second << endl;
    }
}

    /*
    1. initialize a map of pageranks with size = amount of websites and all pageranks =  1/size (DONE)
    2. for # of powerIts:
        for size of map:
            pagerank(j) = SUM (weight in pair * previousPageRank of paired weight) where previous page rank is stored in vector from step 1
    3. sort alphabetically (although i think maps are already sorted by key value so shouldalready be in alphabetical order)
    4. print
    */

 /* prints the PageRank of all pages after p powerIterations in
ascending alphabetical order of web pages and rounding rank to two
decimal places*/

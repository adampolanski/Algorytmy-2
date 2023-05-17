#include <iostream>
#include <algorithm>
#include <map>
#include <climits>
#include <queue>

using std::cin;
using std::cout;
using std::sort;
using std::map;
using std::queue;

struct Node{

    int x, y, index;
    bool visited = false;
    map<int, int> edges; //key: index, value: dlugosc sciezki (value)
    Node(){};

    void setValues(int index, int x, int y){
        this->index = index;
        this->x = x;
        this->y = y;
    } 

    static int compareX(Node& a, Node& b){ return b.x - a.x; }
    static int compareY(Node& a, Node& b){ return b.y - a.y; }
};

Node* nodes;
int* idArr;

void buildGraph(int size, int compareFunc(Node&, Node&)){  //dla kazdego wierzcholka przekazuje indeksy innych "bliskich" wierzcholkow i wartosci krawędzi
    int tmpValue;
    for(int i = 0; i < size - 1; i++){
        tmpValue = compareFunc(nodes[idArr[i]], nodes[idArr[i+1]]);

        if(nodes[idArr[i]].edges.empty() || nodes[idArr[i]].edges.find(idArr[i]) == nodes[idArr[i]].edges.end()){
            nodes[idArr[i]].edges.insert({idArr[i+1], tmpValue});
            nodes[idArr[i+1]].edges.insert({idArr[i], tmpValue});
        } else if (tmpValue < nodes[idArr[i]].edges.at(idArr[i])){
            nodes[idArr[i]].edges.at(idArr[i+1]) = tmpValue;
            nodes[idArr[i+1]].edges.at(idArr[i]) = tmpValue;
        }
    }
}

int findPath(int startIndex, int destIndex, int size){       //Dijkstra
    int* ranges = new int[size];
    queue<int> Q;
    Node* tmp;
    Q.push(startIndex);
    for(int i = 0; i < size; i++){
        ranges[i] = INT32_MAX;
    }
    ranges[startIndex] = 0;

    while(!Q.empty()){
        tmp = &nodes[Q.front()];
        Q.pop();
        if(!tmp->visited){
            tmp->visited == true;
            for(auto &iter: tmp->edges){ 
                if(ranges[iter.first] > ranges[tmp->index] + iter.second){      
                    ranges[iter.first] = ranges[tmp->index] + iter.second;      
                    Q.push(iter.first);                                         
                }
            }
        }
    }

    int result = ranges[destIndex];
    delete[] ranges;
    return result;
}

bool compareX(int& a, int& b){
    return nodes[a].x < nodes[b].x;
}

bool compareY(int& a, int& b){
    return nodes[a].y < nodes[b].y;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n, tmpX, tmpY;
    cin >> n;
    
    nodes = new Node[n];
    idArr = new int[n];

    for(int i = 0; i < n; i++){
        cin >> tmpX >> tmpY;
        nodes[i].setValues(i, tmpX, tmpY);
        idArr[i] = i;
    }
    cin >> tmpX;
    int startIndex = nodes[tmpX].index;
    cin >> tmpY;
    int destinationIndex = nodes[tmpY].index;

    sort(idArr, idArr + n, compareX);
    buildGraph(n, Node::compareX);
    sort(idArr, idArr + n, compareY);
    buildGraph(n, Node::compareY);

    cout << findPath(startIndex, destinationIndex, n);

    delete[] nodes;
    delete[] idArr;
    
    return 0;
}
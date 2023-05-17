#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using std::cin, std::cout, std::vector, std::queue;

struct Node{
    int value;
    vector<Node*> edges;
    Node* pair;
    int distance = INT_MAX;
    Node(){};
};

Node* dummy = new Node();

vector<Node*> createGraph(Node** board, const int& size){
    int j, i;
    vector<Node*> result;
    bool valid;
    for(int i = 0; i < size; i++){
        for(int j = i % 2; j < size; j+=2){
            valid = false;
            switch (board[i][j].value){
                case 0:{
                    break;
                }
                case 1:{
                    if(i >= 1 && j < size - 2){
                        if(board[i-1][j+2].value != 0){
                            board[i][j].edges.push_back(&board[i-1][j+2]);
                            board[i-1][j+2].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    if( j < size - 3){
                        if(board[i][j+3].value != 0){
                            board[i][j].edges.push_back(&board[i][j+3]);
                            board[i][j+3].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    if(i < size - 1 && j < size - 2){
                        if(board[i+1][j+2].value != 0){
                            board[i][j].edges.push_back(&board[i+1][j+2]);
                            board[i+1][j+2].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    break;
                }
                case 2:{
                    if(i >= 1){
                        if(board[i-1][j].value != 0){
                            board[i][j].edges.push_back(&board[i-1][j]);
                            board[i-1][j].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    if( j < size - 1){
                        if(board[i][j+1].value != 0){
                            board[i][j].edges.push_back(&board[i][j+1]);
                            board[i][j+1].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    if(i < size - 1){
                        if(board[i+1][j].value != 0){
                            board[i][j].edges.push_back(&board[i+1][j]);
                            board[i+1][j].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    break;
                }
                case 3:{
                    if(i >= 1 && j < size - 2){
                        if(board[i-1][j+2].value != 0){
                            board[i][j].edges.push_back(&board[i-1][j+2]);
                            board[i-1][j+2].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    if( j < size - 1){
                        if(board[i][j+1].value != 0){
                            board[i][j].edges.push_back(&board[i][j+1]);
                            board[i][j+1].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    if(i < size - 1 && j < size - 2){
                        if(board[i+1][j+2].value != 0){
                            board[i][j].edges.push_back(&board[i+1][j+2]);
                            board[i+1][j+2].edges.push_back(&board[i][j]);
                            valid = true;
                        }
                    }
                    break;
                }
            }
            if(valid) result.push_back(&board[i][j]);
        }
    }
    return result;
}

bool bfs(const vector<Node*>& blacks) {
    queue<Node*> Q;
    for(int i = 0; i < blacks.size(); i++){
        if(blacks[i]->pair == dummy){
            blacks[i]->distance = 0;
            Q.push(blacks[i]);
        } else {
            blacks[i]->distance = INT_MAX;
        }
    }
    Node* temp;
    dummy->distance = INT_MAX;
    while(!Q.empty()){
        temp = Q.front();
        Q.pop();
        if(temp->distance < dummy->distance){
            for(int i = 0; i < temp->edges.size(); i++){
                if(temp->edges[i]->pair->distance == INT_MAX){
                    temp->edges[i]->pair->distance = temp->distance + 1;
                    Q.push(temp->edges[i]->pair);
                }
            }
        }
    }
    return dummy->distance != INT_MAX;
}

bool dfs(Node* node) {
    if(node != dummy){
        for(int i = 0; i < node->edges.size(); i++){
            if(node->edges[i]->pair->distance == node->distance + 1 && dfs(node->edges[i]->pair)){
                node->edges[i]->pair = node;
                node->pair = node->edges[i];
                return true;
            }
        }
        node->distance = INT_MAX;
        return false;
    }
    return true;
}

int hopcroft_karp(const vector<Node*>& blacks) {
    int pairs = 0;
    while(bfs(blacks)){
        for(int i = 0; i < blacks.size(); i++){
            if(blacks[i]->pair == dummy && dfs(blacks[i])){
                pairs++;
            }
        }
    }
    return pairs;
}

int main(){
    int n, x, y, val;
    cin >> n;
    Node** board = new Node*[n];
    for(int i = 0; i < n; i++){
        board[i] = new Node[n];
        for(int j = 0; j < n; j++){
            cin >> board[i][j].value;
            board[i][j].pair = dummy;
        }
    }

    vector<Node*> blacks = createGraph(board, n);

    cout << n*n - hopcroft_karp(blacks);

    for(int i = 0; i < n; i++){
        delete[] board[i];
    }
    delete[] board;
    delete dummy;

    return 0;
}
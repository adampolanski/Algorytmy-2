#include <iostream>
#include <unordered_set>

using std::cout, std::cin, std::unordered_set;

struct Node{
    int val;
    Node* less;
    Node* more;
    Node(const int& val){
        this->val = val;
        this->less = NULL;
        this->more = NULL;    
    }
    void addNode(Node* newNode){
        if(newNode->val == this->val){
            return;
        }
        if(newNode->val < this->val){
            if(this->less == NULL){
                this->less = newNode;
            } else {
                less->addNode(newNode);
            }
        } else {
            if(this->more == NULL){
                this->more = newNode;
            } else {
                more->addNode(newNode);
            }
        }
        return;
    }
        
    Node* cutMinMax(Node* curr, const int& min, const int& max){
        if(curr == NULL) return NULL;
        curr->less = cutMinMax(curr->less, min, max);
        curr->more = cutMinMax(curr->more, min, max);

        if(curr->val < min){
            Node* tmp = curr->more;
            delete curr;
            return tmp;
        }

        if(curr->val > max){
            Node* tmp = curr->less;
            delete curr;
            return tmp;
        }

        return curr;
    }

    void insertValues(Node* curr, unordered_set<int>& set){
        if(curr == NULL){return;}
        
        insertValues(curr->more, set);
        set.insert(curr->val);
        insertValues(curr->less, set);
    }
};

void findAnswer(int& answ1, int& answ2, const int& value, const unordered_set<int>& set){
    int diff;
    for(int x : set){
        diff = value - x;
        if(set.find(diff) != set.end()){
            if(abs(answ1 - answ2) > abs(diff - x) || (answ1 == -1 && answ2 == -1)){
                answ1 = std::min(diff, x);
                answ2 = std::max(diff, x);
            }
        }
    }
}

int main(){
    int n, tmp;
    cin >> n;
    if(n > 0) cin >> tmp;
    Node* top = new Node(tmp);
    Node* nNode;
    for(int i = 1; i < n; i++){
        cin >> tmp;
        nNode = new Node(tmp);
        top->addNode(nNode);
    }

    int minVal, maxVal;
    cin >> minVal >> maxVal;
    top = top->cutMinMax(top, minVal, maxVal);

    int answSum;
    cin >> answSum;
    unordered_set<int> set;
    top->insertValues(top, set);

    int answ1 = -1;
    int answ2 = -1;
    findAnswer(answ1, answ2, answSum, set);

    if(answ1 == -1 || answ2 == -1){cout << "NIE ZNALEZIONO";}
    else {cout << answ1 << " " << answ2;}
    
    return 0;
}
#include <iostream>
#include <string>

using std::cin, std::cout, std::string;

struct Node{
    bool red;
    string key;
    Node* lLeft;
    Node* lRight;
    Node* trLeft;
    Node* trRight;
    Node* trTop;
    Node(string key){
        this->key = key;
        this->red = true;
        this->trTop = NULL;
        this->lLeft = NULL;
        this->lRight = NULL;
    }

    void addNode(Node* newNode){
        if(this->key == newNode->key){
            return;
        }
        if(newNode->key < this->key){
            if(this->trLeft->key != ""){
                this->trLeft->addNode(newNode);
                return;
            } else {
                this->trLeft = newNode;
                newNode->trTop = this;
            }
        } else {
            if(this->trRight->key != ""){
                this->trRight->addNode(newNode);
                return;
            } else {
                this->trRight = newNode;
                newNode->trTop = this;
            }
        }
    }

    Node* findKey(const string& key){
        if(this->key == key) return this;
        if(key < this->key && this->trLeft->key != "") return this->trLeft->findKey(key);
        if(key > this->key && this->trRight->key != "") return this->trRight->findKey(key);
    }
};

Node* sentinel;

struct rbTree{
    Node* root;
    rbTree(){
        root = NULL;
    }

    void addNode(Node* newNode){
        newNode->trLeft = sentinel;
        newNode->trRight = sentinel;
        newNode->trTop = sentinel;

        if(root == NULL){
            root = newNode;
        } else {
            root->addNode(newNode);
        }

        checkTree(newNode);
    }

    void rotateLeft(Node* tNode){
        Node* rNode = tNode->trRight;

        if(root == tNode){
            root = rNode;
        }

        if(tNode->trTop != sentinel){
            if(tNode->trTop->trLeft == tNode){
                tNode->trTop->trLeft = rNode;
            } else {
                tNode->trTop->trRight = rNode;
            }
        }
        rNode->trTop = tNode->trTop;
        tNode->trTop = rNode;

        tNode->trRight = rNode->trLeft;
        rNode->trLeft->trTop = tNode;

        rNode->trLeft = tNode;
        return;
    }

    void rotateRight(Node* tNode){
        Node* lNode = tNode->trLeft;

        if(root == tNode){
            root = lNode;
        }

        if(tNode->trTop != sentinel){
            if(tNode->trTop->trLeft == tNode){
                tNode->trTop->trLeft = lNode;
            } else {
                tNode->trTop->trRight = lNode;
            }
        }        
        lNode->trTop = tNode->trTop;
        tNode->trTop = lNode;

        tNode->trLeft = lNode->trRight;
        lNode->trRight->trTop = tNode;

        lNode->trRight = tNode;
        return;
    }

    void checkTree(Node* newNode){
        if(newNode == root){
            newNode->red = false;
            return;
        }
        if(!newNode->trTop->red){
            return;
        } else {
            if(newNode->trTop->trLeft == newNode){ //lewy syn
                if(newNode->trTop->trTop->trLeft == newNode->trTop){ //ojciec lewym synem dziadka
                    if(newNode->trTop->trTop->trRight->red){ //wujek jest czerwony
                        newNode->trTop->red = false;
                        newNode->trTop->trTop->trRight->red = false;
                        if(newNode->trTop->trTop == root){
                            return;
                        } else {
                            newNode->trTop->trTop->red = true;
                            checkTree(newNode->trTop->trTop);
                            return;
                        }
                    } else { //wujek jest czarny
                        newNode->trTop->red = !newNode->trTop->red;
                        newNode->trTop->trTop->red = !newNode->trTop->trTop->red;
                        rotateRight(newNode->trTop->trTop);
                    }
                } else { //ojciec prawym synem dziadka
                    if(newNode->trTop->trTop->trLeft->red){ //wujek jest czerwony
                        newNode->trTop->red = false;
                        newNode->trTop->trTop->trLeft->red = false;
                        if(newNode->trTop->trTop == root){
                            return;
                        } else {
                            newNode->trTop->trTop->red = true;
                            checkTree(newNode->trTop->trTop);
                            return;
                        }
                    } else { //wujek jest czarny
                        rotateRight(newNode->trTop);
                        newNode = newNode->trRight;
                        newNode->trTop->red = !newNode->trTop->red;
                        newNode->trTop->trTop->red = !newNode->trTop->trTop->red;
                        rotateLeft(newNode->trTop->trTop);
                    }
                }
            } else { //prawy syn
                if(newNode->trTop->trTop->trLeft == newNode->trTop){ //ojciec lewym synem dziadka
                    if(newNode->trTop->trTop->trRight->red){ //wujek jest czerwony
                        newNode->trTop->red = false;
                        newNode->trTop->trTop->trRight->red = false;
                        if(newNode->trTop->trTop == root){
                            return;
                        } else {
                            newNode->trTop->trTop->red = true;
                            checkTree(newNode->trTop->trTop);
                            return;
                        }
                    } else { //wujek jest czarny
                        rotateLeft(newNode->trTop);
                        newNode = newNode->trLeft;
                        newNode->trTop->red = !newNode->trTop->red;
                        newNode->trTop->trTop->red = !newNode->trTop->trTop->red;
                        rotateRight(newNode->trTop->trTop);
                    }
                } else { //ojciec prawym synem dziadka
                    if(newNode->trTop->trTop->trLeft->red){ //wujek jest czerwony
                        newNode->trTop->red = false;
                        newNode->trTop->trTop->trLeft->red = false;
                        if(newNode->trTop->trTop == root){
                            return;
                        } else {
                            newNode->trTop->trTop->red = true;
                            checkTree(newNode->trTop->trTop);
                            return;
                        }
                    } else {
                        newNode->trTop->red = !newNode->trTop->red;
                        newNode->trTop->trTop->red = !newNode->trTop->trTop->red;
                        rotateLeft(newNode->trTop->trTop);
                    }
                }
            }
        }
    }

    Node* find(const string& key){
        return root->findKey(key);
    }
};

struct List{
    Node* first;
    Node* last;

    List(){
        this->first = sentinel;
        this->last = sentinel;
    }

    ~List(){
        Node* tmp = last;
        while(tmp != sentinel){
            last = tmp->lLeft;
            delete tmp;
            tmp = last;
        }
    }

    void push_back(Node* newNode){
        newNode->lLeft = sentinel;
        newNode->lRight = sentinel;
        if(this->first == sentinel){
            this->first = newNode;
            this->last = newNode;
        } else {
            this->last->lRight = newNode;
            newNode->lLeft = this->last;
            this->last = newNode;
        }
    }

    void move(Node* a, int moves){
        if(moves == 0) return;
        Node* tmp = a;

        if(moves > 0){
            if(tmp == first) return;
            while(moves != 0){
                if(tmp->lLeft == sentinel){
                    moves = 0;
                    this->first = a;
                } else {
                    tmp = tmp->lLeft;
                    moves--;
                }
            }
            if(tmp->lLeft == sentinel){
                this->first = a;
            }

            if(a->lLeft != sentinel) {
                a->lLeft->lRight = a->lRight;
                tmp->lLeft->lRight = a;

            }
            if(a->lRight != sentinel) {a->lRight->lLeft = a->lLeft;}
            else {this->last = a->lLeft;}

            a->lLeft = tmp->lLeft;
            tmp->lLeft = a;
            a->lRight = tmp;

        } else {
            if(tmp == last) return;
            while(moves != 0){
                if(tmp->lRight == sentinel){
                    moves = 0;
                    this->last = a;
                } else {
                    tmp = tmp->lRight;
                    moves++;
                }
            }
            if(tmp->lRight == sentinel){
                this->last = a;
            }

            if(a->lRight != sentinel) {
                a->lRight->lLeft = a->lLeft;
                tmp->lRight->lLeft = a;

            }
            if(a->lLeft!= sentinel) {a->lLeft->lRight = a->lRight;}
            else {this->first = a->lRight;}

            a->lRight = tmp->lRight;
            tmp->lRight = a;
            a->lLeft = tmp;
        }
    }

    void swap(Node* a, Node* b){

        if(a == first){
            first = b;
        } else if(b == first){
            first = a;
        }

        if(a == last){
            last = b;
        } else if(b == last){
            last = a;
        }

        Node* tmp;

        tmp = a->lLeft;
        if(tmp != sentinel){
            tmp->lRight = b;
        }

        a->lLeft = b->lLeft;
        b->lLeft->lRight = a;

        b->lLeft = tmp;

        tmp = a->lRight;
        if(tmp != sentinel){
            tmp->lLeft = b;
        }

        a->lRight = b->lRight;
        b->lRight->lLeft = a;

        b->lRight = tmp;
    }

    void display(){
        Node* tmp = first;
        while(tmp != sentinel){
            cout << tmp->key << "\n";
            tmp = tmp->lRight;
        }
    }
};

int main(){
    sentinel = new Node("");
    sentinel->red = false;
    int n, m, index = 0;
    string s;
    Node* newNode;
    Node* a;
    Node* b;
    rbTree* tree = new rbTree();
    List* list = new List();
    cin >> n;

    while(index < n){
        cin >> s;
        newNode = new Node(s);
        tree->addNode(newNode);
        list->push_back(newNode);
        index++;
    }

    cin >> m;
    char op;
    int moves;

    for(int i = 0; i < m; i++){
        cin >> op;

        switch(op){
            case 'a':{
                cin >> s;
                newNode = new Node(s);
                tree->addNode(newNode);
                list->push_back(newNode);
                index++;
                break;
            }
            case 'm':{
                cin >> s;
                cin >> moves;
                a = tree->find(s);

                list->move(a, moves);

                break;
            }
            case 'r':{
                cin >> s;
                a = tree->find(s);
                cin >> s;
                b = tree->find(s);
                list->swap(a, b);
                break;
            }
        }
    }

    list->display();
 
    delete tree;
    delete list;
    delete sentinel;

    return 0;
}
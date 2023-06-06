#include <stdio.h>
#include <list>
#include <stack>
#include <math.h>

using std::list, std::stack;
using std::pow, std::atan2;

struct Point{
    int x, y;
    float dist, alpha;

    Point(int x, int y){
        this->x = x;
        this->y = y;
        this->dist = 0;
        this->alpha = 0;
    }

    void setDistanceSquared(Point* a){
        this->dist = pow((this->x - a->x), 2) + pow((this->y - a->y), 2);
    }

    void setAlpha(Point* a){
        this->alpha = atan2((this->y - a->y), (this->x - a->x));
    }

    static bool compare(Point* a, Point* b){
        if(a->alpha != b->alpha)
            return a->alpha < b->alpha;
        else
            return a->dist < b->dist;
    }

    static float getDistance(Point* a, Point* b){
        return sqrt((float)(pow((a->x - b->x), 2) + pow((a->y - b->y), 2)));
    }
};

void trimByAlpha(list<Point*>& L){
    for(auto i = L.begin(), prev = L.end(); i != L.end(); prev = i, i++){
        if(prev != L.end() && (*i)->alpha == (*prev)->alpha){
            delete (*prev);
            L.erase(prev);
        }
    }
}

int getMatrixDeterminant(Point* a, Point* b, Point* c){
    int result = 0;

    result += b->x * c->y;
    result += c->x * a->y;
    result += a->x * b->y;
    result -= b->x * a->y;
    result -= a->x * c->y;
    result -= c->x * b->y;
    
    return result;
}

void getConvexHull(stack<Point*>& S, list<Point*>& L){
    Point* first;
    Point* second;
    Point* p;
    while(!L.empty()){
        second = S.top();
        S.pop();
        first = S.top();
        p = L.front();
        if(getMatrixDeterminant(first, second, p) <= 0){
            delete second;
        } else {
            S.push(second);
            S.push(p);
            L.pop_front();
        }
    }
}

float getCirc(stack<Point*>& S){
    float result = 0.0f;
    Point* start = S.top();
    Point* first = S.top();
    S.pop();
    Point* second;
    while(!S.empty()){
        second = S.top();
        S.pop();
        result += Point::getDistance(first, second);
        if(first != start) delete first;
        first = second;
    }
    result += Point::getDistance(second, start);
    delete start;
    return result;
} 

int main(){

    int n;
    scanf("%d", &n);

    list<Point*> L;
    Point* start = NULL;
    int x, y;
    for(int i = 0; i < n; i++){
        scanf("%d %d", &x, &y);

        if(start == NULL){
            start = new Point(x, y);
        } else if(y < start->y || (y == start->y && x < start->y)){
            L.push_front(start);
            start = new Point(x, y);
        } else {
            L.push_back(new Point(x, y));
        }
    }

    for(Point* p: L){
        p->setDistanceSquared(start);
        p->setAlpha(start);
    }

    L.sort(Point::compare);

    trimByAlpha(L);

    stack<Point*> S;
    S.push(start);
    S.push(L.front());
    L.pop_front();
    S.push(L.front());
    L.pop_front();

    getConvexHull(S, L);

    printf("%.02f", getCirc(S));

    return 0;
}
/*
  Algorytm Grahama - otoczka wypukla
  wybieramy skrajnie dolny-lewy punkt - najmniejszy y i wtedy pierwszy z lewej
  sprawdzamy punkt posrodku dwoch punktow:
  - jak po srodku to wywalamy go
  - jak po lewej to wywalam
  - jak po prawej to dodaje

  jak okreslic z ktorej jest punkt?
  iloczyn wektorowy - z tych 3 punktow - zapisujemy w macierzy
  | 1  1  1  |
  | x1 x2 x3 |
  | y1 y2 y3 |
  aby okreslic strone to obliczyc wyznacznik macierzy - (mnozenie na ukosy)
  jezeli jest <0 to po lewej stronie, =0 to na linii - jak wiekszy to po prawej

  liczyc arctan aby liczyc kat - amplituda - funkcja wbudowana chb

  jak amplituda (alfa) jest rowna to wykluczamy punkty blizsze - liczymy odleglosc - sa wspoliniowe wiec nie trzeba pierwiastka

  test moze byc co ma punkty w prawie jednej liniii tylko

  1. posortowac - kat i odleglosc
  2. usunac wspoliniowe - O(n)
  3. posortowac pozostale

  1 albo 3 wybrac - nie dwa na raz

  ALGORYTM:
  (L to lista - std np.)
  1. L = {A,B,C,D,E,...} - szukamy punktu skrajnie dolnego i skrajnie lewego - min(y), min(x)
    znalezlismy punkt O - zlozonosc O(n)
  2. O, L = {A,B,C,D,E,...} - O usuwamy juz z tej listy bo niepotrzebny
    liczymy alfe i odleglosc d
    dla kazdego punktu robimy funkcje liczaca odleglosc od O do tego punktu
    atan2 do liczenia alfy
    (x1 - x2)^2 + (y1 - y2)^2 do liczenia odleglosci - bez pierwiastka
    zlozonosc O(n)
  3. sortujemy punkty - comparator najpierw po alfa potem po d
    zlozonosc O(nlogn) - MOZNA SORTA Z STL
  4. usuwamy elementy o tym samym alfa
    zlozonosc O(n)
  5. inicjalizacja struktur danych - stos - na stos trafia O i pierwsze 2 z listy ~
    S = {O,B,C}, L = {E,F,...}
  6.  def(B,C,O) - dwa ostatnie punkty ze stosu i pierwszy element z listy
    jezeli jej wartosc jest <= 0 to ze stosu sciagam element ostatni (C) [S.pop()] i
    teraz robie dla kolejnych def(O,B,E) > 0 to na stos wrzucam E i usuwam go z listy - [S.push(E), L.pop_front()]
    ^ wywolujemy w petli dla calej listy - for elem in L:...
    zlozonosc O(n)
  7. L = {} - na stosie sa wszystkie elementy tworzace otoczke wypukla S = {O,B,E,...}
  8. Obliczyc obwod figury:
    |OB| + |BE| + |EF| + ... = wynik algorytmu
    zlozonosc O(n)
  CZYLI ZLOZONOSC O(nlogn) ale duzo O(n) wiec trzeba optymalnie wszystko

  PRZYKLAD:
  wejscie jak w przykladzie na tichy - punkty A,B,C,D,E,F,G,H,I
  1. najnizszy po lewej stronie to punkt A(1,1), wiec L = {B,C,D,E,F,G,H,I}
  2. wyznaczam
  3. sortuje liste -> O(1,1), L = {D,G,H,E,I,F,B,C}
  4. iteruje po kolei i usuwam punkty o tych samych katach - zostawiam drugi ~ usuwam w srodku trojki
  5. O(1,1), L = {G,H,I,F,C}
  stos S = {O,G,H}, lista L = {I,F,C}
  6. iteruje po elementach listy
    sprawdzam wartosc wyznacznika macierzy - dwa ostatnie ze stosu i pierwszy z listy - czy  >= 0 -> usuwam ze stosu ostatni element: S = {O,G}
    iteruje dalej S = {O,G,I}, L = {F,C} >= 0 nie -> dodaje na stos i usuwam z listy
    ??? - iteruje po kolei az sie lista skonczy
    {OGIF}
    {OIFC}
    {OGIC}
  7. stos na koniec S = {O,G,I,C}
  8. iteruje w petli po stosie i licze dlugosci odcinkow |OG| + |GI| + |IC| + |CO| = 2 + 2 + 2 + 2 = 8.00
*/

#include <iostream>
#include <list>
#include <stack>
#include <math.h>

using std::cout, std::cin;
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

    void display(){
        printf("x: %d\ny: %d\ndist: %0.2f\nalpha: %0.2f\n\n", this->x, this->y, this->dist, this->alpha);
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
};

void trimByAlpha(list<Point*>& L){
    for(auto i = L.begin(), prev = L.end(); i != L.end(); prev = i, i++){
        if(prev != L.end() && (*i)->alpha == (*prev)->alpha){
            delete (*prev);
            L.erase(prev);
        }
    }
}

int main(){
    int n;
    cin >> n;

    list<Point*> L;
    Point* start = NULL;
    int x, y;
    for(int i = 0; i < n; i++){
        cin >> x >> y;

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



    start->display();

    for(Point* p: L){
        p->display();
        delete p;
    }

    return 0;
}
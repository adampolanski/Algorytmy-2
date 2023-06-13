#include <iostream>
#include <math.h>

using std::cin, std::cout;

double butelka(double cm) {
    return 10 - (cm-2) * (cm-2);
}

double getV(double a, double b, int n = 1000){
    double result = 0;
    double h = (b - a) / n;

    for(int i = 0; i < n; i++){
        double x = i * h;
        result += pow(butelka(x), 2) * h;
    }
    return M_PI * result;
}

int main(){
    double x, y, z, p;
    cin >> x >> y >> z >> p;
    double maxV = x*y*z;
    double target = maxV - x*y*z*p;

    int n;
    double f;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> f;
        target -= getV(0, f);
        if(target < 0){
            cout << i+1;
            break;
        }
    } 
    if(target >= 0){
        cout << "NIE";
    }  
    return 0;
}
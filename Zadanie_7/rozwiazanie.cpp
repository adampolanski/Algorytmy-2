#include <iostream>

using std::cin, std::cout;

double butelka(double cm) {
	return 10 - (cm-2) * (cm-2);
}

double getV(double f, int n = 20){
    double h = f / n;
    double result = 0;
    for(int i = 1; i < n; i++){
        result += ((butelka(h * (i - 1)) + butelka(h * i)) / 2) * h;
    }
    cout << result << "\n";
    return result;
}

int main(){
    double x, y, z, p;
    cin >> x >> y >> z >> p;
    double maxV = x*y*z;
    double target = maxV - x*y*z*p;

    int n;
    double f, height = 0;
    cin >> n;
    double currentV = 0;
    for(int i = 0; i < n; i++){
        cin >> f;
        height += f;
        currentV = getV(height);
        if(currentV > target){
            cout << i+1;
            break;
        }
    } 
    if(currentV <= target){
        cout << "NIE";
    }  
    return 0;
}
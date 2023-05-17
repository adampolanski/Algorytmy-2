#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::getline;

char parse_char(char& c){
    if(c == '?' || c == '!' || c == ',' || c == ';' || c == ':' || c == '-' ){
        c = '.';
    } else if(isdigit(c)){
        c = '0';
    } else if(isupper(c)){
        c = 'A';
    } else if(islower(c)){
        c = 'a';
    }
    return c;
}

int* create_prefix(string key){
    int* ps = new int[key.length()];
    ps[0] = 0;

    int l = 0;
    int i = 1;

    while(i < key.length()){
        if(key[l] == key[i]){
            l++;
            ps[i] = l;
            i++;
        } else {
            if(l > 0){
                l = ps[l-1];
            } else {
                ps[i] = l;
                i++;
            }
        }
    }

    return ps;
}

char find_pattern(string& key, int* ps){
    int key_iter = 0;
    char t;
    bool next = true;

    while(true){
        if(next) t = getchar();
        next = true;
        if(key_iter == key.length()) return 'T';
        if(t == '\n' || t == 3) return 'N';

        if(parse_char(t) == key[key_iter]){
            key_iter++;
        } else {
            if(key_iter > 0){
                key_iter = ps[key_iter - 1];
                next = false;
            }
        }
    }
}

int main(){
    string text, key;
    getline(cin, key);
    int* ps = create_prefix(key);
    
    cout << find_pattern(key, ps);

    delete ps;
    return 0;
}
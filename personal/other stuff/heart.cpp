#include <iostream>

using namespace std;

int main(){
    cout << " ___       ___" << endl;
    cout << "/    \\____/   \\ " << endl;
    cout << "|             |" << endl;
    for (int j = 11; j > 0; j--){
        cout << "\\";
        for (int i = j; i > 0; i--){
            cout << " ";
        }
        cout << "/" << endl;
    }
}
#include <iostream>

using namespace std;

int main(){

    char c;

    cin >> c;

    if(isdigit(c))   cout << "this is a digit\n";

    else cout << "this is not a digit\n";

    string str = "penis cock poop";

    string str2 = str;

    cout << str2 << endl << endl;

    int array[10][10];

    if(str == "penis cock poop"){
        //do something
    }

    while(str == "penis cock poop"){
        str = "penis poop cock";
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            array[i][j] = j;
        }
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << array[i][j];
        }
        cout << endl;
    }

    return 0;
}
#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to Dausen's darts simulation!\n\tSelect a mode:\n\t\t(C)ricket\n\t\t(0)1\n";

    char selection;

    cin >> selection;

    cout << "You chose: ";

    if(toupper(selection) == 'C') cout << "Cricket";
    else if (selection == '0') cout << "01\n";

    if(selection == '0'){
        cout << "301? 501? Something else?\n";

        int sel;

        cin >> sel;

        cout << sel * 100 + 1;
    }


    return 0;
}
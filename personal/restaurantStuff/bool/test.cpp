#include <iostream>
#include "tableOrg.cpp"
#include "staffing.cpp"

using namespace std;

int main(){
    int num;
    cout << "welcome to the earliest testing phase of the new CM accounting software\n\t\t(how exciting!)\n";

    cout << "i think this is a start. enter a number i guess" << endl;
    cin >> num;

    cout << "you entered: " << num << endl;

    int g = 3;
    Table test(num, g);

    test.printInfo();

    test.printPerson();

    return 0;
}
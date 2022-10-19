#include <iostream>
#include <fstream>
#include "ops.cpp"
#include "class.cpp"

using namespace std;

int main(int argc, char **argv){
    cout << "welcome to aloha analysis (note to self: make a better name)\n\t\tby dausen\n";

    string choice;

    cout << "Proceeding with regular startup (reading weekly menu mix). Enter y to continue or n to canacel\n\n";

    cin >> choice;

    if(choice == "y"){
        string date;
        cout << "please enter today's date (format mmddyyyy)\n";
        cin >> date;
        string reportName = "dbonerReport" + date + ".txt";

        cout << "report name: \n\t" << reportName << endl;
        newReport(reportName);
    }

    while(choice != "exit"){
        //do stuff
        cout << "enter choice\n";
        cin >> choice;
    }

    return 0;
}

/*
TO DO:
    print statement promting choices
    take input file
    write class file
    write operations file
 */
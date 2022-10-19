#include <iostream>
#include <fstream>
#include "class.cpp"

using namespace std;

void newReport(string reportName){
    ifstream inputFile;
    inputFile.open("testInput1.txt", ios::in);

    string test;
    getline(inputFile, test);

    cout << test << endl;

    getline(inputFile, test);
    getline(inputFile, test);

    cout << test << endl;

    Item *buf = new Item(test);

    buf->print();
    cout << endl;

    ofstream outFile;
    outFile.open(reportName);
    outFile << test;

    return;
}

void write(){
    cout << "\twrite function entered\n";
}

void read(){
    cout << "\tread function entered\n";
    //do stuff
    return;
}

void compare(){
    cout << "\tcompare function entered!\n";
    //do stuff
    return;
}

/*
TO DO:

*/

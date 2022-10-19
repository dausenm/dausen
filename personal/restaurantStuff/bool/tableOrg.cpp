#include <iostream>

using namespace std;

class Item{
    private:
        int num;
        double cost;
        string name;
        Item *next;
        Item *prev;
    public:
};

class Seat{
    private:
        double total;
        Item *head;

    public:
        Seat(){
            total = 69.69;
            head = nullptr;
        }

        void manualAdjustTotal(double tba){
            total += tba;
        }

        void printSeat(){
            cout << "beginning print seat protocol!\n\ttotal: " << total << endl;
        }
};

class Table{
    private:
        int guests;
        int tableNum;
        double tTotal;
        Seat *seat1;

    public:
        Table(int g, int n){
            guests = g;
            tableNum = n;
            tTotal = 69.42;
            seat1 = new Seat;
        }

        void printPerson(){
            seat1->printSeat();
        }

        void printInfo(){
            cout << "Running Table Print Procedure:\n\tTable #: " << tableNum << "\n\tGuests #: " << guests << "\n\tTotal: " << tTotal << endl;
        }

};
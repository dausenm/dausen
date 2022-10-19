#include <iostream>
#include "tableOrg.cpp"

using namespace std;

class Server{
    private:
        string name;
        double foodSales;
        double beerSales;
        double wineSales;
        double liqSales;
        double totSales;
        double tips;
        double hrly = 2.13;

    public:
        void clockIn(){
            //do stuff
        }

        void clockOut(){
            //do stuff
        }

        void cashOut(){
            //do stuff
        }

        //Table *newTable(){
            //not sure how tables will be organized and associated with the server
            //return new Table(1, 1);
        //}
};

class Bartender: private Server{
    
};
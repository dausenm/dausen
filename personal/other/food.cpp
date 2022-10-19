#include<string>
#include<iostream>
#include<cstdlib>

using namespace std;

void RandomRestaurant();

int main() {
    string in;

    bool keepgoing = true;
    while(keepgoing) {
        RandomRestaurant();

        cout << "keep going? Y/N" << endl;
        
        char reroll = getchar();
        
        if (reroll == 'Y' || reroll == 'y'){
            keepgoing = true;
        }
        else if(reroll == 'N' || reroll == 'n'){
            keepgoing = false;
        }
        
    }

    cout << "Enjoy your meal!\n" << endl;
        
}

void RandomRestaurant(){
    string rests[1000] {"taco casa", "whataburger", "panda", "jalapenos", "chick fil a", "burgerfi", "central mesa", "avenue pub", "urban cookhouse", "urban bar and kitchen", "cook", "boomhobers", "buffalo's cafe", "billys", "metro diner", "wendys", "zaxbys", "mr chens", "mr gs", "chuck's"};
    srand(time(NULL));
    cout << rests[rand() % 20] << endl;
}
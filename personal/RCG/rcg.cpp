/*
for this project, we need to design a cod mw2 random loadout generator.

    class loadout
        private
            gun primary
                attachments for each(optional)
            gun secondary
                attachments for each(optional)
            other equipment
            other tactical
            perks   
                base
                bonus
                ultimate
            field upgrade(optional)
            killstreaks(optional)
            strat/troll

    class gun
        string type;
        string attachments[5];
            
    other things:
        low level mode w/ low level attachments

    public: 
        createLoadout(bool troll){

        }
*/

#include <iostream>
#include "gunsnperks.cpp"
using namespace std;





int main(){

    char troll;
    cout << "Welcome to MW2 Random Class Generator\n\t\t By dausen\n" << "troll mode? Y/N?" << endl;
    cin >> troll;

    bool t = false;
    if(troll == 'Y' || troll == 'y') t = true;

    char reroll = 'y';



    while(1){
        Loadout yeahBoi(t);
        
        cout << "\t\tReroll? Y/N\n";
        cin >> reroll;
        if (reroll == 'n' || reroll == 'N') break;
        cout << "troll mode? Y/N\n";
        cin >> troll;
        if(troll == 'Y' || troll == 'y') t = true;

    }

    cout << "thanks for using this!\n\t\t-dausen";

    return 0;
}
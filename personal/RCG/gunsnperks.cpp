#include <iostream>
using namespace std;

string lethals[] = {"claymore", "frag", "molotov", "c4", "drill charge", "sticky grenade", "throwing knife", "proximity mine", "thermite", "tomahawk"};
string tacticals[] = {"spotter scope", "flash grenade", "stun grenade", "smoke grenade", "snapshot grenade", "heartbeat sensor", "stim", "decoy", "gas grenade", "shock stick"};

string basePerks[] = {"battle hardened", "double time", "scavenger", "tracker", "strong arm", "EOD", "extra tactical", "overkill", "scavenger"};
string bonusPerks[] = {"resupply", "spotter", "cold blooded", "fast hands", "quick fix", "focus"};
string ultPerks[] = {"high alert", "ghost", "hardline", "overclock", "survivor", "bird's eye"};

string attachments[6];  //attachments[0] ar attachments, attachments[1] smg attachments

class gun{
    private:
        int type;   //0 = ar, 1 = smg, 2 = shotgun, 3 = sniper, 4 = marksman, 5 = lmg, 6 = pistol;
        string attachments[5]; // come back to this, may not be 5
        int attCount = 0;          //the main issue with this project will be the attachments, knowing what guns can take what attachments
        

    public:
        gun(){
            cout << "hey dude i dont think this was supposed to happen\n";
            type = 300;
        }

        gun(char type){
            type = 1;
        }
        void createGun(int mode, bool slot){
            int attLimit = 5;

            if(mode == 1){
                cout << "You entered limited mode.\n\tEnter attachment limit:\n";
                cin >> attLimit;
            }

            if (slot){// primary
                if(mode == 0){
                    while(attCount < attLimit){
                        //fetch attachment
                        attCount++;
                    }
                }
            }
            else{//secondary
                if(mode == 0){
                    while(attCount < attLimit){
                        //fetch attachment
                        attCount++;
                    }
                }
            }
            cout << "this->something = " << this->type << "\n\n\t(btw, nice naming there bro)\n" << endl;

            return;
        }
};

class Loadout{
    private:
        gun primary;
        gun secondary;

        string *base[2];
        string *bonus;
        string *ultimate;


    public:

    Loadout(bool troll){
        if(troll) getStrat();
        getGuns();
        getPerks();
        getEquipment();
    }

    void getGuns(){
        cout << "farts and cums a little bit\n";

        int mode1, mode2;
        
        cout << "Enter primary mode:\n\tNormal (fill all slots): 0\n\tLimited (choose how many attachments): 1\n\tBroke Ass Mode (low level attachments only): 2\n\tBase Gun Only: 3\n";
        cin >> mode1;

        cout << "Enter secondary mode:\n\tNormal (fill all slots): 0\n\tLimited (choose how many attachments): 1\n\tBroke Ass Mode (low level attachments only): 2\n\tBase Gun Only: 3\n";
        cin >> mode2;

        primary.createGun(mode1, true);
        secondary.createGun(0, false);
    }

    void getPerks(){
        //what do you think this is supposed to do?
    }

    void getEquipment(){
        //if u use stims you're sweaty
    }

    void getStrat(){
        cout << "i doubt this project will really be worth it,\nbut i think this is the only way it will be\n";
    }
};



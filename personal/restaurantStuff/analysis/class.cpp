#include <iostream>
#pragma once

using namespace std;

class Item{
    private:
        string name;
        double pcCat;
        double pcTot;
        int numSold;
        double totalRev;

    public:
        Item(string line){
            cout << "hey you made it here\n";
            
            int index;

            for(int i = 0; i < line.size(); i++){
                if(line[i] == ' '){
                    if(line[i + 1] == ' '){
                        cout << "\tD: we here. i = " << i << endl;
                        index = i;
                        break;
                    }
                }
            }
            this->name = line.substr(0, index);

            cout << this->name << endl;

            for(int i = index; i < line.size(); i++){
                if(line[i] != ' '){
                    index = i;
                    break;
                }
            }

            cout << "D: value of index: " << index << endl;

            int rIndex;

            for (int i = index; i < line.size(); i++){
                if(line[i] == ' '){
                    cout << "\tD: how many times does this hit?" << endl;
                    if(line[i + 1] == ' '){
                        cout << "\t\tD: value of i: " << i << endl;
                        rIndex = i - index;
                        break;
                    }
                }
            }

            string buf = line.substr(index, rIndex);

            cout << "\tD: value used for qty: " << buf << endl;

            this->numSold = stoi(buf);

            for(int i = index + rIndex; i < line.size(); i++){
                if(line[i] == '$'){
                    index = i + 1;
                }
            }

            for(int i = index; i < line.size(); i++){
                if(line[i] == ' '){
                    rIndex = i - index;
                    break;
                }
            }

            buf = line.substr(index, rIndex);

            cout << "\tD: buf: " << buf << endl;

            this->totalRev = stof(buf);

            for(int i = index + rIndex; i < line.size(); i++){
                if(isdigit(line[i])){
                    index = i;
                    break;
                }
            }

            for(int i = index; i < line.size(); i++){
                if(line[i] == ' '){
                    rIndex = i - index;
                    break;
                }
            }

            buf = line.substr(index, rIndex);

            this->pcCat = stof(buf);

            for(int i = index + rIndex; i < line.size(); i++){
                if(isdigit(line[i])){
                    index = i;
                    break;
                }
            }

            for(int i = index; i < line.size(); i++){
                if(line[i] == ' '){
                    rIndex = i - index;
                    break;
                }
            }

            buf = line.substr(index, rIndex);

            this->pcTot = stof(buf);
        }

        void print(){
            cout << "\tD: you are in the print function.\n\t\tName: ";
            cout << name;

            cout << endl << "\t\tnumSold: " << numSold;

            cout << endl << "\t\ttotalRev: " << totalRev;

            cout << endl << "\t\tpcCat: " << pcCat;

            cout << endl << "\t\tpcTot: " << pcTot;
        }
};

/*
TO DO:

*/
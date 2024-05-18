#include <iostream>

using namespace std;

void fiveohone(int startingScore);
int calculateScore(string dart1, string dart2, string dart3);
int calculateDartScore(string dart);
bool checkForDouble(string dart);
bool checkForTriple(string dart);
bool checkValidDarts(string dart1, string dart2, string dart3);
bool check(string dart);

int main() {
    cout << "Welcome to Dausen's darts tool!\nFor information on how to use this utility, I have nothing for you yet lol\n\n\n\tSelect a mode:\n\t\t(C)ricket\n\t\t(0)1\n";

    char selection;

    cin >> selection;

    cout << "You chose: ";

    if(toupper(selection) == 'C') cout << "Cricket";
    else if (selection == '0') cout << "01\n";

    if(selection == '0'){
        cout << "301? 501? Something else?\n";

        int sel;

        cin >> sel;

        int startingScore = sel * 100 + 1;

        cout << "\tD:starting score: " << startingScore << endl;

        fiveohone(startingScore);
    }
    
    cout << "Thanks for using this!\n";

    return 0;
}

void fiveohone(int startingScore){
    cout << "\tD: we here bruh\n";

    int playerScore = startingScore, opponentScore = startingScore;

    while(!(playerScore ==0) || !(opponentScore == 0)){
        string dart1, dart2, dart3;
        cout << "Player Turn\n\tYou have " << playerScore << " left.\tEnter Dart 1.\n";

        cin >> dart1;

        cout << "\tEnter dart 2.\n";

        cin >> dart2;

        cout << "\tEnter dart 3.\n";

        cin >> dart3;

        char dub = dart3[0];

        bool valid = checkValidDarts(dart1, dart2, dart3);

        if(!valid){
            cout << "ERROR: Darts not valid!\n\tUsage: t20 (triple 20), s15 (single 15), d25 (double bull)\n";

            continue;
        }

        int roundScore = calculateScore(dart1, dart2, dart3);

        cout << "Score for this round: " << roundScore << endl;;

        if(playerScore - roundScore == 0 && dub == 'd'){
            cout << "Congrats! You win!\n";
            break;
        }
        if(roundScore >= playerScore - 1) cout << "----------BUST----------\n";
        else{
            playerScore -= roundScore;
            cout << "You have " << playerScore << " left." << endl;
        }
    }

    return;
}

int calculateScore(string dart1, string dart2, string dart3){
    int score = 0;

    score += calculateDartScore(dart1);
    score += calculateDartScore(dart2);
    score += calculateDartScore(dart3);

    return score;
}

int calculateDartScore(string dart){
    bool dub = checkForDouble(dart);
    bool trip = checkForTriple(dart);

    char d = dart[0];

    dart.erase(0, 1);

    int score = stoi(dart);

    if(dub) score *= 2;
    if(trip) score *= 3;

    return score;
}

bool checkForTriple(string dart){
    if(tolower(dart[0]) == 't') return true;
    return false;
}

bool checkForDouble(string dart){
    if(tolower(dart[0]) == 'd') return true;
    return false;
}

bool checkValidDarts(string dart1, string dart2, string dart3){
    if(!check(dart1)){
        return false;
    }

    if(!check(dart2)){
        return false;
    }

    if(!check(dart3)){
        return false;
    }

    return true;
}

bool check(string dart){
    if(dart[0] == 't' || dart[0] == 'd' || dart[0] == 's') return true;

    return false; 
}
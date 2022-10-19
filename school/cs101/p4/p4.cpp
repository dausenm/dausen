#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;


uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;
};

class Node {
private:
    Person *cur;
    Person *next;
}

class HashTable {       //write hash table constructor that creates an empty hash table with size TableSize (from command line args)
    private:
        static const int buckets = 8;
        list<pair<int, string>> table[buckets];
    public:
        bool isEmpty() const;
        int hashFn(string key);
        void insertItem(string key, Person *add);
        void printTable();

};

HashTable(int size){
        HashTable *ptr = new HashTable;
        for (int i = 0; i < TS; i++)
            ht[i] = NULL;
    }

bool HashTable::isEmpty() const{
    int sum{};
    for (int i{}; i < buckets; i++){
        sum += table[i].size();
    }
    if(!sum){
        return true;
    }
    return false;
}

void HashTable::insertItem(string key, Person *add){
    int hashValue = hashFn(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    return;
}

int HashTable::hashFn(string key){
    return djb2(key) % buckets;
}

void HashTable::printTable(){
    for(int i{}; i < buckets; i++){
        if(table[i].size() == 0) continue;

        auto bItr = table[i].begin();
        for(; bItr != table[i].end(); bItr++){
            cout << "[INFO] key: " << bItr->first << "Value: " << bItr->second << endl;
        }
    }
    return;
}

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

void AddPersonInfo(int col, Person *toAdd, string text);

int main(int argc, char **argv) {
   
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
   
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    string line, token;
    int i = 0;
    getline(file, line); // consume header line
    Person *add = new Person();
    while (getline(file, line)) {
        istringstream iss(line);
        while (getline(iss, token, '\t')) {
            //cout << token << "\t";
            AddPersonInfo(i, add, token);
            i++;
        }
        //add to hash table here
        //cout << endl;
    }
   
    cout << "attributes, not separated" << add->id << add->first << add->last << add->email << add->phone << add->city << add->state << add->postalCode << endl;

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            // print code here
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            // lookup code here
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}

void AddPersonInfo(int col, Person *toAdd, string text){
    if(col == 0) toAdd->id = text;
    else if(col == 1) toAdd->first = text;
    else if(col == 2) toAdd->last = text;
    else if(col == 3) toAdd->email = text;
    else if(col == 4) toAdd->phone = text;
    else if(col == 5) toAdd->city = text;
    else if(col == 6) toAdd->state = text;
    else if(col == 7) toAdd->postalCode = text;
    return;
}
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <vector>

using namespace std;

class Huffman{                      //currently, this is partially configured for 3 files to build the tree from. Edit to make it accept just 1 file

public:
    struct Node{        //done
        Node *left, *right;
        int key;
    };

    int *selectKey(int input[], int level[], int x, int y){     //done
        int *newLevel = new int[x], j = 0;
        for(int i = 0; i < y; i++)
            if (find(input, 0, x - 1, level[i])) newLevel[j] = level[i], j++;
        return newLevel; 
    }

    int find(int Huff[], int head, int stop, int key){  //done
        for(int i = head; i <= stop; i++){
            if (Huff[i] == key) return i;
        }
        return 0;  
    }

    struct Node *root;

    void buildHuffman(int head, int stop, int size, int v1Array[]){      //done      removed final arg int v2Array
        root = Huff(v1Array, &head, stop , size);
    }

    Node *newNode(int key){     //done
        Node *node = new Node;
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    Node *Huff(int input[], int level[], int head, int stop){        //done
        
        if(sizeof(level) == 0)  return nullptr;
        if (head > stop)        return nullptr;

        Node *root = newNode(level[0]);

        if (head == stop)   return root;
    
        int index = find(input, head, stop, root->key);
        
        int *leftLevel = selectKey(input, level, index);
        int *rightLevel = selectKey(input + index + 1, level, x - 1, x);
        root->left = Huff(input, leftLevel, head, index - 1);     //removed index - head from final arg
        root->right = Huff(input, rightLevel, index + 1, stop);   //removed stop - index from final arg
        
        delete[] leftLevel, delete[] rightLevel;
        return root;
    }

    void decodeText(string str){        //done
        Node* cur = root;
        for(int i = 0; i < str.length(); i++){
            if(str[i] == '0') cur = cur->left;
            
            else cur = cur->right;

            if (cur->key < 128){
                cout << char(cur->key);
                cur = root;
            }
        }
    }
};

void vectorToArray(vector<int> &vector, int *array){        //done
    for(int i = 0; i < vector.size(); i++) array[i] = vector[i];
}



int main(int argc, char *argv[]){       //done
    ifstream input;
    // level, encode;
    string file1 = argv[1];
    // file2 = argv[2], file3 = argv[3];
    input.open(file1);
    //level.open(file2);
    //encode.open(file3);

    int t1 = 0;
    //t2 = 0;
    vector<int> v1;
    // v2;

    while (input >> t1)  v1.push_back(t1);
    //while (level >> t2)  v2.push_back(t2);

    int v1Array[v1.size()];
    // v2Array[v2.size()];

    if(v1.size()==0) return NULL;

    vectorToArray(v1, v1Array);
    //vectorToArray(v2, v2Array);

    Huffman buff;
    buff.buildHuffman(0, v1.size() - 1, v1.size(), v1Array);    //removed v2Array
    string temp, encodedTxt = "";
    //while(encode >> temp)  encodedTxt += temp;

    buff.decodeText(encodedTxt);
    input.close();
    //level.close(),encode.close();

    return 0;
}
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class Node{
    public: 
        bool valid = true;
        char key;
        int freq;
        Node *left;
        Node *right;
        Node *next;
        Node(char key, int freq){
            this->key = key;
            this->freq = freq;
        }
};

class List{
    public:
        Node *min;
        int len;

    List(){
        this->min = nullptr;
        len = 0;
    }
    void insert(Node *tba){
        if(this->min == nullptr){
            this->min = tba;
            tba->next = nullptr;
            this->len++;
            return;
        }
        else if(tba->freq < this->min->freq){
        tba->next = min;
        this->min = tba;
        this->len++;
        return;
        }
        else{
            Node *cur = this->min;
            Node *prev = cur;
            cur = cur->next;
            if(cur == nullptr){
                prev->next = tba;
                this->len++;
                return;
            }
            else{
                while(1){
                    if(tba->freq < cur->freq){
                        prev->next = tba;
                        tba->next = cur;
                        this->len++;
                        return;
                    }
                    prev = prev->next;
                    cur = cur->next;
                    if(cur == nullptr){
                        prev->next = tba;
                        tba->next = nullptr;
                        this->len++;
                        return;
                    }
                }
            }
        }
    }

    Node *dq(){
        Node *rt = this->min;

        this->min = this->min->next;
        this->len--;
        return rt;
    }
};

class MinHeap{
    public: 
        char arr[128];
        int freq[128];
        int count;

    MinHeap(){
        for (int i = 0; i < 128; i++){
            freq[i] = 0;
        }
        count = 0;
    }
    void insert(Node *tbi){
        this->count++;

        arr[count] = tbi->key;
        freq[count] = tbi->freq;

        int q = count;

        while(q > 1 && freq[q] < freq[q/2]){
            if(q <= 1) break;
            if (freq[q] < freq[q/2]){
                swap(freq[q], freq[q/2]);
                swap(arr[q], arr[q/2]);
            }
            q /= 2;
        }
        return;
    }
    Node *extract(){
        if (count < 1){
            return nullptr;
        }

        Node *hi = new Node(arr[1], freq[1]);

        if (count == 1){
            count--;
            return hi;
        }

        arr[1] = arr[count];
        freq[1] = freq[count];
        
        count--;

        int q = 1;

        while(q < count && q * 2 < count){
            if(freq[q] > freq [q * 2] || freq[q] > freq[(q * 2) + 1]){
                if (freq[q] > freq [q * 2] && freq[q] > freq[(q * 2) + 1]){
                    if(freq[q * 2] < freq[(q * 2) + 1]){        //left child < right child
                        swap(freq[q], freq[q * 2]);
                        swap(arr[q], arr[q * 2]);
                        q = (q * 2);
                    }
                    else{   //right child < left child
                        swap(freq[q], freq[(q * 2) + 1]);
                        swap(arr[q], arr[(q * 2) + 1]);
                        q = (q * 2) + 1;
                    }
                }
                else if(freq[q] > freq[q*2]){
                    swap(freq[q], freq[q * 2]);
                    swap(arr[q], arr[q * 2]);
                    q = q * 2;
                }
                else if(freq[q] > freq[(q * 2) + 1]){
                    swap(freq[q], freq[(q * 2) + 1]);
                    swap(arr[q], arr[(q * 2) + 1]);
                    q = (q * 2) + 1;
                }
            }
            else return hi;
        }//end of while(q < count)
        return hi;
    }
};

class Huffman{
    public:
        Node *head;

        Huffman(MinHeap src){
            if(src.count < 2){
                return;
            }
            List *queue = new List();
                while(src.count > 0){
                    queue->insert(src.extract());       //fixed
                }
                    
                Node *debug = queue->min;
                while(debug != nullptr) {
                    debug = debug->next;
                }
                while(queue->len > 1){
                    Node *buf1 = queue->dq();
                    Node *buf2 = queue->dq();
                    Node *parent = new Node('a', buf1->freq + buf2->freq);
                    parent->valid = false;
                    if(buf1 != nullptr){
                     parent->right = buf1;
                    }
                    if(buf2 != nullptr){ 
                        parent->left = buf2;
                    }
                    queue->insert(parent);
                    debug = queue->min;
                    while(debug != nullptr) {
                        debug = debug->next;
                    }
                }
            this->head = queue->min;
        }
};

MinHeap buildMinHeap(int array[]);

void print(Node *parent, string code, int array[]);

int getLen(Node *parent, string code, int array[]);

int main(int argc, char *argv[]){       //done
    string file = argv[1];
    ifstream inputFile;
    inputFile.open(file, ios::in);

    int arr[128];
    for(int i = 0; i < 128; i++){
        arr[i] = 0;
    }
    char buf;
    if(inputFile.is_open())
        while(!inputFile.eof()){
            buf = inputFile.get();
            arr[(int) buf]++;
        }

    int uncomp;
    for(int i = 0; i < 128; i++) uncomp += arr[i];

    uncomp = uncomp * 8;

    cout << "Uncompressed length: " << uncomp << " bits." << endl;

    MinHeap mHeap = buildMinHeap(arr);

    Huffman *huf = new Huffman(mHeap);

    Node *trav = huf->head;

    string code;
    string buffer;
    int total;

    total = getLen(trav, buffer, arr);

    cout << "Compressed length: " << total << " bits\n";

    cout << "CHAR | FREQ | CODE_LEN\n";
    
    print(trav, code, arr);

    return 0;
}

MinHeap buildMinHeap(int array[]){
        MinHeap *mh = new MinHeap();
        for(int i = 0; i < 128; i++){
            if(array[i] == 0) continue;
            else{
                Node *buf = new Node((char) i, array[i]);
                mh->insert(buf);
            }
        }
        return *mh;
}

void print(Node *parent, string code, int array[]){
    if(parent == nullptr){
        return;
    }
    if(parent->valid){
        cout << "'" << parent->key << "' | " << array[(int) parent->key] << " | " << code.length()<< endl;
    }
        string code1 = code;
        print(parent->left, code1 += '0', array);
        string code2 = code;
        print(parent->right, code2 += '1', array);
    return;
}

int getLen(Node *parent, string code, int array[]){
    int rt = 0;
    if(parent == nullptr){
      return rt;
    }
    if(parent->valid){
        rt += (code.length() * array[(int) parent->key]);
    }
        string code1 = code;
        rt += getLen(parent->left, code1 += '0', array);
        string code2 = code;
        rt += getLen(parent->right, code2 += '1', array);
    return rt;
}
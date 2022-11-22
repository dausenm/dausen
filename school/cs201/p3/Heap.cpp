#include <iostream>

using namespace std;

template <class T>

class Heap{
    private:
        int size;
        CircularDynamicArray<T>* h;

    public:

    Heap(){
        size = 0;
        h = new CircularDynamicArray<T>;
    }
    
    Heap(T array[], int s){
        this->size = s;
    }
    
    ~Heap(){
        delete this->size;
        delete this->h;
    }

    T peekKey(){
        return h[1];
    }
    
    T extractMin(){
        //return the min key and maintain heap properties
    }

    void insert(T key){
        h->addEnd(key);
        size++;
    }

    void printKey(){
        for (int i = 1; i <= size; i++){
            cout << h[i] << " ";
        }
        cout << endl;
    }
};
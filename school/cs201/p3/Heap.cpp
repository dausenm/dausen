#include <iostream>
#include "CircularDynamicArray.cpp"

using namespace std;

template <class T>

class Heap{
    private:
        int size;
        CircularDynamicArray<T>* h;

    public:

    Heap(){
        size = 0;
        h = new CircularDynamicArray()<T>;
    }
    
    Heap(K array[], int s){
        this->size = s;
    }
    
    ~Heap(){
        delete this->size;
        delete this->h;
    }

    K peekKey(){
        return h[1];
    }
    
    K extractMin(){
        //return the min key and maintain heap properties
    }

    void insert(K key){
        h->addEnd(key)
        size++;
    }

    void printKey(){
        for (int i = 1; i <= size; i++){
            cout << h[i] << " ";
        }
        cout << endl;
    }
};
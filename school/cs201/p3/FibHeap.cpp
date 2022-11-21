#include <iostream>

using namespace std;

template <class T>

class FibHeapNode{
    private: 
        int size;
        T key;
        FibHeapNode *c;

    public: 

    FibHeapNode(T kee){
        size = 0;
        key = kee;
        c = nullptr;
    }

};

template <class T>

class FibHeap{
    private:
    

    public:

        FibHeap(){  //default constructor. create an empty heap
            return;
        }

        FibHeap(T array[], int s, CircularDynamicArray <FibHeapNode <T> *> &handle){
            /*
            Heap should be built using the array k containing s items of type T.
            Once all the data is in the heap, a single call of consolidate should be used to form the binomial trees.
            The handles for the keys should be added to the end of the circular dynamic array named handle.
            */
        }

        ~FibHeap(){ //destructor

        }

        T peekKey(){    //returns min key in heap. does not modify heap

        }

        T extractMin(){     //removes and returns min key

        }

        FibHeapNode * insert(T k){  //inserts key k into heap. returns pointer handle for direct access to the key for decrease key

        }

        bool decreaseKey(FibHeapNode <T> *h, T k){  //decrease key of h to k. assume h exists in this heap. if k > h return false and do nothing. else return true.

        }

        void merge(FibHeap<T> &H2){

        }
        
        void printKey(){    //writes keys stored in heap, starting at head of the list. when printing a binomial tree, print the size first, use modified preoder traversal

        }

};
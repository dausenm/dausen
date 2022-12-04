#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"
#include "Heap.cpp"
#include "FibHeap.cpp"

//inside FibHeap.cpp the definitition of FibHeapNode is expected, for example:
//template <typename keytype>
//struct FibHeapNode {
//    keytype x;
//    FibHeapNode<keytype> *ptr;
//    etc.  You may define any elements needed inside FibHeapNode
//};


int main(){

    Heap<int> H1;

    for (int i = -100; i < 100; i++) H1.insert(i);

    for(int i = 0; i < 200; i++){
        if(H1.peekKey() != i - 100){
            cout << "i = " << i << " peekKey error\n";
        }

        if(H1.extractMin() != i - 100){
            cout << "extractMin error\n";
        }
    }

    H1.printKey();
}
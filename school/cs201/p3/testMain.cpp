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

    CircularDynamicArray<FibHeapNode<char>*> H1;

    FibHeap <char> T1;

    H1.addEnd(T1.insert('b'));

    H1.addEnd(T1.insert('a'));

    T1.consolidate();

    // H1.addEnd(T1.insert('c'));

    // H1.addEnd(T1.insert('d'));

    // H1.addEnd(T1.insert('e'));

    T1.printKey();

    return 0;

}
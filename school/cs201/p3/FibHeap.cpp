#include <iostream>
#include <cmath>

using namespace std;

template <class T>

class FibHeapNode{
    public:
        int degree;
        T key;
        FibHeapNode *c;
        FibHeapNode *p;
        FibHeapNode *right;
        FibHeapNode *left;

    FibHeapNode <T> (){
        degree = -1;
        c = nullptr;
        p = nullptr;
        right = nullptr;
        left = nullptr;
    }

    FibHeapNode<T>(T kee){
        degree = 0;
        key = kee;
        c = nullptr;
    }
};

template <class T>

class FibHeap{
    private:
        int size;
        FibHeapNode<T> *head;
        FibHeapNode<T> *tail;
        FibHeapNode<T> *min;

    public:

        FibHeap(){  //default constructor. create an empty heap
            head = nullptr;
            tail = nullptr;
            min = nullptr;
            return;
        }

        FibHeap(T array[], int s, CircularDynamicArray <FibHeapNode <T> *> &handle){
            /*
            Heap should be built using the array k containing s items of type T.
            Once all the data is in the heap, a single call of consolidate should be used to form the binomial trees.
            The handles for the keys should be added to the end of the circular dynamic array named handle.
            */
           for(int i = 0; i < s; i++){
                insert(array[i]);
           }
           consolidate();
           return;
        }

        ~FibHeap(){ //destructor

        }

        T peekKey(){    //returns min key in heap. does not modify heap
            return min->key;
        }

        T extractMin(){     //removes and returns min key
            return min->key;
        }

        FibHeapNode<T> *insert(T k){  //inserts key k into heap. returns pointer handle for direct access to the key for decrease key
            FibHeapNode<T> *newOne = new FibHeapNode(k);
            cout << "\tD: in insert, key: " << newOne->key << endl;
            size++;

            if(head == nullptr){
                cout << "\tD: head == nullptr\n";
                head = newOne;
                tail = newOne;
                min = newOne;
                newOne->right = newOne;
                newOne->left = newOne;

                cout << "\t\tD: head now == " << head->key << "    head->right = " << head->right->key << endl;
                return newOne;
            }
            else if (tail == head){

                cout << "\tD:tail == head\n";
                if(newOne->key < min->key) min = newOne;
                tail = newOne;
                newOne->left = head;
                newOne->right = head;
                head->right = newOne;
                head->left = newOne;

                cout << "\t\tD: now head = " << head->key << "   tail = " << tail->key << "    head->right = " << head->right->key << endl;
                return newOne;
            }
            else{
                cout << "\tD: non edge insert\n";
                if(newOne->key < min->key) min = newOne;
                tail->right = newOne;
                newOne->right = head;
                head->left = newOne;
                newOne->left = tail;
                tail = newOne;
                
                cout << "\t\tD: head = " << head->key << "    tail = " << tail->key << "    head->right = " << head->right->key << endl;
                return newOne;
            }
        }

        bool decreaseKey(FibHeapNode <T> *h, T k){  //decrease key of h to k. assume h exists in this heap. if k > h return false and do nothing. else return true.
            return true;
        }

        void merge(FibHeap<T> &H2){ //merges two fib heaps. i assume we just add the root list of h2 to this->rootList after tail.

        }
        
        void printKey(){    //writes keys stored in heap, starting at head of the list. when printing a binomial tree, print the size first, use modified preoder traversal
            FibHeapNode<T> *trav = head;

            // for(int i = 0; i < 5; i++){
            //     cout << trav->key << " ";
            //     trav = trav->right;
            // }
            cout << head->key << " child: " << head->c->key << endl; 

            cout << "\n\tmin: " << min->key << endl;
            return;
        }

        void consolidate(){
            FibHeapNode<T> *trav = head;

            int s = int(log(size)/log(2));

            FibHeapNode<T> *array[s];

            for(int i = 0; i < s; i++){
                array[i] = NULL;
            }

            bool go = true;

            while(go){
                if(trav == tail) go = false;

                if(array[trav->degree] != NULL){
                    FibHeapNode<T> *tbc = array[trav->degree];
                    combine(tbc, trav);
                }
                array[trav->degree] = trav;
                trav = trav->right;
            }
            
            return;
        }

        void combine(FibHeapNode<T> *N1, FibHeapNode<T> *N2){
            cout << "\tD: combining " << N1->key << " and " << N2->key << endl;
            if(N1->key < N2->key){
                if(N2 == head){
                    head = N1;
                }
                N2->left->right = N2->right;
                N2->right->left = N2->left;
                if(N1->c == nullptr){
                    N1->c = N2;
                    N2->p = N1;
                }
                else{
                    addToC(N1, N2);
                }
            }
            else{
                if(N1 == head){
                    head = N2;
                }
                cout << "This should print\n";
                N1->left->right = N1->right;
                N1->right->left = N1->left;
                if(N2->c == nullptr){
                    cout << "\td: but does it go here\n";
                    N2->c = N1;
                    N1->p = N2;
                }
                else{
                    addToC(N2,N1);
                }
            }
            return;
        }

        void addToC(FibHeapNode<T> *parent, FibHeapNode<T> *child){
            FibHeapNode<T> *trav = parent->c;
            while(trav->right != nullptr){
                trav = trav->right;
            }
            trav->right = child;
            child->left = trav;
            child->p = parent;
        }

};

/*
decreaseKey, extractMin, and destructor.

when you left off, you were working on consolidate. you just got combine working with only 2 elements in the tree, but honestly it may work to scale in its current state. my only concern
is the size of the array may not be large enough, but i'm pretty sure it's gonna work fine.
*/
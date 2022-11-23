#include <iostream>
#include <cmath>

using namespace std;

template <class T>

class FibHeapNode{
    public:
        int degree;
        T key;
        bool mark;
        FibHeapNode *c;
        FibHeapNode *p;
        FibHeapNode *right;
        FibHeapNode *left;

    FibHeapNode <T> (){
        degree = -1;
        mark = false;
        c = NULL;
        p = NULL;
        right = NULL;
        left = NULL;
    }

    FibHeapNode<T>(T kee){
        degree = 0;
        key = kee;
        mark = false;
        c = NULL;
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
            head = NULL;
            tail = NULL;
            min = NULL;
            return;
        }

        FibHeap(T array[], int s, CircularDynamicArray <FibHeapNode <T> *> &handle){
            /*
            Heap should be built using the array k containing s items of type T.
            Once all the data is in the heap, a single call of consolidate should be used to form the binomial trees.
            The handles for the keys should be added to the end of the circular dynamic array named handle.
            */
           head = NULL;
           tail = NULL; 
           min = NULL;
           for(int i = 0; i < s; i++){
                handle.addEnd(insert(array[i]));
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
            T rt = min->key;
            if(min == head && min == tail){     //this checks if the min is the only element in the heap
                head = NULL;
                tail = NULL;
            }
            else if(min == head){        //this checks if the min is the head of the root list.
                head = min->right;
                head->left = tail;
                tail->right = head;
            }
            else if(min == tail){        //this checks if the min is the tail of the root list.
                tail = min->left;
                tail->right = head;
                head->left = tail;
            }
            else{
                min->left->right = min->right;
                min->right->left = min->left;       //at this point, the min is removed from the root list
            }

            FibHeapNode<T> *buf = min;


            addChildrenToList(buf);     //this function adds the children of the min to the root list.
            findNewMin();               //this finds the new min in the root list after all of the children are added
            consolidate();              //we finish extract min with a consolidate
            checkRootOrder();
            return rt;
        }
        
        void printRootList(){
            cout << "\td: printing root list:    ";
            FibHeapNode<T> *trav = head;
            cout << trav->key << " ";

            trav = trav->right;

            while(trav != head){
                cout << trav->key << " ";
                trav = trav->right;
            }

            cout << "\n\tD: end of root list\n";
        }

        void addChildrenToList(FibHeapNode<T> *parent){
            if(parent->c == NULL){
                return;
            }
            
            FibHeapNode<T> *buf = parent->c;
            while(buf != NULL){
                FibHeapNode<T> *next = buf->right;
                buf->p = NULL;
                tail->right = buf;
                buf->left = tail;
                tail = buf;
                buf->right = head;

                buf = next;
            }
        }

        void findNewMin(){
            min = head;
            FibHeapNode<T> *trav = head;

            if(trav->right == NULL || trav->right == trav){
                return;
            }

            trav = trav->right;

            while(trav != NULL && trav != head){
                if(trav->key < min->key) min = trav;
                trav = trav->right;
            }

            return;
        }

        FibHeapNode<T> *insert(T k){  //inserts key k into heap. returns pointer handle for direct access to the key for decrease key
            FibHeapNode<T> *newOne = new FibHeapNode<T>(k);
            size++;

            if(head == NULL){
                head = newOne;
                tail = newOne;
                min = newOne;
                newOne->right = newOne;
                newOne->left = newOne;
                return newOne;
            }
            else if (tail == head){
                if(newOne->key < min->key) min = newOne;
                tail = newOne;
                newOne->left = head;
                newOne->right = head;
                head->right = newOne;
                head->left = newOne;

                return newOne;
            }
            else{
                if(newOne->key < min->key) min = newOne;
                tail->right = newOne;
                newOne->right = head;
                head->left = newOne;
                newOne->left = tail;
                tail = newOne;
                
                return newOne;
            }
        }

        bool decreaseKey(FibHeapNode <T> *h, T k){  //decrease key of h to k. assume h exists in this heap. if k > h return false and do nothing. else return true.
            if(h->key <= k) return false;

            h->key = k;

            if(h->p == NULL){
                return true;
            }
            if(h->p->key > h->key){
                decreaseKeyFixUp(h);
            }

            findNewMin();

            return true;
        }

        void decreaseKeyFixUp(FibHeapNode<T> *node){
            //first we have to deal with if node has siblings

            FibHeapNode<T> *parent = node->p;

            parent->degree--;

            bool pMark = false;

            if(node->p->mark){
                pMark = true;
            }

            node->p->mark = true;

            if(node->left != NULL && node->right != NULL){        //this is for if node is in between two children
                node->right->left = node->left;
                node->left->right = node->right;
                node->right = NULL;
                node->left = NULL;
                node->p = NULL;
            }

            else if (node->right == NULL && node->left != NULL){    //this is for if node has a left sibling, but no right sibling
                node->left->right = NULL;
                node->left = NULL;
                node->p = NULL;
            }

            else if (node->left == NULL && node->right != NULL){    //this is for if node is the leftmost child
                node->p->c = node->right;
                node->right->left = NULL;
                node->right = NULL;
                node->p = NULL;
            }

            else if(node->left == NULL && node->right == NULL){               //this is for if node is the only child;
                node->p->c = NULL;
            }


            node->p = NULL;
            if(head == tail){
                tail = node;
                head->right = tail;
                tail->right = head;
                tail->left = head;
                head->left = tail;
            }
            else{
                tail->right = node;
                node->left = tail;
                node->right = head;
                head->left = node;
                tail = node;
            }

            if(pMark){
                decreaseKeyFixUp(parent);
            }
        }

        void merge(FibHeap<T> &H2){ //merges two fib heaps. i assume we just add the root list of h2 to this->rootList after tail.
            FibHeapNode<T> *head2 = H2.head;
            FibHeapNode<T> *tail2 = H2.tail;

            cout << head2->key << endl;

            tail->right = head2;
            head2->left = tail;

            head->left = tail2;
            tail2->right = head;

            tail = tail2;

            findNewMin();

            return;
        }
        
        void printKey(){    //writes keys stored in heap, starting at head of the list. when printing a binomial tree, print the size first, use modified preoder traversal
            FibHeapNode<T> *trav = head;
            cout << "Rank " << head->degree << endl;

            cout << head->key << " ";

            if(trav->c != NULL){
                printChildren(trav);
            }

            trav = trav->right;

            while(trav != head){
                cout << endl << endl;
                cout << "Rank " << trav->degree << endl;
                cout << trav->key << " ";
                if(trav->c != NULL){
                    printChildren(trav);
                }
                trav = trav->right;
            }

            cout << endl;
            
            return;
        }

        void printChildren(FibHeapNode<T> *parent){
            if(parent->c == NULL){
                return;
            }

            FibHeapNode<T> *trav = parent->c;

            cout << trav->key << " ";

            if(trav->c != NULL){
                printChildren(trav);
            }

            while(trav->right != NULL){
                trav = trav->right;
                cout << trav->key << " ";
                if(trav->c != NULL){
                    printChildren(trav);
                }
            }
        }

        void consolidate(){

            FibHeapNode<T> *trav = head;

            int s = (int)log2(size) + 2;

            FibHeapNode<T> *array[s];

            for(int i = 0; i < s; i++){
                array[i] = NULL;
            }

            bool go = true;

            while(go){
                if(trav == tail) go = false;

                if(array[trav->degree] != NULL && array[trav->degree] != trav){
                    FibHeapNode<T> *tbc = array[trav->degree];
                    array[trav->degree] = NULL;
                    FibHeapNode <T> *buf = combine(tbc, trav);
                    trav = buf;
                    if(trav == tail){
                        array[trav->degree] = NULL;
                        trav = head;
                        go = true;
                    } 
                    continue;
                }
                array[trav->degree] = trav;
                trav = trav->right;
            }

            checkRootOrder();

            return;
        }

        void checkRootOrder(){
            if (tail == head || head == NULL) return;

            FibHeapNode<T> *trav = head;
            FibHeapNode<T> *next = trav->right;

            while(next != head){
                if(trav->degree > next->degree) reorder(trav, next);

                trav = trav->right;
                next = next->right;
            }
        }

        void reorder(FibHeapNode<T> *first, FibHeapNode<T> *second){
            if(first == head){
                head = second;
            }
            if(second == tail){
                tail = first;
            }

            first->left->right = second;
            first->right = second->right;
            second->left = first->left;
            first->left = second;
            second->right = first;

            tail->left->right = tail;

            return;
        }

        FibHeapNode<T> *combine(FibHeapNode<T> *N1, FibHeapNode<T> *N2){
            FibHeapNode<T> *rt;
            if(N1->key < N2->key){
                rt = N1;
                N1->degree++;
                if(N2 == head){
                    head = N1;
                }
                else if(N2 == tail){
                    tail = N2->left;
                    tail->right = head;
                    head->left = tail;
                }
                else{
                    N2->left->right = N2->right;
                    N2->right->left = N2->left;
                }

                N2->left = NULL;
                N2->right = NULL;

                if(N1->c == NULL){
                    N1->c = N2;
                    N2->p = N1;
                }
                else{
                    addToC(N1, N2);
                }
            }
            else{
                rt = N2;
                N2->degree++;
                if(N1 == head){
                    head = N1->right;
                    head->left = tail;
                    tail->right = head;
                }
                else if(N1 == tail){
                    tail = N1->left;
                    tail->right = head;
                }
                else{
                    N1->left->right = N1->right;
                    N1->right->left = N1->left;
                }

                N1->right = NULL;
                N1->left = NULL;
                if(N2->c == NULL){
                    N2->c = N1;
                    N1->p = N2;
                }
                else{
                    addToC(N2,N1);
                }
            }
            return rt;
        }

        void addToC(FibHeapNode<T> *parent, FibHeapNode<T> *child){
            child->p = parent;
            FibHeapNode<T> *trav = parent->c;

            parent->c = child;

            child->right = trav;
            trav->left = child;
        }

};

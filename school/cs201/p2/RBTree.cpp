#include <iostream>

using namespace std;

template <class K, class V>

struct Node{
    public:
        K key;
        V value;
        Node *left, *right, *parent;
        bool red;

        Node(){
            key = 0;
            value = 0;

            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        Node(K keys, V val){
            key = keys;
            value = val;

            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        void po(){
            printNode(this);

            if(this->left != nullptr) this->left->po();

            if(this->right != nullptr) this->right->po();
        }

        void io(){
            if(this->left != nullptr) this->left->io();

            printNode(this);

            if(this->right != nullptr) this->right->io();
        }

        void poo(){
            if(this->left != nullptr) this->left->poo();

            if(this->right != nullptr) this->right->poo();

            printNode(this);
        }

        void printNode(Node <K, V> *p){
            // cout << "\tD: Fix this later:\tkey: " << p->key << "  val:  " << p->value << " color:  ";
            // if(p->red) cout << "red\n";

            // else cout << "black\n";

            cout << p->key << " ";
        }

        // Node <K, V> copy(const Node <K, V> &old){
        //     Node <K, V> *oldHead = old;
        //     *this->key = old.key;
        //     *this->value = old.value;
        //     this->red = old.red;

        //     if(old.left != nullptr){
        //         //copy the left subtree
        //         this->left = copy(old.left);
        //     }

        //     if(old.right != nullptr){
        //         //copy the right subtree
        //         this->right = copy(old.right);
        //     }
            
        //     return this;
        // }
    };

template <class K, class V>

class RBTree{
    

    private:
        int i;
        Node <K, V> *head;
        //Node <K, V> *nullptr;

    public:
        RBTree(){       //this is good
            i = 0;
            head = nullptr;
            // nullptr->red = false;
            // nullptr->left = nullptr;
            // nullptr->right = nullptr;
            // nullptr->parent = nullptr;
        }

        RBTree(K keys[], V vals[], int s){  //this is good
            head = nullptr;
            // nullptr->red = false;
            // nullptr->left = nullptr;
            // nullptr->right = nullptr;
            // nullptr->parent = nullptr;
            i = 0;
            for (int i = 0; i < s; i++){
                insert(keys[i], vals[i]);
            }
        }

        // RBTree (const RBTree <K, V> &old){
        //     Node <K, V> *oldHead = old.head;
        //     this->head->key = *old.head.key;
        //     this->head->value = *old.head.value;
        //     this->head->red = *old.head.red;
            
        //     if(old.head.left != nullptr){
        //         //copy the left subtree
        //         this->left = copy(old.left);
        //     }

        //     if(old.head.right != nullptr){
        //         //copy the right subtree
        //         this->right = copy(old.right);
        //     }

        //     return;
        // }
        
        ~RBTree(){  //i think this is good but tbh this may be what's causing the weird segfaults
            Node <K, V> *trav = head;

            if (trav == nullptr) return;

            if (trav->left != nullptr) del(trav->left);

            if (trav ->right != nullptr) del(trav->right);

            delete trav;
        }

        V *search(K keys){      //this should be working
            Node <K, V> *trav = head;

            V *rt = NULL;

            while (trav != nullptr){
                if (trav->key == keys){
                    rt = &trav->value;
                    return rt;
                }

                if(trav->key > keys){ 
                    trav = trav->left;
                    if (trav == nullptr){
                        rt = &head->value;
                        return rt;
                    }
                    continue;
                }

                if(trav->key < keys){ 
                    trav = trav->right;
                    if (trav == nullptr){
                        trav = trav->parent;
                        rt = &trav->value;
                        return rt;
                    }
                    continue;
                }
            }
            rt = &head->value;
            return rt;
        }

        void insert(K keys, V val){     //this is the majority of the work that is left
            Node <K, V> *buf = new Node(keys, val);

            if(head == nullptr){
                head = buf;
                head->red = false;
                head->parent = nullptr;
                // nullptr->key = keys;
                // nullptr->value = val;
                i++;
                return;
            }

            Node <K, V> *trav = head;

            bool placed = false;

            while(!placed){
                // cout << "\t\tD: top loop\n\t\t\tyou are adding " << keys << " to the tree\n";
                if(keys < trav->key){
                    if(trav->left == nullptr){
                        // cout << "\t\t\tD: insertion: keys = " << keys << "  trav->key = " << trav->key << endl;
                        trav->left = buf;
                        buf->parent = trav;
                        buf->red = true;
                        i++;
                        placed = true;
                        insertFixUp(buf);
                        return;
                    }

                    else{
                        trav = trav->left;
                        continue;
                    }
                }


                if(keys > trav->key){
                    if(trav->right == nullptr){
                        // cout << "\t\t\tD: insertion: keys = " << keys << "  trav->key = " << trav->key <<"\n\t\t\t\t" << trav->key << " right is being assigned to " << buf->key << endl;
                        
                        trav->right = buf;
                        buf->parent = trav;
                        buf->red = true;
                        placed = true;
                        i++;
                        insertFixUp(buf);
                        return;
                    }

                    else{
                        trav = trav->right;
                        continue;
                    }
                }
            }

            //cout << "----------------------------------------------\n\n";
            return;
        }

        int remove(K keys){     //fixup needs to be done for this
                //return 1 if it's found and removed
                //return 0 if not found
                //replace with predecessor
                Node <K, V> *trav = head;
                Node <K, V> *buf;
                Node <K, V> *n; 

                bool b = false;

                // cout << "\tD: you are looking for " << keys << endl;

                while(trav != nullptr){
                    // cout << "\t\tD: top while\n";
                    if (keys == trav->key){
                        // cout << "\tD: hey dude you made it here you fucking stupid idiot who doesn't know how to code\n";
                        i--;
                        if(trav == head){   //this branch for if we are removing the root of the tree
                            if(trav->left == nullptr){
                                if (trav->right == nullptr){    //this branch for if the root is the only element in the tree
                                    head == nullptr;
                                    del(trav);
                                    return 1;
                                }
                                head = head->right;     //this is for if there are no elements to the left of the root, but there are elements to the right
                                del(trav);
                                return 1;
                            }
                            // cout << "\tD: you made it here boy\n";
                            trav = trav->left;      //this branch for when you are removing the root and there are elements to the left

                            if(head->right == nullptr){     //if left of the root is not null, make the left child of the root the new root and delete the old root
                                trav = head;
                                head= head->left;
                                del(trav);
                                return 1;
                            }

                            n = trav;

                            if(trav->right != nullptr){     //if the right child of the left child of the root is null, do this if body

                                // cout << "\t\t\t b = true\n";
                                b = true;
                                while(trav->right != nullptr){
                                    trav = trav->right;
                                }
                            }

                            buf = head;
                            this->head = trav;

                            trav->parent = nullptr;
                            head->right = buf->right;
                            if(trav != n){
                                 trav->left = n;
                                 n->parent = head;
                            }

                            // cout << "\t\t\t\tD: buf = " << buf->key << "  head = " << head->key << "  head left = " << head->left->key << "  " << head->left->key << " parent = " << head->left->parent->key <<  endl;
                            // cout << "\t\t\tD: buf = " << buf->key << "  trav = " << trav->key << "  head = " << head->key << endl;
                            // cout << "\t\t\tD: head->right = " << head->right->key << endl;

                            buf->right->parent = buf;
                            head->red = false;
                            if(b){
                                // cout << "\t\t\t\t\tD: you are here\n";
                                head->left = n;
                                n->right = nullptr;
                                head->left->parent = head;
                            } 

                            // cout << "\t\t\t\tD: buf = " << buf->key << "  head = " << head->key << "  head left = " << head->left->key << "  " << head->left->key << " parent = " << head->left->parent->key <<  endl;
                            // cout << "\t\t\tD: buf = " << buf->key << "  trav = " << trav->key << "  head = " << head->key << endl;
                            // cout << "\t\t\tD: head->right = " << head->right->key << endl;

                            // cout << "\t\t\tD: n = " << n->key << endl;

                            // cout << "\t\t\tD: head = " << head->key << "  head->left = " << head->left->key << "  head->right = " << head->right->key << "  b parent = " << head->left->parent << endl;
                            del(buf);
                            return 1;
                        }
                        if(trav->key < trav->parent->key){  //if trav is left child
                            if(trav->left == nullptr){
                                if(trav->right == nullptr){
                                    // cout << "\t\tD: you made it here\n\t\t\tbecause: " << trav->key << " == " << keys << endl;
                                    trav->parent->left = nullptr;
                                    del(trav);
                                    return 1;
                                }
                                else{
                                    trav->parent->left = trav->right;
                                    del(trav);
                                    return 1;
                                }
                            }
                            else{
                                // cout << "\t\t\tD: this is executing\n";

                                // cout << "\t\t\tD: head = " << head->key << endl;

                                // cout << "\t\t\t\tD: " << head->right->right->right->key << endl;

                                // cout << "\t\t\t\tD: trav = " << trav->key << endl;

                                // printf("hello\n");

                                buf = trav->parent;
                                // printf("\tworld\n");
                                if(trav->left != nullptr){
                                    buf->left = trav->left;
                                    buf->left->parent = buf;
                                }
                                // printf("\t\t!\n");

                                del(trav);
                                return 1;
                            }
                        }
                        else{       //if trav is right child
                            if(trav->left == nullptr){
                                if(trav->right == nullptr){
                                    trav->parent->right = nullptr;
                                    return 1;
                                }
                                else{
                                    trav->parent->right = trav->right;
                                    trav->right->parent = trav->parent;
                                    trav->right = nullptr;
                                    trav->parent = nullptr;
                                    trav->left = nullptr;
                                    del(trav);
                                    return 1;
                                }
                            }
                            else{
                                // cout << "\t\t\tD: hey bro you made it here you fucking idiot\n";
                                // cout << "\t\t\t\tD: you are removing " << trav->key << " and replacing it with " << trav->left->key << endl;
                                buf = trav->parent;
                                buf->right = trav->left;
                                buf->parent = trav->parent;
                                buf->right = trav->right;
                                del(trav);
                                return 1;
                            }
                        }
                    }

                    // cout << "\t\tD: you made it here because " << trav->key << " != " << keys << endl;

                    if(keys < trav->key){
                        if(trav->left == nullptr){
                            // cout << "\t\t\tD: returning 0 because " << keys << " < " << trav->key << " and trav->left == nullptr\n";
                            return 0;
                        }
                        trav = trav->left;
                        continue;
                    }

                    if (keys > trav->key){
                        if(trav->right == nullptr){
                            // cout << "\t\t\tD: returning 0 because " << keys << " > " << trav->key << " and trav->right == nullptr\n";
                            return 0;
                        }
                        trav = trav->right;
                        continue;
                    }

                    // cout << "\t\t\tD: you made it here because you're fucking stupid\n";
                }
                
                return 0;
        }

        int rank(K keys){       //this is done but it may not cover all edge cases
            //return 0 if not found, else return the rank of the item. smallest item is rank 1
            Node <K, V> *trav = head;

            while(trav->left != nullptr){
                trav = trav->left;
            }      //trav is now the smallest element in the tree

            int r = 1;
            K last = trav->key;

            while(trav != nullptr){
                
                if(trav->key == keys) return r;

                if(trav->left != nullptr && trav->left->key > last){
                    trav = trav->left;
                    continue;
                }

                else if(trav->right != nullptr && trav->right->key > last){
                    trav = trav->right;
                    last = trav->key;
                    r++;
                    continue;
                }

                else if (trav->parent != nullptr && trav->parent->key > last) {
                    trav = trav->parent;
                    last = trav->key;
                    r++;
                    continue;
                }
                
                if (r == i)  return 0;
            }
            
            return 0;
        }

        K select(int pos){      //this should be done
            //return key of node at position pos. pos = 1 means smallest element. pos = n means largest.
            if(pos > this->i){
                cout << "Error: you are trying to print the " << pos << "th element in the tree when there are only " << i << " elements in the tree!\n";
            }
            
            Node <K, V> *trav = head;

            while(trav->left != nullptr){
                trav = trav->left; 
            }   //trav is now the bottom left element in the tree

            int rank = 1;
            K last = trav->key;
            

            while(1){
                if(rank == pos) return trav->key;

                if(trav->left != nullptr && trav->left->key > last){
                    trav = trav->left;
                    continue;
                }

                else if(trav->right != nullptr && trav->right->key > last){
                    trav = trav->right;
                    last = trav->key;
                    rank++;
                    continue;
                }

                else {
                    trav = trav->parent;
                    last = trav->key;
                    rank++;
                    continue;
                }
            }
        }

        K *successor(K keys){       //this should be done
            //return nullptr if no successor
            //else return the key after k

            Node <K, V> *trav = head;

            while(trav != nullptr){
                if (trav->key == keys){
                    if(trav->right == nullptr){
                        if(trav->parent != nullptr && trav->parent->right != trav) return &trav->parent->key;
                        return NULL;
                    }
                    return &trav->right->key;
                }

                if(keys < trav->key){
                    if(trav->left == nullptr) return NULL;
                    trav = trav->left;
                    continue;
                }
                if(keys > trav->key){
                    if(trav->right == nullptr) return NULL;
                    trav = trav->right;
                    continue;
                }
            }
            return NULL;
        }
        
        K *predecessor(K keys){ //this should be done
            //return nullptr if no predecessor
            //else return the key before k
            Node <K, V> *trav = head;

            while(trav != nullptr){
                if(trav->key == keys){
                    if(trav->left == nullptr){
                        if(trav->parent->left != trav){
                            return &trav->parent->key;
                        }
                    }

                    else if(trav->left != nullptr){
                        return &trav->left->key;
                    }

                    else return NULL;
                }

                if(keys < trav->key){
                    if(trav->left == nullptr) return NULL;
                    trav = trav->left;
                    continue;
                }

                if(keys > trav->key){
                    if(trav->right == nullptr) return NULL;
                    trav = trav->right;
                    continue;
                }
            }
            return NULL;
        }

        int size(){ //this one's done
            return this->i;
        }

        void preorder(){    //this one should be done
            Node <K, V> *trav;
            trav = head;

            printNode(trav);

            if(trav->left != nullptr) trav->left->po();

            if(trav->right != nullptr) trav->right->po();

            cout << endl;
        }

        void inorder(){     //this one should be done
            //print left
            //print this
            //print right
            //do this using recursion
            Node <K, V> *trav;
            trav = head;

            if(trav->left != nullptr) trav->left->io();

            printNode(trav);

            if(trav->right != nullptr) trav->right->io();

            cout << endl;
        }

        void postorder(){   //this one should be done
            Node <K, V> *trav;
            trav = head;

            if (trav->left != nullptr) trav->left->poo();

            if (trav ->right != nullptr) trav->right->poo();

            printNode(trav);

            cout << endl;
        }

        void printk(int k){     //this should be done
            //print k smallest terms in the tree
            if(k > this->i){
                cout << "Error: you are wanting to print " << k << " items when there are only " << i << " items in the tree!\n";
                return;
            }

            Node <K, V> *trav = head;

            K last;

            while(trav->left != nullptr){
                trav = trav->left;
            }

            int p = 1;
            printNode(trav);
            last = trav->key;       //this block here could cause rank tracking issues
            if(trav->parent != nullptr){
                trav = trav->parent;    //keep this in mind if you have issues with this in larger trees
            }
            while(p < k){

                if(trav->left != nullptr && trav->left->key > last){
                    trav = trav->left;
                    continue;
                }

                if(trav->key > last){
                    printNode(trav);
                    p++;
                    last = trav->key;
                }

                if(trav->right != nullptr && trav->right->key > last){
                    trav = trav->right;
                    continue;
                }

                trav = trav->parent;
            }
            cout << endl;
            
            return;
        }

        void printNode(Node <K, V> *p){     //fix this one before submitting
            // cout << "\tD: Fix this later:\tkey: " << p->key << "  val:  " << p->value << " color:  ";
            // if(p->red) cout << "red\n";

            // else cout << "black\n";
            cout << p->key << " ";
        }

        void fixup(){
            return;
        }

        void del(Node <K, V> *tbd){
            delete tbd;
        }

        void rotateRight(Node <K, V> *x){
            Node <K, V> *y;
            x->left = y->left;

            if(y->right != nullptr){
                y->right->parent = x;
            }

            y->parent = x->parent;

            if(x->parent = nullptr){
                head = y;
            }
            else if(x == x->parent->right){
                x->parent->right = y;
            }
            else{
                x->parent->left = y;
            }

            y->right = x;
            x->parent = y;
        }

        void rotateLeft(Node <K, V> *x){
            Node <K, V> *y = x->right;
            x->right = y->left;

            if(y->left != nullptr){
                y->left->parent = x;
            }

            y->parent = x->parent;

            if(x->parent == nullptr){
                head = y;
            }
            else if(x == x->parent->left){
                x->parent->left = y;
            }
            else{
                x->parent->right = y;
            }

            y->left = x;
            x->parent = y;

            return;
        }

        void insertFixUp(Node <K, V> *z){
            while(z->parent->red){
                printf("\tD: you are here\n");
                if(z->parent == z->parent->parent->left){
                    Node <K, V> *y = z->parent->parent->right;
                    if(y->red){
                        z->parent->red = false;
                        y->red = false;
                        z->parent->parent->red = true;
                        z = z->parent->parent;
                    }
                    else if(z == z->parent->right){
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    rotateRight(z->parent->parent);
                }
                else{
                    Node <K, V> *y = z->parent->parent->left;
                    if(y->red){
                        z->parent->red = false;
                        y->red = false;
                        z->parent->parent->red = true;
                        z = z->parent->parent;
                    }
                    else if(z == z->parent->left){
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    rotateLeft(z->parent->parent);
                }
            }
            head->red = false;
        }

        void removeFixUp(Node <K, V> *x){
            while(x != head && x->red == false){
                if(x == x->parent->left){
                    Node <K, V> *w = x->parent->right;
                    if(w->red){
                        w->red = false;
                        x->parent->red = true;
                        rotateLeft(x->parent);
                        w = x->parent->right;
                    }
                    if(!w->left->red && !w->right->red){
                        w->red = true;
                        x = x->parent;
                    }
                    else if(!w->right->red){
                        w->left->red = false;
                        w->red = true;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->right->red = false;
                    rotateLeft(x->parent);
                    x = head;
                }
                else{
                    Node <K, V> *w = x->parent->left;
                    if(w->red){
                        w->red = false;
                        x->parent->red = true;
                        rotateRight(x->parent);
                        w = x->parent->left;
                    }
                    if(!w->right->red && !w->left->red){
                        w->red = true;
                        x = x->parent;
                    }
                    else if(!w->left->red){
                        w->right->red = false;
                        w->red = true;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->left->red = false;
                    rotateRight(x->parent);
                    x = head;
                }
                x->red = false;
            }
        }

        void transplant(Node <K, V> *u, Node <K, V> *v){
            if(u->parent == nullptr){
                head = v;
            }
            else if(u == u->parent->left){
                u->parent->left = v;
            }
            else{
                u->parent->right = v;
            }
            v->parent = u->parent;

            return;
        }
};

/*
this is pretty fucked. i've got a lot of work to do if i'm gonna make an 80 on this shit. i need to write the fixup functions for remove and insert. 
check if you can use the ones from the book or maybe modify the ones from the book, but either way, it's gonna take some time. 
the insertBal function and rotateLeft / rotateRight functions are in here now, but you're probably gonna have to remove them and fix them later.
you got this homie. clear your head, get some coffee and some water, and bang this shit out.
*/
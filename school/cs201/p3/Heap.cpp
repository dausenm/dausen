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
        size = s;
        h = new CircularDynamicArray<T>(s + 1);

        h->array[0] = array[0];

        cout << h->array[0] << endl << endl;

        for(int i = 0; i < s; i++){
            h->array[i + 1] = array[i];
        }

        for(int i = s; i > 0; i--){
            int index = i * 2;
            if(index > s) continue;

            if(index != s){
                if(h->array[index] < h->array[i] || h->array[index + 1] < h->array[i]){ //both children smaller
                    floatDown(i);
                }
            }
            if(h->array[index] < h->array[i]){
                floatDown(i);
            }
        }
    }

    void floatDown(int index){
        if(index * 2 > size){
            return;
        }

        if(h->array[index] < h->array[index * 2] && h->array[index] < h->array[(index * 2) + 1]){
            return;
        }

        if(h->array[index * 2] < h->array[index] && h->array[(index * 2) + 1] < h->array[index]){
            if(h->array[(index * 2) + 1] < h->array[index * 2]){
                swap(h->array[(index * 2) + 1], h->array[index]);
                floatDown(index * 2 + 1);
            }
            else{
                swap(h->array[index * 2], h->array[index]);
                floatDown(index * 2);
            }
        }
        else if(h->array[index * 2] < h->array[index]){
            swap(h->array[index * 2], h->array[index]);
            floatDown(index * 2);
        }
        else if(h->array[(index * 2) + 1] < h->array[index]){
            swap(h->array[(index * 2) + 1], h->array[index]);
            floatDown(index * 2 + 1);
        }
        return;
    }
    
    ~Heap(){
        delete this->h;
    }

    T peekKey(){
        return h->array[1];
    }
    
    T extractMin(){
        T min = h->array[1];
        swap(h->array[1], h->array[size]);
        size--;
        h->delEnd();

        floatDown(1);
        
        return min;
    }

    void insert(T key){
        if(size == 0){
            h->addEnd(key);
        }
        h->addEnd(key);
        size++;

        int index = size;

        if (size == 1) return;

        while(h->array[index] < h->array[index / 2]){
            swap(h->array[index], h->array[index /2]);
            index = index / 2;
            if (index == 1) break;
        }

    }

    void printKey(){
        for (int i = 1; i <= size; i++){
            cout << h->array[i] << " ";
        }
        cout << endl;
    }
};
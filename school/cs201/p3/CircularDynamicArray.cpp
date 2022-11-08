#include <iostream>
using namespace std;

template <class T>
class CircularDynamicArray{
    private:
    T *array;
    int size;
    int cap;
    int front = 0;
    T noBugs = -2;

    public:
        CircularDynamicArray(){     //default constructor. array should be capacity 2 and size 0
            array = new T [2];
            cap = 2;
            size = 0;
            return;
        }

        CircularDynamicArray(int s){    //create an array with capacity and size s
            array = new T [s];
            cap = s;
            size = s;
            return;
        }
        
        ~CircularDynamicArray(){    //destructor for the class
            delete[] array;
            return;
        }

        T& operator[](int i){     //[] operator. print a message if index is out of bounds and return a reference to value of type T stored in the class for this purpose.
            if (i > cap - 1){
                cout << "Out of bounds index. Returning bug prevention value\n\n";
                return noBugs;
            }
            return array[(front + i) % cap];
        }
        
        void addEnd(T v){     //add an item to the end of the array. if array is full, create a new array of capacity 2x the capacity of the original and copy over.
            if (size == cap){
                noBugs = v;
                T *buf = new T [this->cap * 2];
                for(int i = 0; i < size; i++) buf[i] = array[(front + i) % cap];
                array = buf;
                cap = cap*2;
                front = 0;
            }
                array[(front + size) % cap] = v;
                size++;
            return;
        }

        void addFront(T v){   //add an item to the front of the array. if full, same as above.
            noBugs = v;
            if (size == cap){
                T *buf = new T [this->cap * 2];
                for(int i = 0; i <= size; i++) buf[i+1] = array[(front + i) % cap];
                buf[0] = v;
                array = buf;
                size++;
                cap = cap*2;
                front = 0;
            }
            else if (front == 0){
                    int temp = cap - 1;
                    array[temp] = v;
                    front = temp;
                    size++;
            }
            else{
                array[front - 1] = v;
                front--;
                size++;
            }
            
            return;
        }

        void delEnd(){      //delete the item at the end of the array. if array is less than 1/4 full, create a new array of capacity 1/2 the capacity of the original and copy elements over
            size--;
            if(size <= cap * 0.25){
                T *buf = new T [this->cap / 2];
                for(int i = 0; i < size; i++) buf[i] = array[(front + i) % cap];
                array = buf;
                cap = cap / 2;
                front = 0;
            }
            return;
        }

        void delFront(){    //delete the item at the front of the array. if less than 1/4 full, same as above.
            front++;
            size--;
            if(size <= cap * 0.25){
                T *buf = new T [this->cap / 2];
                for(int i = 0; i < size; i++) buf[i] = array[(front + i) % cap];
                array = buf;
                cap = cap / 2;
                front = 0;
            }
            return;
        }

        int length(){   //return the size of the array
            return size;
        }

        int capacity(){ //return array capacity
            return cap;
        }

        CircularDynamicArray(const CircularDynamicArray& a){    //copy constructor
            cap = a.cap;
            size = a.size;

            int buf;
            buf = a.front;
            front = buf;

            T temp = a.noBugs;

            noBugs = temp;
            array = new T[buf];
            for(int i = 0; i < size; i++){
                temp = a.array[(a.front + i) % cap];
                array[(front + i) % cap] = temp;
            }
        }

        CircularDynamicArray &operator =(const CircularDynamicArray a){
            cap = a.cap;
            size = a.size;

            int buf;
            buf = a.front;
            front = buf;

            T temp = a.noBugs;

            noBugs = temp;
            array = new T[buf];
            for(int i = 0; i < size; i++){
                array[(front + i) % cap] = a.array[(front + i) % a.cap];
            }
            return *this;
        }

        void clear(){   //free any space currently used and start over wtih an array of capacity 2 and size 0
            delete [] this->array;
            size = 0;
            cap = 2;
            this->array = new T [2];
            front = 0;
            return;
        }
        
        T QuickSelect(int k){     //returns the kth smallest element in the array using the quickselect algorithm
            T *q = new T [size];   
            for(int i = 0; i < size; i++) q[i] = array[(front + i) % cap];
            T kSmallest = qs(q, k - 1, 0, size - 1);
            return kSmallest;
        }
        
        T WCSelect(int k){    //returns the kth smallest element in the array using the worst case O(N) time algorithm
            T *q = new T [size];
            for(int i = 0; i < size; i++) q[i] = array[(front + i) % cap];
            T kSmallest = wcs(q, k - 1, 0, size - 1);
            return kSmallest;
        }

        void stableSort(){      //sorts the values in the array using a comparison based O(N lg N) algorithm. The sort must be stable.
            T *a1 = new T [size / 2], *a2 = new T [size - (size / 2)];
            int a1Size = (size / 2), a2Size = (size - (size / 2));
            for(int i = 0; i < a1Size; i++) a1[i] = array[(front + i) % cap];
            for(int i = a1Size; i < size; i++) a2[i - a1Size] = array[(front + i) % cap];
            ms(a1, a1Size);
            ms(a2, a2Size);
            merge(array, a1, a2, size);
            front = 0;
            delete[] a1;
            delete[] a2;
            return;
        }

        int linearSearch(T e){    //performs a linear search of the array looking for the item e. Returns the index of the item if found or -1 otherwise.
            for(int i = 0; i < this->size; i++){
                if(this->array[(front + i) % cap] == e) return ((front + i) % cap);
            }
            return -1;
        }
        
        int binSearch(T e){   //performs binary search (assume array is sorted) looking for element e. return index of e. if e is not found, return -1.
            int r, l, index;
            l = front;
            r = front + size - 1;
            if(e == array[l]) return l;
            else if(e == array[r]) return r;
            else if ((l == r) || (r - l == 1)) return -1;
            else{
                while(1){
                    index = (l + r) / 2;
                    if(e ==  array[index]) return index;
                        if(e < array[index]){
                            r = index;
                        }
                        else if (e > array[index]){
                            l = index;
                        }
                    
                    if (l == r){
                        if (e == array[l]) return l;
                        return -1;
                    }
                    else if((r - l) == 1){
                        if(array[r] == e) return r;
                        if(array[l] == e) return l;
                        return -1;
                    }
                }
            }
        } 

        void ms(T *a, int size){
            if(size<=1) return;

            T *a1 = new T [size / 2], *a2 = new T [size - (size / 2)];

            int a1Size = size / 2, a2Size = size - (size / 2);

            for(int i = 0; i < a1Size; i++) a1[i] = a[i];
            
            for(int i = 0; i < a2Size; i++) a2[i] = a[i + a1Size];
            

            ms(a1, a1Size);
            ms(a2, a2Size);
            merge(a, a1, a2, size);
            delete[] a1;
            delete[] a2;
            return;
        }

        void merge(T *a, T *a1, T *a2, int size){
            int n1 = size / 2, n2 = size - (size / 2);

            int p1 = 0, p2 = 0, i = 0;

            while(p1 < n1 && p2 < n2) a[i++] = a1[p1] < a2[p2] ? a1[p1++] : a2[p2++];

            while (p1 < n1) a[i++] = a1[p1++];
            while (p2 < n2) a[i++] = a2[p2++];
        }

        T qs(T *array, int k, int l, int r){
            if(k > 0 && k <= (r - l) + 1) return -1;

            int index = partQS(array, l, r);
        
            if(index == k) return array[index];
            if(index > k) return qs(array, k, l, index - 1);
            else return qs(array, k, index + 1, r);
        }

        T wcs(T *array, int k, int l, int r){
            if(k < 0 || k > (r - l) + 1) return -1;

            int index = partWCS(array, l, r);
        
            if(index == k) return array[index];
            if(index > k) return qs(array, k, l, index - 1);
            else return qs(array, k, index + 1, r);
        }

        int partQS(T *array, int l, int r){
            T x = array[r];
            int i = l;

            for(int j = l; j < r; j++){
                if(array[j] <= x){
                    swap(array[i], array[j]);
                    i++;
                }
            }
            swap(array[i], array[r]);
            return i;
        }

        int partWCS(T *array, int l, int r){
            T x = array[r + l / 2];
            int i = l;

            for(int j = l; j < r; j++){
                if(array[j] <= x){
                    swap(array[i], array[j]);
                    i++;
                }
            }
            swap(array[i], array[r]);
            return i;
        }
};

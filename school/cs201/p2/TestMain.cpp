#include <iostream>
using namespace std;
#include "RBTree.cpp"

int main(){


    char a[3] = {'B', 'A', 'C'};

    int b[3] = {2, 1, 3};

    RBTree <char, int> T1(a, b, 3);


    // T1.insert('B', 2);

    // T1.insert('A', 1);

    // T1.insert('C', 3);

    T1.preorder();
    
    T1.inorder();

    T1.postorder();

    T1.search('B');

    T1.search('C');

    T1.search('A');

    T1.remove('A');

    T1.remove('A');

    cout << endl;

    T1.remove('C');

    cout << T1.remove('C') << endl;

    cout << "\tD: C should not be on the next line\n";

    T1.preorder();

    cout << "1------------------------------\n";

    T1.insert('A', 1);
    
    T1.insert('C', 3);

    T1.inorder();
    
    cout << "\n\n";

    cout << *(T1.successor('B')) << endl;

    cout << *(T1.successor('A')) << endl;

    cout << *(T1.predecessor('C')) << endl;

    cout << *(T1.predecessor('B')) << endl;

    cout << "\n\n";

    T1.printk(5);

    T1.printk(2);

    T1.printk(3);

    T1.printk(1);

    cout << endl << endl;

    cout << T1.select(1) << endl;

    T1.select(5);

    cout << T1.select(2) << endl;

    cout << T1.select(3) << endl;

    cout << "T1 size = " << T1.size();

    cout << "\n\n";

    cout << T1.rank('A') << endl;

    cout << T1.rank('B') << endl;

    cout << T1.rank('C') << endl;

    cout << T1.rank('F') << endl;


    cout << "2-----------------------------------------\n";

    char c[] = {'D', 'B', 'F', 'G', 'C', 'A', 'E'};

    int d[] = {4, 2, 6, 7, 3, 1, 5};

    RBTree <char, int> T2(c, d, 7);

    T2.inorder();

    cout << "\n\n3----------------------------------------------\n\n";

    T2.preorder();

    cout << "\n\n4----------------------------------------------\n\n";

    T2.postorder();

    cout << "\n\n5----------------------------------------------\n\n";

    cout << "\tD: " << T2.remove('D') << endl;

    T2.inorder();

    cout << "\n\n6----------------------------------------------\n\n";

    //RBTree <char, int> T3;

    //T3 = T2;

    T2.remove('F');

    T2.inorder();

    //cout << "\n\n7----------------------------------------------\n\n";

    //T3.inorder();
}
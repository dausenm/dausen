#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

void intMode(string f1, string f2);
void stringMode(string f1, string f2);
void sortInt(int a[], int n);
void mergeInt(int a[], int a1[], int a2[], int n);
void printDupeInts(int arr1[], int arr2[], int lim1, int lim2);
void sortStr(string a[], int n);
void mergeStr(string a[], string a1[], string a2[], int n);
void printDupeStr(string arr1[], string arr2[], int lim1, int lim2);

int main (int argc, char **argv){
    char mode = argv[1][0];
    string f1 = argv[2];
    string f2 = argv[3];

    if(mode == 'i'){
        intMode(f1, f2);
    }
    else if (mode == 's'){
        stringMode(f1, f2);
    }

return 0;
}

void intMode(string f1, string f2){
    ifstream inputFile;
    inputFile.open(f1, ios::in);

    int arr[40000];
    int arr2[40000];
    int i = 0;

    if (inputFile.is_open()){
        while(inputFile >> arr[i]){
            i++;
        }
    }
    inputFile.close();

    ifstream file2;
    file2.open(f2, ios::in);

    int j = 0;
    if(file2.is_open()){
        while(file2 >> arr2[j]){
            j++;
        }
    }
    sortInt(arr, i);
    sortInt(arr2, j);
    printDupeInts(arr, arr2, i, j);
}

void stringMode(string f1, string f2){
    ifstream inputFile;
    inputFile.open(f1, ios::in);

    string arr1[40000]; 
    string arr2[40000];

    int i = 0;
    if (inputFile.is_open()){
        while(inputFile >> arr1[i]){
            i++;
        }
    }
    inputFile.close();

    ifstream file2;
    file2.open(f2, ios::in);

    int j = 0;
    if(file2.is_open()){
        while(file2 >> arr2[j]){
            j++;
        }
    }

    sortStr(arr1, i);
    sortStr(arr2, j);
    printDupeStr(arr1, arr2, i, j);
}

void sortInt(int a[], int n){
    if (n<=1){
        return;
    }
    int *a1 = new int [n/2];
    int *a2 = new int [n-(n/2)];
    for(int i = 0; i < n/2; i++){
        a1[i] = a[i];
    }
    for (int i = n/2; i < n; i++){
        a2[i-n/2] = a[i];
    }

    sortInt(a1, n/2);
    sortInt(a2, n-n/2);
    mergeInt(a, a1, a2, n);
}

void mergeInt(int a[], int a1[], int a2[], int n){
    int n1 = n/2, n2 = n-n/2;
    int p1 = 0, p2 = 0, i = 0;
    while(p1 < n1 && p2 < n2){
        a[i++] = a1[p1] < a2[p2] ? a1[p1++] : a2[p2++];
    }
    while (p1 < n1) a[i++] = a1[p1++];
    while (p2 < n2) a[i++] = a2[p2++];
}

void printDupeInts(int arr1[], int arr2[], int lim1, int lim2){
    int lastDupe;
    bool isDupe = false;

    int i = 0;
    int j = 0;

    while(true){
        if(arr1[i] == arr2[j]){
            isDupe = true;
            lastDupe = arr1[i];
            i++;
            j++;
        }
        else if (arr1[i] < arr2[j]){
            i++;
        }
        else if (arr1[i] > arr2[j]){
            j++;
        }
        if(isDupe && (arr1[i] != lastDupe) && (arr2[j] != lastDupe)){
            cout << lastDupe << endl;
            isDupe = false;
        }
        if (i == lim1 || j == lim2){
            break;
        }
    }
}

void sortStr(string a[], int n){
    if (n <= 1) return;
    string *a1 = new string[n/2];
    string *a2 = new string[n-(n/2)];
    for (int i = 0; i < n/2; i++)
        a1[i] = a[i];
    for (int i = n/2; i < n; i++)
        a2[i-n/2] = a[i];

    sortStr(a1, n/2);
    sortStr(a2, n-n/2);
    mergeStr(a, a1, a2, n);
}

void mergeStr(string a[], string a1[], string a2[], int n){
    int n1 = n/2, n2 = n-n/2;
    int p1 = 0, p2 = 0, i = 0;
    while (p1 < n1 && p2 < n2){
        a[i++] = a1[p1] < a2[p2] ? a1[p1++] : a2[p2++];
    }
    while (p1 < n1) a[i++] = a1[p1++];
    while (p2 < n2) a[i++] = a2[p2++];
}

void printDupeStr(string arr1[], string arr2[], int lim1, int lim2){
    string lastDupe;
    bool isDupe = false;

    int i = 0, j = 0;

    while (true){
        if(arr1[i] == arr2[j]){
            isDupe = true;
            lastDupe = arr1[i];
            i++;
            j++;
        }
        else if (arr1[i] < arr2[j]){
            i++;
        }
        else if (arr1[i] > arr2[j]){
            j++;
        }
        if(isDupe && (arr1[i] != lastDupe) && (arr2[j] != lastDupe)){
            cout << lastDupe << endl;
            isDupe = false;
        }
        if (i == lim1 || j == lim2){
            break;
        }
    }
}
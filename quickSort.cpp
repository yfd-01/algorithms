#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void swap(vector<int>& v, int i, int j){
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

//Method 1
void quickSort(vector<int>& v, int l, int r){
    int i = l;
    int j = r;
    int pivot = v[l];

    while(i < j){
        while(i < j && v[j] >= pivot) j--;
        while(i < j && v[i] <= pivot) i++;

        if(i != j)
            swap(v, i, j);
    }

    swap(v, i, l);

    if(l < i - 1) quickSort(v, l, i - 1);
    if(r > i + 1) quickSort(v, i + 1, r);
}

//Method 2
void quickSort(vector<int>& v, int l, int r){
    int i = l;
    int pivot = v[l];

    for(int j = i + 1; j <= r; j++){
        /*
            If u add equal sign in expression "v[i] <= pivot", which is going to lead that all the sorted
        elements in the right side are more than pivot value, simultaneously, the elements in the left sides
        are less than or equalize pivot value.
            Think about the consequence if we remove equal sign in expression "v[i] < pivot", the element
        that equals with pivot value may appear in this time.
        */
        if(v[j] <= pivot){
            i++;
            swap(v, i, j);
        }
    }

    swap(v, i, l);

    if(l < i - 1) quickSort(v, l, i - 1);
    if(r > i + 1) quickSort(v, i + 1, r);
}

int main(){
    vector<int> v = {7, 9, 11, -1, 0, 3, 1, 100, -20, 99, 4};

    cout<< "Before sorting: ";
    for_each(v.begin(), v.end(), [](int n){
        cout<< n<< ' ';
    });

    quickSort(v, 0, int(v.size()) - 1);

    cout<< "\nAfter sorting: ";

    for_each(v.begin(), v.end(), [](int n){
        cout<< n<< ' ';
    });

    /*  Outputs:

        Before sorting: 7 9 11 -1 0 3 1 100 -20 99 4
        After sorting: -20 -1 0 1 3 4 7 9 11 99 100
    */

    return 0;
}

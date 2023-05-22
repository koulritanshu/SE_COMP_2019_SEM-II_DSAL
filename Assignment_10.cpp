//============================================================================
// Name        : Assignment_10.cpp
// Author      : Ritanshu Koul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*


Problem Statement
Read the marks obtained by students of second year in an online
examination of particular subject. Find out maximum / minimum marks
obtained in that subject. Use heap data structure. Analyze the algorithm.

*/

#include <iostream>
#include <vector>
using namespace std;
#define MAX 1000

class Heap
{
    int arr[MAX];
    int n;
    int size;
public:
    Heap(int x)
    {
        n = x;
        size = n;
        for (int i = 0; i < n; i++)
        {
            arr[i] = 0;
        }
    }
    void display()
    {
        cout << "[";
        for (int i = 0; i < size - 1; i++)
        {
            cout << arr[i] << ", ";
        }
        cout << arr[size - 1] << "]" << endl;
    }
    void read_values()
    {
        for (int i = 0; i < n; i++)
        {
            cout << ">> Enter the marks of student " << i + 1 << ": ";
            cin >> arr[i];
        }
    }
    int get_parent(int i)
    {
        return (i - 1) / 2;
    }
    void swap(int arr[], int i, int j)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    void heapify(int N, int i){
        int largest = i;

        int left = 2*i + 1;
        int right = 2*i + 2;

        // check if left node is largest
        if(left < N && arr[largest]<arr[left]){
            largest = left;
        }
        // check if right node is largest
        if(right < N && arr[largest]<arr[right]){
            largest = right;
        }
        if(largest != i){
            swap(arr,i,largest);
            heapify(N,largest);
        }
    }
    void heap_sort()
    {
        for(int i=n/2-1;i>=0;i--){
            heapify(n,i);
        }
        for(int i=n-1;i>=0;i--){
            swap(arr,0,i);
            heapify(i,0);   
            cout << n - 1 - i + 1 << ". ";
            display();
        }
    }
    int get_min()
    {
        return arr[0];
    }
    int get_max()
    {
        return arr[n - 1];
    }
};

int main()
{
    int n;
    cout << "---------------CREATING A HEAP---------------" << endl;
    cout << ">> Enter the number of students: " << endl
         << "--> ";
    cin >> n;
    Heap obj(n);
    obj.read_values();
    cout << "----------HEAP CREATED SUCCESSFULLY----------" << endl;
    cout << "---------------USING HEAP SORT---------------" << endl;
    obj.heap_sort();
    cout << "------------------MAX/MIN--------------------" << endl;
    cout << ">> Maximum marks = " << obj.get_max() << endl;
    cout << ">> Minimum marks = " << obj.get_min() << endl;
    cout << "--------------------EXIT---------------------" << endl;
    return 0;
}
// Linear Probing with chaining without replacement
// It is a type of open addressing

#include <iostream>
using namespace std;

class Bucket{
    int data;
    int chain;
public:
    Bucket(){
        data = -1;
        chain = -1;
    }
    friend class hashtable;
};

int h(int x){
    return x%10;
}

class hashtable{
    Bucket arr[10];
public:
    void display(){
        for(int i=0;i<10;i++){
            cout << arr[i].data << " " << arr[i].chain << endl;
        }
    }
    void insert(int x){
        int key = h(x);
        if(arr[key].data == -1){
            arr[key].data = x;
        }
        else if(arr[key].data != -1){
            while(arr[key].chain != -1){
                key = arr[key].chain;
            }
            int temp = key;
            while(arr[key].data != -1){
                if(arr[key].data % 10 == h(x)){
                    temp = key;
                }
                key = (key+1)%10;
                if(temp==key) return;
            }
            if(arr[temp].data % 10 == h(x))
            arr[temp].chain = key;
            arr[key].data = x;
        }
    }
};

int main()
{
    hashtable h;
    h.insert(1);
    h.insert(2);
    h.insert(11);
    h.insert(4);
    h.insert(3);
    h.insert(33);
    h.insert(55);
    h.insert(105);
    h.insert(10);    
    h.insert(20);    
    h.display();
}
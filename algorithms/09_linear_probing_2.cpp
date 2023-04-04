// linear probing without chaining

#include <iostream>
using namespace std;

class htable{
    int arr[10];
public:
    htable(){
        for(int i=0;i<10;i++){
            arr[i] = -1;
        }
    }
    void insert(int x){
        int key = x%10;
        if(arr[key] == -1){
            arr[key] = x;
            return;
        }
        else{
            int temp = key;
            while(arr[key] != -1){
                key = (key+1)%10;
                if(key==temp) return;
            }
            arr[key] = x;
        }
    }
    void display(){
        for(int i=0;i<10;i++){
            cout << i << "-> " << arr[i] << endl;
        }
    }
};

int main()
{
    htable h;  
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
    h.insert(100); // should not be inserted
    h.display();
}
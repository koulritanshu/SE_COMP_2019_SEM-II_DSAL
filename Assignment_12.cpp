#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Employee{
    string name;
    int id;
public:
    Employee(){
        name = "";
        id = 0;
    }
    friend class DAF;
};

class DAF{
    string fname;
    int arr[50];
    int num;
public:
    DAF(string n, int number){
        fname = n;
        num = number;
        for(int i=0;i<50;i++){
            arr[i] = -1;
        }
    }
    int hashfunc(int ind){
        return ind % num;
    }
    void dispTable(){
        for(int i=0;i<num;i++){
            cout << i << "-> " << arr[i] << endl;
        }
    }
    void addRecord(string name, int id){
        ofstream obj;
        obj.open(fname,ios::app|ios::ate);
        int location = obj.tellp();
        int hash = hashfunc(id);
        if(arr[hash] == -1){
            arr[hash] = location;
        }
        else{
            int temp = hash + 1;
            while(temp!=hash){
                if(temp == num){
                    temp = 0;
                }
                else{
                    if(arr[temp] == -1){
                        arr[temp] = location;
                        break;
                    }
                    else{
                        temp = temp + 1;
                    }
                }
            }
            if(temp == hash){
                cout << "Table Full." << endl;
                obj.close();
                return;
            }
        }
        obj << id << " " << name << "\n";
        obj.close();
    }
    void searchRecord(int id){
        int index = hashfunc(id);
        if(arr[index] == -1){
            cout << "Record not present." << endl;
        }
        else{
            int count = 0;
            while(count != num){
                count++;
                if(index == num){
                    index = 0;
                }
                int loc = arr[index];
                ifstream obj;
                obj.open(fname);
                obj.seekg(loc,ios::beg);
                string s;
                getline(obj,s);
                string x = "";
                int i = 0;
                while(s[i] != ' '){
                    x += s[i];
                    i++;
                }
                if(x == to_string(id)){
                    cout << "Record Found: " << s << endl;
                    return;
                }
                index++;
            }
            cout << "Record not present" << endl;
        }
    }
    void insert_records(int iddel,vector<string> v){
        for(int i=0;i<v.size()-1;i++)
        {
            string curr = v[i];
            string id = "";
            string name = "";
            int ind = 0;
            while(curr[ind]!=' '){
                id += curr[ind];
                ind++;
            }
            if(id == to_string(iddel)) continue;
            ind++;
            while(ind != curr.size()){
                name += curr[ind];
                ind++;
            }
            addRecord(name,stoi(id));
        }
    }
    void del(int id){
        vector<string> v;
        ifstream obj;
        obj.open(fname);
        string s;
        while(!obj.eof()){
            getline(obj,s);
            v.push_back(s);
        }
        obj.close();
        ofstream obj2;
        obj2.open(fname,ios::trunc);
        obj2.close();
        for(int i=0;i<num;i++){
            arr[i] = -1;
        }
        insert_records(id,v);
    }
};


int main()
{
    cout << "Enter the size of the table: ";
    int n;
    cin >> n;
    DAF obj("DAF.txt",n);
    while(true){
        cout << "1. Insert record." << endl;
        cout << "2. Search record." << endl;
        cout << "3. Delete record." << endl;
        cout << "4. Display table." << endl;
        cout << "5. Exit." << endl;
        int ch;
        cout << "Make choice: ";
        cin >> ch;
        if(ch == 1){
            cout << "Enter id: ";
            int id;
            cin >> id;
            cout << "Enter name: ";
            string name;
            cin >> name;
            obj.addRecord(name,id);
        }
        else if(ch == 2){
            cout << "Enter id: ";
            int id;
            cin >> id;
            obj.searchRecord(id);
        }
        else if(ch == 3){
            cout << "Enter id: ";
            int id;
            cin >> id;
            obj.del(id);
        }
        else if(ch == 4){
            obj.dispTable();
        }
        else if(ch == 5){
            cout << "OK!" << endl;
            break;
        }
    }
    return 0;
}
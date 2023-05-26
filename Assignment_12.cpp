#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ios>
#include <climits>
using namespace std;

class Employee{
    string id;
    string name;
    string city;
public:
    Employee(){}
    Employee(string a,string b, string c){
        id = a;
        name = b;
        city = c;
    }
    friend class DirectAccessFile;
    int size(){
        string obj = "";
        obj = obj + id + " " + name + " " + city;
        return (int)obj.size();
    }
};

class DirectAccessFile{
    map<string,int> hash;
    string filename;
    bool isEmpty = true;
public:
    DirectAccessFile(string f){
        filename = f;
    }
    void insertData(string id, string name, string city){
        Employee emp(id,name,city);
        ofstream obj;
        int previous = INT_MIN;
        if(isEmpty){
            hash[id] = emp.size();
            isEmpty = false;
        }
        else{
            int maxi = -1;
            for(auto i:hash){
                maxi = max(maxi,i.second);
            }
            hash[id] = maxi + emp.size();
        }
        obj.open(filename,ios::app);
        obj << emp.id << " " << emp.name << " " << emp.city << "\n";
        obj.close();
    }
    void printFileData(){
        string s;
        ifstream obj;
        obj.open(filename);
        if(!obj){
            cout << ">> File could not be opened." << endl;
            return;
        }
        while(!obj.eof()){
            getline(obj,s);
            cout << s << endl;
        }
        obj.close();
    }
    void deleteRecord(string id){
        vector<string> v;
        ifstream obj;
        obj.open(filename);
        while(!obj.eof()){
            string s;
            getline(obj,s);
            v.push_back(s);
        }
        obj.close();
        ofstream ob;
        ob.open(filename);
        for(int i=0;i<(int)v.size();i++){
            string id1 = "";
            id1 += v[i][0]; 
            id1 += v[i][1]; 
            id1 += v[i][2];
            if(id1==id) continue;
            ob << v[i] << "\n";
        }
        obj.close();
    }
};

int main()
{
    cout << "-------------------CREATING A FILE-------------------" << endl;
    DirectAccessFile obj("emplyee.txt");
    cout << "------------------ADDING EMP. DETAILS----------------" << endl;
    obj.insertData("213","Ritanshu","Jammu");
    obj.insertData("214","Tom","New York");
    obj.insertData("215","Andrew","London");
    obj.insertData("216","Lisa","Paris");
    obj.insertData("217","Ajay","Jaipur");
    cout << "-------------------PRINTING RECORDS------------------" << endl;
    obj.printFileData();
    cout << "------------------DELETING A RECORD------------------" << endl;
    obj.deleteRecord("215");
    obj.deleteRecord("217");
    obj.printFileData();
    cout << "-----------------------EXIT--------------------------" << endl;
    return 0;
}
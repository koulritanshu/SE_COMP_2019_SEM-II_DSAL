#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Record{
    string roll_number;
    string name;
    int division;
    string city;
public:
    Record(){
        roll_number = "";
        name = "";
        division = 0;
        city = "";
    }
    Record(string r, string s, int d, string c){
        roll_number = r;
        name = s;
        division = d;
        city = c;
    }
    friend class SequentialFile;
};

class SequentialFile{
    string filename;
public:
    SequentialFile(){
        cout << ">> Please pass the name of the file." << endl;
        cin >> filename;
    }
    SequentialFile(string f){
        filename = f;
    }
    void searchRecords(string ro){
        ifstream obj;
        obj.open(filename);
        Record r;
        if(!obj){
            cout << ">> Error opening the file!" << endl;
            return;
        }
        bool isFound = false;
        string s;
        while(!obj.eof()){
            getline(obj,s);
            if(s == ro){
                isFound = true;
                cout << ">> Roll Number of Student is present." << endl;
                break;
            }
        }
        if(!isFound){
            cout << ">> Record of student is not present." << endl;
        }
        else{
            string temp;
            for(int i=0;i<3;i++){
                getline(obj,temp);
                cout << temp << endl;
            }
        }
    }
    void addRecord(string name, string city, string r, int d){
        Record rec(r,name,d,city);
        ofstream obj;
        obj.open(filename,ios::app);
        obj << rec.roll_number << "\n";
        obj << rec.name << "\n";
        obj << rec.city << "\n";
        obj << rec.division << "\n";
    }
    void printRecords(){
        ifstream obj;
        obj.open(filename);
        if(!obj){
            cout << ">> Trouble opening the file." << endl;
            return;
        }
        string s;
        int i = 4;
        while(!obj.eof()){
            getline(obj,s);
            if(i%4 == 0 && !obj.eof() && s != " "){
                cout << "---------" << i/4 << "---------" << endl;
            }
            cout << s << endl;
            i++;
        }
    }
    void deleteRecords(string r){
        vector<string> v;
        ifstream obj;
        obj.open(filename);
        while(!obj.eof()){
            string s;
            getline(obj,s);
            if(s == r){
                getline(obj,s);
                getline(obj,s);
                getline(obj,s);
                getline(obj,s);
            }
            v.push_back(s);
        }
        obj.close();
        ofstream ob;
        ob.open(filename);
        for(int i=0;i<v.size();i++){
            ob << v[i] << "\n";
        }
    }
};

int main()
{
    SequentialFile obj("records.txt");
    cout << "------------------ADDING 5 RECORDS-------------------\n";
    obj.addRecord("Ritanshu Koul","Jammu","21167",1);
    obj.addRecord("Tom","New York","21111",2);
    obj.addRecord("Andrew","London","21789",3);
    obj.addRecord("Lisa","Paris","21212",4);
    obj.addRecord("Ronit Koul","Jammu","12345",2);
    cout << "----------------- SUCCESSFUL SEARCH-------------------\n";
    obj.searchRecords("21212");
    cout << "-----------------UNSUCCESSFUL SEARCH------------------\n";
    obj.searchRecords("12121");
    cout << "----------------PRINTING ALL RECORDS------------------\n";
    obj.printRecords();
    cout << "------------------DELETING A RECORD-------------------\n";
    obj.deleteRecords("21212");
    cout << "------------------- AGAIN PRINTING--------------------\n";
    obj.printRecords();
    cout << "------------------------OVER--------------------------\n";
    return 0;
}
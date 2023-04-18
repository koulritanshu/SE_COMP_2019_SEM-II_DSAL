//============================================================================
// Name        : Assignment_06.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <queue>
using namespace std;

template <class T>
class Stack
{
    T arr[1000];
    int top = -1;

public:
    bool empty()
    {
        return (top == -1);
    }
    void push(T x)
    {
        top++;
        arr[top] = x;
    }
    T pop()
    {
        T temp = arr[top];
        top--;
        return temp;
    }
    T TOP()
    {
        return arr[top];
    }
};

template <class T>
class Queue
{
    T arr[1000];
    int front = -1;
    int rear = -1;

public:
    bool empty()
    {
        if (rear == -1)
        {
            return true;
        }
        else if (front == (rear))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    T pop()
    {
        front++;
        T temp = arr[front];
        return temp;
    }
    void push(T x)
    {
        rear++;
        arr[rear] = x;
    }
};

class Node
{
    string data;
    Node *next;
    Node *down;

public:
    Node(string x)
    {
        data = x;
        next = NULL;
        down = NULL;
    }
    friend class Graph;
};

class Graph
{
    Node *head;

public:
    Graph()
    {
        head = NULL;
    }
    void addNode(string d, string x)
    {
        Node *newNode = new Node(d);
        Node *newNode2 = new Node(x);
        if (head == NULL)
        {
            newNode->next = newNode2;
            head = newNode;
            return;
        }
        else
        {
            Node *curr = head;
            while (curr->down != NULL && curr->data != d)
            {
                curr = curr->down;
            }
            if (curr->data == d)
            {
                while (curr->next != NULL)
                {
                    curr = curr->next;
                }
                curr->next = newNode2;
            }
            else
            {
                newNode->next = newNode2;
                curr->down = newNode;
            }
        }
    }
    void add(string d, string x)
    {
        addNode(d, x);
        addNode(x, d);
    }
    void display()
    {
        Node *curr = head;
        while (curr)
        {
            Node *insidecurr = curr;
            cout << " >> " << insidecurr->data;
            insidecurr = insidecurr->next;
            while (insidecurr)
            {
                cout << "-> " << insidecurr->data;
                insidecurr = insidecurr->next;
            }
            curr = curr->down;
            cout << endl;
        }
    }
    void breadth(string d)
    {
        Node *curr = head;
        while (curr->data != d)
        {
            curr = curr->down;
        }
        Queue<Node *> q;
        map<string, bool> mp;
        q.push(curr);
        mp[curr->data] = true;
        while (!q.empty())
        {
            string x = q.pop()->data;
            cout << x << ' ';
            curr = head;
            while (curr->data != x)
            {
                curr = curr->down;
            }
            while (curr)
            {
                if (!mp[curr->data])
                {
                    q.push(curr);
                    mp[curr->data] = true;
                }
                curr = curr->next;
            }
        }
    }
    void dfs(string d)
    {
        Node *curr = head;
        while (curr->data != d)
        {
            curr = curr->down;
        }
        Stack<Node *> st;
        map<string, bool> mp;
        st.push(curr);
        mp[curr->data] = true;
        while (!st.empty())
        {
            string x = st.TOP()->data;
            cout << x << " ";
            st.pop();
            Node *curr = head;
            while (curr->data != x)
            {
                curr = curr->down;
            }
            while (curr)
            {
                if (!mp[curr->data])
                {
                    st.push(curr);
                    mp[curr->data] = true;
                }
                curr = curr->next;
            }
        }
    }
};

int main()
{
    Graph obj;
    obj.add("PICT", "BVP");
    obj.add("PICT", "Wellness Forever");
    obj.add("Pune", "Maharashtra");
    obj.add("Pune", "PICT");
    obj.add("India", "Maharashtra");
    cout << endl;
    cout << "--------------DISPLAYING GRAPH--------------------" << endl;
    cout << endl;
    obj.display();
    cout << endl;
    cout << "--------------BREADTH FIRST SEARCH----------------" << endl;
    cout << endl;
    obj.breadth("PICT");
    cout << endl;
    cout << endl;
    cout << "--------------DEPTH FIRST SEARCH----------------" << endl;
    cout << endl;
    obj.dfs("PICT");
    cout << endl;
    cout << endl;
    cout << "------------------------------------------------" << endl;
    return 0;
}

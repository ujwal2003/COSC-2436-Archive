
#include <iostream>
#include<fstream>
#include<sstream>
#include <stack>
#include <string>
#include "ArgumentManager.h"

using namespace std;

struct Node {
    string data;
    Node* next;
};

string decodeId(string s);

void insertNodeAtEnd(Node* &head, string data);
Node* reverseList(Node* &head);
void mergeLists(Node* &head1, Node* head2);
bool firstIsGreaterThanSecond(string first, string second);
void sortList(Node* &head, Node* p1, Node* p2);
Node* getDuplicates(Node* head, Node* &duplicateList);
Node* removeDuplicates(Node* head, Node* &duplicateList);
void deleteNodeByValue(Node* &head, string value);
void printList(Node* head, ofstream& out);

int main(int argc, char* argv[]) {

  ArgumentManager am(argc, argv);

  string input = am.get("input");
  string output = am.get("output");

  ifstream in;
  ofstream out;
  istringstream inSS;

  in.open(input);
  out.open(output);


    // ==============================  Decode all IDs and add to respective Linked Lists  ==============================

    try
    {
        if (!in.is_open())
        {
            throw runtime_error("ERROR: File not found");
        }

        if (in.peek() == EOF)
        {
            throw runtime_error("ERROR: File is empty");
        }

        string line = "";
        string id = "";

        string currentListToAdd;

        Node* bar1 = NULL;
        Node* bar2 = NULL;

        while (getline(in, line))
        {
            if (line.empty()) { continue; }

            else if (line == "Bar1" || line == "Bar2")
            {
                currentListToAdd = line;
            }

            else
            {
                id = decodeId(line);

                if (currentListToAdd == "Bar1")
                {
                    insertNodeAtEnd(bar1, id);
                }
                else if (currentListToAdd == "Bar2")
                {
                    insertNodeAtEnd(bar2, id);
                }
            }
        }

        // ==============================  Merge both lists and sort in ascending order  ==============================
        mergeLists(bar1, bar2);
        sortList(bar1, bar1, bar1->next);

        // ==============================  Find duplicates and remove them from the list  ==============================

        Node* innocentList = NULL;
        Node* guiltyList = NULL;

        guiltyList = getDuplicates(bar1, guiltyList);
        innocentList = removeDuplicates(bar1, guiltyList);

        if(guiltyList) {
            cout<<"Guilty:"<<endl;
            out<<"Guilty:"<<endl;
            printList(guiltyList, out);
        }

        if(innocentList) {
            if(guiltyList) {
                cout<<endl;
                out<<endl;
            }
            cout<<"Innocent:"<<endl;
            out<<"Innocent:"<<endl;
            printList(innocentList, out);
        }


    }
    catch (runtime_error & e)
    {
        out << e.what() << endl;
    }

    in.close();
    out.close();

    return 0;

}

string decodeId(string s) {

    string id="";

    stack<char> st1;
    stack<char> st2;

    for(char c: s) {
        if(c!=')'){
            st1.push(c);
        }
        if(c==')'){
            string temp="";
            while(st1.top()!='('){
                temp=temp+st1.top();
                st1.pop();
            }
            st1.pop();
            for(char a: temp){
                st1.push(a);
            }
        }
    }

    while(!st1.empty()){
        st2.push(st1.top());
        st1.pop();
    }

    while(!st2.empty()){
        id = id + st2.top();
        st2.pop();
    }

    return id;
}

bool firstIsGreaterThanSecond(string first, string second) {

    string a = first.erase(0, first.find_first_not_of('0'));
    string b = second.erase(0, second.find_first_not_of('0'));

    if (a.length() > b.length()) { return true; }

    if (a.length() < b.length()) { return false; }

    for(int i=0; i<first.length(); i++) {
        if(a[i] < b[i]) {
            return false;
        }

        if(a[i] > b[i]) {
            return true;
        }
    }

    return true;
}

void sortList(Node* &head, Node* p1, Node* p2) {

    if(p2==NULL) { return; }

    Node* p3 = p1->next;

    while(p3!=NULL)
    {
        if(firstIsGreaterThanSecond(p1->data, p3->data)) {
            swap(p1->data,p3->data);
        }

        p3 = p3->next;
    }

    sortList(head,p2,p2->next);
}

Node* reverseList(Node* &head)
{
    if (head == NULL || head->next == NULL)
        return head;

    Node* rest = reverseList(head->next);
    head->next->next = head;

    head->next = NULL;

    return rest;
}


void insertNodeAtEnd(Node* &head, string data) {
    Node *temp = new Node();
    temp->data = data;
    temp->next = NULL;

    if(head == NULL) {
        head = temp;
    }
    else {
        insertNodeAtEnd(head->next, data);
    }
}



void mergeLists(Node* &head1, Node* head2) {

    if(!head1 && !head2)
    {
        return;
    }

    if(head1 && !head2) {
        return;
    }

    if(!head1 && head2) {
        head1 = head2;
        return;
    }

    else {
        Node* curr = head1;

        if(curr->next != NULL) {
            mergeLists(curr->next, head2);
        }
        else {
            curr->next = head2;
            return;
        }
    }
}

Node* getDuplicates(Node* head, Node* &duplicateList) {
    if (!head) {
        return NULL;
    }

    if (head->next == NULL) {
        return duplicateList;
    }

    if (head->data == head->next->data) {
        insertNodeAtEnd(duplicateList, head->data);
    }

    return getDuplicates(head->next, duplicateList);
}

Node* removeDuplicates(Node* head, Node* &duplicateList) {
    if(!duplicateList) { return head; }

    deleteNodeByValue(head, duplicateList->data);

    return removeDuplicates(head, duplicateList->next);
}

void deleteNodeByValue(Node* &head, string value) {

    if(!head) {
        cout<<"Value not found in list!"<<endl;
        return;
    }

    if(head-> data == value) {
        Node* temp1 = head;
        Node* temp2 = head->next;
        head = head->next->next;
        delete temp1;
        delete temp2;
        return;
    }

    if(head->next->data == value) {
        Node* temp1 = head->next;
        Node* temp2 = head->next->next;
        head->next = head->next->next->next;
        delete temp1;
        delete temp2;
        return;
    }

    deleteNodeByValue(head->next, value);

}


void printList(Node* head, ofstream& out) {

    if(!head) {
        return;
    }

    if(head->next == NULL) {
        out<<head->data;
        cout<<head->data;
    }
    else {
        out<<head->data<<endl;
        cout<<head->data<<endl;
    }

    printList(head->next, out);
}

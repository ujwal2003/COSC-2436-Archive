#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct node{
    string data1;
    long int data2;
    node *next;
};

class ll{
    public:
        node*head;
        node*tail;
        vector<string> duplicates;

        //Constructor
        ll(){
            head = nullptr;
            tail = nullptr;
        }

        //Checks if a list is empty
        bool isEmpty(){
            if(!head){
                return true;
            }
            return false;
        }

        //Adds to the front of the list
        void add_front(string d){
            node *temp = new node;
            temp->data1 = d;
            temp->next = nullptr;

            if(isEmpty()){
                head = temp;
                tail=temp;
            }else{
                temp->next = head;
                head=temp;
            }
        }

        //Changes the numbers into long ints
        long int toInt(string basic){
            long int x;
            stringstream toN(basic);
            toN >> x;
            return x;
        }

        //Gets the vector of duplicates
        vector<string> getDuplicates(){
            return duplicates;
        }

        //Adds at the end of the list
        void add_end(string d){
            node *temp = new node;
            temp->data1 = d;
            temp->data2 = toInt(d);
            temp->next = nullptr;

            if(isEmpty()){
                head=temp;
                tail=temp;
            }else{
                tail -> next = temp;
                temp->next = nullptr;
                tail = temp;
            }
        }  

        //Sorts the list
        node *sort(node *start){
            if( start == NULL ) return NULL;
            if( start->next !=NULL && start->data2 > start->next->data2)
                start = list_switch( start, start->next );
                start->next = sort(start->next);
            if( start->next !=NULL && start->data2 > start->next->data2){
                start = list_switch(start,start->next);
                start->next = sort(start->next);
            }
            return start;
        }

        //Switches the nodes of the list
        node *list_switch( node *l1, node *l2 ){
            l1->next = l2->next;
            l2->next = l1;
            return l2;
        }

        //Prints the list recursively
        void print(node *trav, ofstream &ofs){
            if(trav == NULL){
                return;
            }else{
                ofs << trav->data1 << endl;
                print(trav->next,ofs);
            }
        }
        //Prints the list to console
        void printToScreen(node *trav){
            if(trav == NULL){
                return;
            }else{
                cout << trav->data1 << endl;
                printToScreen(trav->next);
            }
        }
        //Deletes a duplicate then sends the other out to get deleted
        void deleteDuplicates(node *h, int count, ofstream &ofs) { 
            if (h != NULL && h->next != NULL) {
                if (h->data1 == h->next->data1) {
                    //outputs that there is a guilty person
                    //then creates a list of guilty people
                    duplicates.push_back(h->data1);
                    count++;
                    if(count == 1){
                        ofs << "Guilty:" << endl;
                    }
                    ofs << h->data1 << endl;

                    
                     node *x = h->next;
                     h->next = x->next;
                     free(x);
                    deleteDuplicates(h->next, count,ofs);
                }else {
                    deleteDuplicates(h->next, count,ofs);
                }
            }
        }

        //Deletes the second duplicate
        void delete1(string s, node *h, node*prev){
            if(head == nullptr){
                return;
            }else if(s == h->data1){
                 /*if(prev == nullptr) {
                    cout << " deleting value with prev == nullptr : " << h->data1 << endl;
                         node*temp = h;
                         h = h->next;
                         delete(temp);
                         return;
                 }*/
                cout << " deleting value : " << h->data1 << endl;
                node*temp = prev->next;
                prev->next = h->next;
                free(temp);
                return;
            }else{
                delete1(s,h->next, prev = h);
            }
        }

};
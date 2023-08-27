#include <iostream>
#include <string>
#include "sll.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ArgumentManager.h"
#include "myStack.h"
using namespace std;

string reverseParentheses(string line, int size){
    myStack<int> stk;
 
    for (int i = 0; i < size; i++) {
        if (line[i] == '(') {
            stk.push(i);
        }else if (line[i] == ')') {
            reverse(line.begin() + stk.peek() + 1,
                    line.begin() + i);
            stk.pop();
        }
    }
 
    string res = "";
    for (int i = 0; i < size; i++) {
        if (line[i] != ')' && line[i] != '(')
            res += (line[i]);
    }
    return res;
}

// ./main input=input11.txt output=output11.txt
// ./main input=input12.txt output=output12.txt
// ./main input=input13.txt output=output13.txt
int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    string infilename = am.get("input");
    string outfilename = am.get("output");

    //File streams
    ifstream ifs(infilename);
    ofstream ofs(outfilename);

    //Linked Lists
    ll inIds;
    ll list1;
    ll inList1;
    ll inList2;
    

    //String variables to input the data into a linked list
    string inLine_1;

    while(getline(ifs,inLine_1)){
        if(inLine_1.empty()){}else if(inLine_1 == "Bar1" || inLine_1 == "Bar2"){}else{
            std::size_t found = inLine_1.find_last_not_of("\r");
            if(found != std::string::npos){
                inLine_1.erase(found+1);
            }
            int lineLength = inLine_1.size();
            string finish = reverseParentheses(inLine_1,lineLength);
            inIds.add_end(finish);
        }
    }
   
    list1.head = inIds.sort(inIds.head);
    list1.printToScreen(list1.head);
    //Gets the guilty ID's, if any
    list1.deleteDuplicates(list1.head,0,ofs);
    vector<string> list3 = list1.getDuplicates();
  
    //cout << " for loop size : "<<list3.size() << endl;
    list1.printToScreen(list1.head);
    //Deletes all duplicates, if any
    for(int i = 0; i < list3.size(); i++){
        //cout << "entered loop for delete1 with value : " << list3.at(i) << endl;
        list1.delete1(list3.at(i),list1.head, list1.head);
        //cout << "list after delete1 : " << endl;
        list1.printToScreen(list1.head);
    }
  
    //cout << "hello world" << endl;
    //Prints the innocent ID's
    if(list1.head){
        ofs<< "Innocent:" << endl;
        list1.print(list1.head,ofs);
        //list1.printToScreen(list1.head);
    }
    
    //Close streams
    ifs.close();
    ofs.close();
    return 0;
}

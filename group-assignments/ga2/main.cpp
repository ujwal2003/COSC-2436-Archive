#include "ArgumentManager.h"
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct pCheck{
  char data;
  int value;
};
int isBrace(stack<pCheck> &myStack, string st, int p, int secondPoint, int thirdPoint, int line,
         ofstream &out);
int isBracket(stack<pCheck> &myStack, string st, int p, int firstPoint, int secondPoint, int line,
         ofstream &out);
int isParenthesis(stack<pCheck> &myStack, string st, int p, int firstPoint, int secondPoint, int line,
         ofstream &out);

int isBrace(stack<pCheck> &myStack, string st, int p, int secondPoint, int thirdPoint, int line,
         ofstream &out) {
  int next = 1;
  int firstPoint = 1;
  if (p != 0) {
    if (st[p - 1] == '-') {
      firstPoint = -1;
    }
  }
  p++;
  while (st[p] != '}') {
    if (st[p] == '+') {
      next = 1;
    } else if (st[p] == '-') {
      next = -1;
    } else if (st[p] == '[') {
      p = isBracket(myStack, st, p, firstPoint, thirdPoint, line, out);
    } else if (st[p] == '{') {
      p = isBrace(myStack, st, p, secondPoint, thirdPoint, line, out);
    } else if (st[p] == '(') {
      p= isParenthesis(myStack, st, p, firstPoint, secondPoint, line, out);
    } else if (st[p] == ')' or st[p] == ']') {
      out << "Error at: " << line << endl;
      return st.length() + line;
    } else {
      pCheck temp;
      temp.data = st[p];
      temp.value = secondPoint * thirdPoint * firstPoint * next;
      myStack.emplace(temp);
    }
    if (p == st.length() + line) {
      return st.length() + line;
    }
    p++;
    if (p >= st.length()) {
      out << "Error at: " << line << endl;
      return st.length() + line;
    }
  }
  return p;
}
int isBracket(stack<pCheck> &myStack, string st, int p, int firstPoint, int thirdPoint, int line,
         ofstream &out) {
  int next = 1;
  int secondPoint = 1;
  if (p != 0) {
    if (st[p - 1] == '-') {
      secondPoint = -1;
    }
  }
  p++;
  while (st[p] != ']') {
    if (st[p] == '+') {
      next = 1;
    } else if (st[p] == '-') {
      next = -1;
    } else if (st[p] == '{') {
      p = isBrace(myStack, st, p, secondPoint, thirdPoint, line, out);
    } else if (st[p] == '[') {
      p = isBracket(myStack, st, p, firstPoint, thirdPoint, line, out);
    } else if (st[p] == '(') {
      p = isParenthesis(myStack, st, p, firstPoint, secondPoint, line, out);
    } else if (st[p] == ')' or st[p] == '}') {
      out << "Error at: " << line << endl;
      return st.length() + line;
    } else {
      pCheck temp;
      temp.data = st[p];
      temp.value = secondPoint * thirdPoint * firstPoint * next;
      myStack.emplace(temp);
    }
    if (p == st.length() + line) {
      return st.length() + line;
    }
    p++;
    if (p >= st.length()) {
      out << "Error at: " << line << endl;
      return st.length() + line;
    }
  }
  return p;
}
int isParenthesis(stack<pCheck> &myStack, string st, int p, int firstPoint, int secondPoint, int line,
         ofstream &out) {
  int next = 1;
  int thirdPoint = 1;
  if (p != 0) {
    if (st[p - 1] == '-') {
     thirdPoint = -1;
    }
  }
  p++;
  while (st[p] != ')') {
    if (st[p] == '+') {
      next = 1;
    } else if (st[p] == '-') {
      next = -1;
    } else if (st[p] == '{') {
      p = isBrace(myStack, st, p, secondPoint, thirdPoint, line, out);
    } else if (st[p] == '(') {
      p = isParenthesis(myStack, st, p, firstPoint, secondPoint, line, out);
    } else if (st[p] == '[') {
      p = isBracket(myStack, st, p, firstPoint, thirdPoint, line, out);
    } else if (st[p] == '}' or st[p] == ']') {
      out << "Error at: " << line << endl;
      return st.length() + line;
    } else {
      pCheck temp;
      temp.data = st[p];
      temp.value = secondPoint * thirdPoint * firstPoint * next;
      myStack.emplace(temp);
    }
    if (p == st.length() + line) {
      return st.length() + line;
    }
    p++;
    if (p >= st.length()) {
      out << "Error at: " << line << endl;
      return st.length() + line;
    }
  }
  return p;
}
void checkSimilar(ifstream &ifs);
bool isOpenPar(char x);
bool isClosedPar(char x);
bool isOper(char x);
string removePar(string equation);

void checkSimilar(ifstream &ifs, ofstream &ofs) {
  bool repeats = true;
  vector<string> cleanExps;
  string exps;
  while (getline(ifs, exps)) {
    if (exps == "") {
      exps.clear();
    } else {
      cleanExps.push_back(removePar(exps));
    }
  }

  int max = cleanExps.size();

  for (int i = 0; i < max - 1; i++) {
    string st1 = cleanExps.at(i);
    if (!repeats) {
      break;
    } else {
      for (int j = i + 1; j < max; j++) {
        if (!repeats) {
          break;
        } else {
          string st2 = cleanExps.at(j);
          for (int k = 0; k < st1.size(); k++) {
            bool current = false;
            if (st1[k] != '+' and st1[k] != '-') {
              for (int u = 0; u < st1.size(); u++) {
                if (st1[k] == st2[u]) {
                  if (k == 0) {
                    if (u == 0) {
                      current = true;
                      break;
                    } else if (st2[u - 1] == '+') {
                      current = true;
                      break;
                    }
                  } else {
                    if (st1[k - 1] == '+') {
                      if (u == 0) {
                        current = true;
                        break;
                      } else if (st2[u - 1] == '+') {
                        current = true;
                        break;
                      }
                    } else if (st1[k - 1] == '-') {
                      if (st2[u - 1] == '-') {
                        current = true;
                        break;
                      }
                    } else {
                    }
                  }
                } else {
                  current = false;
                }
              }
              if (!current) {
                repeats = false;
                break;
              }
            }
          }
        }
      }
    }
  }
  if (repeats)
    ofs << "Yes" << endl;
  else
    ofs << "No" << endl;
}

string removePar(string equation) {
  string result, clean;
  char x;
  int intotal = 0;
  stack<int> s;
  s.push(0);
  stack<pCheck> allint;
  for (int i = 0; i < equation.length(); i++) {
    x = equation[i];
    if (x == '+' && i == 0) {
      continue;
    } else if (s.empty()) {
      if (equation[i] == '+') {
        s.push(0);
        result += '+';
      } else if (equation[i] == '-') {
        s.push(1);
        result += '-';
      }
    } else if (x == '+') {
      if (s.top() == 1) {
        result += '-';
      } else if (s.top() == 0) {
        result += '+';
      }
    } else if (x == '-') {
      if (s.top() == 1) {
        result += '+';
      } else if (s.top() == 0) {
        result += '-';
      }
    } else if (isOpenPar(x) && i > 0) {
      if (equation[i - 1] == '-') {
        int flip;
        if (s.top() == 1) {
          flip = 0;
        } else if (s.top() == 0) {
          flip = 1;
        }
        s.push(flip);
      } else if (equation[i - 1] == '+') {
        s.push(s.top());
      }
    } else if (isOpenPar(x)) {
      s.push(s.top());
    }

    else if (isClosedPar(x))
      s.pop();
    else if (isdigit(x)) {
      intotal++;
      pCheck special;
      if (result.size() > 0) {
        char mine = result.back();
        result.pop_back();
        if (mine == '-' or mine == '-') {
          special.data = x;
          special.value = -1;
          allint.emplace(special);
        }

        else if (mine == '+') {
          special.data = x;
          special.value = 1;
          allint.emplace(special);
        }
      }
    } else {
      result += x;
    }
  }
  int end = 0;
  int temp;
  for (int i = 0; i < intotal; i++) {
    pCheck special = allint.top();
    if (special.value == -1) {
      temp = special.data - '0';
      end -= temp;
    } else if (special.value == 1) {
      temp = special.data - '0';
      end += temp;
    }
    allint.pop();
  }
  
  stack<char> intex;
  if (end < 0) {
    if (end < -9) {
      end = end - 2 * end;
      result += '-';
      while (end > 0) {
        int ugh = end % 10;
        end = end / 10;
        char mychar = '0' + ugh;
        intex.push(mychar);
      }
      while (!intex.empty()) {
        result += intex.top();
        intex.pop();
      }

    } else {
      end = end - 2 * end;
      result += '-';
      char mychar = '0' + end;
      result += mychar;
    }
  } else {
    if (end > 9) {
      result += '+';
      while (end > 0) {
        int ugh = end % 10;
        end = end / 10;
        char mychar = '0' + ugh;
        intex.push(mychar);
      }
      while (!intex.empty()) {
        result += intex.top();
        intex.pop();
      }

    } else {
      result += '+';
      char mychar = '0' + end;
      result += mychar;
    }
  }
  for (int i = 0; i < result.length(); i++) {
    if (isOper(result[i]) && isOper(result[i + 1])) {
        continue;
    }else{
        clean += result[i];
    }
  }
  return clean;
}

bool isOpenPar(char x) {
    if((x == '(') || (x == '{') || (x == '[')){
        return true;
    }
    return false;
}

bool isClosedPar(char x) { 
    if((x == ')') || (x == '}') || (x == ']')){
        return true;
    }
    return false; 
}

bool isOper(char x) { 
    if(x == '+' || x == '-'){
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string inname = am.get("input");
  string outname = am.get("output");
  ifstream input(inname.c_str());
  ofstream output(outname.c_str());

  string st;
  bool isvalid =true;
  int linecount = 0;
  vector<stack<pCheck>> allstacks;
  while (getline(input, st)) {
    if (!st.empty()) {
      linecount++;
      stack<pCheck> mystack;
      int dataNext, firstPoint, secondPoint, thirdPoint;
      dataNext = 1;
      for (int i = 0; i < st.length(); i++) {
        firstPoint = secondPoint = thirdPoint = 1;
        if (st[i] == '{') {
          i = isBrace(mystack, st, i, secondPoint, thirdPoint, linecount, output);
        } else if (st[i] == '[') {
          i = isBracket(mystack, st, i, firstPoint, thirdPoint, linecount, output);
        } else if (st[i] == '(') {
          i = isParenthesis(mystack, st, i, firstPoint, secondPoint, linecount, output);
        } else if (st[i] == '+') {
          dataNext = 1;
        } else if (st[i] == '-') {
          dataNext = -1;
        } else if (st[i] == ')' or st[i] == '}' or st[i] == ']') {
          output << "Error at: " << linecount << endl;
          break;
        } else {
          pCheck temp;
          temp.data = st[i];
          temp.value = dataNext;
          mystack.emplace(temp);
        }
        if (i == st.length() + linecount) {
          isvalid = false;
        }
      }
      allstacks.push_back(mystack);
    }
  }
  if (isvalid) {
    input.close();
    input.open(inname);
    checkSimilar(input, output);
    output.close();
  }
  return 0;
}

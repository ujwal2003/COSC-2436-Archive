#include "ArgumentManager.h"
#include <fstream>
#include <iostream>

using namespace std;

struct node {
  int data;
  node *left;
  node *right;

  node(int d) {
    data = d;
    left = nullptr;
    right = nullptr;
  }
};

node *insert(node *root, int val) {
  if (root == nullptr) {
    root = new node(val);

  } else if (val > root->data) {
    root->right = insert(root->right, val);

  } else if (val < root->data) {
    root->left = insert(root->left, val);
  }

  return root;
}

void preOrderTraversal(node *root, ofstream &ss, string str) {
  if (root == nullptr)
    return;
  ss << "[" << str << "] " << root->data << endl;
  preOrderTraversal(root->left, ss, str + "l");
  preOrderTraversal(root->right, ss, str + "r");
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);

  string infile = am.get("input");
  string outfile = am.get("output");

  ifstream ifs(infile.c_str());
  ofstream ofs(outfile.c_str());

  node *bst = nullptr;
  int num;

  while (ifs >> num) {
    bst = insert(bst, num);
  }

  // stringstream ss;
  string s = "x";
  preOrderTraversal(bst, ofs, s);
  // cout << ss.str();

  // ofs << "write to output file here";
  ofs.flush();

  ifs.close();
  ofs.close();
}
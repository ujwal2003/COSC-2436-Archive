#include <iostream>
using namespace std;

struct node {
    int *keys;
    node **childptr;
    bool leaf;
    int size;

    // when you have a minimum degree, keys = 2*degree +1

    node(int degree) {
        keys = new int[degree];
        childptr = new node*[degree+1];
        leaf = true;
        size = 0;

        for(int i=0; i<degree; i++)
            keys[i] = -1;

        for(int i=0; i<degree+1; i++)
            childptr[i] = nullptr;
    }
};

class btree {
    private:
        node* root;
        int degree;

    public:
        btree(int _degree) {
            root = nullptr;
            degree = _degree;
        }
    
        void insert(int data) {
            if(root == nullptr) {
                root = new node(degree);
                root->keys[0] = data;
                root->size += 1;
            }
            else
                addAtLeaf(nullptr, root, data);
        }

        void addAtLeaf(node* parent, node* n, int data) {
            if(n->leaf) {
                int i = n->size;
                // add data at the correct position in keys
                while(i != 0 && n->keys[i-1] > data) {
                    n->keys[i] = n->keys[i-1];
                    i--;
                }
				
                n->keys[i] = data;
                // increase size
                n->size += 1;
            }
            else {
                // find the approriate leaf
                int i = 0;
                while(i < n->size && data > n->keys[i])
                    i++;
                addAtLeaf(n, n->childptr[i], data);
            }

            if(n->size == degree) {
                // split
                if(n == root) {
                    node* temp = new node(degree);
                    temp->leaf = false;
                    temp->childptr[0] = n;
                    splitChild(temp, n);
                    root = temp;
                }
                else
                    splitChild(parent, n);
            }
        }

        void splitChild(node* parent,  node* leftNode) {
            node* rightNode = new node(degree);
            int mid = (degree-1)/2;

            // copy the second half keys of leftNode to rightNode
            int rightKeyIndex = 0;
            for(int i=mid+1; i<degree; i++) {
                rightNode->keys[rightKeyIndex] = leftNode->keys[i];
                leftNode->keys[i] = -1;
                rightKeyIndex++;
                leftNode->size -= 1;
                rightNode->size += 1;
            }
            
            // if leftNode is not a leaf, copy the second half child pointer of leftNode to rightNode
            int rightChildIndex = 0;
            if(!leftNode->leaf) {
                for(int i=(degree+1)/2; i<=degree; i++) {
                    rightNode->childptr[rightChildIndex] = leftNode->childptr[i];
                    leftNode->childptr[i] = nullptr;
                    rightChildIndex++;
                }
                rightNode->leaf = false;
            }

            // add rightNode to the correct pointer position in the parent
            int rightNodeIndex = degree-1;
            while(parent->childptr[rightNodeIndex] != leftNode) {
                parent->childptr[rightNodeIndex+1] = parent->childptr[rightNodeIndex];
                rightNodeIndex--;
            }
            parent->childptr[rightNodeIndex+1] = rightNode;

            // add the middle key to the parent
            int j = parent->size;
            int addToParent = leftNode->keys[mid];
            while(j != 0 && parent->keys[j-1] > addToParent) {
                parent->keys[j] = parent->keys[j-1];
                j--;
            }
            parent->keys[j] = addToParent;
            leftNode->keys[mid] = -1;
            parent->size += 1;
            leftNode->size -= 1;
        }

        node* getRoot() {
            return root;
        }

};
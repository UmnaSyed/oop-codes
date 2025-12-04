#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data=val;
        left=right=nullptr;
    }
};

class BST{
    private:
    Node* root;
    Node* inOrderArr[100];
    int index;

    Node* insert(Node* root, int val){
        if (root==nullptr){
            return new Node(val);
        }
        else if (val<root->data){
            root->left=insert(root->left, val);
        }
        else if (val>root->data){
            root->right=insert(root->right, val);
        }
        return root;
    }

    void inOrderStore(Node* root){
        if (root==nullptr){
            return;
        }
        inOrderStore(root->left);
        inOrderArr[index++]=root;
        inOrderStore(root->right);
    }

    Node* balancedBST(int start, int end){
        if (start>end){
            return nullptr;
        }
        int mid = (start+end)/2;
        Node* node = inOrderArr[mid];

        node->left=balancedBST(start, mid-1);
        node->right=balancedBST(mid+1, end);
        return node;
    }

    void inOrderDisplay(Node* root){
        if (root==nullptr){
            return;
        }
        inOrderDisplay(root->left);
        cout<<root->data<<" ";
        inOrderDisplay(root->right);
    }

    public:
    BST(){
        root=nullptr;
        index=0;
    }

    void insertNode(int val){
        root=insert(root, val);
    }

    void inTraversal(){
        cout<<"Inorder Traversal: "<<endl;
        inOrderDisplay(root);
    }

    void balanceTree(){
        index=0;
        inOrderStore(root);
        root=balancedBST(0, index-1);
        cout<<"\nBST balanced!\n";
    }
};

int main() {
    BST tree;

    tree.insertNode(10);
    tree.insertNode(20);
    tree.insertNode(30);
    tree.insertNode(40);
    tree.insertNode(50);

    cout<<"Before Balancing: \n";
    tree.inTraversal();
    tree.balanceTree();
    tree.inTraversal();

    return 0;
}


#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// ---------------- Queue Implementation ----------------
class Queue {
private:
    Node* arr[100];
    int front, rear;

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(Node* val) {
        if (rear == 99) {
            cout << "Queue Overflow\n";
            return;
        }
        if (front == -1)
            front = 0;
        arr[++rear] = val;
    }

    Node* dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return nullptr;
        }
        return arr[front++];
    }
};

// ---------------- BST Implementation ----------------
class BST {
private:
    Node* root;
    Node* inOrderArr[100];
    int index;

    Node* insert(Node* root, int val) {
        if (root == nullptr)
            return new Node(val);
        else if (val < root->data)
            root->left = insert(root->left, val);
        else if (val > root->data)
            root->right = insert(root->right, val);
        return root;
    }

    void inOrderStore(Node* root) {
        if (root == nullptr)
            return;
        inOrderStore(root->left);
        inOrderArr[index++] = root;
        inOrderStore(root->right);
    }

    Node* balancedBST(int start, int end) {
        if (start > end)
            return nullptr;
        int mid = (start + end) / 2;
        Node* node = inOrderArr[mid];

        node->left = balancedBST(start, mid - 1);
        node->right = balancedBST(mid + 1, end);
        return node;
    }

    void inOrderDisplay(Node* root) {
        if (root == nullptr)
            return;
        inOrderDisplay(root->left);
        cout << root->data << " ";
        inOrderDisplay(root->right);
    }

public:
    BST() {
        root = nullptr;
        index = 0;
    }

    void insertNode(int val) {
        root = insert(root, val);
    }

    void inTraversal() {
        cout << "\nInorder Traversal: ";
        inOrderDisplay(root);
        cout << endl;
    }

    void balanceTree() {
        index = 0;
        inOrderStore(root);
        root = balancedBST(0, index - 1);
        cout << "BST balanced successfully!\n";
    }

    // ---------------- Level Order Traversal ----------------
    void levelOrderTraversal() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }

        Queue q;
        q.enqueue(root);
        cout << "Level Order Traversal: ";

        while (!q.isEmpty()) {
            Node* current = q.dequeue();
            cout << current->data << " ";

            if (current->left)
                q.enqueue(current->left);
            if (current->right)
                q.enqueue(current->right);
        }
        cout << endl;
    }
};

// ---------------- Main ----------------
int main() {
    BST tree;

    tree.insertNode(10);
    tree.insertNode(20);
    tree.insertNode(30);
    tree.insertNode(40);
    tree.insertNode(50);

    cout << "Before balancing:";
    tree.inTraversal();

    tree.balanceTree();

    cout << "After balancing:";
    tree.inTraversal();

    tree.levelOrderTraversal();

    return 0;
}

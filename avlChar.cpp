#include <iostream>
using namespace std;

class Node{
    public:
    char ch;
    int freq;
    Node* left;
    Node* right;
    int height;

    Node (char c, int fr){
        ch=c;
        freq=fr;
        left=right=NULL;
        height=1;
    }
};

int getHeight(Node* root){
        if (root==NULL){
            return 0;
        }

        return root->height;
    }

    int getBalanceFactor(Node* root){
        if (root==NULL){
            return 0;
        }

        return getHeight(root->left)-getHeight(root->right);
    }

    int max(int a, int b){
        if (a>b){
            return a;
        }
        return b;
    }

    Node* RightRot(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* LeftRot(Node* y){
        Node* x = y->right;
        Node* T2 = x->left;

        x->left = y;
        y->right = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* insert(Node* root, char c, int f){
        if (root==NULL){
            return new Node (c, f);
        }

        if (f < root->freq){
            root->left = insert(root->left, c, f);
        }
        else {
            root->right = insert(root->right, c, f);
        }
        
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        
        int balance = getBalanceFactor(root);

        if ((balance > 1) && f < root->left->freq){
            return RightRot(root);
        } 

        if ((balance < -1 && f > root->right->freq)){
            return LeftRot(root);
        }

        if ((balance > 1 && f > root->left->freq )){
            root->left = LeftRot(root->left);
            return RightRot(root);
        }

        if ((balance < -1 && f < root->right->freq)){
            root->right = RightRot(root->right);
            return LeftRot(root);
        }

        return root;    
    }

    Node* minVal(Node* root){
        Node* current = root;
        while (current->left!=NULL){
            current=current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, int f){
        if (root==NULL){
            return root;
        }

        if (f < root->freq){
            root->left = deleteNode(root->left, f);
        }
        else if (f > root->freq){
            root->right = deleteNode(root->right, f);
        }
        else {
            if (root->left == NULL || root->right == NULL){
                Node* temp;
                if(root->left){
                    temp = root->left;
                }
                else {
                    temp = root->right;
                }
                
                if (temp==NULL){
                    temp = root;
                    root = NULL;
                }
                else {
                    *root = * temp;
                }

                delete temp;
            }
            else {
               Node* temp = minVal(root->right);
               root->freq = temp->freq;
               root->ch = temp->ch;
               root->right = deleteNode(root->right, temp->freq); 
            }
        }

        if (root == NULL){
            return root;
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left)>=0){
            return RightRot(root);
        }

        if (balance > 1 && getBalanceFactor(root->left) < 0){
            root->left = LeftRot(root->left);
            return RightRot(root);
        }

        if (balance < -1 && getBalanceFactor(root->right)>=0){
            return LeftRot(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) < 0){
            root->right = RightRot(root->right);
            return LeftRot(root);
        }
        return root;
    }

    Node* extractMin(Node* &root, char &outChar, int &outFreq){
        Node* minNode = minVal(root);
        outChar = minNode->ch;
        outFreq = minNode->freq;
        root = deleteNode(root, outFreq);
        return root;
    }

    int computeLoad(Node* root){
        if (root == NULL){
            return 0 ;
        }
        return root->freq * root->freq + computeLoad(root->left) + computeLoad(root->right);
    }

    void fillString(Node* root, char result[], int &pos){
        if (root == NULL){
            return;
        }
        for (int i=0; i< root->freq; i++){
            result[pos++] = root->ch;
        }
        fillString(root->left, result, pos);
        fillString(root->right, result, pos);
    }

int main(){
    char str[1000];
    int k;

    cout << "Enter your stream: ";
    cin >> str;

    cout<< "Enter K (maximum removals): ";
    cin >> k;

    int freq[256];
    for (int i=0; i<256; i++){
        freq[i]=0;
    }

    for (int i=0; str[i]!='\0'; i++){
        char ch = str[i];
        freq[ch]++;
    }

    Node* root = NULL;

    for (int i=0; i<256; i++){
        if (freq[i] > 0){
            root = insert(root, (char)i, freq[i]);
        }
    }

    char removed[1000];
    int removedCount = 0;

    for (int i=0; i<k; i++){
        if(root == NULL){
            break;
        }
        char c;
        int f;
        extractMin(root,c,f);
        removed[removedCount++]=c;

        if (f-1 > 0){
            root = insert(root, c, f-1);
        }
    }

    char result[1000];
    int pos = 0; 
    fillString(root, result, pos);
    result[pos]='\0';

    cout<<"\nCharacters removed: ";
    for (int i=0; i < removedCount; i++){
        cout << removed[i]<< " ";
    }

    cout <<"\nResultant String: "<< result;
    cout<< "\nFinal Load: " << computeLoad(root) << endl;

    return 0;
}

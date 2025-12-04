// Suppose you are working on a program that needs to store a large number of strings, withthepossibility of duplicate strings. You decide to use chain hashing to efficiently store andretrieve the strings, but you want to ensure that collisions are avoided as much as possible. Your hash function simply takes the sum of the ASCII values of the characters in the stringand returns the remainder after dividing by the number of buckets. You decide to implement
// the hash table using a linked list for each bucket. Input and output:
// HashTable myhash;
// [hine: key is A]
// myhash.insert("A","aaaaa");
// myhash.insert("B","bbbbb");
// myhash.insert("C","ccccc");
// myhash.insert("A","zzzzz");

#include <iostream>
using namespace std;

#define maxSize 10

class Node
{
public:
    string key;
    string value;
    Node *next;
};

class hashTable
{
private:
    Node *table[maxSize];

public:
    hashTable()
    {
        for (int i = 0; i < maxSize; i++)
            table[i] = NULL;
    }

    int hashFunction(const string &key)
    {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i];
        return sum % maxSize;
    }

    void insert(const string &key, const string &val)
    {
        int index = hashFunction(key);

        Node *temp = table[index];

        while (temp != NULL)
        {
            if (temp->key == key)
            {
                temp->value = val;
                return;
            }
            temp = temp->next;
        }

        // 2️⃣ Key not found → insert new node at head
        Node *newNode = new Node;
        newNode->key = key;
        newNode->value = val;
        newNode->next = table[index];

        table[index] = newNode;
    }

    void display()
    {
        for (int i = 0; i < maxSize; i++)
        {
            cout << i << ": ";
            Node *temp = table[i];
            while (temp != NULL)
            {
                cout << "(" << temp->key << ", " << temp->value << ") --> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

    ~hashTable()
    {
        for (int i = 0; i < maxSize; i++)
        {
            Node *temp = table[i];
            while (temp)
            {
                Node *toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
    }
};

int main()
{
    hashTable myhash;
    myhash.insert("A", "aaaaa");
    myhash.insert("B", "bbbbb");
    myhash.insert("C", "ccccc");
    myhash.insert("A", "zzzzz"); 
    myhash.display();

    return 0;
}

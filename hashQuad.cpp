// Implement a C++ class StudentHashTable to manage student records in a hash table with a
// size of 15. Use quadratic probing for collision resolution with the formula (index + attempt^2)
// % table size.Implement the function InsertRecord that takes a student's roll number and name,
// inserting the record into the hash table using quadratic probing.Implement the function
// SearchRecord that takes a roll number, searches for the corresponding record using quadratic
// probing, and prints the student's name if found; otherwise, print a "Record not found" message.



#include <iostream>
using namespace std;
#define TABLE_SIZE 15
class StudentHashTable
{
private:
    int rollNumbers[TABLE_SIZE];
    string names[TABLE_SIZE];

public:
    StudentHashTable()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            rollNumbers[i] = -1;
            names[i] = "";
        }
    }
    int hashFunction(int roll)
    {
        return roll % TABLE_SIZE;
    }
    void InsertRecord(int roll, string name)
    {
        int index = hashFunction(roll);
        for (int attempt = 0; attempt < TABLE_SIZE; attempt++)
        {
            int newIndex = (index + attempt * attempt) % TABLE_SIZE;
            if (rollNumbers[newIndex] == -1 || rollNumbers[newIndex] == roll)
            {
                rollNumbers[newIndex] = roll;
                names[newIndex] = name;
                cout << "Inserted: " << roll << " - " << name << endl;
                return;
            }
        }
        cout << "Hash table full. Cannot insert record.\n";
    }
    void SearchRecord(int roll)
    {
        int index = hashFunction(roll);
        for (int attempt = 0; attempt < TABLE_SIZE; attempt++)
        {
            int newIndex = (index + attempt * attempt) % TABLE_SIZE;
            if (rollNumbers[newIndex] == roll)
            {
                cout << "Record Found -> " << roll
                     << " : " << names[newIndex] << endl;
                return;
            }
            if (rollNumbers[newIndex] == -1)
            {
                break;
            }
        }
        cout << "Record not found\n";
    }
    void DisplayTable()
    {
        cout << "\nHash Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (rollNumbers[i] != -1)
                cout << i << " - " << rollNumbers[i]
                     << " : " << names[i] << endl;
            else
                cout << i << " - EMPTY\n";
        }
    }
};
int main()
{
    StudentHashTable ht;
    ht.InsertRecord(101, "Ali");
    ht.InsertRecord(116, "Sana");
    ht.InsertRecord(131, "Zainab");
    ht.InsertRecord(146, "Hassan");
    cout << endl;
    ht.SearchRecord(131);
    ht.SearchRecord(200);
    ht.DisplayTable();
    return 0;
}
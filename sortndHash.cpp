#include <iostream>
#include <string>
using namespace std;

// Student structure
struct Student {
    int id;
    string name;
    float gpa;
    Student* next;  // For chaining in hash table
    
    Student(int i, string n, float g) : id(i), name(n), gpa(g), next(nullptr) {}
};

// Hash Table using separate chaining (manual linked list)
class StudentHashTable {
private:
    static const int SIZE = 10;
    Student* table[SIZE];  // Array of pointers (heads of linked lists)

public:
    // Constructor - initialize all to nullptr
    StudentHashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // Hash function
    int hashFunction(int id) {
        return id % SIZE;
    }

    // Insert student
    void insert(Student* student) {
        int index = hashFunction(student->id);
        
        // Check for duplicate ID
        Student* current = table[index];
        while (current != nullptr) {
            if (current->id == student->id) {
                cout << "Student ID " << student->id << " already exists!\n";
                return;
            }
            current = current->next;
        }
        
        // Insert at the beginning of the chain
        student->next = table[index];
        table[index] = student;
        cout << "Student " << student->name << " (ID: " << student->id 
             << ") inserted at hash index " << index << "\n";
    }

    // Search student by ID
    Student* search(int id) {
        int index = hashFunction(id);
        Student* current = table[index];
        
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Delete student by ID
    bool deleteStudent(int id) {
        int index = hashFunction(id);
        Student* current = table[index];
        Student* prev = nullptr;
        
        while (current != nullptr) {
            if (current->id == id) {
                if (prev == nullptr) {
                    // Deleting first node
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                cout << "Student " << current->name << " (ID: " << id << ") deleted\n";
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // Get all students into an array (for sorting)
    int getAllStudents(Student* arr[], int maxSize) {
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            Student* current = table[i];
            while (current != nullptr && count < maxSize) {
                arr[count++] = current;
                current = current->next;
            }
        }
        return count;
    }

    // Display hash table structure
    void displayHashTable() {
        cout << "\n========== HASH TABLE STRUCTURE ==========\n";
        for (int i = 0; i < SIZE; i++) {
            cout << "Index " << i << ": ";
            if (table[i] == nullptr) {
                cout << "EMPTY";
            } else {
                Student* current = table[i];
                while (current != nullptr) {
                    cout << "[ID:" << current->id << " " << current->name << "] -> ";
                    current = current->next;
                }
                cout << "NULL";
            }
            cout << "\n";
        }
        cout << "==========================================\n\n";
    }

    // Destructor - free all memory
    ~StudentHashTable() {
        for (int i = 0; i < SIZE; i++) {
            Student* current = table[i];
            while (current != nullptr) {
                Student* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

// Quick Sort - Partition function for sorting by ID
int partitionByID(Student* arr[], int low, int high) {
    int pivot = arr[high]->id;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j]->id < pivot) {
            i++;
            Student* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Quick Sort by ID
void quickSortByID(Student* arr[], int low, int high) {
    if (low < high) {
        int pi = partitionByID(arr, low, high);
        quickSortByID(arr, low, pi - 1);
        quickSortByID(arr, pi + 1, high);
    }
}

// Quick Sort - Partition function for sorting by Name
int partitionByName(Student* arr[], int low, int high) {
    string pivot = arr[high]->name;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j]->name < pivot) {
            i++;
            Student* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Quick Sort by Name
void quickSortByName(Student* arr[], int low, int high) {
    if (low < high) {
        int pi = partitionByName(arr, low, high);
        quickSortByName(arr, low, pi - 1);
        quickSortByName(arr, pi + 1, high);
    }
}

// Quick Sort - Partition function for sorting by GPA (descending)
int partitionByGPA(Student* arr[], int low, int high) {
    float pivot = arr[high]->gpa;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j]->gpa > pivot) {  // > for descending order
            i++;
            Student* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Quick Sort by GPA (descending)
void quickSortByGPA(Student* arr[], int low, int high) {
    if (low < high) {
        int pi = partitionByGPA(arr, low, high);
        quickSortByGPA(arr, low, pi - 1);
        quickSortByGPA(arr, pi + 1, high);
    }
}

// Display students array
void displayStudents(Student* arr[], int n, string title) {
    cout << "\n========== " << title << " ==========\n";
    cout << "ID\tName\t\tGPA\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i]->id << "\t" << arr[i]->name << "\t\t" << arr[i]->gpa << "\n";
    }
    cout << "====================================\n\n";
}

// Copy array of pointers
void copyArray(Student* source[], Student* dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main() {
    StudentHashTable hashTable;
    const int MAX_STUDENTS = 100;
    
    // Insert students (O(1) average time with hashing)
    cout << "===== INSERTING STUDENTS =====\n";
    hashTable.insert(new Student(101, "Alice", 3.8));
    hashTable.insert(new Student(205, "Bob", 3.5));
    hashTable.insert(new Student(312, "Charlie", 3.9));
    hashTable.insert(new Student(89, "Diana", 3.7));
    hashTable.insert(new Student(156, "Eve", 3.6));
    hashTable.insert(new Student(223, "Frank", 3.4));
    hashTable.insert(new Student(45, "Grace", 4.0));
    hashTable.insert(new Student(178, "Henry", 3.3));
    
    // Display hash table structure
    hashTable.displayHashTable();
    
    // Search for a student (O(1) average time with hashing)
    cout << "===== SEARCHING STUDENTS =====\n";
    int searchID = 205;
    Student* found = hashTable.search(searchID);
    if (found != nullptr) {
        cout << "Found: " << found->name << " (ID: " << found->id 
             << ", GPA: " << found->gpa << ")\n";
    } else {
        cout << "Student with ID " << searchID << " not found!\n";
    }
    
    searchID = 999;
    found = hashTable.search(searchID);
    if (found != nullptr) {
        cout << "Found: " << found->name << "\n";
    } else {
        cout << "Student with ID " << searchID << " not found!\n";
    }
    cout << "\n";
    
    // Get all students for sorting
    Student* students[MAX_STUDENTS];
    int numStudents = hashTable.getAllStudents(students, MAX_STUDENTS);
    
    // Create temporary arrays for different sorting
    Student* byID[MAX_STUDENTS];
    Student* byName[MAX_STUDENTS];
    Student* byGPA[MAX_STUDENTS];
    
    // Sort by ID using Quick Sort
    copyArray(students, byID, numStudents);
    quickSortByID(byID, 0, numStudents - 1);
    displayStudents(byID, numStudents, "SORTED BY ID (Quick Sort)");
    
    // Sort by Name using Quick Sort
    copyArray(students, byName, numStudents);
    quickSortByName(byName, 0, numStudents - 1);
    displayStudents(byName, numStudents, "SORTED BY NAME (Quick Sort)");
    
    // Sort by GPA (highest first) using Quick Sort
    copyArray(students, byGPA, numStudents);
    quickSortByGPA(byGPA, 0, numStudents - 1);
    displayStudents(byGPA, numStudents, "SORTED BY GPA - Descending (Quick Sort)");
    
    // Delete a student
    cout << "===== DELETING STUDENT =====\n";
    hashTable.deleteStudent(156);
    
    // Display updated hash table
    hashTable.displayHashTable();
    
    // Show updated sorted list
    numStudents = hashTable.getAllStudents(students, MAX_STUDENTS);
    quickSortByID(students, 0, numStudents - 1);
    displayStudents(students, numStudents, "UPDATED LIST (Sorted by ID)");
    
    return 0;
}
// Question 1: Sorting and Searching (CLO: 1)
// 5 points Shaheen Real Estate Agency is one of the authorized dealers of New-Malir housing society. The society contains multiple blocks of houses. Each block contains N houses of equal in size. Shaheen agency got the license to sale the houses of only I block of the society. Luckily all the houses are sold to the N no of different families in a week. Initially at the booking, they were randomly allocating the house from 1 to N. But according to the rules of society, every family allotted a house must have a neighboring family with less no of family members to its left.
// You need to design an algorithm to solve the issue and re-shuffle them according to the rule of the society.

#include <iostream>
using namespace std;

// Merge two halves
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int leftArr[10000], rightArr[10000];

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

// Recursive merge sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int N;
    cout << "Enter number of houses (families): ";
    cin >> N;

    int arr[10000];
    cout << "Enter number of members in each family:\n";
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    mergeSort(arr, 0, N - 1);

    cout << "\nReshuffled arrangement (according to rule):\n";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}

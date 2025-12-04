#include <iostream>
#include <cstring>
using namespace std;

void heapifyDown(char letters[], int freq[], int size, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && freq[left] < freq[smallest])
        smallest = left;

    if (right < size && freq[right] < freq[smallest])
        smallest = right;

    if (smallest != i) {
        int tf = freq[i];
        freq[i] = freq[smallest];
        freq[smallest] = tf;

        char tc = letters[i];
        letters[i] = letters[smallest];
        letters[smallest] = tc;

        heapifyDown(letters, freq, size, smallest);
    }
}

void heapifyUp(char letters[], int freq[], int i) {
    int parent = (i - 1) / 2;

    while (i > 0 && freq[i] < freq[parent]) {
        int tf = freq[i];
        freq[i] = freq[parent];
        freq[parent] = tf;

        char tc = letters[i];
        letters[i] = letters[parent];
        letters[parent] = tc;

        i = parent;
        parent = (i - 1) / 2;
    }
}

int main() {
    char str[1000];
    int K;

    cout << "Enter data stream: ";
    cin >> str;

    cout << "Enter K (removals): ";
    cin >> K;

    int count[256];
    for (int i = 0; i < 256; i++){
        count[i] = 0;
    }

    for (int i = 0; str[i] != '\0'; i++){
        count[(int)str[i]]++;
    }

    char letters[256];
    int freq[256];
    int size = 0;

    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            letters[size] = (char)i;
            freq[size] = count[i];
            heapifyUp(letters, freq, size);
            size++;
        }
    }

    char removed[1000];
    int removedCount = 0;

    for (int i = 0; i < K; i++) {
        if (size == 0) break;

        char ch = letters[0];
        removed[removedCount++] = ch;

        freq[0]--;  

        if (freq[0] == 0) {
            letters[0] = letters[size-1];
            freq[0] = freq[size-1];
            size--;
        }

        heapifyDown(letters, freq, size, 0);
    }

    memset(count, 0, sizeof(count));

    for (int i = 0; i < size; i++)
        count[(int)letters[i]] = freq[i];

    char result[1000];
    int pos = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (count[(int)str[i]] > 0) {
            result[pos++] = str[i];
            count[(int)str[i]]--;
        }
    }
    result[pos] = '\0';

    int load = 0;
    for (int i = 0; i < size; i++)
        load += freq[i] * freq[i];

    cout << "\nCharacters removed: ";
    for (int i = 0; i < removedCount; i++)
        cout << removed[i] << " ";

    cout << "\nResultant string: " << result;
    cout << "\nFinal Load: " << load << endl;

    return 0;
}

// Task # 5
// Given an array of distinct integers, find using hashing if there are two pairs (a, b) and (c, d)
// such that
// a+b = c+d, and a, b, c, and d are distinct elements. If there are multiple answers, then print any
// of
// them.
// Input: {3, 4, 7, 1, 2, 9, 8}
// Output: (3, 8) and (4, 7)
// Explanation: 3+8 = 4+7
// Input: {3, 4, 7, 1, 12, 9};
// Output: (4, 12) and (7, 9)
// Explanation: 4+12 = 7+9
// Input: {65, 30, 7, 90, 1, 9, 8};
// Output: No pairs found

#include <iostream>
using namespace std;
#define maxSize 100
struct PairStore
{
    int a;
    int b;
    bool used;
};
int hashFunction(int sum)
{
    return sum % maxSize;
}
int main()
{
    int arr[] = {3, 4, 7, 1, 2, 9, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    PairStore hashTable[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        hashTable[i].used = false;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int sum = arr[i] + arr[j];
            int index = hashFunction(sum);
            for (int k = 0; k < maxSize; k++)
            {
                int newIndex = (index + k) % maxSize;
                if (hashTable[newIndex].used &&
                    hashTable[newIndex].a + hashTable[newIndex].b == sum)
                {
                    int x = hashTable[newIndex].a;
                    int y = hashTable[newIndex].b;
                    if (x != arr[i] && x != arr[j] &&
                        y != arr[i] && y != arr[j])
                    {

                        cout << "(" << x << ", " << y << ") and ("
                             << arr[i] << ", " << arr[j] << ")" << endl;
                        return 0;
                    }
                }
                if (!hashTable[newIndex].used)
                {
                    hashTable[newIndex].a = arr[i];
                    hashTable[newIndex].b = arr[j];
                    hashTable[newIndex].used = true;
                    break;
                }
            }
        }
    }
    cout << "No pairs found" << endl;
    return 0;
}
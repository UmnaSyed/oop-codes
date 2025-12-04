#include <iostream>
#include <string>
using namespace std;
int bruteForceSearch(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
        {
            j++;
        }
        if (j == m)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    string text = "umnzsambeervanzqraseelaumnzsambeervanzqraseela";
    string patt1 = "qraseela";
    string patt2 = "hello12345";
    int index = bruteForceSearch(text, patt1);
    if (index != -1)
    {
        cout << "First occurrence found at index " << index << endl;
    }
    else
    {
        cout << "Pattern not found." << endl;
    }

    int index2 = bruteForceSearch(text, patt2);
    if (index2 != -1)
    {
        cout << "First occurrence found at index " << index << endl;
    }
    else
    {
        cout << "Pattern not found." << endl;
    }
    return 0;
}
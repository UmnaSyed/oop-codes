#include <iostream>
#include <string>
using namespace std;
#define NO_OF_CHARS 256
void badCharTable(string pattern, int badChar[])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
        badChar[i] = -1;
    for (int i = 0; i < pattern.length(); i++)
        badChar[(unsigned char)pattern[i]] = i;
}
void boyerMooreSearch(string text, string pattern)
{
    int m = pattern.length();
    int n = text.length();
    if (m > n)
    {
        cout << "Pattern longer than text.\n";
        return;
    }
    int badChar[NO_OF_CHARS];
    badCharTable(pattern, badChar);
    int shift = 0;
    while (shift <= (n - m))
    {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;
        if (j < 0)
        {
            cout << "Pattern found at index " << shift << endl;
            shift += (shift + m < n) ? m - badChar[(unsigned char)text[shift + m]] : 1;
        }
        else
        {
            shift += max(1, j - badChar[(unsigned char)text[shift + j]]);
        }
    }
}
int main()
{
    string log = "Server started... Error: Disk full ... restarting ... Error: Disk full again!";
    string pattern = "Error: Disk full";
    string log2 = "hello world";
    string pattern2 = "0909";

    boyerMooreSearch(log, pattern);
    return 0;
}
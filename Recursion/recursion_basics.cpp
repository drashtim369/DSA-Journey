#include <bits/stdc++.h>
using namespace std;

// print name
void printname(string s, int i, int n) {
    if (i > n) return;
    cout << s << endl;
    printname(s, i+1, n);
}

// 1 -> n
void OnetoN(int i, int n) {
    if (i > n) return;
    cout << i << endl;
    OnetoN(i+1, n);
}

// n -> 1
void NtoOne(int i) {
    if (i < 1) return;
    cout << i << endl;
    NtoOne(i-1);
}

// 1 -> n [Backtrack]
void OnetoNBacktrack(int i) {
    if (i < 1) return;
    OnetoNBacktrack(i-1);
    cout << i << endl;
}

// n -> 1 [Backtrack]
void NtoOneBacktrack(int i, int n) {
    if (i > n) return;
    NtoOneBacktrack(i+1, n);
    cout << i << endl;
}

// Sum of n numbers (return value instead of printing inside)
int sumtillN(int N) {
    if (N == 0) return 0;
    return N + sumtillN(N-1);
}

// palindrome check
bool palin(string s, int i, int n) {
    if (i >= n/2) return true;              // base case
    if (s[i] != s[n-i-1]) return false;     // mismatch found
    return palin(s, i+1, n);                // check next
}

int main() {
    cout << "Print name: " << endl;
    printname("Drashti", 1, 5);

    cout << "1 -> N: " << endl;
    OnetoN(1,5);

    cout << "1 -> N [Backtrack]: " << endl;
    OnetoNBacktrack(5);

    cout << "N -> 1: " << endl;
    NtoOne(5);

    cout << "N -> 1 [Backtrack]: " << endl;
    NtoOneBacktrack(1,5);

    cout << "Sum till N numbers: " << endl;
    cout << sumtillN(5) << endl;   // prints 15

    cout << "Is palindrome: " << endl;
    cout << (palin("naman", 0, 5) ? "Yes" : "No") << endl; // prints Yes
}

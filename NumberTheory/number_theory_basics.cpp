#include <bits/stdc++.h>
using namespace std;

void countdigits(int n) {
    int count = 0;
    while (n != 0) {
        int d = n % 10;
        count++;
        n = n / 10;
    }
    cout << "Count: " << count << endl;
}

void reversedigits(int n) {
    int sum = 0;
    while (n != 0) {
        int d = n % 10;
        sum = (sum * 10) + d;
        n = n / 10;
    }
    cout << "Reversed num: " << sum << endl;
}

void checkpalindrome(int n) {
    int sum = 0;
    int m = n;
    while (n != 0) {
        int d = n % 10;
        sum = (sum * 10) + d;
        n = n / 10;
    }
    if (sum == m) {
        cout << "Palindrome." << endl;
    } else cout << "Not a palindrome." << endl;
}

void armstrongnumber(int n) {
    int sum = 0;
    int m = n;
    while (n != 0) {
        int d = n % 10;
        sum = sum + pow(d,3);
        n = n / 10;
    }
    if (sum == m) {
        cout << "Armstrong number." << endl;
    } else cout << "Not an armstrong number." << endl;
}

void printdivisors(int n) {
    vector<int> ls;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ls.emplace_back(i);
            if ((n / i) != i) {
                ls.emplace_back(n/i);
            } 
        }
    }
    sort(ls.begin(),ls.end());
    for (auto val : ls) cout << val << " "; cout << endl;
}

void checkprime(int n) {
    int count = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            count++;
            if ((n / i) != i) {
                count++;
            } 
        }
    }
    if (count == 2) {
        cout << "Prime." << endl;
    } else cout << "Not prime." << endl;
}

void gcd(int a, int b) {
    //Euclidian Algorithm GCD(a,b) = GCD(a%b,b) provided a > b
    while (a > 0 && b > 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    if (a == 0) cout << b << endl;
    else cout << a << endl;
}

int main()
{
    countdigits(123456);
    checkpalindrome(242);
    checkpalindrome(241);
    reversedigits(192);
    armstrongnumber(371);
    armstrongnumber(171);
    printdivisors(36);
    checkprime(13);
    checkprime(18);
    checkprime(1);
    gcd(13,11);
    gcd(52,2);
    return 0;
}
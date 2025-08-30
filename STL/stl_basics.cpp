#include <bits/stdc++.h>
using namespace std;

// 1) Pair
void explainPair() {
    // Simple Pair
    pair<int, int> p = {1, 3};
    cout << p.first << " " << p.second << endl;

    // Nested Pair
    pair<int, pair<int, int>> nested = {1, {3, 4}};
    cout << nested.first << " " << nested.second.second << " " << nested.second.first << endl;

    // Array of Pairs
    pair<int, int> arr[] = {{1, 2}, {2, 5}, {5, 1}};
    cout << arr[1].second << endl;
}

// 2) Vector
void explainVector() {
    // Basic Vector
    vector<int> v;
    v.push_back(1);
    v.emplace_back(2);

    // Vector with pairs
    vector<pair<int, int>> vec;
    vec.push_back({1, 2});
    vec.emplace_back(3, 4);

    // Vector with fixed size and value
    vector<int> v1(5, 100); // {100, 100, 100, 100, 100}

    // Copy vector
    vector<int> v2(v1);

    // Iterating using iterators
    vector<int>::iterator it = v1.begin();
    cout << *(it) << endl; // prints 100

    for (auto it = v1.begin(); it != v1.end(); it++) {
        cout << *(it) << " ";
    } cout << endl;

    // Range-based loop
    for (auto val : v1) cout << val << " ";
    cout << endl;

    // Erase
    v1.erase(v1.begin());

    // Insert
    v1.insert(v1.begin(), 300);
    v1.insert(v1.begin() + 1, 2, 10); // Inserts 10, 10 before index 1

    //Copy
    vector<int> copy(2,50);
    v1.insert(v1.begin(), copy.begin(), copy.end());
    // Size
    cout << "Size: " << v1.size() << endl;

    // Pop -> pops the last element
    v1.pop_back();

    // Swap
    v1.swap(v2);

    // Clear
    v1.clear();

    // Empty -> 1 (True) if Empty, 0 (False) if not
    v1.empty()
}

// 3) List
void explainList() {
    list<int> ls;

    ls.push_back(2);
    ls.emplace_back(4);
    ls.push_front(1);
    ls.emplace_front(0);

    for (auto val : ls) cout << val << " ";
    cout << endl;
    
    //rest functions are same as vector
}

// 4) Deque
void explainDeque() {
    deque<int> dq;
    dq.push_back(1);
    dq.emplace_back(2);
    dq.push_front(4);
    dq.emplace_front(3);

    dq.pop_back();
    dq.pop_front();

    cout << dq.front() << " " << dq.back() << endl;

    //rest functions same as vector
}

// 5) Stack
void explainStack() {
    stack<int> st;
    st.push(1); //{1}
    st.push(2); //{2,1}
    st.emplace(3); //{3,2,1}

    cout << st.top() << endl; // prints 3
    st.pop();
    cout << st.top() << endl; // prints 2

    cout << "Size: " << st.size() << endl;
    st.empty();

    stack<int> st1,st2;
    st1.swap(st2);
}

// 6) Queue
void explainQueue() {
    queue<int> q;
    q.push(1); // {1}
    q.push(2); // {1,2}
    q.emplace(3); //{1,2,3}

    cout << q.front() << endl; // 1
    q.pop();
    cout << q.front() << endl; // 2

    cout << "Size: " << q.size() << endl;

    //rest functions same as stack

}

// 7) Priority Queue (Max & Min Heap)
void explainPriorityQueue() {
    // Max Heap
    priority_queue<int> pq;
    pq.push(5); //{5}
    pq.push(2); //{5,2}
    pq.push(8); //{8,5,2}
    pq.emplace(10); //{10,8,5,2}

    cout << pq.top() << endl; // 10
    pq.pop();
    cout << pq.top() << endl; // 8

    // Min Heap
    priority_queue<int, vector<int>, greater<int>> mpq;
    mpq.push(5); //{5}
    mpq.push(2); //{2,5}
    mpq.push(8); //{2,5,8}
    mpq.emplace(10); //{2,5,8,10}

    cout << mpq.top() << endl; // 2
    mpq.pop();
    cout << mpq.top() << endl; // 5
}

// 8) Set -> Sorted + Unique
void explainSet() {
    set<int> st;
    st.insert(1);
    st.emplace(2);
    st.insert(2);
    st.insert(4);
    st.insert(3);

    for (auto it : st) cout << it << " "; 
    cout << endl; // {1,2,3,4}

    auto it = st.find(3); // returns iterator
    if (it != st.end()) cout << "Found: " << *it << endl;
    st.erase(it); // Erases 3 (takes constant time)

    // {1,2,3}
    st.erase(2); //Erases 2 (takes logarithmic time)

    // {1,2,3,4,5}
    auto it1 = st.find(2);
    auto it2 = st.find(4);
    st.erase(it1,it2); // After erase [Start,End) -> {1,4,5} 

    // {1,2,3,4,5}
    auto it2 = st.lower_bound(2); //2
    auto it3 = st.upper_bound(3); //4

    /* Lower Bound / Upper Bound Concept -> 
    To do binary search using c++ stl for competitive programming
    Q1) Check if X exists in sorted array or not
    arr[] = {1,2,4,5,6}; a -> Iterator points to start position a.being(), a+n -> Iterator points to end position a.end()
    bool res = binary_search(a,a+n,3) -> returns false 
    bool res = binary_search(a,a+n,6) -> returns true

    LOWER BOUND ->
    a[] = {1,4,5,6,9,9}
    int ind = lower_bound(a.begin(),a.end(),4) - a.begin(); Returns index 1 
    int ind = lower_bound(a.begin(),a.end(),7) - a.begin(); Returns index 4
    int ind = lower_bound(a.begin(),a.end(),10) - a.begin(); Returns index 6 aka one after arr.length() or a.end()

    UPPER BOUND -> (log n)
    a[] = {1,4,5,6,9,9} 
    int ind = upper_bound(a.begin(),a.end(),4) - a.begin(); Returns index 2 (aka next greater element than 4) 
    int ind = upper_bound(a.begin(),a.end(),7) - a.begin(); Returns index 4 
    int ind = upper_bound(a.begin(),a.end(),10) - a.begin(); Returns index 6 aka one after arr.length() or a.end()
    
    Q) Find 1st Occurence of X in an sorted array. If not present than print -1
    a[] = {1,4,4,4,4,9,9,10,11}; //NOTE: This is an array so .being .end doesnt work. Use vectors!!!
    -> int ind = lower_bound(a.begin(), a.end(), X) - a.begin();
    if (ind != a.end() && a[ind] == X) cout << ind; else cout << -1;
    
    Q) Find last Occurence of X in an sorted array. If not present than print -1
    a[] = {1,4,4,4,4,9,9,10,11}; //NOTE: This is an array so .being .end doesnt work. Use vectors!!!
    -> int ind = upper_bound(a.begin(), a.end(), X) - a.begin();
    ind--;
    if ((ind) >= 0 && a[ind] == X) cout << ind; else cout << -1;

    Q) Find the largest element smaller than X in an sorted array. If no number exists print -1
    a[] = {1,4,4,4,4,9,9,10,11};
    -> int ind = lower_bound(a.begin(), a.end(), X) - a.begin();
    ind--;
    if ((ind >= 0)) cout << a[ind]; else cout << -1;

    Q) Find the smallest element greater than X in an sorted array. If no number exists print -1
    a[] = {1,4,4,4,4,9,9,10,11};
    -> int ind = upper_bound(a.begin(), a.end(), X) - a.begin();
    if ((ind != a.end()) cout << a[ind]; else cout << -1;
    */ 
}

// 9) MultiSet -> Sorted + NOT Unique
void explainMultiSet() {
    multiset<int> ms;
    ms.insert(1);
    ms.insert(1);
    ms.insert(1);

    ms.erase(1); // Erases all 1s
    ms.insert(1);
    ms.insert(1);
    ms.insert(1);
    ms.erase(ms.find(1)); // Erases only one 1
    ms.erase(ms.find(1),ms.find(1)+2);

    for (auto val : ms) cout << val << " ";
    cout << endl;
}

// 10) Unordered Set -> Unique + Not sorted
void explainUnorderedSet() {
    unordered_set<int> st;
    // lower and upper bound doesn't work, rest all fnc same 
    // Time complexity in most case -> O(1)
    // Worst case (rare) -> O(n)
}

// 11) Map -> Same as dictionary or object
void explainMap() {

}

int main() {
    cout << "C++ STL -> (Containers, Iterators, Algorithms, Functions)" << endl;

    cout << "\n1) Pairs ->" << endl;
    explainPair();

    cout << "\n2) Vectors ->" << endl;
    explainVector();

    cout << "\n3) List ->" << endl;
    explainList();

    cout << "\n4) Deque ->" << endl;
    explainDeque();

    cout << "\n5) Stack ->" << endl;
    explainStack();

    cout << "\n6) Queue ->" << endl;
    explainQueue();

    cout << "\n7) Priority Queue ->" << endl;
    explainPriorityQueue();

    cout << "\n8) Set (Sorted + Unique) ->" << endl;
    explainSet();

    cout << "\n9) Multiset (Sorted + NOT Unique) ->" << endl;
    explainMultiset();

    return 0;
}

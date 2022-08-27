#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <memory>
#include <initializer_list>
#include <iomanip>
#include <stack>
#include <bitset>
#include <cstdio>

 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
const ll INF = 1e9;

int n, m, k;
vector<set<int>> g;

bool kek(set<int>& c) { //lol
    if (c.size() > k) {
        return false;
    }
 
    int i = 0;
    vector<int> ad;
    while (i < n) {
        if (g[i].size() == 0 || c.find(i) != c.end()) {
            ++i;
            continue;
        }
        for (auto j : g[i]) {
            if (c.find(j) == c.end()) {
                ad.push_back(j);
            }
        }
        if (ad.size() > 0)
            break;
        ++i;
    }
 
    if (i == n)
        return true;
 
    for (auto j : ad)
        c.insert(j);
    auto res = kek(c);
    if (res)
        return true;
    
    for (auto v : ad)
        c.erase(v);
    
    c.insert(i);
    res = kek(c);
    if (res)
        return true;
    c.erase(i);
    return false;
}
 
void solve() {
    cin >> n >> m >> k;
    
    if (k > n) {
        cout << "No\n";
        return;
    }

    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, d;
        cin >> a >> d;
        --a;
        --d;
        g[a].insert(d);
        g[d].insert(a);
    }
    
    set<int> c;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() == 1) {
            int v = *g[i].begin();
            c.insert(v);
            for (int x : g[v]) {
                g[x].erase(v);
            }
            g[v].clear();
        }
        if (g[i].size() > k) {
            c.insert(i);
            g[i].clear();
            for (int j = 0; j < n; ++j)
                g[j].erase(i);
        }
    }
    
    
    bool res = kek(c);
    if (!res) {
        cout << "No";
        return;
    }

    cout << "Yes\n";
    for (int i = 0; c.size() < k; ++i) {
        c.insert(i);
    }
    for (auto x : c) {
        cout << x + 1 << " ";
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
    solve();
    return 0;
}


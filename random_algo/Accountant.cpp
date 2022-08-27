#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;

vector<ll> a, t;

void build_tree (int v, int tl, int tr) {
    if (tl == tr) t[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build_tree(v * 2, tl, tm);
        build_tree(v * 2 + 1, tm + 1, tr);
        t[v] = -1;
    }
}

void update (int v, int tl, int tr, int l, int r, ll x) {
    if (l > r) return;
    if (l == tl && tr == r)
        t[v] = x;
    else {
        if (t[v] != -1) {
            t[v * 2] = t[v];
            t[v * 2 + 1] = t[v];
            t[v] = -1;
        }
        int tm = (tl + tr) / 2;
        update (v * 2, tl, tm, l, min(r, tm), x);
        update (v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
    }
}

int current;
bool is_nondecreasing(int v, int tl, int tr, int l, int r) {
    if (l == r) return true;
    if (tl > r || tr < l) return true;
    if (t[v] != -1) {
        if (current > t[v]) return false;
        if (tl <= l && tr >= r) return true;
        current = t[v];
    } else {
        int tm = (tl + tr) / 2;
        bool left = is_nondecreasing(2 * v, tl, tm, l, r);
        if (!left) return false;
        bool right = is_nondecreasing(2 * v + 1, tm + 1, tr, l, r);
        if (!right) return false;
    }
    return true;
}

int main() {
    int n, q;
    cin >> n >> q;
    a.resize(n + 1);
    t.resize(4 * n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build_tree(1, 1, n);

    while (q--) {
        int qq;
        cin >> qq;
        if (qq == 2) {
            int l, r;
            cin >> l >> r;
            current = -1;
            if (is_nondecreasing(1, 1, n, l, r)) cout << "Yes" << endl;
            else cout << "No" << endl;
        } else {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            update(1, 1, n, l, r, x);
        }
    }
 
}
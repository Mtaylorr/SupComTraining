// Mtaylor
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;
 
template <typename T>
struct FenwickTree {
    vector<T> tree;
    T default_value;
    int n;
 
    T mrg(T x, T y) {
        return (x + y);
    }
 
    void init(int _n, T _default_value = 0) {
        // make sure to assign correct default value
        n = _n;
        default_value = _default_value;
        tree.assign(n + 1, default_value);
    }
 
    void upd(int x, T v) {
        for (; x <= n; x += x & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
 
    T getPrefix(int x) {
        if (x <= 0) return default_value;
        T res = default_value;
        for (; x; x -= x & (-x)) {
            res = mrg(res, tree[x]);
        }
        return res;
    }
 
    T getRange(int l, int r) {
        return getPrefix(r) - getPrefix(l - 1);
    }
};
FenwickTree<int> ft;
int n;
int a[N];
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += ft.getPrefix(a[i]);
        ft.upd(a[i], 1);
    }
    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        ft.upd(a[i], -1);
    }
}
 
int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    ft.init(1e7);
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
 

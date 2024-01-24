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
struct FenwickTreeBS {
    vector<T> tree;
    T default_value;
    int n;
    int lg;

    T mrg(T x, T y) {
        return (x + y);
    }

    void init(int _n, T _default_value = 0) {
        // make sure to assign correct default value
        lg = __lg(_n) + 1;
        n = 1 << lg;
        default_value = _default_value;
        tree.assign(n + 1, default_value);
    }

    int getKth(int k) {
        int cur = n;
        if (k > getPrefix(n) || k <= 0) {
            return -1;
        }
        for (int bit = lg - 1; bit >= 0; bit--) {
            T s = tree[cur - (1 << bit)];
            if (s >= k) {
                cur -= (1 << bit);
            } else {
                k -= s;
            }
        }
        return cur;
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
FenwickTreeBS<int> ft;

template <typename T>
struct OrderedMultiSetFT {
    //  1 based values !!
    FenwickTreeBS<T> ft;
    int n;
    void init(int _n) {
        n = _n;
        ft.init(n);
    }

    int count(int x) {
        return ft.getRange(x, x);
    }

    void insert(int x) {
        ft.upd(x, 1);
    }
    void erase(int x) {
        ft.upd(x, -1);
    }

    int getKth(int k) {
        return ft.getKth(k);
    }

    int countSmaller(int x) {
        return ft.getPrefix(x);
    }

    T size() {
        return ft.getPrefix(n);
    }
    void clear() {
        int s = size();
        while (s--) {
            erase(getKth(1));
        }
    }
};

OrderedMultiSetFT<int> mst;

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    int greaterThanOrEqual(ll x) {
        return (lower_bound(all(values), x) - values.begin());
    }
    ll decompress(int p) { return values[p]; }
} compressor;

int n;
char c[N];
int v[N];
void test_case() {
    cin >> n;
    compressor.init();
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> v[i];
        if (c[i] == 'I' || c[i] == 'D') {
            compressor.add(v[i]);
        } else if (c[i] == 'C') {
            compressor.add(v[i] - 1);
        }
    }
    compressor.run();
    mst.init(compressor.n);
    for (int i = 0; i < n; i++) {
        switch (c[i]) {
            case 'I':
                v[i] = compressor.compress(v[i]) + 1;
                if (!mst.count(v[i])) {
                    mst.insert(v[i]);
                }
                break;
            case 'D':
                v[i] = compressor.compress(v[i]) + 1;
                if (mst.count(v[i])) {
                    mst.erase(v[i]);
                }
                break;
            case 'K': {
                int rs = mst.getKth(v[i]);
                if (rs == -1) {
                    cout << "invalid\n";
                } else {
                    cout << compressor.decompress(rs-1) << "\n";
                }
                break;
            }
            case 'C':
                v[i] = compressor.compress(v[i] - 1) + 1;
                cout << mst.countSmaller(v[i]) << endl;
                break;
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}

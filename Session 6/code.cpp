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

const int MAXSPTN = N;
const int MAXSPTL = 20;
template <typename T>
struct SparseTable {
    int spt[MAXSPTL][MAXSPTN];
    int lg[MAXSPTN];
    T mrg(T l, T r) {
        return l + r;
    }
    void init(vector<T> &a) {
        int n = a.size();
        lg[0] = -1;
        for (int i = 1; i <= n; i++) {
            lg[i] = 1 + lg[i / 2];
        }
        for (int i = 0; i < n; i++) {
            spt[0][i] = a[i];
        }
        for (int b = 1; b < MAXSPTL; b++) {
            for (int i = 0; i + (1 << b) <= n; i++) {
                spt[b][i] = mrg(spt[b - 1][i], spt[b - 1][i + (1 << (b - 1))]);
            }
        }
    }
    T query(int l, int r) {
        int sz = (r - l + 1);
        // make sure to update default value
        T res = 0;
        while (sz) {
            res = mrg(res, spt[lg[sz]][l]);
            l += 1 << lg[sz];
            sz = r - l + 1;
        }
        return res;
    }

    int getFirstOnCondition(int l, int k) {
        // without cumulative
        if (spt[0][l] < k) return -1;
        for (int b = MAXSPTL - 1; b >= 0; b--) {
            if (l + (1 << b) > n) continue;
            if (spt[b][l] >= k) {
                l += (1 << b);
            }
        }
        return l - 1;
    }

    int getFirstOnCondition(int l, int k) {
        // with cumulative !!  sum
        if (spt[0][l] > k) return -1;
        for (int b = MAXSPTL - 1; b >= 0; b--) {
            if (l + (1 << b) > n) continue;
            if (spt[b][l] <= k) {
                k -= spt[b][l];
                l += (1 << b);
            }
        }
        return l - 1;
    }

    T query2(int l, int r) {
        // with intersction O(1)
        int sz = (r - l + 1);
        int _lg = lg[sz];
        return mrg(spt[_lg][l], spt[_lg][r - (1 << _lg) + 1]);
    }
};
SparseTable<int> spt;
/// given l : find the first maximum r such that sum(l...r) <= k

int n = 10;
vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
void test_case() {
    spt.init(a);
    cout << spt.query(2, 7) << endl;
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

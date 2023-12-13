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

//  given Q queries in this format:
//  L, R , K , print the index of the first element in the range [L,R] that is >= K
// 3 2 6 8 2 1, k = 5, (L+2)

long long tree[4 * N];
int a[N];
int n;

long long default_value = 0;

int mrg(int vl, int vr) {
    return max(vl, vr);
}
void pull_up(int id) {
    tree[id] = mrg(tree[2 * id + 1], tree[2 * id + 2]);
}
void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id] = a[ns];
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;  //(ns+ne)/2;
    build(l, ns, md);
    build(r, md + 1, ne);
    pull_up(id);
}

// range query , point update

void updPosition(int p, int v, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id] = v;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    if (p <= md) {
        updPosition(p, v, l, ns, md);
    } else {
        updPosition(p, v, r, md + 1, ne);
    }
    pull_up(id);
}

long long getRange(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    if (qs > ne || qe < ns) return default_value;
    if (qs <= ns && qe >= ne) return tree[id];
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return mrg(getRange(qs, qe, l, ns, md), getRange(qs, qe, r, md + 1, ne));
}

int getFirstOnCondition(int qs, int qe, int k, int id = 0, int ns = 0, int ne = n - 1) {
    // log(n)
    if (qs > ne || qe < ns) return -1;
    if (tree[id] < k) return -1;
    if (ns == ne) return ns;
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    int p = getFirstOnCondition(qs, qe, k, l, ns, md);
    if (p == -1) p = getFirstOnCondition(qs, qe, k, r, md + 1, ne);
    return p;
}
int getLastOnCondition(int qs, int qe, int k, int id = 0, int ns = 0, int ne = n - 1) {
    // log(n)
    if (qs > ne || qe < ns) return -1;
    if (tree[id] < k) return -1;
    if (ns == ne) return ns;
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    int p = getFirstOnCondition(qs, qe, k, r, md + 1, ne);
    if (p == -1) p = getFirstOnCondition(qs, qe, k, l, ns, md);
    return p;
}

int solve(int qs, int qe, int k) {
    // log(n)*log(n)
    if (getRange(qs, qe) < k) return -1;
    int lb = qs;
    int ub = qe;
    while (lb < ub) {
        int md = (lb + ub) / 2;
        if (getRange(qs, md) >= k) {
            ub = md;
        } else {
            lb = md + 1;
        }
    }
    return lb;
}

void test_case() {
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}

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

long long tree[4 * N];
int a[N];
int n;

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
    tree[id] = 0;
}

// point query , range update !! be careful

long long getPosition(int p, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        return tree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    if (p <= md) {
        return tree[id] + getPosition(p, l, ns, md);
    } else {
        return tree[id] + getPosition(p, r, md + 1, ne);
    }
}

void updateRange(int qs, int qe, int v, int id = 0, int ns = 0, int ne = n - 1) {
    if (qs > ne || qe < ns) {
        return;
    }
    if (qs <= ns && qe >= ne) {
        return tree[id] += v;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    updateRange(qs, qe, v, l, ns, md);
    updateRange(qs, qe, v, r, md + 1, ne);
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

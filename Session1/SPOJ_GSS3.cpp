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

struct Node {
    ll ans, suff, pref, sm;
    Node() {
        ans = -1e9;
        suff = -1e9;
        pref = -1e9;
        sm = 0;
    }
    Node(ll _ans, ll _suff, ll _pref, ll _sm) : ans(_ans), suff(_suff), pref(_pref), sm(_sm) {
    }
};

Node tree[4 * N];
int a[N];
int n;

Node mrg(Node& vl, Node& vr) {
    ll ans = max(vl.ans, vr.ans);
    ll sm = vl.sm + vr.sm;
    ans = max(ans, vl.suff + vr.pref);
    ll suff = max(vr.suff, vr.sm + vl.suff);
    ll pref = max(vl.pref, vl.sm + vr.pref);
    return Node(ans, suff, pref, sm);
}
void pull_up(int id) {
    tree[id] = mrg(tree[2 * id + 1], tree[2 * id + 2]);
}
void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id] = Node(a[ns], a[ns], a[ns], a[ns]);
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
        tree[id] = Node(v, v, v, v);
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

Node getRange(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    if (qs > ne || qe < ns) return Node();
    if (qs <= ns && qe >= ne) return tree[id];
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    Node vl = getRange(qs, qe, l, ns, md);
    Node vr = getRange(qs, qe, r, md + 1, ne);
    return mrg(vl, vr);
}
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build();
    int q;
    cin >> q;
    while (q--) {
        int ty, x, y;
        cin >> ty >> x >> y;
        if (ty == 0) {
            x--;
            updPosition(x, y);
        } else {
            cout << getRange(--x, --y).ans << endl;
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

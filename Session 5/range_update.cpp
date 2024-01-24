template <typename T>
struct FenwickTree {
    vector<T> tree;
    T default_value;
    int n;

    T mrg(T x, T y) { return (x + y); }

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

    T getRange(int l, int r) { return getPrefix(r) - getPrefix(l - 1); }
};
FenwickTree<int> ft;

template <typename T>
struct RangeFenwickTree {
    FenwickTree<T> ft0, ft1;
    void init(int n) {
        ft0.init(n + 1);
        ft1.init(n + 1);
    }
    void upd(int l, int r, T v) {
        ft0.upd(l, v);
        ft0.upb(r + 1, -v);
        ft1.upd(l, -(l - 1) * v);
        ft1.upb(r + 1, r * v);
    }

    T getPrefix(int p) { return p * ft0.getPrefix(p) + ft1.getPrefix(p); }

    T getRange(int l, int r) { return getPrefix(r) - getPrefix(l - 1); }
};

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<long long> tree;
    int n;

    // Build the segment tree
    void build(int node, int start, int end, const vector<int>& arr) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid, arr);
        build(2 * node + 2, mid + 1, end, arr);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Range query [l, r]
    long long query(int node, int start, int end, int l, int r) {
        // Completely outside
        if (r < start || end < l) return 0;

        // Completely inside
        if (l <= start && end <= r) return tree[node];

        // Partial overlap
        int mid = (start + end) / 2;
        long long left = query(2 * node + 1, start, mid, l, r);
        long long right = query(2 * node + 2, mid + 1, end, l, r);

        return left + right;
    }

    // Point update: arr[idx] = val
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node + 1, start, mid, idx, val);
        else
            update(2 * node + 2, mid + 1, end, idx, val);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, arr);
    }

    // Public APIs
    long long rangeQuery(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    void pointUpdate(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    cout << st.rangeQuery(1, 3) << endl; // 3 + 5 + 7 = 15

    st.pointUpdate(1, 10); // arr[1] = 10

    cout << st.rangeQuery(1, 3) << endl; // 10 + 5 + 7 = 22
}

#include <bits/stdc++.h>
using namespace std;

class LazySegmentTree {
private:
    int n;
    vector<long long> tree;   
    vector<long long> lazy;   

    void build(int node, int start, int end, const vector<long long>& arr) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid, arr);
        build(2 * node + 2, mid + 1, end, arr);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Push lazy value to children
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            // Apply pending update to current node
            tree[node] += (end - start + 1) * lazy[node];

            if (start != end) {
                // Propagate to children
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }

            lazy[node] = 0;
        }
    }

    // Range update: add val to [l, r]
    void update(int node, int start, int end, int l, int r, long long val) {
        push(node, start, end);

        // Completely outside
        if (r < start || end < l)
            return;

        // Completely inside
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }

        // Partial overlap
        int mid = (start + end) / 2;

        update(2 * node + 1, start, mid, l, r, val);
        update(2 * node + 2, mid + 1, end, l, r, val);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Range query: sum of [l, r]
    long long query(int node, int start, int end, int l, int r) {
        push(node, start, end);

        // Completely outside
        if (r < start || end < l)
            return 0;

        // Completely inside
        if (l <= start && end <= r)
            return tree[node];

        int mid = (start + end) / 2;

        long long left = query(2 * node + 1, start, mid, l, r);
        long long right = query(2 * node + 2, mid + 1, end, l, r);

        return left + right;
    }

public:
    LazySegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1, arr);
    }

    void rangeUpdate(int l, int r, long long val) {
        update(0, 0, n - 1, l, r, val);
    }

    long long rangeQuery(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

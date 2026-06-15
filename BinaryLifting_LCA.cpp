#include <bits/stdc++.h>
using namespace std;

class BinaryLifting {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj;

    void dfs(int node, int parent) {
        up[node][0] = parent;

        for(int j = 1; j < LOG; j++) {
            if(up[node][j - 1] != -1) {
                up[node][j] = up[up[node][j - 1]][j - 1];
            }
        }

        for(int child : adj[node]) {
            if(child == parent) continue;

            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }

public:
    BinaryLifting(int n, vector<vector<int>>& edges) {
        this->n = n;
        LOG = log2(n) + 1;

        adj.resize(n);
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);

        for(auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(0, -1);
    }

    int kthAncestor(int node, int k) {
        for(int j = 0; j < LOG && node != -1; j++) {
            if(k & (1LL << j)) {
                node = up[node][j];
            }
        }
        return node;
    }

    int lca(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];
        u = kthAncestor(u, diff);

        if(u == v) return u;

        for(int j = LOG - 1; j >= 0; j--) {
            if(up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }
};
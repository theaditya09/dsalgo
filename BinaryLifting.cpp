#include <bits/stdc++.h>
using namespace std;

class BinaryLifting {
    vector<vector<int>> up;
    int LOG;

public:
    BinaryLifting(int n, vector<int>& parent) {
        LOG = log2(n) + 1;

        up.assign(n, vector<int>(LOG, -1));

        for(int node = 0; node < n; node++) {
            up[node][0] = parent[node];
        }

        for(int j = 1; j < LOG; j++) {
            for(int node = 0; node < n; node++) {
                if(up[node][j - 1] != -1) {
                    up[node][j] = up[up[node][j - 1]][j - 1];
                }
            }
        }
    }

    int getKthAncestor(int node, int k) {
        for(int j = 0; j < LOG && node != -1; j++) {
            if(k & (1LL << j)) {
                node = up[node][j];
            }
        }
        return node;
    }
};
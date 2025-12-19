#include <bits/stdc++.h>
using namespace std; 

// Use ONLY one: unionByRank OR unionBySize (do not mix)
class DisjointSet{
    vector<int> parent, rank, size;
public:
    DisjointSet(int n){
        rank.resize(n+1); //n+1 for 1 based indexing
        size.resize(n+1);
        parent.resize(n+1);
        for(int i=0; i<=n; i++) {
            parent[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
    }

    int findUltimateParent(int node){
        if(node == parent[node]) return node;
        return parent[node] = findUltimateParent(parent[node]); //path compression
    }

    void unionByRank(int u, int v){
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);
        if(ulp_u == ulp_v) return;

        if(rank[ulp_u] < rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        } else if(rank[ulp_v] < rank[ulp_u]){
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v){
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);
        if(ulp_u == ulp_v) return;

        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }

    bool isConnected(int u, int v){
        return findUltimateParent(u) == findUltimateParent(v);
    }
};

int main() {
    DisjointSet ds(7);
    ds.unionBySize(1,2);
    ds.unionBySize(2,3);
    ds.unionBySize(4,5);
    ds.unionBySize(6,7);
    ds.unionBySize(5,6);

    //if 3 and 7 belong to the same component?
    if(ds.findUltimateParent(3) == ds.findUltimateParent(7)){
        cout<<"Same parent"<<endl;
    } else {
        cout<<"Different parent"<<endl;
    }

    ds.unionBySize(3,7);

    //if 3 and 7 belong to the same component?
    if(ds.findUltimateParent(3) == ds.findUltimateParent(7)){
        cout<<"Same parent"<<endl;
    } else {
        cout<<"Different parent"<<endl;
    }
}
#include <algorithm>
#include <iostream>

#include "Graph.hpp"
template <typename T>
void dfs(int u, Graph<T> &g, std::vector<int> &vis, std::vector<int> &ans) {
    for (int &i = g.lst[u]; ~i;) {
        if (vis[i]) {
            i = g.edges[i].next;
            continue;
        };
        if (!g.is_directed) {
            vis[i] = vis[i ^ 1] = 1;
        } else {
            vis[i] = 1;
        }
        int j = g.edges[i].weight;
        dfs(g.edges[i].to, g, vis, ans);
        ans.push_back(j);
    }
}

template <typename T>
bool euler_circuit(Graph<T> g, std::vector<int> &circuit) {
    circuit.clear();
    std::vector<int> vis(g.m, 0);
    std::vector<int> in(g.n), out(g.n);

    for (int i = 0; i < g.n; ++i) {
        for (int _ = g.lst[i]; ~_; _ = g.edges[_].next) {
            ++out[i];
            ++in[g.edges[_].to];
        }
    }

    for (int i = 0; i < g.n; ++i) {
        if (g.lst[i] == -1) continue;
        if (!g.is_directed) {
            if (in[i] & 1) return false;
        } else {
            if (in[i] != out[i]) return false;
        }
    }

    for (int i = 0; i < g.n; ++i) {
        if (in[i] > 0) {
            dfs(i, g, vis, circuit);
        }
    }
    std::reverse(circuit.begin(), circuit.end());
    if (!g.is_directed)
        return circuit.size() == g.m / 2;
    else
        return circuit.size() == g.m;
}
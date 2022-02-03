#include <stack>
#include <vector>

#include "Graph.hpp"

template <typename T>
void strong_connected(const Graph<T> &g, int u, std::vector<int> &dfn,
                      std::vector<int> &low, std::vector<bool> &in_stack,
                      std::vector<int> &id, int &cnt, int &tot) {
    static std::stack<int> stk;
    dfn[u] = low[u] = ++cnt;
    stk.push(u);
    in_stack[u] = true;
    for (int i = g.lst[u]; ~i; i = g.edges[i].next) {
        int v = g.edges[i].to;
        if (!dfn[v]) {
            strong_connected(g, v, dfn, low, in_stack, id, cnt, tot);
            low[u] = std::min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        while (in_stack[u]) {
            int v = stk.top();
            stk.pop();
            in_stack[v] = false;
            id[v] = tot;
        }
        ++tot;
    }
}

template <typename T>
void biconnected(const Graph<T> &g, int u, int last_visit,
                 std::vector<int> &dfn, std::vector<int> &low,
                 std::vector<bool> &in_stack, std::vector<int> &id, int &cnt,
                 int &tot) {
    static std::stack<int> stk;
    dfn[u] = low[u] = ++cnt;
    stk.push(u);
    in_stack[u] = true;
    for (int i = g.lst[u]; ~i; i = g.edges[i].next) {
        if ((i ^ last_visit) == 1) continue;
        int v = g.edges[i].to;
        if (!dfn[v]) {
            biconnected(g, v, i, dfn, low, in_stack, id, cnt, tot);
            low[u] = std::min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (low[u] >= dfn[u]) {
        while (in_stack[u]) {
            int v = stk.top();
            stk.pop();
            in_stack[v] = false;
            id[v] = tot;
        }
        ++tot;
    }
}

template <typename T>
void tarjan(const Graph<T> &g, std::vector<int> &dfn, std::vector<int> &low,
            std::vector<int> &id) {
    dfn.resize(g.n);
    low.resize(g.n);
    id.resize(g.n);
    std::fill(dfn.begin(), dfn.end(), 0);
    std::fill(low.begin(), low.end(), 0);
    std::fill(id.begin(), id.end(), -1);

    std::vector<bool> in_stack(g.n, false);

    if (!g.is_directed) {
        int cnt = 0, tot = 0;
        for (int i = 0; i < g.n; ++i) {
            if (!dfn[i]) {
                biconnected(g, i, -1, dfn, low, in_stack, id, cnt, tot);
            }
        }
    } else {
        int cnt = 0, tot = 0;
        for (int i = 0; i < g.n; ++i) {
            if (!dfn[i]) {
                strong_connected(g, i, dfn, low, in_stack, id, cnt, tot);
            }
        }
    }
}

template <typename T>
Graph<T> graph_export(const Graph<T> &g, const std::vector<int> &id) {
    int n = *std::max_element(id.begin(), id.end()) + 1;
    int m = 0;

    for (int i = 0; i < g.n; ++i) {
        for (int j = g.lst[i]; ~j; j = g.edges[j].next) {
            if (id[i] != id[g.edges[j].to]) {
                ++m;
            }
        }
    }

    Graph<T> ret(n, m);

    for (int i = 0; i < g.n; ++i) {
        for (int j = g.lst[i]; ~j; j = g.edges[j].next) {
            if (id[i] != id[g.edges[j].to]) {
                ret.add_edge(id[i], id[g.edges[j].to], g.edges[j].w);
            }
        }
    }

    return std::move(ret);
}

template <>
Graph<void> graph_export<void>(const Graph<void> &g,
                               const std::vector<int> &id) {
    int n = *std::max_element(id.begin(), id.end()) + 1;
    int m = 0;
    for (int i = 0; i < g.n; ++i) {
        for (int j = g.lst[i]; ~j; j = g.edges[j].next) {
            if (id[i] != id[g.edges[j].to]) {
                ++m;
            }
        }
    }

    Graph<void> ret(n, m);

    for (int i = 0; i < g.n; ++i) {
        for (int j = g.lst[i]; ~j; j = g.edges[j].next) {
            if (id[i] != id[g.edges[j].to]) {
                ret.add_edge(id[i], id[g.edges[j].to]);
            }
        }
    }

    return std::move(ret);
}
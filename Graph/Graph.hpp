#pragma once

#include <algorithm>
#include <vector>

template <typename T>
struct Graph {
    struct Edge {
        int to;
        int next;
        T weight;
        Edge() = default;
        Edge(int to, int next, T weight) : to(to), next(next), weight(weight) {}
    };

    std::vector<Edge> edges;
    std::vector<int> lst;
    bool is_directed;
    int ed, n, m;

    Graph(int n, int m, bool is_directed = 1)
        : edges(m), lst(n, -1), is_directed(is_directed), ed(-1), n(n), m(m) {}
    Graph(Graph &&g)
        : edges(std::move(g.edges)),
          lst(std::move(g.lst)),
          is_directed(g.is_directed),
          ed(g.ed),
          n(g.n),
          m(g.m) {}
    Graph(const Graph &g)
        : edges(g.edges),
          lst(g.lst),
          is_directed(g.is_directed),
          ed(g.ed),
          n(g.n),
          m(g.m) {}
    void add_edge(int u, int v, T l) {
        edges[++ed] = Edge(v, lst[u], l);
        lst[u] = ed;
    }
};

template <>
struct Graph<void> {
    struct Edge {
        int to;
        int next;
        Edge() = default;
        Edge(int to, int next) : to(to), next(next) {}
    };

    std::vector<Edge> edges;
    std::vector<int> lst;
    bool is_directed;
    int ed, n, m;

    Graph(int n, int m, bool is_directed = 1)
        : edges(m), lst(n, -1), is_directed(is_directed), ed(-1), n(n), m(m) {}
    Graph(Graph &&g)
        : edges(std::move(g.edges)),
          lst(std::move(g.lst)),
          is_directed(g.is_directed),
          ed(g.ed),
          n(g.n),
          m(g.m) {}
    Graph(const Graph &g)
        : edges(g.edges),
          lst(g.lst),
          is_directed(g.is_directed),
          ed(g.ed),
          n(g.n),
          m(g.m) {}
    void add_edge(int u, int v) {
        edges[++ed] = Edge(v, lst[u]);
        lst[u] = ed;
    }
};
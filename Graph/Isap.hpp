#include <vector>

#include "Graph.hpp"

template <typename T>
T isap(Graph<T> &g, int u, T flow, int s, int t, std::vector<int> &cur,
       std::vector<int> &h, std::vector<int> &gap) {
    if (u == t) return flow;
    T rec = 0;

    for (int &i = cur[u]; ~i; i = g.edges[i].next) {
        int v = g.edges[i].to;
        if (g.edges[i].weight > 0 && h[u] == h[v] + 1) {
            T d = isap(g, v, std::min(flow - rec, g.edges[i].weight), s, t, cur,
                       h, gap);
            if (d > 0) {
                g.edges[i].weight -= d;
                g.edges[i ^ 1].weight += d;
                rec += d;
                if (rec == flow) return flow;
            }
        }
    }

    if (!(--gap[h[u]])) h[s] = t + 1;
    ++gap[++h[u]];
    cur[u] = g.lst[u];
    return rec;
}

template <typename T, T MAX = T(1e17)>
T maxflow(Graph<T> g, int s, int t) {
    std::vector<int> cur(g.lst), h(g.n, 0), gap(g.n + 2, 0);

    gap[s] = g.n;
    T flow = 0;

    while (h[s] < g.n) {
        flow += isap(g, s, MAX, s, t, cur, h, gap);
    }

    return flow;
}

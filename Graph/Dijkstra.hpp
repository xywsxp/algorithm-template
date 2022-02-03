#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
#include <utility>
#include <vector>

#include "Graph.hpp"

template <typename T, T MIN, T MAX>
std::vector<T> dijkstra(const Graph<T>& g, int u) {
    using namespace __gnu_pbds;

    typedef std::pair<T, int> pii;
    typedef __gnu_pbds::priority_queue<pii, std::greater<pii>, pairing_heap_tag>
        heap;
    typedef typename heap::point_iterator iter;

    std::vector<iter> id(g.n, nullptr);
    std::vector<T> dist(g.n, MAX);
    heap q;
    dist[u] = MIN;
    id[u] = q.push(pii(dist[u], u));
    while (!q.empty()) {
        u = q.top().second;
        q.pop();
        for (int i = g.lst[u]; ~i; i = g.edges[i].next) {
            int v = g.edges[i].to, l = g.edges[i].weight;
            if (dist[v] > dist[u] + l) {
                dist[v] = dist[u] + l;
                if (id[v] != 0)
                    q.modify(id[v], pii(dist[v], v));
                else
                    id[v] = q.push(pii(dist[v], v));
            }
        }
    }
    return std::move(dist);
}
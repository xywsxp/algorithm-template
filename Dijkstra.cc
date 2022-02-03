#include <vector>

template <typename T, T MAX>
class Dijkstra {
    const int N = 2e5 + 19, M = 4e5 + 19;

    struct edge {
        int v, id;
        int nxt;
        T l;
        edge() = default;
        edge(int v, int id, T l, int nxt) : v(v), id(id), l(l), nxt(nxt) {}
    };

    std::vector<edge> e;
    std::vector<T> dist;
};
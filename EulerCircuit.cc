#include <bits/stdc++.h>
using namespace std;

namespace EulerCircuit {
const int N = 2e5 + 19, M = 4e5 + 19;
struct edge {
    int v, id;
    int nxt;
    edge() = default;
    edge(int v, int id, int nxt) : v(v), id(id), nxt(nxt) {}
} e[M];

int n, m;
int lst[N], ed, vis[M], is_undirected;
int in[N], out[N];
vector<int> ans;
void init(int N, int M, int flag) {
    n = N;
    m = M;
    for (int i = 0; i < n; ++i) {
        lst[i] = -1;
        in[i] = out[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        vis[i] = 0;
    }
    ed = -1;
    is_undirected = flag;
    ans.clear();
}

void add_edge(int u, int v, int id) {
    e[++ed] = edge(v, id, lst[u]);
    lst[u] = ed;
    ++out[u];
    ++in[v];
}

void dfs(int u) {
    for (int &i = lst[u]; ~i;) {
        if (vis[i]) {
            i = e[i].nxt;
            continue;
        };
        if (is_undirected) {
            vis[i] = vis[i ^ 1] = 1;
        } else {
            vis[i] = 1;
        }
        int j = e[i].id;
        dfs(e[i].v);
        ans.push_back(j);
    }
}

bool check() {
    for (int i = 0; i < n; ++i) {
        if (is_undirected) {
            if (in[i] & 1) return false;
        } else {
            if (in[i] != out[i]) return false;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (in[i] > 0) {
            dfs(i);
            break;
        }
    }
    if (is_undirected)
        return ans.size() == m / 2;
    else
        return ans.size() == m;
}

vector<int> get_euler_circuit() {
    reverse(ans.begin(), ans.end());
    return ans;
}

}  // namespace EulerCircuit

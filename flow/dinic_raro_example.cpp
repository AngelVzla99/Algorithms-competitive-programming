#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <math.h>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <array>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;
typedef vector<int> vi;
typedef vector<pii> vii;

int dadsadasda;

#define ri(a) dadsadasda=scanf("%d", &a)
#define rii(a,b) dadsadasda=scanf("%d %d", &a, &b)
#define riii(a,b,c) dadsadasda=scanf("%d %d %d", &a, &b, &c)
#define rl(a) dadsadasda=scanf("%lld", &a)
#define rll(a,b) dadsadasda=scanf("%lld %lld", &a, &b)
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define ALL(s) s.begin(),s.end()
#define SZ(s) (int)s.size()

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 5010; // CAMBIAR ESTE

// GJNM
// O(N * M * log(MC)), where MC is maximum edge capacity.
// importante, s debe ser 0 y t debe ser el nodo mas grande, no se muy bien como funciona xD
struct Dinic { 
    struct edge { 
        int a, b, f, c;
    };
    const int inf = 1000 * 1000 * 1000;
    int n, s, t, lim;
    vector <edge> e;
    vi pt; // very important performance trick
    vector<vi> g;
    long long flow = 0;
    queue <int> q;
    vi d;

    Dinic(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        pt.resize(n, 0);
        g.resize(n);
        d.resize(n, 0);
    }

    void add_edge(int a, int b, int c) {
        edge ed;

        //keep edges in vector: e[ind] - direct edge, e[ind ^ 1] - back edge

        ed.a = a; ed.b = b; ed.f = 0; ed.c = c;
        g[a].push_back(e.size());
        e.push_back(ed);

        ed.a = b; ed.b = a; ed.f = c; ed.c = c;
        g[b].push_back(e.size());
        e.push_back(ed);
    }

    bool bfs() {
        for (int i = s; i <= t; i++)
            d[i] = inf;
        d[s] = 0;
        q.push(s);
        while (!q.empty() && d[t] == inf) {
            int cur = q.front(); q.pop();
            for (size_t i = 0; i < g[cur].size(); i++) {
                int id = g[cur][i];
                int to = e[id].b;

                //printf("cur = %d id = %d a = %d b = %d f = %d c = %d\n", cur, id, e[id].a, e[id].b, e[id].f, e[id].c);

                if (d[to] == inf && e[id].c - e[id].f >= lim) {
                    d[to] = d[cur] + 1;
                    q.push(to);
                }
            }
        }
        while (!q.empty())
            q.pop();
        return d[t] != inf;
    }

    bool dfs(int v, int flw) {
        if (flw == 0)
            return false;
        if (v == t) {
            //cout << v << endl;
            return true;
        }
        for (; pt[v] < SZ(g[v]); pt[v]++) {
            int id = g[v][pt[v]];
            int to = e[id].b;

            //printf("v = %d id = %d a = %d b = %d f = %d c = %d\n", v, id, e[id].a, e[id].b, e[id].f, e[id].c);

            if (d[to] == d[v] + 1 && e[id].c - e[id].f >= flw) {
                int pushed = dfs(to, flw);
                if (pushed) {
                    e[id].f += flw;
                    e[id ^ 1].f -= flw;
                    return true;
                }
            }
        }
        return false;
    }

    ll dinic() {
        for (lim = (1 << 30); lim >= 1;) {
            if (!bfs()) {
                lim >>= 1;
                continue;
            }

            for (int i = s; i <= t; i++)
                pt[i] = 0;

            int pushed;

            while ((pushed = dfs(s, lim))) {
                flow = flow + lim;
            }

            //cout << flow << endl;
        }
        return flow;
    }
};

int in(int i, int j) {
    return 2 * (50 * i + j) + 1;
}
int out(int i, int j) {
    return in(i, j) + 1;
}
int DI[4] = {1, -1, 0, 0};
int DJ[4] = {0, 0, 1, -1};

void solve() {
    int n, m, b; riii(n, m, b);
    int s = 0, t = 5001;
    Dinic mxf(t + 1, s, t);
    FOR(i, 0, n) FOR(j, 0, m) {
        mxf.add_edge(in(i, j), out(i, j), 1);
        if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
            mxf.add_edge(out(i, j), t, 1);

        FOR(k, 0, 4) {
            int new_i = i + DI[k], new_j = j + DJ[k];
            if (min(new_i, new_j) >= 0 && new_i < n && new_j < m)
                mxf.add_edge(out(i, j), in(new_i, new_j), 1);
        }
    }
    FOR(_, 0, b) {
        int i, j; rii(i, j); --i, --j;
        mxf.add_edge(s, in(i, j), 1);
    }

    printf("%s\n", mxf.dinic() == b ? "possible" : "not possible");
}


int main() {
    int t; ri(t);
    while (t--) solve();
    return 0;
}

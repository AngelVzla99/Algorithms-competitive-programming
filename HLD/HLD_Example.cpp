// https://www.spoj.com/problems/QTREE/

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

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;
typedef vector<int> vi;
typedef vector<pii> vii;

#define ri(a) scanf("%d", &a)
#define rii(a,b) scanf("%d %d", &a, &b)
#define riii(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define rl(a) scanf("%lld", &a)
#define rll(a,b) scanf("%lld %lld", &a, &b)
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5; // CAMBIAR ESTE

// GJNM
struct edge {
    int to, from, cost;
};
edge E[MAXN];
int n;


// SEGMENT TREE PARA QUERIES EN EL HLD
// Todos los rangos son semi-abiertos [a,b)
int N, A[MAXN];
struct STN {
    int val;
    void merge(STN& L, STN& R) {
        val = max(L.val, R.val);
    }
    void operator=(int a) {
        val = a;
    }
};
STN ST[4 * MAXN];
void STB(int id = 1, int l = 0, int r = N) {
    if (r - l < 2) {
        ST[id] = A[l];
        return;
    }
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    STB(L, l, m); STB(R, m, r);
    ST[id].merge(ST[L], ST[R]);
}
STN STQ(int x, int y, int id = 1, int l = 0, int r = N) {
    if (x == l && y == r) return ST[id];
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    if (x >= m) return STQ(x, y, R, m, r);
    if (y <= m) return STQ(x, y, L, l, m);
    STN res, ln = STQ(x, m, L, l, m), rn = STQ(m, y, R, m, r);
    return res.merge(ln, rn), res;
}
void STU(int p, int x, int id = 1, int l = 0, int r = N) {
    if (r - l < 2) {
        ST[id] = x;
        return;
    }
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    if (p < m) STU(p, x, L, l, m);
    else STU(p, x, R, m, r);
    ST[id].merge(ST[L], ST[R]);
}


// HEAVY LIGHT DECOMP
vector<int> G[MAXN];
int wg[MAXN], dad[MAXN], dep[MAXN]; // weight,father,depth
void dfs1(int x) {
    wg[x] = 1;
    for (int y : G[x])if (y != dad[x]) {
            dad[y] = x; dep[y] = dep[x] + 1; dfs1(y);
            wg[x] += wg[y];
        }
}
int curpos, pos[MAXN], head[MAXN];
void hld(int x, int c) {
    if (c < 0)c = x;
    pos[x] = curpos++; head[x] = c;
    int mx = -1;
    for (int y : G[x])if (y != dad[x] && (mx < 0 || wg[mx] < wg[y]))mx = y;
    if (mx >= 0)hld(mx, c);
    for (int y : G[x])if (y != mx && y != dad[x])hld(y, -1);
}
void hld_init() {dad[0] = -1; dep[0] = 0; dfs1(0); curpos = 0; hld(0, -1);}
int query(int x, int y) {
    int r = 0;
    while (head[x] != head[y]) {
        if (dep[head[x]] > dep[head[y]])swap(x, y);
        r = max(r, STQ(pos[head[y]], pos[y] + 1).val);
        y = dad[head[y]];
    }
    if (dep[x] > dep[y])swap(x, y); // now x is lca
    if (x != y) // so ST doesnt blow up 
        r = max(r, STQ(pos[x] + 1, pos[y] + 1).val); // +1 because queries are on edges
    return r;
}
// for updating: rmq.upd(pos[x],v);
// queries on edges: - assign values of edges to "child" node
//                   - change pos[x] to pos[x]+1 in query (line 28)




void solve() {
    ri(n);
    FOR(i, 1, n) {
        int a, b, c;
        riii(a, b, c); a--, b--;
        G[a].pb(b);
        G[b].pb(a);
        E[i] = {a, b, c};
    }

    curpos = 0;
    hld_init();

    FOR(i, 1, n) { // colocando los valores de los hijos en el arreglo
        if (dad[E[i].from] == E[i].to)
            A[pos[E[i].from]] = E[i].cost;
        else
            A[pos[E[i].to]] = E[i].cost;
    }

    N = curpos;
    STB();
    
    char aux[16];
    while (scanf("%s", aux), aux[0] != 'D') {
        int a, b; rii(a, b);
        if (aux[0] == 'C') {
            if (dad[E[a].from] == E[a].to)
                STU(pos[E[a].from], b);
            else
                STU(pos[E[a].to], b);
        }
        else {
            printf("%d\n", query(a - 1, b - 1));
        }
    }
    FOR(i, 0, n) {
        G[i].clear();
    }
}



int main() {
    int t;
    ri(t);
    while (t--)
        solve();

    return 0;
}

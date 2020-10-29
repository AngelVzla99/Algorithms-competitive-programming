//https://codeforces.com/problemset/problem/321/C?mobile=false

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
const int MAXN = 1e5 + 10; // CAMBIAR ESTE

// GJNM
// CENTROID TREE
vector<int> G[MAXN]; int n;
bool tk[MAXN]; // already selected as a centroid
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f) {
    szt[x] = 1;
    for (auto y : G[x])if (y != f && !tk[y])szt[x] += calcsz(y, x);
    return szt[x];
}
void cdfs(int x = 0, int f = -1, int sz = -1) { // O(nlogn)
    if (sz < 0)sz = calcsz(x, -1);
    for (auto y : G[x])if (!tk[y] && szt[y] * 2 >= sz) {
            szt[x] = 0; cdfs(y, f, sz); return;
        }
    tk[x] = true; fat[x] = f;
    for (auto y : G[x])if (!tk[y])cdfs(y, x);
}
void centroid() {memset(tk, false, sizeof(tk)); cdfs();}


vi CT[MAXN];
char ans[MAXN];

int main() {
    ri(n);
    FOR(i, 1, n) {
        int a, b;
        rii(a, b); a--, b--;
        G[a].pb(b);
        G[b].pb(a);
    }

    centroid();

    queue<int> bfs;

    FOR(i, 0, n) {
        if (fat[i] != -1)
            CT[fat[i]].pb(i);
        else {
            bfs.push(i);
            ans[i] = 'A';
        }
    }

    while (!bfs.empty()) {
        int x = bfs.front();
        bfs.pop();
        for (auto y : CT[x]) {
            bfs.push(y);
            ans[y] = ans[x] + 1;
        }
    }

    FOR(i, 0, n) {
        printf("%c ", ans[i]);
    }
    printf("\n");

    return 0;
}

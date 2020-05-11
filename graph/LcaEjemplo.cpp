#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <string.h>
#include <math.h>
#include <set>
#include <map>
using namespace std;

typedef long long ll;
typedef long double ld;
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define ri(a) scanf("%d",&a)
#define rii(a,b) ri(a),ri(b)
#define riii(a,b,c) rii(a,b),ri(c)
#define lri(a) scanf("%lld",&a)
#define lrii(a,b) lri(a),lri(b)
#define pb push_back
#define _1 first
#define _2 second

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1000000007;
const int alphabet = 26;
const int MAXINT = 2e5+1;

// ------------ LCA en logN --------------
// Se guarda en anc[v][i] el padre a distancia
// 2**i de v
//
// Se utiliza tiempo de entrada y salida de un nodo
// (al hacer DFS) para identificar un ancestro en la misma rama
//
// LCA consiste en buscar el nodo mas arriba de u tq
// NO sea ancestro de v, despues se retorna el padre de este u

int n, l;
vector<int> G[MAXINT];

int timer;
int tin[MAXINT], tout[MAXINT], anc[MAXINT][ int(log2(MAXINT))+1 ];

void dfs(int v, int p){
    tin[v] = ++timer;
    anc[v][0] = p;

    for(int i = 1; i <= l; ++i) anc[v][i] = anc[anc[v][i-1]][i-1];
    for(int w : G[v]) if(w!=p) dfs(w, v);

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v){ return tin[u]<=tin[v] && tout[u]>=tout[v]; }

int lca(int u, int v){
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i = l; i >= 0; --i){
        if (!is_ancestor(anc[u][i], v)){
            u = anc[u][i];
        }
    }
    return anc[u][0];
}

int main(){
    int root = 1, v, w;

    ri(n); // Ejemplo mas abajo
    FOR(i,0,n-1) rii(v,w), G[v].pb(w), G[w].pb(v);

    l = ceil(log2(n));
    dfs(root, root);

    int q = 10;
    while(q--){
        cout << "Nodos v y w" << endl;
        rii(v,w);
        cout << "=> " << lca(v,w) << endl;
    }
}

/*
10
1 2
2 3
2 4
1 5
5 6
6 7
6 8 
5 9
9 10

*/  
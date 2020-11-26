int n, l; // l = log(n)
vector<int> G[MAXINT];

int timer; // Tiempos de entrada y salida de cada nodo y su ancestro a dist 2**i
int tin[MAXINT], tout[MAXINT], anc[MAXINT][ int(log2(MAXINT))+1 ];

void dfs(int v, int p){ // Se inicializa con dfs(1,1)
    tin[v] = ++timer;
    anc[v][0] = p;

    for(int i = 1; i <= l; ++i) anc[v][i] = anc[ anc[v][i-1] ][i-1];
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
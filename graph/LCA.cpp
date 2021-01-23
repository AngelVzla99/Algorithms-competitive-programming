// Para usar, l=log2(n), y se llama a dfs(1,1), luego se usa lca(u,v)

int n, l; // l = log(n)
vector<int> G[MAXN];

int timer; // Tiempos de entrada y salida de cada nodo y su ancestro a dist 2**i
int tin[MAXN], tout[MAXN], anc[MAXN][ int(log2(MAXN))+1 ];

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

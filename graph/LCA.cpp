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

// ============== Codigo con solo binary lifting

const int K = log2(MAXN)+1;
vector<int> G[1<<K];int n;  // K such that 2^K>=n
int F[K][1<<K],D[1<<K];
void lca_dfs(int x){
	FOR(i,0,G[x].size()){
		int y=g[x][i];if(y==F[0][x])continue;
		F[0][y]=x;D[y]=D[x]+1;lca_dfs(y);
	}
}
void lca_init(){
	D[0]=0;F[0][0]=-1;
	lca_dfs(0); // graph indexed in 0
	FOR(k,1,K) FOR(x,0,n){ 
		if(F[k-1][x]<0)F[k][x]=-1;
		else F[k][x]=F[k-1][F[k-1][x]];
	}
}
int lca(int x, int y){
	if(D[x]<D[y])swap(x,y);
	for(int k=K-1;k>=0;--k)
		if(D[x]-(1<<k)>=D[y])
			x=F[k][x];
	if(x==y)return x;
	for(int k=K-1;k>=0;--k)
		if(F[k][x]!=F[k][y])
			x=F[k][x],y=F[k][y];
	return F[0][x];
}

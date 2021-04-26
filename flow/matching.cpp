/*
Para matching es el mejor y es corto
* add_edge(v,w,1)_se hace con G[v].pb(w) v,w<MAXN
Si se busca una cierta cantidad de mach agregando edges, es mejor
hacer binary sobre ellos y hacer G[v].pop_back()
*/

int mark[MAXN], mat[MAXN][2];
int n;
vector<int> G[MAXN]; // [0,n) -> [0,n)

bool dfs(int v){
    if(mark[v])  return 0;
    mark[v] = 1;
    for(auto u : G[v])
        if(mat[u][1] == -1 || dfs(mat[u][1]))
            return mat[v][0] = u, mat[u][1] = v, 1;
    return 0;
}
int maximum_matching(){
    memset(mat, -1, sizeof mat);
    bool br = 0;
    int ans = 0;
    while(br ^= 1){
        memset(mark, 0, sizeof mark);
        for(int i = 0; i < n; i++)
            if(mat[i][0] == -1 && dfs(i))
                ans++, br = 0;
    }
    return ans;
}

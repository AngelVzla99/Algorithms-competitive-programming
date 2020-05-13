int low[maxN], disc[maxN];
bool vis[maxN];
int t;

void dfs(int x, int father = -1){
	low[x] = disc[x] = t++;
	vis[x] = true;
	int children = 0;
	for(auto y : g[x]){
		if ( !vis[y] ){
			children++;
			dfs(y,x);
			if (low[y]>=disc[x] && father!=-1){
				// PUNTO DE ARTICULACION
			}
			if (low[y]>disc[x]){
				// PUENTE
			}
			low[x] = min(low[x],low[y]);
		}
		else if ( y != father ){
			low[x] = min(low[x], disc[y]);
		}
	}
	if ( father == -1 && children > 1 ){
		// PTO DE ART
	}
}

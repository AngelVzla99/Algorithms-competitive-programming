int t;
int low[maxN], disc[maxN];
bool vis[maxN];
stack<int> st;

void tarjan(int u){
	low[u] = disc[u] = t++;
	vis[u] = true;
	st.push(u);

	for(auto v : g[u]){
		if ( low[v] == -1 )
			tarjan(v);
		if ( vis[v] )
			low[u] = min(low[u], low[v]);
	}

	if ( low[u] == disc[u] ){
		while(1){ // Los que salgan de la pila en este ciclo son de la misma comp
			int v = st.top();
			st.pop();
			vis[v] = false;


			if ( u == v )
				break;
		}
	}
}
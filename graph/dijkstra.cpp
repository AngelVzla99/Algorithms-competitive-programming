vector<ld> dijkstra(int s){
    vector<ld> dist(n+1,INFLL);
    bool visit[n+1]={};
    priority_queue< pair<ld,int>, vector<pair<ld,int>>, greater<pair<ld,int>> > pq;

    dist[s] = 0;
    pq.push({0,s});

    int v, u;
    while(!pq.empty()){
        v = pq.top()._2; pq.pop();
        if( visit[v] ) continue;

        for(auto e: G[v]){ // G[from].pb({to,cost})
            u = e._1;
            ld d = e._2 + dist[v];
            if( dist[u] > d && !visit[u] ){
                dist[u] = d;
                pq.push({d,u});
            }
        }
        visit[v] = true;
    }
    return dist;
}
/*
Dini's algorithm, para encontrar el flujo Maximo en un grafo
Teoria: https://cp-algorithms.com/graph/dinic.html
Video teoria: https://www.youtube.com/watch?v=M6cm8UeeziI

PROBLEMA: https://codeforces.com/submissions/AngelVzla99

Uso del struct, basta con solo usar la funcion add_edge
para conectar los nodos, y luego llamar a la funcion 
max_flow con la fuente y el sumidero (recordar que es dirigido)
*/

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
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define ri(a) scanf("%d",&a)
#define rii(a,b) ri(a),ri(b)
#define riii(a,b,c) rii(a,b),ri(c)
#define lri(a) scanf("%lld",&a)
#define lrii(a,b) lri(a),lri(b)
#define lriii(a,b,c) lrii(a,b),lri(c)
#define pb push_back
#define _1 first
#define _2 second
#define ALL(s) s.begin(),s.end()
#define SZ(x) int((x).size())

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1000000007;
const int alphabet = 26;
const double PI = 3.1415926535;
const int MAXINT = 9e4+1;

struct Dinic{
	int nodes,src,dst;
	vector<int> dist,q,work;
	struct edge {int to,rev;ll f,cap;};
	vector<vector<edge>> g;
	Dinic(int x):nodes(x),g(x),dist(x),q(x),work(x){}
	void add_edge(int s, int t, ll cap){
		g[s].pb((edge){t,SZ(g[t]),0,cap});
		g[t].pb((edge){s,SZ(g[s])-1,0,0});
	}
	bool dinic_bfs(){
		fill(ALL(dist),-1);dist[src]=0;
		int qt=0;q[qt++]=src;
		for(int qh=0;qh<qt;qh++){
			int u=q[qh];
			FOR(i,0,SZ(g[u])){
				edge &e=g[u][i];int v=g[u][i].to;
				if(dist[v]<0&&e.f<e.cap)dist[v]=dist[u]+1,q[qt++]=v;
			}
		}
		return dist[dst]>=0;
	}
	ll dinic_dfs(int u, ll f){
		if(u==dst)return f;
		for(int &i=work[u];i<SZ(g[u]);i++){
			edge &e=g[u][i];
			if(e.cap<=e.f)continue;
			int v=e.to;
			if(dist[v]==dist[u]+1){
				ll df=dinic_dfs(v,min(f,e.cap-e.f));
				if(df>0){e.f+=df;g[v][e.rev].f-=df;return df;}
			}
		}
		return 0;
	}
	ll max_flow(int _src, int _dst){
		src=_src;dst=_dst;
		ll result=0;
		while(dinic_bfs()){
			fill(ALL(work),0);
			while(ll delta=dinic_dfs(src,INF))result+=delta;
		}
		return result;
	}
};

vector<pii> fac(int n){
	vector<pii> ans;
	FOR(i,2,sqrt(n)+1) if(n%i==0){
		ans.pb({i,0});
		while(n%i==0) n/=i, ans.back()._2++;
	}
	if(n!=1) ans.pb({n,1});
	return ans;
}

int main() {
	int n, m, a[100];
	rii(n,m);

	int nodes = n*100, S = nodes, T = nodes+1, cuNode=0;
	Dinic mf( nodes+2 );

	vector<pii> facto[n];
	map<int,int> label[n];
	FOR(i,0,n){
		ri(a[i]);
		facto[i] = fac(a[i]);
		for(auto p: facto[i]){
			label[i][ p._1 ] = cuNode++;
			if((i&1)) mf.add_edge( cuNode-1, T, p._2 );
			else mf.add_edge( S, cuNode-1, p._2 );
		}
	}

	FOR(k,0,m){
		int i, j; rii(i,j); i--; j--;
		if((i&1)) swap(i,j);
		for(pii p: facto[i]) if( label[j].count(p._1) )
			mf.add_edge( label[i][p._1], label[j][p._1], INF );
	}
	cout << mf.max_flow(S,T) << endl;	
}
/*
*/  
 

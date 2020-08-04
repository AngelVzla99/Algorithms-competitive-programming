/*
Teoria: https://cp-algorithms.com/graph/min_cost_flow.html

Problema: https://codeforces.com/group/j1UosVRZar/contest/287506/problem/A
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

typedef ll tf;
typedef ll tc;
const tf INFFLOW=1e9;
const tc INFCOST=1e9;
struct MCF{
	int n;
	vector<tc> prio, pot; vector<tf> curflow; vector<int> prevedge,prevnode;
	priority_queue<pair<tc, int>, vector<pair<tc, int>>, greater<pair<tc, int>>> q;
	struct edge{int to, rev; tf f, cap; tc cost;};
	vector<vector<edge>> g;
	MCF(int n):n(n),prio(n),curflow(n),prevedge(n),prevnode(n),pot(n),g(n){}
	void add_edge(int s, int t, tf cap, tc cost) {
		g[s].pb((edge){t,SZ(g[t]),0,cap,cost});
		g[t].pb((edge){s,SZ(g[s])-1,0,0,-cost});
	}
	pair<tf,tc> get_flow(int s, int t) {
		tf flow=0; tc flowcost=0;
		while(1){
			q.push({0, s});
			fill(ALL(prio),INFCOST); 
			prio[s]=0; curflow[s]=INFFLOW;
			while(!q.empty()) {
				auto cur=q.top();
				tc d=cur._1;
				int u=cur._2;
				q.pop();
				if(d!=prio[u]) continue;
				for(int i=0; i<SZ(g[u]); ++i) {
					edge &e=g[u][i];
					int v=e.to;
					if(e.cap<=e.f) continue;
					tc nprio=prio[u]+e.cost+pot[u]-pot[v];
					if(prio[v]>nprio) {
						prio[v]=nprio;
						q.push({nprio, v});
						prevnode[v]=u; prevedge[v]=i;
						curflow[v]=min(curflow[u], e.cap-e.f);
					}
				}
			}
			if(prio[t]==INFCOST) break;
			FOR(i,0,n) pot[i]+=prio[i];
			tf df=min(curflow[t], INFFLOW-flow);
			flow+=df;
			for(int v=t; v!=s; v=prevnode[v]) {
				edge &e=g[prevnode[v]][prevedge[v]];
				e.f+=df; g[v][e.rev].f-=df;
				flowcost+=df*e.cost;
			}
		}
		return {flow,flowcost};
	}
};

int main() {
	int n, q; rii(n,q);

	vector<int> mx(n+1,n), mi(n+1,1);
	FOR(i,0,q){
		int op, l, r, vi; riii(op,l,r); ri(vi);
		if(op==1) FOR(j,l,r+1) mi[j] = max(mi[j],vi);
		else FOR(j,l,r+1) mx[j] = min(mx[j],vi);
	}
	//FOR(i,1,n+1) if( mi[i] > mx[i] ){ printf("-1\n"); return 0; }

	int cuNode = 0, S = cuNode++, T = cuNode++;
	MCF mf(2*n+2);

	int label[2][n+1];
	FOR(i,1,n+1) label[0][i] = cuNode++, mf.add_edge(S,label[0][i],1,0);
	FOR(i,1,n+1){
		label[1][i] = cuNode++;
		FOR(j,0,n) mf.add_edge(label[1][i], T, 1, 2*j+1);
	}

	FOR(i,1,n+1){
		FOR(j,mi[i],mx[i]+1) mf.add_edge(label[0][i],label[1][j],1,0);
	}

	pair<ll,ll> ans = mf.get_flow(S,T);
	if( ans._1 < n ) printf("-1\n");
	else printf("%lld\n", ans._2);
	return 0;
}
/*
*/  
 

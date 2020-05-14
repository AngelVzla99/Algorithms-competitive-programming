#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <math.h>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,pair<int,int>> piii;
typedef vector<int> vi;
typedef vector<pii> vii;

#define ri(a) scanf("%d", &a)
#define rii(a,b) scanf("%d %d", &a, &b)
#define riii(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define rl(a) scanf("%lld", &a)
#define rll(a,b) scanf("%lld %lld", &a, &b)
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int maxN = 100; // CAMBIAR ESTE

// GJNM
map<string,int> getId;
map<int,string> getName;

vi g[maxN];

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
		while(1){
			int v = st.top();
			st.pop();
			vis[v] = false;
			cout << getName[v];
			if ( u == v )
				break;
			cout << ", ";
		}
		printf("\n");
	}
}

int main(){
	int n,m;
	int w = 1;
	while(rii(n,m), n!=0 || m!=0){
		if ( w > 1 )
			printf("\n");
		t = 0;
		FOR(i,0,30){
			vis[i] = false;
			low[i] = disc[i] = -1;
			g[i].clear();
		}
		getId.clear(), getName.clear();

		int aux = 0;
		FOR(i,0,m){
			string s,t;
			cin >> s >> t;
			if ( getId.find(s) == getId.end() ){
				getId[s] = aux;
				getName[aux++] = s;
			}
			if ( getId.find(t) == getId.end() ){
				getId[t] = aux;
				getName[aux++] = t;
			}
			g[getId[t]].pb(getId[s]);
		}

		printf("Calling circles for data set %d:\n",w++);
		FOR(i,0,n){
			if ( low[i] == -1 )
				tarjan(i);
		}
	}
	return 0;
}
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
const int maxN = 200; // CAMBIAR ESTE

// GJNM
int n,m;
map<string,int> getId;
map<int,string> getStr;

vi g[maxN];
set<string> ans;

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
				ans.insert(getStr[x]);
			}
			if (low[y]>disc[x]){
				// puente
			}
			low[x] = min(low[x],low[y]);
		}
		else if ( y != father ){
			low[x] = min(low[x], disc[y]);
		}
	}

	if ( father == -1 && children > 1 ){
		ans.insert(getStr[x]);		
	}
}


int main(){
	int k = 1;
	while(ri(n), n!=0){
		getStr.clear();
		getId.clear();
		FOR(i,0,n){
			string s;
			cin >> s;
			getId[s] = i;
			getStr[i] = s;
			low[i] = disc[i] = -1;
			vis[i] = false;
			g[i].clear();
		}
		ans.clear();
		ri(m);
		FOR(i,0,m){
			string s,t;
			cin >> s >> t;
			g[getId[s]].pb(getId[t]);
			g[getId[t]].pb(getId[s]);
		}
		t = 0;
		FOR(i,0,n){
			if (!vis[i])
				dfs(i);
		}
		if ( k > 1 )
			printf("\n");
		printf("City map #%d: %d camera(s) found\n", k++, (int)ans.size());
		for(auto x : ans){
			cout << x << endl;
		}

	}
	return 0;
}
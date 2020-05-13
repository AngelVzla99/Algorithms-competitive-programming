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
const int maxN = 2e5+19; // CAMBIAR ESTE

// GJNM
int n,m;

vi g[maxN];

set<pii> ans;

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
			}
			if (low[y]>disc[x]){
				ans.insert({min(x,y),max(x,y)});
			}
			low[x] = min(low[x],low[y]);
		}
		else if ( y != father ){
			low[x] = min(low[x], disc[y]);
		}
	}

	if ( father == -1 && children > 1 ){
	}
}


int main(){
	int first = true;
	while(scanf("%d",&n) != EOF){
		ans.clear();
		FOR(i,0,n)
			g[i].clear();
		FOR(i,0,n){
			int aux;
			ri(aux);
			char c;
			scanf("%*c%*c%d%*c", &m);
			FOR(i,0,m){
				int aux2;
				ri(aux2);
				g[aux].pb(aux2);
				g[aux2].pb(aux);
			}
			low[i] = disc[i] = -1;
			vis[i] = false;
		}
		t = 0;

		FOR(i,0,n){
			if (!vis[i])
				dfs(i);
		}

		printf("%d critical links\n",(int)ans.size() );
		for(auto p : ans){
			printf("%d - %d\n", p.F, p.S);
		}
		printf("\n");

	}
	return 0;
}
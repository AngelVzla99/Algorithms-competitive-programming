//https://codeforces.com/problemset/problem/1423/B

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
#include <assert.h>
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef pair<int, pair<int, int>> piii;
typedef vector<int> vi;
typedef vector<pii> vii;

int dadsadasda;
#define ri(a) dadsadasda=scanf("%d", &a)
#define rii(a,b) dadsadasda=scanf("%d %d", &a, &b)
#define riii(a,b,c) dadsadasda=scanf("%d %d %d", &a, &b, &c)
#define rl(a) dadsadasda=scanf("%lld", &a)
#define rll(a,b) dadsadasda=scanf("%lld %lld", &a, &b)
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define ALL(s) s.begin(),s.end()
#define SZ(s) (int)s.size()

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18+1;
const int MOD = 998244353;
const int MAXN = 1e4+100;

// [0,n) -> [0,n)
int mark[MAXN], mat[MAXN][2];
int n;
vector<int> G[MAXN];
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

struct edge{ 
	int v, u, d; 
	bool operator<( edge e2 ){
		if( d!=e2.d ) return d<e2.d;
		return v<e2.v;
	}
};

vector<edge> E; 

bool valid(int k){
	int val = E[k].d;
	FOR(i,0,n) G[i].clear();
	for(auto e: E) if(e.d<=val) G[e.v-1].pb(e.u-1);
	return maximum_matching()==n;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
	int M; cin >> n >> M; int v, u, d;
	FOR(i,0,M) cin>>v>>u>>d, E.pb({v,u,d});
	sort(ALL(E));
	
	if( !valid(M-1) ) cout << -1 << '\n';
	else{
		int l = -1, r = M-1, mid;
		while( l+1<r ){
			mid = (l+r)/2;
			if( valid(mid) ) r = mid;
			else l = mid;
		}
		cout << E[r].d << '\n';
	}
    
    return 0;
}

/*

*/

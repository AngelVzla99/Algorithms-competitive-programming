https://codeforces.com/problemset/problem/932/F

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
#include <bitset>

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
const int MOD = 1e9+7;
const int MAXN = 1e5+2;

bool Q;
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const {
        return Q ? p < o.p : k < o.k;
    }
};
struct LineContainer : multiset<Line> {
    const ll inf = INFLL;
    ll div(ll a, ll b){
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
        return l.k * x + l.m;
    }
};


int n, F[MAXN];
ll a[MAXN], b[MAXN];
vector<int> G[MAXN];

ll dp[MAXN];
vector<Line> conju[MAXN];
LineContainer s[MAXN];
void dfs(int v, int fa){
	F[v] = v;
	
	// unir como dsu
	FOR(i,0,SZ(G[v])) if( G[v][i]!=fa ){
		int u = G[v][i];
		dfs(u,v);
		
		if( SZ(conju[F[u]])>SZ(conju[F[v]]) ){
			for(auto e: conju[F[v]]) s[F[u]].add(e.k,e.m);
			for(auto e: conju[F[v]]) conju[F[u]].pb(e);
			F[v] = F[u];
		}else{
			for(auto e: conju[F[u]]) s[F[v]].add(e.k,e.m);
			for(auto e: conju[F[u]]) conju[F[v]].pb(e);
		}
	}
	
	if( SZ(conju[F[v]])!=0 ) dp[v] = -s[F[v]].query(a[v]);
	s[F[v]].add( -b[v], -dp[v] );
	conju[F[v]].pb({-b[v], -dp[v]});
}

int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin>>n;
	FOR(i,1,n+1) cin>>a[i];
	FOR(i,1,n+1) cin>>b[i];
	
	int u, v;
	FOR(i,0,n-1) cin>>u>>v, G[u].pb(v), G[v].pb(u);
	
	dfs(1,1);
	FOR(i,1,n+1) cout << dp[i] << " ";
	cout << '\n';
	
	return 0;
}

/*
3
-1 3 4
-10 10 -5
1 2
2 3

*/

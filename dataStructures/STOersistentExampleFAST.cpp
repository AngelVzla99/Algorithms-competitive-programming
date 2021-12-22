//https://codeforces.com/group/gXivUSZQpn/contest/338135/problem/A

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
const int MAXN = 3e5+1;

struct robot{ 
	int x, r, iq; 
	int idIqL, idIqR;
	bool operator<( robot r2 ){
		if(r!=r2.r) return r>r2.r;
		if(x!=r2.x) return x<r2.x;
		return iq<r2.iq;
	}
};

#define oper2(st, L, R, ks) ((L[ks] == -1 ? 0 : st[L[ks]]) + (R[ks] == -1 ? 0 : st[R[ks]]))
#define oper(a, b) (a+b)
#define NEUT 0
#define INF 1000000007
struct STree { // persistent segment tree for sum over integers
	vector<int> st, L, R; int n,sz,rt;
	STree(int n): st(1,NEUT),L(1,-1),R(1,-1),n(n),rt(0),sz(1){}
	STree(){}
	int new_node(){
		int ids=SZ(st);
		st.pb(NEUT);L.pb(-1);R.pb(-1);
		return ids;
	}
	int upd(int id, int l, int r, int p, int v){
		int ids = (id == -1 ? new_node() : id);
		if(l+1==r){st[ids]+=v;return ids;}
		int m=(l+r)>>1,ps;
		if(p<m)ps=upd(L[ids],l,m,p,v),L[ids]=ps;
		else ps=upd(R[ids],m,r,p,v),R[ids]=ps;
		st[ids]=oper2(st, L, R, ids);
		return ids;
	}
	int query(int id, int l, int r, int a, int b){
		if(r<=a||b<=l||id==-1)return NEUT;
		if(a<=l&&r<=b)return st[id];
		int m=(l+r)>>1;
		return oper(query(L[id],l,m,a,b),query(R[id],m,r,a,b));
	}
	int upd(int p, int v){return rt=upd(rt,0,n,p,v);} // update on last root
	int query(int a, int b){return query(rt,0,n,max(0,a),min(b,INF));}; // sin pasarle la raiz
	//int query(int idRoot,int a, int b){return query(idRoot,0,n,a,b);};
	//int upd(int idRoot, int p, int v){return rt=upd(idRoot,0,n,p,v);}
};

int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	int n, k;  cin>>n>>k; robot r[n];
	FOR(i,0,n) cin>>r[i].x>>r[i].r>>r[i].iq;
	sort(r,r+n);
	
	// compress the iqs
	set<int> s;
	FOR(i,0,n) s.insert(r[i].iq);
	unordered_map<int,int> id; int cnt = 1;
	for(int e: s) id[e] = cnt++;
	
	// two-pinters
	vector<pii> iqs;
	FOR(i,0,n) iqs.pb({ r[i].iq, i });
	sort(ALL(iqs));
	int lPos = 0, rPos = 0;
	FOR(i,0,n){ 
		while( rPos+1<n && iqs[i].F+k>=iqs[rPos+1].F) rPos++;
		while( lPos<n && iqs[i].F-k>iqs[lPos].F) lPos++;
		r[iqs[i].S].idIqL = id[iqs[lPos].F];
		r[iqs[i].S].idIqR = id[iqs[rPos].F];
	}
	
	STree* ST[n+1];
	FOR(i,0,n+1) ST[i] = new STree(1e9+7);
	
	ll ans = 0;
	FOR(i,0,n){
		int L = r[i].idIqL, R = r[i].idIqR;
		int valL = r[i].x-r[i].r, valR = r[i].x+r[i].r; 
		FOR(idIq,L,R+1){
			int val = ST[idIq]->query( valL, valR+1 );
			ans += val;
		} 
		int idIQ = id[r[i].iq];
		ST[idIQ]->upd( r[i].x, 1 );
	}
	cout << ans << '\n';
	
	return 0;
}

/*
4 8
4 100 2
5 100 2
10 100 2
20 100 2

4 8
2 100 2
5 100 5
10 100 10
20 100 20

4 3
2 100 2
2 100 4
2 100 5
2 100 8


*/

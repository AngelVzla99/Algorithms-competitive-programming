// https://codeforces.com/group/gXivUSZQpn/contest/336659/problem/L
// El codigo es una version modificada de STPersistent.cpp
// En este STQ() retorna un nodo correspondiente al rango indicado (no un entero)
// para evitar crear un nodo en cada llamada de STQ se crea una memoria
// Para modificar el codigo:
// Lo que se haga en el constructor de STN se copia y pega en la funcion merge

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
const int MAXN = 1e5+1;

// ST de 1's y 0's
// val = maxima cantidad de 1's consecutivos en el rgo del nodo
struct STN{
    STN *l, *r;
    int val, mxL, mxR, cnt;
    STN(int val) : l(0), r(0), val(val){
		mxL = mxR = val;
		cnt = 1;
	}
    STN(STN *l, STN *r) : l(l), r(r), val(0){
		val = mxL = mxR = 0;
		cnt = l->cnt+r->cnt;
		
        if( l&&r ){
			val = max( val, l->val );
			val = max( val, l->mxR+r->mxL );
			val = max( val, r->val );
			
			mxL = l->mxL;
			if( l->mxL==l->cnt ) mxL += r->mxL;
			
			mxR = r->mxR;
			if( r->mxR==r->cnt ) mxR += l->mxR;
			
		}else if( l&&!r ){
			val = l->val;
			mxL = l->mxL;
			mxR = l->mxR;
		}else if( !l&&r ){
			val = r->val;
			mxL = r->mxL;
			mxR = r->mxR;
		}
    }
    void merge(STN *l, STN *r){
		val = mxL = mxR = 0;
		cnt = l->cnt+r->cnt;
		
        if( l&&r ){
			val = max( val, l->val );
			val = max( val, l->mxR+r->mxL );
			val = max( val, r->val );
			
			mxL = l->mxL;
			if( l->mxL==l->cnt ) mxL += r->mxL;
			
			mxR = r->mxR;
			if( r->mxR==r->cnt ) mxR += l->mxR;
			
		}else if( l&&!r ){
			val = l->val;
			mxL = l->mxL;
			mxR = l->mxR;
		}else if( !l&&r ){
			val = r->val;
			mxL = r->mxL;
			mxR = r->mxR;
		}
	}
};

int N=MAXN, A[MAXN];
STN* memST[4*MAXN];
STN* STB(int l = 0, int r = N, int id = 1){
	memST[id] = new STN(0);
    if(r - l < 2) return new STN(A[l]);
    int m = (l+r)>>1, L = id<<1, R = L|1;
    return new STN(STB(l, m, L), STB(m, r, R));
}
STN* STQ(int x, int y, STN* v, int id=1, int l = 0, int r = N){
    if(x == l && y == r) return v;
    int m = (l+r)>>1, L = id<<1, R = L|1;
    if(x >= m) return STQ(max(x, m), y, v->r, R, m, r);
    if(y <= m) return STQ(x, min(y, m), v->l, L, l, m);
    
    memST[id]->merge( STQ(x, min(y, m), v->l, L, l, m), STQ(max(x, m), y, v->r, R, m, r) );
    return memST[id];
}
STN* STU(int p, int x, STN *v, int l = 0, int r = N){
    if(r - l < 2) return new STN(x);
    int m = (l+r)>>1;
    if(p < m)
        return new STN(STU(p, x, v->l, l, m), v->r);
    else
        return new STN(v->l, STU(p, x, v->r, m, r));
}
void printST( STN *v ){
	FOR(i,1,N) cout << STQ(i,i+1,v)->val << " ";
	cout << endl;
}

STN* ver[MAXN];

int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);

	int n; cin>>n; int h[n+1];
	FOR(i,1,n+1) cin>>h[i];
	
	// quitar repetidos
	set<int> setVals;
	FOR(i,1,n+1) setVals.insert(h[i]);
	vector<int> val(ALL(setVals));
	reverse(ALL(val)); // ordenados de mayor a menor
	N = n+1;
	
	// crear segment tree
	map<int,vector<int>> pos;
	FOR(i,1,n+1) pos[h[i]].pb(i);
	ver[0] = STB(); int cuST = 1;
	for(int v: val){
		ver[cuST] = STU( 0, 0, ver[cuST-1] );
		for(int p: pos[v]){
			ver[cuST] = STU( p, 1, ver[cuST] );
		}
		cuST++;
	}
	
	int q; cin>>q;
	while(q--){
		int L, R, w; cin>>L>>R>>w;
		
		int l = 0, r = SZ(val), mid; // r tiene la respuesta
		while(l+1<r){
			mid = (l+r)/2;
			if( STQ(L,R+1,ver[mid])->val>=w ) r = mid;
			else l = mid;
		}
		cout << val[r-1] << endl;
	}

	return 0;
}

/*

*/

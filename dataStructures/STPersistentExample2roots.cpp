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
const int MOD = 998244353;
const int MAXN = 3e5+2; //////////////////////////////////

#define oper(a,b) a+b
#define NEUT 0
struct STree { // persistent segment tree for min over integers
  vector<int> st, L, R; int n,sz,rt;
  STree(int n): st(1,NEUT),L(1,0),R(1,0),n(n),rt(0),sz(1){}
  int new_node(int v, int l=0, int r=0){
      int ks=SZ(st);
      st.pb(v);L.pb(l);R.pb(r);
      return ks;
  }
  int init(int s, int e, int *a){ // not necessary in most cases
      if(s+1==e)return new_node(a[s]);
      int m=(s+e)/2, l=init(s,m,a),r=init(m,e,a);
      return new_node(oper(st[l],st[r]),l,r);
  }
  int upd(int k, int s, int e, int p, int v){
      int ks=new_node(st[k],L[k],R[k]);
      if(s+1==e){st[ks]=v;return ks;}
      int m=(s+e)/2, ps;
      if(p<m)ps=upd(L[ks],s,m,p,v),L[ks]=ps;
      else ps=upd(R[ks],m,e,p,v),R[ks]=ps;
      st[ks] = oper(st[L[ks]],st[R[ks]]);
      return ks;
  }
  int query(int k, int s, int e, int a, int b){
      if(e<=a||b<=s)return NEUT;
      if(a<=s&&e<=b)return st[k];
      int m=(s+e)/2;
      return oper(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
  }
  int init(int *a){return init(0,n,a);}
  int upd(int k, int p, int v){return rt=upd(k,0,n,p,v);}
  int upd(int p, int v){return upd(rt,p,v);} // update on last root
  int query(int k,int a, int b){return query(k,0,n,a,b);};
}; // usage: STree rmq(n);root=rmq.init(x);new_root=rmq.upd(root,i,v);rmq.query(root,s,e);


struct comp{
	int fa;
	vector<string> var[2];
	vector<int> prop[2];
};
comp C[MAXN];

vector<int> G[MAXN];
int r[MAXN];
STree ST(MAXN);
void makeST( int v ){
	//cout <<"Visito "<< v << " padre " << C[v].fa << " | "<<r[C[v].fa] << endl;
	r[v] = r[C[v].fa];
	
	// se agregan las var al arbol
	FOR(i,0,SZ(C[v].prop[0])){
		//cout <<"=> "<< i << " | "<< SZ(C[v].prop[0]) << " "<< SZ(C[v].prop[1]) << endl;
		int pos = C[v].prop[0][i];
		int val = C[v].prop[1][i];
		//cout <<"Insertare "<< pos << " "<< val << endl;
		r[v] = ST.upd(r[v],pos,val);
	}
	//FOR(i,0,10) cout << ST.query(r[v],i,i+1) << " ";
	//cout << endl;
	//cout <<"=> "<< r[v] << " de "<< v << endl;
	
	for( int u: G[v] ) makeST(u);
}

int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);

	int n; cin>>n;
	FOR(i,1,n+1){
		int p, k; cin>>p>>k;
		G[p].pb(i);
		C[i].fa = p;
		FOR(j,0,k){
			string s; cin>>s;
			int p = -1;
			FOR(z,0,SZ(s)) if(s[z]=='=') p = z;
			string s1 = s.substr(0,p), s2 = s.substr(p+1,SZ(s)-(p+1));
			//cout << s1 <<"|"<<s2 <<endl;
			C[i].var[0].pb(s1);
			C[i].var[1].pb(s2);
		}
	}
	
	map<string,int> posN[2];
	vector<string> varN[2];
	FOR(c,0,2){
		set<string> s;
		FOR(i,1,n+1) for(auto str: C[i].var[c]) s.insert(str);
		varN[c] = vector<string>(ALL(s));
		int p = 1;
		FOR(i,0,SZ(varN[c])) posN[c][varN[c][i]] = p++;
		FOR(i,1,n+1){
			FOR(j,0,SZ(C[i].var[c])){
				int code = posN[c][ C[i].var[c][j] ]; 
				C[i].prop[c].pb( code );
			}
		}
	}
	
	/*
	FOR(i,1,n+1){
		cout <<"==========="<<endl;
		int len = SZ(C[i].var[0]);
		FOR(j,0,len) cout << C[i].prop[0][j] << " "<< C[i].prop[1][j] << endl;
		//FOR(j,0,len) cout << varN[0][C[i].prop[0][j]-1] << " "<< varN[1][C[i].prop[1][j]-1] << endl;
	}
	cout <<"==========="<<endl;
	FOR(i,0,SZ(varN[1])) cout << varN[1][i] << endl;
	*/
	
	makeST(1);
	int q; cin>>q;
	while(q--){
		int c; string key; cin>>c>>key;
		string ans = "N/A";
		
		int pos = posN[0][key];
		if(pos){
			int val = ST.query(r[c],pos,pos+1);
			//cout <<"Se traduce "<< key<< " "<< pos<<" | "<< val <<endl;
			if(val) ans = varN[1][val-1];
		}
		
		cout << ans << '\n';
		cout.flush();
	}

	return 0;
}

/*

*/

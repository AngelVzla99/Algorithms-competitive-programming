// PROBLEM D https://codeforces.com/group/gXivUSZQpn/contest/337359
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
const int MAXN = 600+1;

typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T EPS = 1e-8, inf = 1 / .0;

vector<int> X,Y;
vector<vector<T> > A;
vector<T> b,c;
T z;
int n,m;
void pivot(int x,int y){
	swap(X[y],Y[x]);
	b[x]/=A[x][y];
	FOR(i,0,m)if(i!=y)A[x][i]/=A[x][y];
	A[x][y]=1/A[x][y];
	FOR(i,0,n)if(i!=x&&abs(A[i][y])>EPS){
		b[i]-=A[i][y]*b[x];
		FOR(j,0,m)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
		A[i][y]=-A[i][y]*A[x][y];
	}
	z+=c[y]*b[x];
	FOR(i,0,m)if(i!=y)c[i]-=c[y]*A[x][i];
	c[y]=-c[y]*A[x][y];
}
pair<T,vector<T> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
		vector<vector<T> > _A, vector<T> _b, vector<T> _c){
	// returns pair (maximum value, solution vector)
	A=_A;b=_b;c=_c;
	n=b.size();m=c.size();z=0.;
	X=vector<int>(m);Y=vector<int>(n);
	FOR(i,0,m)X[i]=i;
	FOR(i,0,n)Y[i]=i+m;
	while(1){
		int x=-1,y=-1;
		double mn=-EPS;
		FOR(i,0,n)if(b[i]<mn)mn=b[i],x=i;
		if(x<0)break;
		FOR(i,0,m)if(A[x][i]<-EPS){y=i;break;}
		assert(y>=0); // no solution to Ax<=b
		pivot(x,y);
	}
	while(1){
		T mx=EPS;
		int x=-1,y=-1;
		FOR(i,0,m)if(c[i]>mx)mx=c[i],y=i;
		if(y<0)break;
		T mn=1e200;
		FOR(i,0,n)if(A[i][y]>EPS&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
		assert(x>=0); // c^T x is unbounded
		pivot(x,y);
	}
	vector<T> r(m);
	FOR(i,0,n)if(Y[i]<m)r[Y[i]]=b[i];
	return {z,r};
}


void printM(vector<vector<T>> &A){ // returns determinant
	int n = SZ(A), m = SZ(A[0]);
	FOR(i,0,n){
		FOR(j,0,m) cout << A[i][j] << " ";
		cout << endl;
	}
}


int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);
	freopen("delight.in", "r", stdin); 
	freopen("delight.out", "w", stdout);
	
	int n, k, ms, me; cin>>n>>k>>ms>>me;
	int s[n], e[n];
	FOR(i,0,n) cin>>s[i];
	FOR(i,0,n) cin>>e[i];
	
	// ================ A y b =================
	vd b, x, c;
	vvd A;
	// xi <= 1
	FOR(i,0,n){
		vd temp(n,0.0); temp[i] = 1.0;
		A.pb(temp); b.pb(1.0);
	}
	
	FOR(i,0,n-k+1){
		vd temp(n,0.0);
		FOR(j,i,i+k) temp[j]=1.0;
		// sumInter <= k-me
		A.pb(temp); b.pb(k-me);
		// sumInter >= ms
		FOR(j,i,i+k) temp[j] = -1.0;
		A.pb(temp); b.pb(-ms);
	}
	
	// ======== vectot de costos ===========
	ll SUMA = 0;
	FOR(i,0,n) c.pb(T(s[i]-e[i])), SUMA += e[i];
	
	// ========= solution ===========
	auto ans = simplex(A,b,c);
	cout << ll(ans.F)+SUMA << '\n';
	FOR(i,0,n) cout <<( ans.S[i]>=0.555555555 ? 'S': 'E');
	cout << '\n';
	
    return 0;
}

/*
10 4 1 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1

*/

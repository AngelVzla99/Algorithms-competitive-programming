https://codeforces.com/gym/103202/problem/M

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
const int MAXN = (1<<20);

ll c1[MAXN+9],c2[MAXN+9];  // MAXN must be power of 2 !!
void fht(ll* p, int n, bool inv){
	for(int l=1;2*l<=n;l*=2)for(int i=0;i<n;i+=2*l)FOR(j,0,l){
		ll u=p[i+j],v=p[i+l+j];
		if(!inv)p[i+j]=u+v,p[i+l+j]=u-v; // XOR
		else p[i+j]=(u+v)/2,p[i+l+j]=(u-v)/2;
		//if(!inv)p[i+j]=v,p[i+l+j]=u+v; // AND
		//else p[i+j]=-u+v,p[i+l+j]=u;
		//if(!inv)p[i+j]=u+v,p[i+l+j]=u; // OR
		//else p[i+j]=v,p[i+l+j]=u-v;
	}
}
// like polynomial multiplication, but XORing exponents
// instead of adding them (also ANDing, ORing)
vector<ll> multiply(vector<ll>& p1, vector<ll>& p2){
	int n=1<<(32-__builtin_clz(max(SZ(p1),SZ(p2))-1));
	FOR(i,0,n)c1[i]=0,c2[i]=0;
	FOR(i,0,SZ(p1))c1[i]=p1[i];
	FOR(i,0,SZ(p2))c2[i]=p2[i];
	fht(c1,n,false);fht(c2,n,false);
	FOR(i,0,n)c1[i]*=c2[i];
	fht(c1,n,true);
	return vector<ll>(c1,c1+n);
}

ll n, m, k;

string getStr(int mask){
	string ans = "";
	FOR(i,0,m) ans += char('0'+bool(mask&(1<<i)));
	return ans;
}

int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m>>k;
	
	vector<ll> N(1<<(m));string s;
	FOR(it,0,n){
		cin>>s;
		int mask=0;
		FOR(i,0,m) if(s[i]=='A') mask+=(1<<i);
		N[mask]++;
	}
	
	// Hadamart transformation
	vector<ll> dp = multiply(N,N);
	
	// dp - sum over submask
	FOR(i,0,m){
		FOR(mask,0,(1<<m)){
			if( ( (mask&(1<<i)) )==0 ){
				dp[mask|(1<<i)] += dp[mask];
			}
		}
	}
	FOR(mask,0,(1<<m)) dp[mask] = n*n - dp[mask];
	
	int ans = 0;
	FOR(mask,0,(1<<m)) if( dp[mask] >= 2*k ) ans++;
	cout << ans << '\n';
	
	return 0;
}

/*

*/

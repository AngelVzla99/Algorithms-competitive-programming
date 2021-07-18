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
const int MOD = 1e9+7;
const int MAXN = 5000+1;

int n, a, b;
string s;
int mxPos[MAXN];

vector<int> kmppre(string& t){ // r[i]: longest border of t[0,i)
	vector<int> r(t.size()+1);r[0]=-1;
	int j=-1;
	FOR(i,0,t.size()){
		while(j>=0&&t[i]!=t[j])j=r[j];
		r[i+1]=++j;
	}
	return r;
}
int kmp(string& s, string& t){ // find t in s
	int mxMatch = -1;
	int j=0;vector<int> b=kmppre(t);
	FOR(i,0,s.size()){
		while(j>=0&&s[i]!=t[j])j=b[j];
		mxMatch = max( mxMatch, j+1 );
		if(++j==t.size()) j=b[j];
	}
	return mxMatch;
}

int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin>>n>>a>>b>>s;
	
	mxPos[0] = -1;
	FOR(i,1,n){ 
		string t = s.substr(0,i), P = s.substr(i,n-i);
		//cout << "=> "<< t << " "<<  P << endl;
		int val = kmp(t,P);
		mxPos[i] = (val==-1? -1: i+val);
		//cout <<"pos "<< i << " | " << mxPos[i] << endl;
	}

	int dp[n+1];
	dp[n] = 0;
	ROF(i,n-1,-1){
		dp[i] = a + dp[i+1];
		if( mxPos[i]!=-1 )
			dp[i] = min( dp[i], b+dp[mxPos[i]] );
	}
	cout << dp[0] << '\n';
	
    return 0;
}

/*

*/

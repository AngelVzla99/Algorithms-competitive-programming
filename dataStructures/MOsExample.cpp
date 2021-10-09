// https://codeforces.com/contest/1514/problem/D

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

int N, Q, BLOCK_SIZE, A[MAXN], ans[MAXN];

struct query{
	int l, r, i;
	bool operator<( query q2 ){
		int v1 = l/BLOCK_SIZE, v2 = q2.l/BLOCK_SIZE;
		if( v1!=v2 ) return l<q2.l;
		if(r!=q2.r) return r<q2.r;
		return i<q2.i;
	}
};
query Qs[MAXN];
 
int cnt[MAXN], cntB[MAXN], cntCnt[MAXN];
void add( int val ){
	if( cnt[val] ) cntB[ cnt[val]/BLOCK_SIZE ]--;
	if( cnt[val] ) cntCnt[ cnt[val] ]--;
	cnt[val]++;
	if(cnt[val]) cntB[ cnt[val]/BLOCK_SIZE ]++;
	if( cnt[val] ) cntCnt[ cnt[val] ]++;
	
}
void remove( int val ){
	if( cnt[val] ) cntB[ cnt[val]/BLOCK_SIZE ]--;
	if( cnt[val] ) cntCnt[ cnt[val] ]--;
	cnt[val]--;
	if( cnt[val] ) cntB[ cnt[val]/BLOCK_SIZE ]++;
	if( cnt[val] ) cntCnt[ cnt[val] ]++;
	
}
 
int main(){ 
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin>>N>>Q;
	BLOCK_SIZE = 400;
	FOR(i,1,N+1) cin>>A[i];
	
	FOR(i,0,Q) cin>>Qs[i].l>>Qs[i].r, Qs[i].i = i;
	sort(Qs,Qs+Q);
	
	int mo_l = 1, mo_r = 0; // [mo_left, mo_right]
	FOR(it,0,Q){
		while(mo_r<Qs[it].r) mo_r++, add(A[mo_r]);
        while(mo_r>Qs[it].r) remove(A[mo_r]), mo_r--;
        while(mo_l<Qs[it].l) remove(A[mo_l]), mo_l++;
        while(mo_l>Qs[it].l) mo_l--, add(A[mo_l]);
        
        ROF(i,N/BLOCK_SIZE,-1){
			if( cntB[i] ){
				int mx = 0;
				FOR(j,i*BLOCK_SIZE,(i+1)*BLOCK_SIZE) if( j<=N && cntCnt[j]){
					mx = j;
				}
				int len = Qs[it].r-Qs[it].l+1;
				if( mx<=len/2+len%2 ) ans[ Qs[it].i ] = 1;
				else ans[ Qs[it].i ] = 2*mx-len;
				
				break;
			}
		}
	}
	
	FOR(i,0,Q) cout << ans[i] << '\n';

	return 0;
}

/*
15 5
1 1 2 2 3 3 3 3 3 4 4 5 6 6 6
1 4
5 5
6 15
7 10
2 15

*/

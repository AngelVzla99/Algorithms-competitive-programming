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
const int maxN = 200010; // CAMBIAR ESTE

int n;
ll BIT[maxN];
void updBIT(int p, ll val){
    p++;
    for(; p < n+1; p += p&-p)
    	BIT[p] += val;
    
}
ll sumBIT(int p){
    p++;
    ll ret = 0;
    for(; p; p -= p&-p) 
    	ret += BIT[p];
    return ret;
}

// GJNM
char q[5];
int arr[maxN];

int main(){
	int t = 1;
	bool first = true;
	while(ri(n), n>0){
		if ( first ) 
			first = false;
		else
			printf("\n");
		printf("Case %d:\n",t++ );
		FOR(i,0,maxN)
			BIT[i] = 0;
		FOR(i,0,n){
			ri(arr[i]);
			updBIT(i,arr[i]);
		}
		while(scanf("%s",q), q[0] != 'E'){
			int a,b;
			rii(a,b);
			if ( q[0] == 'M' ){
				printf("%lld\n",sumBIT(b-1)-sumBIT(a-2) ); // query
			}
			else{
				updBIT(a-1,b-arr[a-1]); // update
				arr[a-1] = b;
			}
		}
	}
	return 0;
}
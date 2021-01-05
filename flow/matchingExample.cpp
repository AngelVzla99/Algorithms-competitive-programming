// Problem: C https://codeforces.com/gym/101408/attachments/download/5626/20082009-northwestern-european-regional-contest-nwerc-2008-en.pdf

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <string.h>
#include <math.h>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define _1 first
#define _2 second
#define ALL(s) s.begin(),s.end()

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 998244353 ;//1e9+9;
const ld PI = atan(1.0)*4L;
const int MAXINT = 1e5+1;

int n;
int cap[600][600];
int visited[600];

/* Find an augmenting path from s to t in the flow graph using DFS.
 * Returns amount of flow added.
 */
int augment(int s, int t, int c) {
  if (s == t) return c;
  visited[s] = true;
  for (int x = 0; x < n+2; ++x) {
    if (cap[s][x] && !visited[x]) {
      // If there is capacity to an unvisited node, try to augment that way.
      int add = augment(x, t, min(c, cap[s][x]));
      if (add) {
		// Augmenting path found, update capacities
		cap[s][x] -= add;
		cap[x][s] += add;
		return add;
      }
    }
  }
  return 0;
}

/* Ford-Fulkersons algorithm for finding the maximum flow from s to t.
 * Returns the total maximum flow that could be added.
 */
int max_flow(int s, int t) {
  int totflow = 0, addflow = 0;
  do {
    memset(visited, 0, sizeof(visited));
    addflow = augment(s, t, 1<<28);
    totflow += addflow;
  } while (addflow);
  return totflow;
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);

	int t; cin >> t;
	while(t--){
		int c, d; cin>>c>>d>>n;
		vector<pii> node[2];
		vector<int> lab[2];
		int cu = 0, S = n, T = n+1;

		memset(cap,0,sizeof(cap));
		FOR(i,0,n){
			char cA, cB; int a, b;
			cin >> cA >> a >> cB >> b;
			if(cA=='C') node[0].pb({a,b}), lab[0].pb(cu++);
			else node[1].pb({b,a}), lab[1].pb(cu++);
		}
		
		int C = lab[0].size(), D = lab[1].size();
		
		FOR(i,0,C) cap[S][lab[0][i]]=1;
		FOR(i,0,D) cap[lab[1][i]][T]=1;
		FOR(i,0,C) FOR(j,0,D){
			bool p = node[0][i]._1 == node[1][j]._1;
			bool q = node[0][i]._2 == node[1][j]._2;
			if( p || q ){
				cap[lab[0][i]][lab[1][j]] = 1;
			}
		}
		cout << n - max_flow(S,T) << endl;
	}
	
	return 0; 
}

/*

*/  











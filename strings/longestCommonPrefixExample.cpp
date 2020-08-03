/*
En este problema se pide, dado dos strings, encontrar el substring de ambos
que sea igual y de mayor tamaño, para esto se usa el lcp
Longest common prefix.

Un problema que tambien se resuelve con el LCP es hallar la cantidad de
substrings diferentes, con LCP dada una posicion, tenemos cuantos son
iguales, si el largo del sufijo es len(Suf[i])
=> ans = sum( len(p[i])-LCP[i] ) (1<=i<=n)
*/

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
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define ri(a) scanf("%d",&a)
#define rii(a,b) ri(a),ri(b)
#define riii(a,b,c) rii(a,b),ri(c)
#define lri(a) scanf("%lld",&a)
#define lrii(a,b) lri(a),lri(b)
#define lriii(a,b,c) lrii(a,b),lri(c)
#define pb push_back
#define _1 first
#define _2 second

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1000000007;
const int alphabet = 26;
const int MAXINT = 2e5+1;

void countingSort(vector< pair<pii,int> > &a){
	int n = a.size();

	// Segunda coordenada
	vector< pair<pii,int> > c[n];
	FOR(i,0,n) c[ (a[i]._1)._2 ].pb(a[i]);
	a.clear();
	FOR(i,0,n) for(auto e: c[i]) a.pb(e);

	// Primera coordenada
	FOR(i,0,n) c[i].clear();
	FOR(i,0,n) c[ (a[i]._1)._1 ].pb(a[i]);
	a.clear();
	FOR(i,0,n) for(auto e: c[i]) a.pb(e);
}

vector<int> sortSuf(string s){
	s += '?';
	int n = s.size();
	vector<int> p(n), c(n);

	// 2^k, k == 0
	{
		vector<pair<char,int>> a(n);
		FOR(i,0,n) a[i] = {s[i],i};
		sort(a.begin(),a.end());

		FOR(i,0,n) p[i] = a[i]._2;
		c[p[0]] = 0;
		FOR(i,1,n) c[p[i]] = c[p[i-1]] + (a[i]._1!=a[i-1]._1);
	}

	// 2^k, k > 0
	int k = 0;
	while( (1ll<<k) < n ){
		vector< pair<pii,int> > a(n); //< <ptos Left,ptos Right> ,en pos i > len 2^(k+1)
		FOR(i,0,n) a[i] = { {c[i],c[(i+(1<<k))%n]}, i };
		//sort(a.begin(),a.end()); //O( n*(log(n))² )
		countingSort(a); //O( n*long(n) ) 

		FOR(i,0,n) p[i] = a[i]._2;
		c[p[0]] = 0;
		FOR(i,1,n) c[p[i]] = c[p[i-1]] + (a[i]._1!=a[i-1]._1);
		k++;
	}
	return p;
}

int main() {
	string s1, s2; cin >> s1 >> s2;
	string s = s1; s += '#'; s+=s2;
	vector<int> p = sortSuf(s); // suffixArray

	int n = s.size(), pos[n+2]={};
	FOR(i,0,p.size()) pos[p[i]] = i;

	// Longest common prefix, for sufixs(i,j) = min(lcp[pos[i]], ... ,lcp[pos[j]])
	int lcp[n+1]={}, k = 0;  // lcp[i] = maxPrefix con respecto a i-1 (p[i] y p[i-1])
	FOR(i,0,n) if(pos[i]!=0){
		int pi = pos[i], j = p[pi-1];
		while( k<n && s[i+k]==s[j+k]) k++;
		lcp[pi] = k;
		k = max(0,k-1);
	}

	int ans = 0, mid=s1.size(), id=1;
	FOR(i,1,n+1) if( p[i]<mid && p[i-1]>mid || p[i]>mid && p[i-1]<mid ){
		//cout << lcp[i] << " | " << p[i] << " " << p[i-1] << " | " << s.substr(p[i],n-p[i]) << " " << s.substr(p[i-1],n-p[i-1]) << endl;
		if( lcp[i]>ans ) ans=lcp[i], id=p[i];
		if( lcp[i]>ans ) ans=lcp[i], id=p[i];
	}
	cout << s.substr(id,ans) << endl;

	//cout << "-----------"<<endl; int posi =0;
	//for(int i: p) cout << posi++ << " | "<< lcp[posi] << " | " << i << " => "<< s.substr(i,n-i) << endl;
}
/*

*/  

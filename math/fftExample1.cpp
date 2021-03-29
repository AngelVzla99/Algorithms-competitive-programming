// Problema A del RPC 8 del 2020
// Se tiene 2 strings S y T con 4 letras y se quiere el matching en cada 
// posicion se colocamos T en la posicion i-esima de S

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
#define ri(a) scanf("%d",&a)
#define rii(a,b) ri(a),ri(b)
#define riii(a,b,c) rii(a,b),ri(c)
#define lri(a) scanf("%lld",&a)
#define lrii(a,b) lri(a),lri(b)
#define lriii(a,b,c) lrii(a,b),lri(c)
#define pb push_back
#define _1 first
#define _2 second
#define ALL(s) s.begin(),s.end()
#define SZ(x) int((x).size())

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int alphabet = 26;
const double PI = 3.1415926535;
const int MAXINT = 1<<20;

int N;
const double TAU = 4.0 * acos(0);
struct cd{
	ld x=0, y=0;
	cd(ld x, ld y) : x(x), y(y) {}
	cd(ld z = 0) : x(z), y(0) {}
	cd operator +(cd z) {return cd(x + z.x, y + z.y);}
	cd operator -(cd z) {return cd(x - z.x, y - z.y);}
	cd operator *(cd z) {return cd(x*z.x - y*z.y, y*z.x + x*z.y);}
	cd operator /(ld z) {return cd(x/z, y/z);}
};
void FFT(cd *a, int rev){
	int n = N;
	for(int i = 1, j = 0; i < n; i++){
		int k = n>>1;
		for(; j&k; k>>=1) j^=k;
		j^=k;
		if(i < j) swap(a[i], a[j]);
	}
	for(int s = 2, ds = 1; s <= n; ds = s, s <<= 1){
		ld ang = TAU / s * rev;
		cd wn(cos(ang), sin(ang));
		for(int i = 0; i < n; i += s){
			cd w(1), t;
			for(int j = i; j < i + ds; j++, w = w*wn){
				cd u = a[j], v = a[j+ds] * w;
				a[j] = u + v;
				a[j + ds] = u - v;
			}
		}
	}
	if(rev == -1)
		FOR(i,0,n) a[i] = a[i] / n;
}
void mult(cd *p, cd *q, cd *r){
	FFT(p, 1); FFT(q, 1);
	FOR(i,0,N) r[i] = p[i] * q[i];
	FFT(r, -1);
}

const int MXLEN = 3e5+1;
char s[MXLEN]={}, t[MXLEN]={}; 

int main(){
	vector<char> ALP = { 'T', 'G', 'A', 'C' };
	while( scanf("%s", &s) != EOF ){
		scanf("%s", &t);
		int n = strlen(s), m = strlen(t), ans[n]={}, ans2[m]={}; N = 1;
		while( N <= n+m ) N*=2;

		for(char c: ALP){
			// --------------- TODO LO DE FFT ----------------------
			cd P[N], Q[N], R[N];
			FOR(i,0,n) P[i] = cd( (s[i]==c) );// Polinomios de 1's y 0's
			FOR(i,0,m) Q[i] = cd( (t[m-1-i]==c) );

			mult(P,Q,R); // Se debio usar el comparador con epsilon en vez de round()
			FOR(i,0,n) ans[i] += round(R[ (m-1)+i ].x);

			//-------------------------------------------

			cd P2[N], Q2[N], R2[N];
			FOR(i,0,m) P2[i] = cd( (t[i]==c) );
			FOR(i,0,n) Q2[i] = cd( (s[n-1-i]==c) );

			mult(P2,Q2,R2);
			FOR(i,0,m) ans2[i] += round(R2[ (n-1)+i ].x);
		}
		int p = max_element(ans,ans+n) - ans;
		int p2 = max_element(ans2,ans2+m) - ans2;

		if( ans2[p2]>ans[p] ){
			printf("%d\n", ans2[p2]);
			if(ans2[p2]==0) printf("No matches\n");
			else{
				int i = 0, j = 0;
				while( j<p2 ) cout << t[j++];
				while( j<m && i<n ) cout << (s[i]==t[j]?s[i]:'X'), i++, j++;
				while( i<n ) cout << s[i++];
				printf("\n");
			}
			printf("\n");
		}else{
			cout << "UNOOOOOOOOOOOOO "<<p<<endl;
			printf("%d\n", ans[p]);
			if(ans[p]==0) printf("No matches\n");
			else{
				int i = 0, j = 0;
				while( i<p ) cout << s[i++];
				while( i<n && j<m ) cout << (s[i]==t[j]?s[i]:'X'), i++, j++;
				while( j<m ) cout << t[j++];
				printf("\n");
			}
			printf("\n");
		}

	}
	return 0;
}
/*
TACAACAG
GATTACCA

AAAA
GGGG

ATTG
GCCA

*/  

 

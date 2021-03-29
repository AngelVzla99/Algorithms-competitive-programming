// Problena L del RPC 3 de 2021
// En este problema se tienen 2 arreglos de numeros 'a' y 'b'
// Se quiere saber cuantos match ocurren si se coloca b en la
// posicion i-esima de a
// Tando a como b tienen wildcard que hacen match con quien sea

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
const int MAXN = 4e5+10;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

int N;
const long double TAU = 4.0 * acos(0);
const long double EPS = 1e-8;
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

bool eq(ld a, ld b){ return abs(a-b) < EPS; }

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    // Mapear el input a un arreglo de enteros
    map< pair<char,int>, int > h;
    vector<char> alph = {'n', 's', 'e', 'w'};
    int lenAlpha = 0;
    FOR(i,1,8) for(char c: alph) h[{c,i}] = lenAlpha++;
    h[{'?',0}] = lenAlpha++;
    
	int n, m; cin >> n >> m;
	
	int a[n], b[m];
	// Llenar a
	FOR(i,0,n){
		char c; cin >> c;
		if(c=='?') a[i] = h[{c,0}];
		else{
			int rep; cin>>rep;
			a[i] = h[{c,rep}];
		}
	}
	
	// Llenar b
	FOR(i,0,m){
		char c; cin >> c;
		if(c=='?') b[i] = h[{c,0}];
		else{
			int rep; cin>>rep;
			b[i] = h[{c,rep}];
		}
	}
	
	// ================== FFT a partir de aca =========================
	
	// Len del polinomio resultante y wildcards
	int wc[n]={}; N = 1;
	while( N <= n+m ) N*=2;	
	
	// cuento cantidad de match entre los wildCard '?' en 'a' y 'b' (28)
	cd P[N], Q[N], R[N];
	FOR(i,0,n) P[i] = cd( (a[i]==28) ); // Polinomio de 1's y 0's
	FOR(i,0,m) Q[i] = cd( (b[m-1-i]==28) );
	mult(P,Q,R);
	FOR(i,0,n-m+1) wc[i] = round(R[(m-1)+i].x); // Macth entre ambos '?'
	int sum[n]={}, sum2=0;
	FOR(i,0,n) sum[i] = (a[i]==28) + (i==0? 0: sum[i-1]); // Wildcard en a
	FOR(i,0,m) sum2 += (b[i]==28); // Wildcards en b
	FOR(i,0,n-m+1) wc[i] = sum[i+m-1] - (i==0? 0: sum[i-1]) + sum2 - wc[i];
	
	// Sumar a cada posicion de ans[] los matchs con el resto de letras
	cd A[N], B[N], C[N];
	FOR(i,0,n){
		ld alpha = TAU*ld(a[i])/ld(lenAlpha);
		A[i] = {cosl(alpha),sinl(alpha)};
		if(a[i]==28) A[i] = {0.0, 0.0};
	}
	FOR(i,0,m){
		ld beta = TAU*ld(b[m-1-i])/ld(lenAlpha);
		B[i] = {cosl(beta),-sinl(beta)};
		if(b[m-1-i]==28) B[i] = {0.0, 0.0};
	}
	mult(A,B,C); // Queda la respuesta a partir de C[m-1+i]
	
	// Contar cuantos hacen match completo 
	int cntMatch = 0;
	FOR(i,0,n-m+1){ // MatchRestoDeLetras[i] == m - matchWildCars[i]
		if( eq( C[(m-1)+i].x, m-wc[i]) && eq(C[(m-1)+i].y,0) ) cntMatch++;
	}
	cout << cntMatch << '\n';

    return 0;
}
/*
8 4

n 1 
? 
? 
s 2
?
n 1
s 2
?

s 2
s 2
s 2
n 1

 */


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
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define ri(a) scanf("%d",&a)
#define rii(a,b) ri(a),ri(b)
#define riii(a,b,c) rii(a,b),ri(c)
#define lri(a) scanf("%lld",&a)
#define lrii(a,b) lri(a),lri(b)
#define pb push_back
#define _1 first
#define _2 second

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1000000007;
const int alphabet = 26;
const int MAXINT = 2e5+1;

// ------------ Segment tree --------------
// El arbol se guarda en el vector tree de tamaño 2*n
// Esta indexado desde 0, [0,n-1]
//
// Actualizar una posicion y preguntar la suma en 
// un intervalo se hace en logN

int n;

ll sum(vector<int> &tree, int a, int b){
    a += n; b += n;
    ll s = 0;
    while (a <= b) {
        if (a%2 == 1) s += tree[a++];
        if (b%2 == 0) s += tree[b--];
        a /= 2; b /= 2;
    }
    return s;
}

void add(vector<int> &tree, int k, int x) {
    k += n;
    tree[k] += x;
    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = tree[2*k]+tree[2*k+1];
    }
}

int main(){
    n = 13;

    int a[n];
    for(int i=0; i<n; i++) a[i] = i+1;

    vector<int> tree(2*n,0);
    for(int i=0; i<n; i++) add(tree,i,a[i]);

    int q = 10, l, r;
    while(q--){
        printf("Rango a preguntar [l,r] entre [0,n-1]\n");
        cin >> l >> r;
        cout << "=> "<< sum(tree,l,r) << endl;
    }

    return 0;
}

/*

*/  
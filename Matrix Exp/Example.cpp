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
typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;
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
const int MAXN = 1e5; // CAMBIAR ESTE

// GJNM
struct Matrix {
    long double m[2][2] = {{0, 0}, {0, 0}};

    Matrix operator *(const Matrix &other) {
        Matrix prod;
        FOR(i, 0, 2) FOR(j, 0, 2) FOR(k, 0, 2) {
            prod.m[i][k] += m[i][j] * other.m[j][k];
        }
        return prod;
    }
};

Matrix bin_pow(Matrix x, int k) {
    Matrix prod;
    FOR(i, 0, 2) {
        prod.m[i][i] = 1;
    }
    while (k > 0) {
        if (k & 1) {
            prod = prod * x;
        }
        x = x * x;
        k >>= 1;
    }
    return prod;
}

int main() {
    int n;
    long double p;
    scanf("%d %Lf", &n, &p);
    Matrix x;
    x.m[0][0] = 1 - p;
    x.m[0][1] = p;
    x.m[1][0] = p;
    x.m[1][1] = 1 - p;
    x = bin_pow(x, n);
    printf("%.7Lf\n", x.m[0][0]);
    return 0;
}
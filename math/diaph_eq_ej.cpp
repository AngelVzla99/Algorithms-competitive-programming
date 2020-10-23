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
__int128 abss(__int128 x) {
    if (x < 0)
        return -x;
    return x;
}


__int128 gcd(__int128 a, __int128 b, __int128& x, __int128& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    __int128 x1, y1;
    __int128 d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(__int128 a, __int128 b, __int128 c, __int128 &x0, __int128 &y0, __int128 &g) {
    g = gcd(abss(a), abss(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

int main() {
    __int128 n, p, w, d;
    ll aux_n, aux_p, aux_w, aux_d;
    rll(aux_n, aux_p), rll(aux_w, aux_d);
    n = aux_n, p = aux_p, w = aux_w, d = aux_d;
    //printf("%lld %lld %lld %lld\n", n, p, w, d);
    __int128 x, y, g;
    ll aux_x, aux_y, aux_g;
    if (!find_any_solution(w, d, p, x, y, g)) {
        printf("-1\n");
        return 0;
    }
    // 1244c cf

    aux_x = x, aux_y = y, aux_g = g;
    ll moves = (y / (w / g));
    y -= moves * (w / g);
    x += moves * (d / g);
    if (y < 0) {
        y += w / g;
        x -= d / g;
    }
    aux_x = x, aux_y = y, aux_g = g;

    // x*w + y*d = p && x + y <= n
    if (x + y > n || y < 0 || x < 0) {
        printf("-1\n");
    }
    else {
        printf("%lld %lld %lld\n", aux_x, aux_y, aux_n - aux_x - aux_y );
    }

    return 0;
}
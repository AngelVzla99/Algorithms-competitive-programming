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
#include <array>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
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
#define ms(a,v) memset(a, v, sizeof(a))

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5; // CAMBIAR ESTE

// GJNM
struct SUF_AUT {
    static const int ASZ = 26;
    struct node { int len, link; ll dp; array<int, ASZ> to;};
    vector<node> d = {{}};
    int last;
    void init(string S) {
        last = d[0].len = 0;
        d[0].link = -1;
        d[0].to.fill(0);
        for (auto C : S) {
            int c = C - 'a', v = SZ(d), p = last; // Be careful with mapping char to int
            d.emplace_back();
            d[v].len = d[last].len + 1;
            for (; p > -1 && !d[p].to[c]; p = d[p].link)
                d[p].to[c] = v;
            if (p == -1) {
                d[v].link = 0;
            }
            else {
                int q = d[p].to[c];
                if (d[p].len + 1 == d[q].len) {
                    d[v].link = q;
                }
                else {
                    int qq = SZ(d);
                    d.emplace_back();
                    d[qq].len = d[p].len + 1;
                    d[qq].to = d[q].to;
                    d[qq].link = d[q].link;
                    d[v].link = d[q].link = qq;
                    for (; p > -1 && d[p].to[c] == q; p = d[p].link)
                        d[p].to[c] = qq;
                }
            }
            last = v;
        }
    }

    ll f(int u = 0) {
        if (d[u].dp != 0) return d[u].dp;
        d[u].dp = u != 0;
        FOR(i, 0, ASZ) if (d[u].to[i]) d[u].dp += f(d[u].to[i]);
        return d[u].dp;
    }

    string solve(ll k) {
        string ans;
        int curr = 0;
        while (k) {
            if (curr) --k;
            if (k == 0) break;
            FOR(i, 0, ASZ) if (d[curr].to[i]) {
                int nxt = d[curr].to[i];
                if (d[nxt].dp >= k) {
                    ans.pb(i + 'a');
                    curr = nxt;
                    break;
                }
                else {
                    k -= d[nxt].dp;
                }
            }
        }
        return ans;
    }
};

int main() {
    string s; cin >> s;
    SUF_AUT sa; sa.init(s); sa.f();

    int q; ri(q);
    while (q--) {
        ll k; rl(k);
        cout << sa.solve(k) << endl;
    }
    return 0;
}
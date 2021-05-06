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

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5; // CAMBIAR ESTE
const int MOD = 1e9 + 7;

// GJNM
struct PalTree {
    static const int ASZ = 26;
    struct node {
        array<int, ASZ> to = array<int, ASZ>();
        int len, link, oc = 0; // # occurrences of pal
        int slink = 0, diff = 0;
        array<int, 2> seriesAns;
        node(int _len, int _link) : len(_len), link(_link) {}
    };
    string s = "@"; vector<array<int, 2>> ans = {{0, MOD}};
    vector<node> d = {{0, 1}, { -1, 0}}; // dummy pals of len 0,-1
    int last = 1;
    int getLink(int v) {
        while (s[SZ(s) - d[v].len - 2] != s.back()) v = d[v].link;
        return v;
    }
    void updAns() { // serial path has O(log n) vertices
        ans.pb({MOD, MOD});
        for (int v = last; d[v].len > 0; v = d[v].slink) {
            d[v].seriesAns = ans[SZ(s) - 1 - d[d[v].slink].len - d[v].diff];
            if (d[v].diff == d[d[v].link].diff)
                FOR(i, 0, 2) d[v].seriesAns[i] = min(d[v].seriesAns[i],
                                                     d[d[v].link].seriesAns[i]);
            // start of previous oc of link[v]=start of last oc of v
            FOR(i, 0, 2) ans[SZ(ans) - 1][i] = min(ans[SZ(ans) - 1][i],
                                                   d[v].seriesAns[i ^ 1] + 1);
        }
    }
    void addChar(char C) {
        s += C; int c = C - 'a'; last = getLink(last);
        if (!d[last].to[c]) {
            d.emplace_back(d[last].len + 2, d[getLink(d[last].link)].to[c]);
            d[last].to[c] = SZ(d) - 1;
            //auto& z = d.back(); z.diff = z.len - d[z.link].len;
            //z.slink = z.diff == d[z.link].diff
            //          ? d[z.link].slink : z.link;
        } // max suf with different dif
        last = d[last].to[c]; d[last].oc ++;
        //updAns();
    }
    void numOc() { for (int i = SZ(d) - 1; i >= 2; --i) d[d[i].link].oc += d[i].oc; }
};

int main() {
    string s; cin >> s;
    PalTree pt;
    for (auto c : s) {
        pt.addChar(c);
        printf("%d ", SZ(pt.d) - 2);
    }
    printf("\n");

    return 0;
}
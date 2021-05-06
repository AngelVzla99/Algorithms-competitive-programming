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

// GJNM
struct PalTree {
    static const int ASZ = 26;
    struct node {
        array<int, ASZ> to = array<int, ASZ>();
        int len, link, oc = 0; // # occurrences of pal
        int slink = 0, diff = 0;
        int par, parc;
        int chain_sz = 0;
        array<int, 2> seriesAns;
        node(int _len, int _link) : len(_len), link(_link) {}
    };
    string s = "@"; vector<array<int, 2>> ans = {{0, INF}};
    vector<node> d = {{0, 1}, { -1, 0}}; // dummy pals of len 0,-1
    vi lasts = {1};
    int oc = 0;
    int getLink(int v) {
        while (s[SZ(s) - d[v].len - 2] != s.back()) v = d[v].link;
        return v;
    }
    void addChar(char C) {
        s += C; int c = C - 'a';
        int last = lasts.back();
        last = getLink(last);
        if (!d[last].to[c]) {
            d.emplace_back(d[last].len + 2, d[getLink(d[last].link)].to[c]);
            d[last].to[c] = SZ(d) - 1;
            d[SZ(d) - 1].par = last;
            d[SZ(d) - 1].parc = c;
            d[SZ(d) - 1].chain_sz = d[ d[SZ(d) - 1].link ].chain_sz + 1;
            //auto& z = d.back(); z.diff = z.len - d[z.link].len;
            //z.slink = z.diff == d[z.link].diff
            //          ? d[z.link].slink : z.link;
        } // max suf with different dif
        last = d[last].to[c];
        d[last].oc++;
        oc += d[last].chain_sz;
        lasts.pb(last);
        //updAns();
    }
    void rmChar() {
        s.pop_back();
        int last = lasts.back();
        lasts.pop_back();

        d[last].oc--;
        oc -= d[last].chain_sz;

        if (d[last].oc == 0)
            d[ d[last].par ].to[ d[last].parc ] = 0;
    }
};
int main() {
    int q; ri(q);
    string s; cin >> s;
    PalTree pt;
    for (auto c : s) {
        if (c == '-') pt.rmChar();
        else pt.addChar(c);
        printf("%d ", pt.oc);
    }
    printf("\n");
    return 0;
}
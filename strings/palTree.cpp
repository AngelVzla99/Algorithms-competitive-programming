// https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Heavy/PalTree.h
/**
 * Description: Used infrequently. Palindromic tree computes
    * number of occurrences of each palindrome within string.
    * \texttt{ans[i][0]} stores min even $x$ such that
    * the prefix $s[1..i]$ can be split into exactly $x$
    * palindromes, \texttt{ans[i][1]} does the same for odd $x.$
 * Time: $O(N\sum)$ for addChar, $O(N\log N)$ for updAns
 * Source:
    * http://codeforces.com/blog/entry/13959
    * https://codeforces.com/blog/entry/19193
 * Verification:
    * https://oj.uz/problem/view/APIO14_palindrome
    * http://acm.timus.ru/problem.aspx?space=1&num=2058 (call vector reserve to pass ML)
    * https://codeforces.com/gym/102141/attachments F
 */

struct PalTree {
    static const int ASZ = 26;
    struct node {
        array<int, ASZ> to = array<int, ASZ>();
        int len, link, oc = 0; // # occurrences of pal
        int slink = 0, diff = 0;
        array<int, 2> seriesAns;
        node(int _len, int _link) : len(_len), link(_link) {}
    };
    string s = "@"; vector<array<int, 2>> ans = {{0, INF}};
    vector<node> d = {{0, 1}, { -1, 0}}; // dummy pals of len 0,-1
    int last = 1;
    int getLink(int v) {
        while (s[SZ(s) - d[v].len - 2] != s.back()) v = d[v].link;
        return v;
    }
    void updAns() { // serial path has O(log n) vertices
        ans.pb({INF, INF});
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
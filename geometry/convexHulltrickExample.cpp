// Teoria
// https://codeforces.com/blog/entry/63823
// https://cp-algorithms.com/geometry/convex_hull_trick.html

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
const ll INFLL = 1e18;

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k > o.k; } // Valor min/max >/<
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const ll inf = INFLL;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        //assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

int main() {
    LineContainer CHT; //Convex Hull trick

    // Añadir rectas
    CHT.add(-1,2);
    CHT.add(1,2);
    CHT.add(3,1);
    CHT.add(1,5);

    // Preguntar el valor maximo/minimo de las rectas dado un punto x
    int q = 100, x;
    while(q--){
        cin >> x;
        cout << "=> "<< CHT.query(x) << endl;
    }
}
/*
*/  


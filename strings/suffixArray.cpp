pair<int, int> sf[MAXN];
bool comp(int lhs, int rhs) {return sf[lhs] < sf[rhs];}
vector<int> SuffixArray(string s){
	int n = s.size();
	vector<int> sa(n), r(n);
	FOR(i,0,n) r[i] = s[i];
    for(int m = 1; m < n; m <<= 1){
		FOR(i,0,n) sa[i]=i, sf[i] = make_pair(r[i], i+m<n? r[i+m]:-1);
        stable_sort(sa.begin(), sa.end(), comp);
        r[sa[0]] = 0;
        FOR(i,1,n) r[sa[i]]= sf[sa[i]] != sf[sa[i - 1]] ? i : r[sa[i-1]];
    }
    return sa;
}
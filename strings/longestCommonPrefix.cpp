// Longest common prefix entre un arreglo de strings ordenados
// Dados dos de estos strings sirve para saber cual es el
// prefijo mas largo que comparten
// Longest common prefix, para string(i,j) = min(lcp[i], ... ,lcp[j])

vector<int> LCP(vector<int> sa, string s){ //sa = suffixArray
	int n = sa.size()-1, pos[n+2]={}, k = 0;
	FOR(i,0,sa.size()) pos[sa[i]] = i;
	vector<int> lcp(n+1,0);  // lcp[i] = maxPrefix con respecto a i-1 (sa[i] y sa[i-1])
	FOR(i,0,n) if(pos[i]!=0){
		int pi = pos[i], j = sa[pi-1];
		while( k<n && s[i+k]==s[j+k]) k++;
		lcp[pi] = k;
		k = max(0,k-1);
	}
	return lcp;
}
/*
initMinDiv usa la criba para calcular cual es el minimo primo que divide
a un numero x, este precalculo toma O(n.log(logn)) y luego factoriza en
O(logn) cada numero
*/

// Minimo primo que divide a i
int minDiv[MAXINT];

// sieve
void initMinDiv(int mxINT){ // mxINT = max entero a factorizar
	FOR(i,0,mxINT+1) minDiv[i] = i;
	FOR(i,2,mxINT+1) if(minDiv[i]==i){
		for(int j=2*i; j<mxINT+1; j+=i) minDiv[j] = min(minDiv[j],i);
	}
}

vector<int> factors(int n){
	vector<int> ans;
	while(n>1){
		int p = minDiv[n], j = 0;
		while(n%p==0) n/=p, j++;
		ans.pb(powl(p,j)); // p^j
	}
	return ans;
}
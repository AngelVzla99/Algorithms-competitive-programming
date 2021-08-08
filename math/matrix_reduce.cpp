void reduceMod2(vector<vector<int> >& x){
	int n=x.size(),m=x[0].size();
	int i=0,j=0, mod = 2;
	while(i<n&&j<m){
		int l=i;
		FOR(k,i+1,n)if(x[k][j]>x[l][j])l=k;
		if(x[l][j]==0){j++;continue;}
		if(l!=i){swap(x[i],x[l]);}
		FOR(k,0,n){
			if(k==i)continue;
			for(int l=m-1;l>=j;l--) 
				x[k][l] = (x[k][l] - x[k][j]*x[i][l] + mod)%mod;
		} 
		i++;j++;
	}
}

double EPS = 1e-6;
double reduce(vector<vector<double> >& x){ // returns determinant
	int n=x.size(),m=x[0].size();
	int i=0,j=0;double r=1.;
	while(i<n&&j<m){
		int l=i;
		FOR(k,i+1,n)if(abs(x[k][j])>abs(x[l][j]))l=k;
		if(abs(x[l][j])<EPS){j++;r=0.;continue;}
		if(l!=i){r=-r;swap(x[i],x[l]);}
		r*=x[i][j];
		for(int k=m-1;k>=j;k--)x[i][k]/=x[i][j];
		FOR(k,0,n){
			if(k==i)continue;
			for(int l=m-1;l>=j;l--)x[k][l]-=x[k][j]*x[i][l];
		}
		i++;j++;
	}
	return r;
}

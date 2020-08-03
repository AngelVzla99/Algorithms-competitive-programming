// Permite hacer update de un valor en un rango y permite
// saber la suma en un rango

struct STree{
	vector<int> st,lazy; int n;
	STree(){}
	STree(int n):st(4*n+5,0),lazy(4*n+5,-1),n(n){}
	void push(int k, int s, int e){
		if(lazy[k]<0)return;
		st[k]=(e-s)*lazy[k];
		if(s+1<e){
			lazy[2*k]=lazy[k];
			lazy[2*k+1]=lazy[k];
		}
		lazy[k]=-1;
	}
	void upd(int k, int s, int e, int a, int b, int v){
		push(k,s,e);
		if(s>=b||e<=a)return;
		if(s>=a&&e<=b){
			lazy[k]=v;
			push(k,s,e);return;
		}
		int m=(s+e)/2;
		upd(2*k,s,m,a,b,v);
		upd(2*k+1,m,e,a,b,v);
		st[k]=st[2*k]+st[2*k+1];
	}
	int query(int k, int s, int e, int a, int b){
		if(s>=b||e<=a)return 0;
		push(k,s,e);
		if(s>=a&&e<=b)return st[k];
		int m=(s+e)/2;
		return query(2*k,s,m,a,b)+query(2*k+1,m,e,a,b);
	}
	void upd(int a, int b, int v){upd(1,0,n,a,b,v);} // [a,b)
	int query(int a, int b){return query(1,0,n,a,b);} // [a,b)
};
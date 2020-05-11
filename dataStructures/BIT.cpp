ll BIT[maxN];
// suma de rangos [0,n-1]
void updBIT(int p, ll val){ 
    p++;	// esto es porque el bit esta indexado desde 1
    for(; p < maxN; p += p&-p) // se puede cambiar maxN por n+1 si hace falta mas velocidad
    	BIT[p] += val;
}
ll sumBIT(int p){
    p++;
    ll ret = 0;
    for(; p; p -= p&-p) 
    	ret += BIT[p];
    return ret;
}
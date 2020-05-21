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

// This is equivalent to calculating lower_bound on prefix sums array
// LOGN = log(N)

int bit_search(int v)
{
	int sum = 0;
	int pos = 0;
	
	for(int i=LOGN; i>=0; i--)
	{
		if(pos + (1 << i) < N and sum + BIT[pos + (1 << i)] < v)
		{
			sum += BIT[pos + (1 << i)];
			pos += (1 << i);
		}
	}

	return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
}
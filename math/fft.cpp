// => N debe esr una potendia de 2 mayor a la suma de los 2 polinomios 
// a multiplicar, es decir: while( N <= n+m ) N*=2;	
// => a mult() se le pasan 3 arreglos de tipo cd
// => la respuesta de mult() puede tener problemas de precision, para eso
// se usa la funcion eq, la cual compara 2 valores con un epsilon

int N;
const long double TAU = 4.0 * acos(0);
const long double EPS = 1e-8;
struct cd{
	ld x=0, y=0;
	cd(ld x, ld y) : x(x), y(y) {}
	cd(ld z = 0) : x(z), y(0) {}
	cd operator +(cd z) {return cd(x + z.x, y + z.y);}
	cd operator -(cd z) {return cd(x - z.x, y - z.y);}
	cd operator *(cd z) {return cd(x*z.x - y*z.y, y*z.x + x*z.y);}
	cd operator /(ld z) {return cd(x/z, y/z);}
};
void FFT(cd *a, int rev){
	int n = N;
	for(int i = 1, j = 0; i < n; i++){
		int k = n>>1;
		for(; j&k; k>>=1) j^=k;
		j^=k;
		if(i < j) swap(a[i], a[j]);
	}
	for(int s = 2, ds = 1; s <= n; ds = s, s <<= 1){
		ld ang = TAU / s * rev;
		cd wn(cos(ang), sin(ang));
		for(int i = 0; i < n; i += s){
			cd w(1), t;
			for(int j = i; j < i + ds; j++, w = w*wn){
				cd u = a[j], v = a[j+ds] * w;
				a[j] = u + v;
				a[j + ds] = u - v;
			}
		}
	}
	if(rev == -1)
		FOR(i,0,n) a[i] = a[i] / n;
}
void mult(cd *p, cd *q, cd *r){
	FFT(p, 1); FFT(q, 1);
	FOR(i,0,N) r[i] = p[i] * q[i];
	FFT(r, -1);
}

bool eq(ld a, ld b){ return abs(a-b) < EPS; }

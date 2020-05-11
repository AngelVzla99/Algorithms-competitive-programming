#include <iostream>
#include <cstring>

ll sum(vector<ll> &tree, int a, int b){
    a += n; b += n;
    ll s = 0;
    while (a <= b) {
        if (a%2 == 1) s += tree[a++];
        if (b%2 == 0) s += tree[b--];
        a /= 2; b /= 2;
    }
    return s;
}

void add(vector<ll> &tree, int k, int x) {
    k += n;
    tree[k] += x;
    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = tree[2*k]+tree[2*k+1];
    }
}

// Esta indexado [1,n], el tamaño del arreglo debe ser 2*n, siendo n potencia de 2
int main(){

    return 0;
}


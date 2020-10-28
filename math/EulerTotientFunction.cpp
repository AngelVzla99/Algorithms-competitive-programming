// Euler's totient function,  counts the number of integers 
// between 1 and n inclusive, which are coprime to n

// Complexity O(sqrt(n)) but you can use the sieve of Eratosthenes 
ll phi(ll n) {
    ll result = n;
    for(ll i = 2; i * i <= n; i++) if(n % i == 0){
        while (n % i == 0) n /= i;
        result -= result / i;
    }
    if (n > 1) result -= result / n;
    return result;
}

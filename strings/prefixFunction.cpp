/*
f[i] is the length of the longest proper prefix of the substring 
s[0…i] which is also a suffix of this substring.

si f[10] = 3 => s[1..10] = abc...abc, Son iguales su sufijo y prefijo tamaño 3
*/

vector<int> prefix_function(string s){
    int n = (int)s.length();
    vector<int> pi(n);
    for(int i = 1; i < n; i++){
        int j = pi[i-1];
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
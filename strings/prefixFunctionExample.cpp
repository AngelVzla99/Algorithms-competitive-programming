// Problema: Encontrar las posiciones en que aparece el string s en t, complex O(n)

#include <iostream>
#include <vector>
using namespace std;

#define FOR(i,n,m) for(int i=n; i<m; i++)

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

int main(){
    string s, t;
    cin >> s >> t;    

    string str = s;
    str += '#'; // Caracter que no aparece en t
    str += t;
    int n = s.size();

    vector<int> pf = prefix_function(str);
    FOR(i,n,pf.size()) if(pf[i]==n) cout << i-n-n << " ";
}
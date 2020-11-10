struct pto { 
    ld x, y; 
    bool operator<(pto p){ return x < p.x || (x == p.x && y < p.y);  } 
}; 
 
ld cross_product(pto O, pto A, pto B){ 
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x); 
} 
 
// Returns a list of ptos on the convex hull 
// in counter-clockwise order 
vector<pto> convex_hull(vector<pto> A) { 
    int n = A.size(), k = 0; 
    if(n<=3) return A; 
    vector<pto> ans(2*n); 
    sort(A.begin(), A.end()); // Sort ptos lexicographically 
 
    // Build lower hull 
    for(int i = 0; i < n; ++i){ 
        while(k>=2 && cross_product(ans[k-2], ans[k-1], A[i])<= 0) k--; 
        ans[k++] = A[i]; 
    }  
    // Build upper hull 
    for(size_t i = n - 1, t = k + 1; i > 0; --i){ 
        while(k>=t && cross_product(ans[k-2], ans[k-1], A[i-1])<= 0) k--; 
        ans[k++] = A[i-1]; 
    } 
    // Resize the array to desired size 
    ans.resize(k-1); 
    return ans; 
} 
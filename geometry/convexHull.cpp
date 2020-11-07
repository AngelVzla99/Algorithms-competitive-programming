//stores convex hull of P in S, CCW order
//left must return >=0 to delete collinear points!
void CH(vector<pto>& P, vector<pto> &S){
    S.clear();
    sort(P.begin(), P.end());//first x, then y
    FOR(i,0,P.size()){//lower hull
        while(S.size()>= 2 && S[S.size()-1].left(S[S.size()-2], P[i])) S.pop_back();
        S.pb(P[i]);
    }
    S.pop_back();
    int k=S.size();
    ROF(i,P.size()-1,-1){//upper hull
        while(S.size() >= k+2 && S[S.size()-1].left(S[S.size()-2], P[i])) S.pop_back();
        S.pb(P[i]);
    }
    S.pop_back();
}
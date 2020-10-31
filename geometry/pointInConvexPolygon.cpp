void normalize(vector<pto> &pt){//delete collinear points first!
	//this makes it clockwise:
    if(pt[2].left(pt[0], pt[1])) reverse(pt.begin(), pt.end());
	int n=pt.size(), pi=0;
	FOR(i,0,n)
		if(pt[i].x<pt[pi].x || (pt[i].x==pt[pi].x && pt[i].y<pt[pi].y))
			pi=i;
	vector<pto> shift(n);//puts pi as first point
    FOR(i,0,n) shift[i]=pt[(pi+i)%n];
    pt.swap(shift);
}
bool inPolygon(pto p, const vector<pto> &pt){
	//call normalize first!
	if(p.left(pt[0], pt[1]) || p.left(pt[pt.size()-1], pt[0])) return false;
	int a=1, b=pt.size()-1;
	while(b-a>1){
		int c=(a+b)/2;
		if(!p.left(pt[0], pt[c])) a=c;
		else b=c;
	}
	return !p.left(pt[a], pt[a+1]);
}
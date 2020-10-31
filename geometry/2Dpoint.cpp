struct pto{
    ld x, y;
    pto(ld x=0, ld y=0):x(x),y(y){}
    pto operator+(pto a){return pto(x+a.x, y+a.y);}
    pto operator-(pto a){return pto(x-a.x, y-a.y);}
    pto operator+(ld a){return pto(x+a, y+a);}
    pto operator*(ld a){return pto(x*a, y*a);}
    pto operator/(ld a){return pto(x/a, y/a);}
    //dot product, producto interno:
    ld operator*(pto a){return x*a.x+y*a.y;}
    //module of the cross product or vectorial product:
    //if a is less than 180 clockwise from b, a^b>0
    ld operator^(pto a){return x*a.y-y*a.x;}
    //returns true if this is at the left side of line qr
    bool left(pto q, pto r){return ((q-*this)^(r-*this))>0;}
    bool operator<(const pto &a) const{return x<a.x-EPS || (abs(x-a.x)<EPS && y<a.y-EPS);}
    bool operator==(pto a){return abs(x-a.x)<EPS && abs(y-a.y)<EPS;}
    ld norm(){return sqrt(x*x+y*y);}
    ld norm_sq(){return x*x+y*y;}
};
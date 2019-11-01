#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long int llu;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define mem(a, v) memset(a, v, sizeof(a))
#define PI acos(-1)
#define S(a) scanf("%d",&a)
#define SL(a) scanf("%lld",&a)
#define S2(a, b) scanf("%d%d",&a,&b)
#define nl printf("\n")
const ll mod = 1000000007LL;
const int lmt = 100005;

typedef double coord_t;   
typedef double coord2_t;  

struct Point {
    coord_t x, y;
  
    bool operator <(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

Point enter(coord_t a, coord_t b){
    Point p;
    p.x = a;
    p.y = b;
    return p;
}
vector<Point> P, H;
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
    return (long)(A.x - O.x) * (B.y - O.y) - (long)(A.y - O.y) * (B.x - O.x);
}

void convex_hull()
{
    H.clear();
    int n = P.size(), k = 0;
    H.resize(2*n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k);
}

double dist(double x1, double y1, double x2, double y2){
    double d = y2 - y1;
    d = d*d;
    double e = x2 - x1;
    e = e*e;
    return sqrt(e+d);
}

int main(){
    int n;
    S(n);
    for(int i = 0; i < n; i++){
        double x, y;
        scanf("%lf%lf",&x, &y);
        P.pb(enter(x, y));
    }
    convex_hull();
    double ans = 0;
    for(int i = 1; i < H.size(); i++){
        ans += dist(H[i-1].x, H[i-1].y, H[i].x, H[i].y);
    }
    ll ians = (ll)ans;
    printf("%lld\n",ians);
    return 0;
}
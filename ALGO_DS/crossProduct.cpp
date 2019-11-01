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
#define deb(x) cout<<#x<<" : "<<x<<endl;
#define deb2(x, y) cout<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<endl;
#define deb3(x, y, z) cout<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<" | "<<#z<<" : "<<z<<endl;
#define debv(x) {cout<<#x<<" : "<<endl; for(int ii =0; ii < x.size(); ii++) cout<<x[ii]<<" "; cout<<endl; }
#define debarr(x, xs) {cout<<#x<<" : "<<endl; for(int ii =0; ii < xs; ii++) cout<<x[ii]<<" "; cout<<endl; }
//auto T=clock(); 
//cout<<double(clock()-T)/CLOCKS_PER_SEC<<'\n';
const ll mod = 1000000007LL;
const int lmt = 1000005;

int cross(pair<int, int> A, pair<int, int> B, pair<int, int> C){
    pair<int, int> AB, AC;
    AB.X = B.X - A.X;
    AB.Y = B.Y - A.Y;
    AC.X = C.X - A.X;
    AC.Y = C.Y - A.Y;
    int cross = AB.X * AC.Y - AB.Y * AC.X;
    return cross;
}

int main(){
    int t;
    S(t);
    while(t--) {
        int n;
        S(n);
        vector<pair<int, int> > points;
        for(int i = 0; i < n; i++) {
            int x, y;
            S2(x, y);
            points.pb(mp(x, y));
        }
        int ans = 0;
        for(int i = 1; i < n-1; i++) {
            ans += cross(points[0], points[i], points[i+1]);
        }
        if(ans > 0)
            printf("fight\n");
        else
            printf("run\n");
    }
    return 0;
}
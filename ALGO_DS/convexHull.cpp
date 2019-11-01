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
const int lmt = 100005;

int a[lmt];
vector<pair<int, int> > H;
vector<pair<int, int> > P;

ll cross(pair<int, int> A, pair<int, int> B, pair<int, int> C){
    pair<ll, ll> AB, AC;
    AB.X = B.X - A.X;
    AB.Y = B.Y - A.Y;
    AC.X = C.X - A.X;
    AC.Y = C.Y - A.Y;
    ll cross = AB.X * AC.Y - AB.Y * AC.X;
    return cross;
}

void convex_hull() {
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


int main(){
    int t;
    S(t);
    while(t--) {
        P.clear();
        int n;
        S(n);
        for(int i = 0; i < n; i++) S(a[i]);
        int mini = a[n-1], maxi = a[n-1];
        for(int i = n-2; i >= 0; i--) {
            P.pb(mp(a[i], mini));
            if(mini != maxi)
                P.pb(mp(a[i], maxi));
            mini = min(mini, a[i]);
            maxi = max(maxi, a[i]);
        }

        sort(P.begin(), P.end() );
        P.erase(unique( P.begin(), P.end()), P.end());
        convex_hull();
        // for(int i = 0; i < P.size(); i++)
        //     deb2(P[i].X, P[i].Y);
        // nl;
        // for(int i = 0; i < H.size(); i++)
        //     deb2(H[i].X, H[i].Y);
        ll ans = 0;
        for(int i = 1; i < H.size()-1; i++) {
            ans += abs(cross(H[0], H[i], H[i+1]));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
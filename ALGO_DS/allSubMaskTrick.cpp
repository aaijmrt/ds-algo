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

//////////////////////////////////////////
// DP TRICK FOR ITERATING ALL SUB-MASKS //
//////////////////////////////////////////

const int inf = 1<<30;

int n, m;
int a[20];
int dp1[1<<18 + 5], dp2[1<<18 + 5];

int main(){
    int t;
    S(t);
    while(t--) {
        S2(n, m);
        for(int i = 0; i < (1<<n); i++)
            dp1[i] = dp2[i] = inf;

        for(int i = 0; i < n; i++) {
            S(a[i]);
            dp1[1<<i] = a[i];
        }
        for(int i = 0; i < m; i++) {
            int p, c, mask = 0;
            S2(p, c);
            for(int j = 0; j < c; j++) {
                int x;
                S(x);
                x--;
                mask |= (1<<x);
            }
            dp1[mask] = min(dp1[mask], p);            
        }
        dp2[0] = 0;
        for(int i = (1<<n)-1; i >= 0; i--) {
            for(int j = 0; j < n; j++) {
                if(i&(1<<j))
                    dp1[i ^ (1 << j)] = min(dp1[i ^ (1 << j)], dp1[i]);
            }
        }
        for(int mask = 0; mask < (1<<n); mask++) {
            for(int sub = mask & (mask - 1); ; sub = (sub - 1) & mask) {
                dp2[mask] = min(dp2[mask], dp2[sub] + dp1[mask ^ sub]);
                if(sub == 0) break;
            }
        }

        printf("%d\n", dp2[(1<<n)-1]);
    }
    return 0;
}
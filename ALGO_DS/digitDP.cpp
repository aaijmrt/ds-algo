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
//cout << fixed << setprecision(10) << f(0, 0, 0) << "\n";
const ll mod = 1000000007LL;
const int lmt = 1000005;
 

ll dp[19][2][5][7][9][16][2];
 
char y[100];
int n;

void clean(int n) {
    for(int i = 0; i < n; i++)
        mem(dp[i], -1);
}

ll solve(int i, int lo, int rem5, int rem7, int rem9, int mask, int zero){
    if(i == n) {
        if(zero == 1)
            return 0;
        if((mask&1) && ((rem9%3) == 0))
            return 0;
        if((mask&2) && (rem5 == 0))
            return 0;
        if((mask&4) && (rem7 == 0))
            return 0;
        if((mask&8) && (rem9 == 0))
            return 0;
        return 1LL;
    }
    if(dp[i][lo][rem5][rem7][rem9][mask][zero] > -1) 
        return dp[i][lo][rem5][rem7][rem9][mask][zero];
    ll ans = 0;
    int upto, dig = y[i] - '0';
    if(lo) upto = 9;
    else upto = dig;

    for(int d = 3; d <= upto; d+=2){
        int tmp = 0;
        if(d == 3) tmp = 1;
        if(d == 5) tmp = 2;
        if(d == 7) tmp = 4;
        if(d == 9) tmp = 8;

        ans += solve(i+1, lo||(d < dig), (rem5*10+d)%5, (rem7*10+d)%7, (rem9*10+d)%9, mask|tmp, 0);
    }
    if(zero == 1) {
        int d = 0;
        ans += solve(i+1, lo||(d < dig), rem5, rem7, rem9, mask, 1);
    }
    dp[i][lo][rem5][rem7][rem9][mask][zero] = ans;
    return ans;
}

int main(){
    // freopen("inp.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    // auto T=clock();

    int t;
    S(t);
    while(t--){
        ll a, b, k;
        SL(a);
        SL(b);
        SL(k);

        a--;
        sprintf(y,"%lld",a);
        n = strlen(y);
        clean(n);
        ll already = solve(0, 0, 0, 0, 0, 0, 1);
        ll rank = already + k;
        sprintf(y,"%lld",b);
        n = strlen(y);
        clean(n);
        ll tot = solve(0, 0, 0, 0, 0, 0, 1);

        if(tot < rank) {
            printf("-1\n");
            continue;
        }

        ll lo = a+1, hi = b;

        while(lo < hi) {
            ll mid = (lo + hi)/2;
            sprintf(y,"%lld",mid);
            n = strlen(y);
            clean(n);
            ll cur = solve(0, 0, 0, 0, 0, 0, 1);

            if(rank > cur)
                lo = mid+1;
            else
                hi = mid;
             
        }
        printf("%lld\n",lo);
    }
    // cerr<<double(clock()-T)/CLOCKS_PER_SEC<<'\n';
    return 0;
}
}
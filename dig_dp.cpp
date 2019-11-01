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

bool isprime[205];

bool pre(){
    mem(isprime, true);
    isprime[1] = isprime[0] = false;
    int upto = 200;
    for(int i = 2; i*i <= upto; i++){
        if(isprime[i]){
            for(int j = 2*i; j <= upto; j+=i)
                isprime[j] = false;
        }
    }
}

char y[100];
int n;
int dp[15][110][110][2];
bool flag;
int solve(int i, int sum1, int sum2, int lo){
    if(i == n) {
        if(n&1) swap(sum2, sum1);
        if(sum2 <= sum1) return 0;
        return (sum2-sum1);
    }
    if(dp[i][sum1][sum2][lo] > -1) return dp[i][sum1][sum2][lo];
    int ans = 0;
    int from = 0, upto, dig = y[i] - '0';
    if(flag){
        from = 1;
        flag = false;
    }
    if(lo) upto = 9;
    else upto = dig;
    for(int d = from; d <= upto; d++){
        int s1 = sum1, s2 = sum2;
        if(i&1) s1+=d;
        else s2+=d;
        ans += solve(i+1, s1, s2, lo||(d < dig));
    }
    return dp[i][sum1][sum2][lo] = ans;
}

int main(){
    pre();
    int t;
    S(t);
    while(t--){
        int ans1 = 0, ans2 = 0;
        int a, b;
        S2(a, b);
        a--;
        a=max(0, a);
        sprintf(y,"%d",a);
        int sz = strlen(y);
        for(int i = 1; i <= sz; i++){
            mem(dp, -1);
            int fl = 1;
            if(i == sz) fl = 0;
            n = i;
            flag = true;
            ans1 += solve(0, 0, 0, fl);
        }
        sprintf(y,"%d",b);
        sz = strlen(y);
        for(int i = 1; i <= sz; i++){
            mem(dp, -1);
            int fl = 1;
            if(i == sz) fl = 0;
            n = i;
            flag = true;
            ans2 += solve(0, 0, 0, fl);
        }
        int ans = ans2-ans1;
        printf("%d\n",ans);
    }
    return 0;
}
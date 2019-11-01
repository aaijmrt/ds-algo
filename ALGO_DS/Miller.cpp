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
#define debv(x) {cout<<#x<<" : "<<endl; for(int ii =0; ii < x.size(); ii++) cout<<x[ii]<<" "; cout<<endl; }
#define debarr(x, xs) {cout<<#x<<" : "<<endl; for(int ii =0; ii < xs; ii++) cout<<x[ii]<<" "; cout<<endl; }
const int lmt = 1000005;

long long mod;
int b[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};


inline long long multiply(long long a,long long b){
    a %= mod;
    b %= mod;
    long double res = a;
    res *= b;
    long long c = (long long)(res / mod);
    a *= b;
    a -= c * mod;
    a %= mod;
    if (a < 0) a += mod;
        return a;
}

inline long long power(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1)
            ans=multiply(ans,a);
        a=multiply(a,a);
        b>>=1;
    }
    return ans;
}

inline bool Miller(long long p){
    if(p<2) return false;
    if(p!=2 && !(p&1)) return false;

    for(int i=0;i<25;i++){
        if(p==b[i])return true;
        else if(p%b[i]==0)return false;
    }

    int count = 0;
    long long s=p-1;
    while(!(s&1)){
        s/=2;
        count++; //p-1 = 2^s*d here count is s and d is remaining s
    }

    long long accuracy=40; //increase accuarcy to get more accurate answer
    for(int i=0;i<accuracy;i++){
        long long a=rand()%(p-1)+1;
        mod=p;
        long long x=power(a,s);
        if(x == 1 || x == p-1) continue;
        int flag = 0;
        for(int i = 1; i < count; i++){
            x = multiply(x,x);
            //if(x == 1) return false;
            if(x == p-1){
                flag = 1;
                break;
            }
        }
        if(flag) continue;
        return false;
    }
    return true;
}

int main(){
    ll n;
    int m;
    SL(n);
    S(m);
    while(m--) {
        ll x, y;
        SL(x);
        SL(y);
        ll tmp = n/2LL;
        bool ans = true;
        if((x > tmp) && Miller(x))
            ans = false;
        if((y > tmp) && Miller(y))
            ans = false;
        if((x == 1) || (y ==1))
            ans = false;
        if(x)
        if(ans)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
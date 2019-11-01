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
const int lmt = 1000005;

ll powMOD(ll x, ll y, ll MOD) {
    if(y == 0)
        return 1LL;
    ll ans = powMOD(x, y/2, MOD);
    ans = (ans*ans) % MOD;
    if(y&1LL)
        ans = (ans*x) % MOD;
    return ans;
}

bool v[lmt];
int sp[lmt];

void sieve(){
    mem(v, false);
    for (int i = 2; i < lmt; i += 2) sp[i] = 2;
    for (ll i = 3; i < lmt; i += 2){
        if (!v[i]){
            sp[i] = i;
            for (ll j = i; (j*i) < lmt; j += 2){
                if (!v[j*i])    v[j*i] = true, sp[j*i] = i;
            }
        }
    }
}

ll calPower(ll n, ll MOD) {
    ll ans = 0;
    while(n) {
        ans += n / MOD;
        n /= MOD;
    }
    return ans;
}

ll fact[lmt];

void pre(int p, int MOD) {
    fact[0] = 1LL;
    for(ll i = 1; i <= MOD; i++) {
        if(i % p != 0)
            fact[i] = (fact[i-1]*i) % MOD;
        else
            fact[i] = fact[i-1];
    }
}

ll fun(ll n, ll MOD) {
    ll ans = powMOD(fact[MOD], n/MOD, MOD);
    ans = (ans * fact[n%MOD]) % MOD;
    return ans;
}

ll nFactorial(ll n, ll p, ll MOD) {
    ll ans = 1LL;
    while(n > 0) {
        ans = (ans * fun(n, MOD)) % MOD;
        n /= p;
    }
    return ans;
}


ll nCrPrimePower(ll n, ll r, ll p, ll MOD) {
    pre(p, MOD);
    ll b = calPower(n, p) - calPower(r, p) - calPower(n-r, p);
    ll ans = powMOD(p, b, MOD);
    ll inv = 1LL;

    ans = (ans*nFactorial(n, p, MOD)) % MOD;
    ll denom = (nFactorial(r, p, MOD) * nFactorial(n-r, p, MOD)) % MOD;

    ll phi = (MOD/p) * (p-1);

    ans = (ans * powMOD(denom, phi - 1, MOD)) % MOD;
    return ans;
}

vector<pair<int, int> > fac;
vector<ll> pp;

void factorize(ll n) {
    fac.clear();
    pp.clear();
    while(n > 1) {
        int d = sp[n], c = 0;
        ll pf = 1;
        while(n % d == 0) {
            c++;
            n /= d;
            pf *= (ll)d;
        }
        fac.pb(mp(d, c));
        pp.pb(pf);
    }
}

ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

vector<ll> rem;
vector<ll> modu;

bool linearCongruences(ll &x, ll &M) {
    ll n = rem.size();
    x = 0; M = 1;
    for(int i = 0; i < n; i++) {
        ll a_ = M, b_ = rem[i] - x, m_ = modu[i];
        ll y, t, g = extgcd(a_, m_, y, t);
        if (b_ % g) return false;
        b_ /= g; m_ /= g;
        x += M * (y * b_ % m_);
        M *= m_;
    }
    x = (x + M) % M;
    return true;
}

ll nCr(ll n, ll r, ll m) {
    if(n < r) return 0;
    if(r == 0) return 1LL;

    factorize(m);
    rem.clear();
    modu.clear();
    for(int i = 0; i < fac.size(); i++) {
        ll _rem = nCrPrimePower(n, r, fac[i].X, pp[i]);
        rem.pb(_rem); modu.pb(pp[i]);
    }
    ll ans, tmp;
    bool flag = linearCongruences(ans, tmp);
    return ans;
}


int main(){
    sieve();
    int t;
    S(t);
    while(t--) {
        ll N, k;
        int m;
        SL(N); SL(k); S(m);
        ll n = N/k;
        if(N%k != 0)
            n++;
        else {
            printf("%lld 1\n", n);
            continue;            
        }
        ll _n = abs(N - (k*n) - 1);
        ll _k = n-1;
        ll ans = nCr(_n+_k-1, min(_k, _n-1), m);
        printf("%lld %lld\n", n, ans);
    }
    return 0;
}
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
const int lmt = 200005;

string s;
struct node {
    int next[26], end, pos, neg;
    node() {
        mem(next, -1);
        end = 0, pos = 0, neg = 0;
    }
};

node trie[lmt];
int par[lmt];
char rec[lmt];
int num = 1;

void add(int ty) {
    int cur = 0;
    for(int i = 0; i < s.size(); i++) {

        int tmp = (s[i] - 'a');
        if(ty == 1) trie[cur].pos += 1;
        else trie[cur].neg += 1;
        if(trie[cur].next[tmp] == -1) {
            trie[cur].next[tmp] = num;
            par[num] = cur;
            rec[num] = s[i];
            // deb3(rec[num], num, cur);
            num++;
        }

        cur = trie[cur].next[tmp];
    }
    if(ty == 1) trie[cur].pos += 1;
    else {
        trie[cur].neg += 1;
        trie[cur].end += 1;
    }
}

vector<int> ans;
bool flag = true;

void solve(int cur) {
    // deb3(cur, trie[cur].pos, trie[cur].neg);

    if(trie[cur].pos == 0) {
        ans.push_back(cur);
        return ;
    } else if(trie[cur].end > 0) {
        flag = false;
        return ;
    } else {
        for(int i = 0; i < 26; i++) {
            if((trie[cur].next[i] != -1) && (trie[trie[cur].next[i]].neg > 0))
                solve(trie[cur].next[i]);
        }
    }
}

int main(){
    // freopen("inp.txt", "r", stdin);
    int n;
    S(n);

    par[0] = 0;

    for(int i = 0; i < n; i++) {
        char ch;        
        cin >> ch >> s;
        if(ch == '+')
            add(1);
        else
            add(-1);
    }

    if(trie[0].neg > 0)
        solve(0);

    if(!flag) {
        printf("-1\n");
        return 0;
    }

    printf("%d\n", (int)ans.size());

    for(int i = 0; i < ans.size(); i++) {
        string x = "";
        int cur = ans[i];
        // deb(ans[i]);
        while(cur != 0) {
            x = rec[cur] + x;
            cur = par[cur];
        }
        cout<<x<<"\n";
    }
    return 0;
}
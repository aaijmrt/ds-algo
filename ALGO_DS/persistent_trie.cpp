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

struct node {
	struct node* next[2];
	int cnt;
	node() {
		cnt = 0;
		next[0] = NULL;
		next[1] = NULL;
	}
	node* insert(int idx);
};

map<int, node*> tries;
// map<int, int> par;

node* zero = new node();

vector<int> binaryArray;

void toBinary(int key) {
	binaryArray.clear();
	for(int i = 0; i <= 30; i++) {
		if((1 << i) & key)
			binaryArray.pb(1);
		else
			binaryArray.pb(0);
	}
	reverse(binaryArray.begin(), binaryArray.end());
}

node* node::insert(int idx) {
	if(idx > binaryArray.size())
		return zero;

	node* tmp = new node();
	tmp->cnt = this->cnt + 1;
	for(int i = 0; i < 2; i++) {
		if(binaryArray[idx] == i)
			tmp->next[i] = this->next[i]->insert(idx+1);
		else
			tmp->next[i] = this->next[i];
	}
	return tmp;
}

int max(node* a) {
	int ans = 0, n = binaryArray.size()-1;
	for(int i = n; i >= 0; i--) {
		int num = binaryArray[n-i] ^ 1;
		if (a->next[num]->cnt <= 0) 
			num ^= 1;
		if(num == 1)
			ans += (1<<i);
		a = a->next[num];
	}
	return ans;
}

int min(node* a) {
	int ans = 0, n = binaryArray.size()-1;
	for(int i = n; i >= 0; i--) {
		int num = binaryArray[n-i];
		if (a->next[num]->cnt <= 0) 
			num ^= 1;
		if(num == 1)
			ans += (1<<i);
		a = a->next[num];
	}
	return ans;
}

void print(node* cur, int num, int pos) {
	if(pos == 31) {
		deb(num);
		return;
	}
	for(int i = 0; i < 2; i++) {
		if(cur->next[i]->cnt > 0)
			print(cur->next[i], num + i*(1<<(30-pos)), pos+1);
	}
}

int main(){
	int n, q;
	S2(n, q);
	int r, k;
	S2(r, k);
	// par[r] = 0;
	zero->next[0] = zero->next[1] = zero;
	toBinary(k);
	tries[r] = zero->insert(0);

	for(int i = 1; i < n; i++) {
		int u, v, w;
        S2(u, v);
        S(w);
        // par[u] = v;
        toBinary(w);
      	tries[u] = tries[v]->insert(0);
	}

	// print(tries[r], 0, 0);
	// for(int i = 1; i <= 6; i++) {
	// 	cout<<"node num : "<<i<<endl;
	// 	print(tries[i], 0, 0);
	// }
	int last_ans = 0;

    while(q--) {
        int ty;
        S(ty);
        ty ^= last_ans;
        if(ty == 1) {
            int u, val;
            S2(u, val);
            u ^= last_ans;
            val ^= last_ans;
            toBinary(val);
            int mn = min(tries[u]) ^ val;
            int mx = max(tries[u]) ^ val;
            printf("%d %d\n", mn, mx);
            last_ans = mn ^ mx;
        } else {
            int u, v, val;
            S2(u, v);
            S(val);
            u ^= last_ans;
            v ^= last_ans;
            val ^= last_ans;

            // par[v] = u;
            toBinary(val);
            tries[v] = tries[u]->insert(0);
        }
    }
    return 0;
}
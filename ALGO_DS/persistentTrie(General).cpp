/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * Created By : Vishwas Tripathi 
 * CSE, MNNIT-ALLAHABAD 
 * vishfrnds@gmail.com
 _._._._._._._._._._._._._._._._._._._._._.*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <assert.h>
//#define inp(n) scanf("%d",&n)
#define inp2(n,m) inp(n), inp(m)
#define ins(s) scanf("%s",s);
#define out(n) printf("%d\n",n)

#define chk(a) cout << endl << #a << " : " << a << endl
#define chk2(a,b) cout << endl << #a << " : " << a << "\t" << #b << " : " << b << endl
#define chk3(a,b,c) cout << endl << #a << " : " << a << "\t" << #b << " : " << b << "\t" << #c << " : " << c << endl
#define chk4(a,b,c,d) cout << endl << #a << " : " << a << "\t" << #b << " : " << b << "\t" << #c << " : " << c << "\t" << #d << " : " << d << endl
#define ALPHABET_SIZE 2
#define CHAR_TO_INDEX(c) (c - '0')

using namespace std;
#define getcx getchar_unlocked
short ch,sign;
inline void inp( int &n ) {
        n=0; ch = getcx(); sign = 1;
        while(ch < '0' || ch > '9') { if(ch == '-') sign=-1; ch = getcx(); }
        while(ch >= '0' && ch <= '9') { n = (n << 3) + (n << 1) + ch - '0', ch = getcx(); }
		n = n * sign;
}

struct trie_node {
	int isEndOfWord, count;
	struct trie_node* next[ALPHABET_SIZE];
	trie_node();
	int searchWord(string arr, int pos);
	int insertWord(string arr);
	trie_node* insert(int arr[20], int pos);
	void print(string arr);
};

trie_node* null = new trie_node();	//sentinel node __/\__
trie_node::trie_node()
{
	this->isEndOfWord = 0;
	this->count = 0;
	for(int i = 0; i < ALPHABET_SIZE; i++)
		this->next[i] = NULL;
}

int trie_node::searchWord(string arr, int pos)
{
	int i = pos;
	trie_node* temp;
	temp = this;
	while(arr[i])
	{
		if(temp->next[CHAR_TO_INDEX(arr[i])] == NULL)
		{
			return 0;
		}
		temp = temp->next[CHAR_TO_INDEX(arr[i])];
		i++;
	}
	return temp->isEndOfWord;
}
int trie_node::insertWord(string arr)
{
	int i = 0;
	trie_node* temp;
	temp = this;
	while(arr[i])
	{
		if(temp->next[CHAR_TO_INDEX(arr[i])] == NULL)
		{
			temp->next[CHAR_TO_INDEX(arr[i])] = new trie_node();
		}
		temp = temp->next[CHAR_TO_INDEX(arr[i])];
		i++;
	}
	temp->isEndOfWord++;
	return temp->isEndOfWord;
}
trie_node* trie_node::insert(int arr[20], int pos)
{
	if (pos <= 19) {
		trie_node* temp = new trie_node();
		temp->count = this->count + 1;
		temp->isEndOfWord = this->isEndOfWord;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (CHAR_TO_INDEX(arr[pos]) == i)
				temp->next[i] = this->next[i]->insert(arr, pos + 1);
			else
				temp->next[i] = this->next[i];
		}
		if (arr[pos] == '\0')
			temp->isEndOfWord++;
	//	chk4(pos, arr[pos], temp->count, temp->isEndOfWord);
		return temp;
	}
	return null;
}

void trie_node::print(string arr)
{
	//cout<<"cnt "<<(this->count)<<endl;
	if (this->count == 0) 
		return;
	if (this->isEndOfWord)
		for (int i = 0; i < this->isEndOfWord; i++)
			cout << arr<<endl;
	for (int i = 0; i <ALPHABET_SIZE; i++) {
		arr = arr + (char)(i + '0');
		this->next[i]->print(arr);
		arr.erase(arr.length() - 1);
	}
}
void toBinary(int x, int ans[20])
{
	for (int i = 0; i < 19; i++) {
		ans[18 - i] = ((x & 1) + '0');
		x >>= 1;
	}
	ans[19] = '\0';	
	for(int i = 0; i <= 18; i++)
		cout<<ans[i]<<" ";
}
int toInt(int arr[20])
{
	int ans = 0;
	for (int i = 19 - 1, x = 1; i >= 0; i--, x <<= 1)
		if (arr[i] - '0')
			ans += x;
	return ans;

}

int query_xor(trie_node* a, trie_node *b, int arr[20])
{
	int ans[20];
	for (int i = 0; i < 19 ; i++) {
		int num = (arr[i] - '0') ^ 1;
//		chk2(b->next[num]->count , a->next[num]->count); 
		if (a->next[num]->count - b->next[num]->count  <= 0) 
			num ^= 1;
		ans[i]  = num + '0';

		b = b->next[num];
		a = a->next[num];
	}
	ans[19] = '\0';
//	cout << arr<< endl<<ans<<endl;
	return toInt(ans);
}
	
int query_rank(trie_node* a, trie_node *b, int arr[20])
{
	int ans = 0;
	for (int i = 0; i < 19 ; i++) {
		int num = (arr[i] - '0');
		int r = a->next[0]->count - b->next[0]->count;
		if (num == 1) {
			ans += r;
		}
	//	chk4(b->next[num]->count , a->next[num]->count, ans, arr[i] - '0'); 
		b = b->next[num];
		a = a->next[num];
	}
	ans += a->isEndOfWord - b->isEndOfWord;
	//cout << arr<< endl<<ans<<endl;
	return ans;

}
int query_select(trie_node* a, trie_node *b, int k)
{
	int ans[20];
	for (int i = 0; i < 19 ; i++) {
		int r = a->next[0]->count - b->next[0]->count, num;
		if (k <= r) {
			ans[i]  = '0';
			num = 0;
		}
		else {
			ans[i]  = '1';
			num = 1;
			k -= r;
		}
//		chk2(b->next[num]->count , a->next[num]->count); 
		b = b->next[num];
		a = a->next[num];
	}
	ans[19] = '\0';
//	assert(a->isEndOfWord - b->isEndOfWord > 0);
//	cout << arr<< endl<<ans<<endl;
	return toInt(ans);
}
int main()
{

	int t, m, k, l, r, x, ch, cur = 0, bin[20];
	toBinary(6, bin);
	inp(m);
	trie_node* root[m];
	int arr[m];
	for (int i = 0; i < ALPHABET_SIZE; i++)
		null->next[i] = null;
	while (m--) {
		inp(ch);
		if (ch == 0) {
			inp(x);
			toBinary(x, bin);
			root[cur] = (cur == 0 ? null : root[cur-1])->insert(bin, 0);
		//	chk(cur);
		//	root[cur]->print("");
			arr[cur++] = x;

		}
		else if (ch == 1) {
			inp2(l, r);
			l--;
			r--;
			inp(x);
			toBinary(x, bin);
			out(query_xor(root[r], (l == 0 ? null:root[l - 1]), bin));
		}
		else if (ch == 2) {
			inp(k);
			cur -= k;
			/*
			for (int i = 0; i < k; i++) {
				cur--;
				free(root[cur]);
			}*/
		}
		else if (ch == 3) {
			inp2(l, r);
			inp(x);
			l--;
			r--;

			toBinary(x, bin);
			out(query_rank(root[r], (l == 0 ? null:root[l - 1]),  bin));
		}	
		else if (ch == 4) {
			inp2(l, r);
			l--;
			r--;
			inp(k);
			out(query_select(root[r], (l == 0 ? null:root[l - 1]), k));
		}
	}
//	cout<<root[cur - 1]->count << " "<<cur;
    return 0;
}

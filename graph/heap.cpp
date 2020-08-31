#include <bits/stdc++.h>
using namespace std;

vector<int> maxHeap;


void maxHeapify(int i, int n) {
	int left = 2*i + 1;
	int right = 2*i + 2; 

	int large = i;
	if (left < n && maxHeap[large] < maxHeap[left]) 
		large = left;
	if (right < n && maxHeap[large] < maxHeap[right])
		large = right;

	if (large != i) {
		swap(maxHeap[large], maxHeap[i]);
		maxHeapify(large, n);
	}
}


int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		maxHeap.push_back(x);
	}

	for(int i = n/2; i >= 0; i--) {
        maxHeapify(i, n);
    }

    for (int i = 0; i < n; i++) {
    	cout << maxHeap[i] << endl;
    }
}
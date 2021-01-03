#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<bool, int> P;

const vector<int> block_mem_size = { 70, 200, 100, 200, 70 };
const vector<P> request_seq = {
	P(true, 130),
	P(true, 60),
	P(true, 100),
	P(false, 60),
	P(true, 200),
	P(false, 100),
	P(false, 130),
	P(true, 140),
	P(true, 60),
	P(true, 50),
	P(true, 60)
};

struct block {
	int mem_size;
	block* next_block;
};

block* init(string mode) {
	vector<int> tmp;
	for (auto it : block_mem_size) tmp.push_back(it);

	if (mode == "BF") {
		sort(tmp.begin(), tmp.end());
	}

	reverse(tmp.begin(), tmp.end());

	block* head = NULL;
	block* last = NULL;

	for (auto it : tmp) {
		head = new block;
		head->mem_size = it;
		head->next_block = last;
		last = head;
	}

	return head;
}

int main() {
	/*
	block* head = init("BF");
	while (head != NULL) {
		cout << head->mem_size << endl;
		head = head->next_block;
	}
	*/
	

	return 0;
}
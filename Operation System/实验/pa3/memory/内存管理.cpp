#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

struct req_work {
	int id;
	bool is_request;
	int mem_size;
};

const vector<int> block_mem_size = { 70, 200, 100, 200, 70 };
const vector<req_work> request_seq = {
	{1, true, 130},
	{2, true, 60},
	{3, true, 100},
	{2, false, 60},
	{4, true, 200},
	{3, false, 100},
	{1, false, 130},
	{5, true, 140},
	{6, true, 60},
	{7, true, 50},
	{8, true, 60}
};

struct block {
	int mem_size;
	block* next_block;
};

map<int, block*> work_block_addr;

void print_mode(string mode) {
	printf("-----------%s�㷨-----------\n", mode.c_str());
	printf("\n");
}

void print_req(req_work req) {
	printf("��ǰ��ҵ����:\n");
	printf("��ҵ%d ����:%s �����ڴ��С:%dKB\n", 
		req.id, req.is_request ? "����" : "�ͷ�",
		req.mem_size);

	printf("\n");
}

void print_link(block* head) {
	printf("-----�����ڴ���������-----\n");
	int pos = 1;
	for (block* now = head; now; now = now->next_block, pos++) {
		printf("����%d: ʣ���ڴ�ռ�:%dKB\n", pos, now->mem_size);
	}
	printf("\n");
}

void print_is_req_succ(req_work req, bool ok, int pos) {
	printf("��ҵ%d�����ڴ�%s! ���������:%d\n", req.id, 
		ok ? "�ɹ�" : "ʧ��", pos);
	printf("\n");
}

void print_release(req_work req) {
	printf("��ҵ%d�ͷ��ڴ�%dKB\n", req.id, req.mem_size);
	printf("\n");
}

block* init(string mode) {
	work_block_addr.clear();

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

void run(string mode) {
	print_mode(mode);

	block* head = init(mode);

	print_link(head);

	for (auto req : request_seq) {
		print_req(req);

		int id = req.id;
		int mem = req.mem_size;
		bool is_req = req.is_request;

		bool ok = false;
		int pos = 1;

		if (is_req) {
			for (block* now = head; now; now = now->next_block, pos++) {
				if (mem <= now->mem_size) {
					now->mem_size -= mem;
					work_block_addr[id] = now;
					ok = true;
					break;
				}
			}
			print_is_req_succ(req, ok, pos);
		}
		else {
			work_block_addr[id]->mem_size += mem;
			print_release(req);
		}

		print_link(head);
	}
}

int main() {
	
	run("FF");
	run("BF");

	return 0;
}

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
const vector<req_work> request_seq = {   //作业请求
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

//作业对应分区的地址
map<int, block*> work_block_addr;

//输出模式
void print_mode(string mode) {
	printf("-----------%s算法-----------\n", mode.c_str());
	printf("\n");
}

//输出请求
void print_req(req_work req) {
	printf("当前作业请求:\n");
	printf("作业%d 操作:%s 请求内存大小:%dKB\n", 
		req.id, req.is_request ? "申请" : "释放",
		req.mem_size);

	printf("\n");
}

//输出空闲分区链情况
void print_link(block* head) {
	printf("-----空闲内存分区链情况-----\n");
	int pos = 1;
	for (block* now = head; now; now = now->next_block, pos++) {
		printf("分区%d: 剩余内存空间:%dKB\n", pos, now->mem_size);
	}
	printf("\n");
}

//输出作业请求是否成功
void print_is_req_succ(req_work req, bool ok, int pos) {
	printf("作业%d申请内存%s! 分配分区号:%d\n", req.id, 
		ok ? "成功" : "失败", pos);
	printf("\n");
}

//输出作业内存释放信息
void print_release(req_work req) {
	printf("作业%d释放内存%dKB\n", req.id, req.mem_size);
	printf("\n");
}

//初始化
block* init(string mode) {
	work_block_addr.clear();

	//对分区大小进行处理
	vector<int> tmp;
	for (auto it : block_mem_size) tmp.push_back(it);
	if (mode == "BF") {
		sort(tmp.begin(), tmp.end());
	}

	//反转, 目的是从链头开始是按正常顺序的
	reverse(tmp.begin(), tmp.end());  

	block* head = NULL;
	block* last = NULL;

	//建立空闲分区链
	for (auto it : tmp) {
		head = new block;
		head->mem_size = it;
		head->next_block = last;
		last = head;
	}

	return head;
}

//执行调度
void run(string mode) {
	print_mode(mode);

	//获得空闲分区链头
	block* head = init(mode);

	print_link(head);

	//处理请求
	for (auto req : request_seq) {
		print_req(req);

		int id = req.id;
		int mem = req.mem_size;
		bool is_req = req.is_request;

		bool ok = false;  //请求是否成功
		int pos = 1;      //分区号

		if (is_req) {
			//从分区链中寻找合适的分区分配内存
			for (block* now = head; now; now = now->next_block, pos++) {
				if (mem <= now->mem_size) {
					now->mem_size -= mem;
					work_block_addr[id] = now;  //记录该作业对应的分区地址
					ok = true;
					break;
				}
			}
			print_is_req_succ(req, ok, pos);
		}
		else {
			//释放内存
			work_block_addr[id]->mem_size += mem;
			print_release(req);
		}

		print_link(head);
	}
}

int main() {
	
	run("FF");   //首次适应算法
	run("BF");   //最佳适应算法

	return 0;
}

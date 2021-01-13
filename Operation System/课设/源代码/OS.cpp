#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <Windows.h>
#include <algorithm>
using namespace std;

struct block {
	int block_id;        //分区号
	int memory_size;     //分区大小
	block* next_block;   //下一个分区地址
};						 
						 
block* block_head;       //空闲分区链头
						 
struct PCB {			 
	int proc_id;         //进程号  
	int job_id;          //作业号
	int memory_size;     //内存大小
	int total_time;      //总运行时间
	int need_time;       //剩下需要运行时间
	int left_unit_time;  //时间片剩余时间
	block* addr;         //分区块地址
};						 

struct JCB {
	int job_id;          //作业号
	int arrive_time;     //到达时间点
	int finish_time;     //完成时间点
	PCB* proc;           //作业进程
};

bool cmp(JCB* a, JCB* b) {
	return a->arrive_time < b->arrive_time;
}

list<JCB*> job_seq;         //作业序列
list<JCB*> job_waiting_que;      //作业就绪队列
list<JCB*> job_running_que;      //作业运行队列
list<JCB*> job_finished_que;     //作业完成队列
							     
list<PCB*> proc_waiting_que;     //进程就绪队列
list<PCB*> proc_finished_que;    //进程完成队列
PCB* running_proc;			     //正在运行的进程

int total_job_cnt = 10;  //总作业数  
int unit_time = 2;       //时间片大小

int max_running_job_cnt = 5;     //最大运行作业数  
int max_rand_memory_size = 100;  //最大单个进程内存大小
int max_rand_arrive_time = 10;   //最大到达时间点
int max_rand_proc_time = 6;      //最大进程运行时间

int now_time;        //当前时间点

const vector<int> block_memory_size = {
	100, 200, 300, 200, 100, 100
};

//输出错误信息
void print_error(string msg) {
	cerr << msg << endl;
	assert(0);
}

//输出当前消息
void print_msg(string msg) {
	cerr << msg << endl;
}

//输出空闲分区链情况
void print_memory_link() {
	printf("-----空闲内存分区链情况-----\n");
	int pos = 1;
	for (block* now = block_head; now; now = now->next_block, pos++) {
		printf("分区%d: 剩余内存空间: %dKB\n", pos, now->memory_size);
	}
	printf("\n");
}

//输出作业序列
void print_job_seq() {
	printf("--------作业序列情况--------\n");
	for (auto job : job_seq) {
		printf("作业号:%d 作业到达时间: %d\n", job->job_id, job->arrive_time);
	}
	printf("\n");
}

//输出初始信息
void print_init() {
	printf("----------初始信息----------\n");
	printf("总作业数: %d\n", total_job_cnt);
	printf("时间片大小: %d\n", unit_time);
	printf("最大运行作业数: %d\n", max_running_job_cnt);
	printf("最大单个进程内存大小: %dKB\n", max_rand_memory_size);
	printf("最大到达时间点: %d\n", max_rand_arrive_time);
	printf("最大进程运行时间: %d\n", max_rand_proc_time);
	printf("\n");
	print_job_seq();
}

//输出作业后备队列
void print_job_waiting_que() {
	printf("------作业后备队列情况------\n");
	for (auto job : job_waiting_que) {
		printf("作业%d 到达时间: %d\n", job->job_id, job->arrive_time);
	}
	printf("\n");
}

//输出作业运行队列
void print_job_running_que() {
	printf("------作业运行队列情况------\n");
	for (auto job : job_running_que) {
		printf("作业%d 进程号: %d\n", job->job_id, job->proc->proc_id);
	}
	printf("\n");
}

//输出作业完成队列
void print_job_finished_que() {
	printf("------作业完成队列情况------\n");
	for (auto job : job_finished_que) {
		printf("作业%d 完成时间点: %d\n", job->job_id, job->finish_time);
	}
	printf("\n");
}

//输出进程等待队列
void print_proc_waiting_que() {
	printf("------进程等待队列情况------\n");
	for (auto proc : proc_waiting_que) {
		printf("进程%d 所属作业号: %d\n", proc->proc_id, proc->job_id);
	}
	printf("\n");
}

//输出正在运行进程
void print_running_proc() {
	printf("------正在运行进程情况------\n");
	printf("进程号: %d\n", running_proc->proc_id);
	printf("所属作业号: %d\n", running_proc->job_id);
	printf("使用内存所在分区: %d\n", running_proc->addr->block_id);
	printf("内存占用大小: %d\n", running_proc->memory_size);
	printf("剩余需要时间: %d\n", running_proc->need_time);
	printf("剩余时间片大小: %d\n", running_proc->left_unit_time);
	printf("\n");
}

//输出进程完成队列
void print_proc_finished_que() {
	printf("------进程完成队列情况------\n");
	for (auto proc : proc_finished_que) {
		printf("进程%d 所属作业号:%d 总花费时间:%d 内存占用大小:%dKB\n", 
			proc->proc_id, proc->job_id, proc->total_time, proc->memory_size);
	}
	printf("\n");
}

//分配内存
block* assign_memory(int memory_size) {
	for (block* now = block_head; now != NULL; now = now->next_block) {
		if (memory_size <= now->memory_size) {
			now->memory_size -= memory_size;
			return now;
		}
	}
	print_error("内存不足, 分配内存失败!");
	return NULL;
}

//回收内存
void back_memory(block* addr, int memory_size) {
	if (addr == NULL) {
		print_error("归还分区地址为空!");
		return;
	}
	addr->memory_size += memory_size;
}

//生成进程
PCB* generate_proc(JCB* job) {
	PCB* proc = new PCB;

	proc->job_id = job->job_id;
	proc->proc_id = job->job_id;
	proc->memory_size = rand() % max_rand_memory_size + 1;
	proc->total_time = rand() % max_rand_proc_time + 1;
	proc->need_time = proc->total_time;
	proc->addr = assign_memory(proc->memory_size);
	proc->left_unit_time = 0;

	return proc;
}

//进程调度
void run_proc() {
	//从就绪队列中取出进程
	if (running_proc == NULL) {
		if (proc_waiting_que.size() == 0) return;

		running_proc = proc_waiting_que.front();
		proc_waiting_que.remove(running_proc);

		//分配时间片
		running_proc->left_unit_time = unit_time;

		print_msg("从就绪队列中取出进程:");
		print_running_proc();

		return;
	}

	//进程剩余时间减少
	running_proc->left_unit_time--;
	running_proc->need_time--;

	print_msg("程序正在运行...");
	print_running_proc();

	//进程运行结束
	if (running_proc->need_time == 0) {
		proc_finished_que.push_back(running_proc);
		print_msg("该进程运行结束!");
		print_proc_finished_que();

		back_memory(running_proc->addr, running_proc->memory_size);
		print_msg("释放内存:");
		print_memory_link();

		running_proc = NULL;
		return;
	}

	//时间片用完
	if (running_proc->left_unit_time == 0) {
		proc_waiting_que.push_back(running_proc);
		print_msg("该进程时间片用完!");
		print_proc_waiting_que();

		running_proc = NULL;
		return;
	}
}

//作业调度
void run_job() {
	//记录到达作业
	vector<JCB*> job_list;
	for (auto job : job_seq) {
		if (job->arrive_time == now_time) {
			job_list.push_back(job);
		}
	}
	
	//取出到达作业, 放到就绪队列
	if(job_list.size()) print_msg("取出到达作业, 放到就绪队列中...");
	for (auto job : job_list) job_seq.remove(job);
	for (auto job : job_list) job_waiting_que.push_back(job);

	print_job_waiting_que();

	//从就绪队列取出作业, 放到运行队列
	job_list.clear();
	for (auto job : job_waiting_que) {
		if (job_running_que.size() == 
			max_running_job_cnt) break;

		job->proc = generate_proc(job);

		printf("作业号:%d 创建进程并分配内存:\n", job->job_id);
		printf("分配成功! 分配了空间: %dKB\n", job->proc->memory_size);
		print_memory_link();
		
		job_list.push_back(job);
		proc_waiting_que.push_back(job->proc);
	}
	for (auto job : job_list) job_waiting_que.remove(job);
	for (auto job : job_list) job_running_que.push_back(job);

	if (job_list.size()) {
		print_msg("从就绪队列取出作业, 放到运行队列中...");
		print_job_waiting_que();
	}

	print_job_running_que();

	run_proc();

	//结束的作业
	JCB* end_job = NULL;
	for (auto job : job_running_que) {
		if (job->proc->need_time == 0) {
			end_job = job;
			break;
		}
	}

	if (end_job != NULL) {
		printf("结束了作业%d!\n", end_job->job_id);
		end_job->finish_time = now_time;
		job_running_que.remove(end_job);
		job_finished_que.push_back(end_job);
		print_job_finished_que();
	}
}

void init() {
	//初始化空闲分区链
	block* last_block = NULL;
	int block_id = 0;
	for (auto memory_size : block_memory_size) {
		block_head = new block;

		block_head->block_id = block_id++;
		block_head->memory_size = memory_size;
		block_head->next_block = last_block;

		last_block = block_head;
	}

	//初始化作业
	vector<JCB*> tmp_job_seq;
	for (int jid = 0; jid < total_job_cnt; jid++) {
		JCB* job = new JCB;
		job->job_id = jid;
		job->arrive_time = rand() % max_rand_arrive_time;
		tmp_job_seq.push_back(job);
	}
	sort(tmp_job_seq.begin(), tmp_job_seq.end(), cmp);
	for (auto job : tmp_job_seq) job_seq.push_back(job);
	
	//初始化进程
	running_proc = NULL;

	print_init();
}

void run() {
	now_time = 0;
	while (1) {
		printf("--------时间点:%2d--------\n\n", now_time);

		if (!job_waiting_que.size() &&
			!job_running_que.size() &&
			!job_seq.size() ) break;

		run_job();
		now_time++;
	}
}

int main() {
	srand(time(0));

	init();    //初始化
	run();     //开始运行

	return 0;
}

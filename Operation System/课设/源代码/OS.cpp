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
	int block_id;        //������
	int memory_size;     //������С
	block* next_block;   //��һ��������ַ
};						 
						 
block* block_head;       //���з�����ͷ
						 
struct PCB {			 
	int proc_id;         //���̺�  
	int job_id;          //��ҵ��
	int memory_size;     //�ڴ��С
	int total_time;      //������ʱ��
	int need_time;       //ʣ����Ҫ����ʱ��
	int left_unit_time;  //ʱ��Ƭʣ��ʱ��
	block* addr;         //�������ַ
};						 

struct JCB {
	int job_id;          //��ҵ��
	int arrive_time;     //����ʱ���
	int finish_time;     //���ʱ���
	PCB* proc;           //��ҵ����
};

bool cmp(JCB* a, JCB* b) {
	return a->arrive_time < b->arrive_time;
}

list<JCB*> job_seq;         //��ҵ����
list<JCB*> job_waiting_que;      //��ҵ��������
list<JCB*> job_running_que;      //��ҵ���ж���
list<JCB*> job_finished_que;     //��ҵ��ɶ���
							     
list<PCB*> proc_waiting_que;     //���̾�������
list<PCB*> proc_finished_que;    //������ɶ���
PCB* running_proc;			     //�������еĽ���

int total_job_cnt = 10;  //����ҵ��  
int unit_time = 2;       //ʱ��Ƭ��С

int max_running_job_cnt = 5;     //���������ҵ��  
int max_rand_memory_size = 100;  //��󵥸������ڴ��С
int max_rand_arrive_time = 10;   //��󵽴�ʱ���
int max_rand_proc_time = 6;      //����������ʱ��

int now_time;        //��ǰʱ���

const vector<int> block_memory_size = {
	100, 200, 300, 200, 100, 100
};

//���������Ϣ
void print_error(string msg) {
	cerr << msg << endl;
	assert(0);
}

//�����ǰ��Ϣ
void print_msg(string msg) {
	cerr << msg << endl;
}

//������з��������
void print_memory_link() {
	printf("-----�����ڴ���������-----\n");
	int pos = 1;
	for (block* now = block_head; now; now = now->next_block, pos++) {
		printf("����%d: ʣ���ڴ�ռ�: %dKB\n", pos, now->memory_size);
	}
	printf("\n");
}

//�����ҵ����
void print_job_seq() {
	printf("--------��ҵ�������--------\n");
	for (auto job : job_seq) {
		printf("��ҵ��:%d ��ҵ����ʱ��: %d\n", job->job_id, job->arrive_time);
	}
	printf("\n");
}

//�����ʼ��Ϣ
void print_init() {
	printf("----------��ʼ��Ϣ----------\n");
	printf("����ҵ��: %d\n", total_job_cnt);
	printf("ʱ��Ƭ��С: %d\n", unit_time);
	printf("���������ҵ��: %d\n", max_running_job_cnt);
	printf("��󵥸������ڴ��С: %dKB\n", max_rand_memory_size);
	printf("��󵽴�ʱ���: %d\n", max_rand_arrive_time);
	printf("����������ʱ��: %d\n", max_rand_proc_time);
	printf("\n");
	print_job_seq();
}

//�����ҵ�󱸶���
void print_job_waiting_que() {
	printf("------��ҵ�󱸶������------\n");
	for (auto job : job_waiting_que) {
		printf("��ҵ%d ����ʱ��: %d\n", job->job_id, job->arrive_time);
	}
	printf("\n");
}

//�����ҵ���ж���
void print_job_running_que() {
	printf("------��ҵ���ж������------\n");
	for (auto job : job_running_que) {
		printf("��ҵ%d ���̺�: %d\n", job->job_id, job->proc->proc_id);
	}
	printf("\n");
}

//�����ҵ��ɶ���
void print_job_finished_que() {
	printf("------��ҵ��ɶ������------\n");
	for (auto job : job_finished_que) {
		printf("��ҵ%d ���ʱ���: %d\n", job->job_id, job->finish_time);
	}
	printf("\n");
}

//������̵ȴ�����
void print_proc_waiting_que() {
	printf("------���̵ȴ��������------\n");
	for (auto proc : proc_waiting_que) {
		printf("����%d ������ҵ��: %d\n", proc->proc_id, proc->job_id);
	}
	printf("\n");
}

//����������н���
void print_running_proc() {
	printf("------�������н������------\n");
	printf("���̺�: %d\n", running_proc->proc_id);
	printf("������ҵ��: %d\n", running_proc->job_id);
	printf("ʹ���ڴ����ڷ���: %d\n", running_proc->addr->block_id);
	printf("�ڴ�ռ�ô�С: %d\n", running_proc->memory_size);
	printf("ʣ����Ҫʱ��: %d\n", running_proc->need_time);
	printf("ʣ��ʱ��Ƭ��С: %d\n", running_proc->left_unit_time);
	printf("\n");
}

//���������ɶ���
void print_proc_finished_que() {
	printf("------������ɶ������------\n");
	for (auto proc : proc_finished_que) {
		printf("����%d ������ҵ��:%d �ܻ���ʱ��:%d �ڴ�ռ�ô�С:%dKB\n", 
			proc->proc_id, proc->job_id, proc->total_time, proc->memory_size);
	}
	printf("\n");
}

//�����ڴ�
block* assign_memory(int memory_size) {
	for (block* now = block_head; now != NULL; now = now->next_block) {
		if (memory_size <= now->memory_size) {
			now->memory_size -= memory_size;
			return now;
		}
	}
	print_error("�ڴ治��, �����ڴ�ʧ��!");
	return NULL;
}

//�����ڴ�
void back_memory(block* addr, int memory_size) {
	if (addr == NULL) {
		print_error("�黹������ַΪ��!");
		return;
	}
	addr->memory_size += memory_size;
}

//���ɽ���
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

//���̵���
void run_proc() {
	//�Ӿ���������ȡ������
	if (running_proc == NULL) {
		if (proc_waiting_que.size() == 0) return;

		running_proc = proc_waiting_que.front();
		proc_waiting_que.remove(running_proc);

		//����ʱ��Ƭ
		running_proc->left_unit_time = unit_time;

		print_msg("�Ӿ���������ȡ������:");
		print_running_proc();

		return;
	}

	//����ʣ��ʱ�����
	running_proc->left_unit_time--;
	running_proc->need_time--;

	print_msg("������������...");
	print_running_proc();

	//�������н���
	if (running_proc->need_time == 0) {
		proc_finished_que.push_back(running_proc);
		print_msg("�ý������н���!");
		print_proc_finished_que();

		back_memory(running_proc->addr, running_proc->memory_size);
		print_msg("�ͷ��ڴ�:");
		print_memory_link();

		running_proc = NULL;
		return;
	}

	//ʱ��Ƭ����
	if (running_proc->left_unit_time == 0) {
		proc_waiting_que.push_back(running_proc);
		print_msg("�ý���ʱ��Ƭ����!");
		print_proc_waiting_que();

		running_proc = NULL;
		return;
	}
}

//��ҵ����
void run_job() {
	//��¼������ҵ
	vector<JCB*> job_list;
	for (auto job : job_seq) {
		if (job->arrive_time == now_time) {
			job_list.push_back(job);
		}
	}
	
	//ȡ��������ҵ, �ŵ���������
	if(job_list.size()) print_msg("ȡ��������ҵ, �ŵ�����������...");
	for (auto job : job_list) job_seq.remove(job);
	for (auto job : job_list) job_waiting_que.push_back(job);

	print_job_waiting_que();

	//�Ӿ�������ȡ����ҵ, �ŵ����ж���
	job_list.clear();
	for (auto job : job_waiting_que) {
		if (job_running_que.size() == 
			max_running_job_cnt) break;

		job->proc = generate_proc(job);

		printf("��ҵ��:%d �������̲������ڴ�:\n", job->job_id);
		printf("����ɹ�! �����˿ռ�: %dKB\n", job->proc->memory_size);
		print_memory_link();
		
		job_list.push_back(job);
		proc_waiting_que.push_back(job->proc);
	}
	for (auto job : job_list) job_waiting_que.remove(job);
	for (auto job : job_list) job_running_que.push_back(job);

	if (job_list.size()) {
		print_msg("�Ӿ�������ȡ����ҵ, �ŵ����ж�����...");
		print_job_waiting_que();
	}

	print_job_running_que();

	run_proc();

	//��������ҵ
	JCB* end_job = NULL;
	for (auto job : job_running_que) {
		if (job->proc->need_time == 0) {
			end_job = job;
			break;
		}
	}

	if (end_job != NULL) {
		printf("��������ҵ%d!\n", end_job->job_id);
		end_job->finish_time = now_time;
		job_running_que.remove(end_job);
		job_finished_que.push_back(end_job);
		print_job_finished_que();
	}
}

void init() {
	//��ʼ�����з�����
	block* last_block = NULL;
	int block_id = 0;
	for (auto memory_size : block_memory_size) {
		block_head = new block;

		block_head->block_id = block_id++;
		block_head->memory_size = memory_size;
		block_head->next_block = last_block;

		last_block = block_head;
	}

	//��ʼ����ҵ
	vector<JCB*> tmp_job_seq;
	for (int jid = 0; jid < total_job_cnt; jid++) {
		JCB* job = new JCB;
		job->job_id = jid;
		job->arrive_time = rand() % max_rand_arrive_time;
		tmp_job_seq.push_back(job);
	}
	sort(tmp_job_seq.begin(), tmp_job_seq.end(), cmp);
	for (auto job : tmp_job_seq) job_seq.push_back(job);
	
	//��ʼ������
	running_proc = NULL;

	print_init();
}

void run() {
	now_time = 0;
	while (1) {
		printf("--------ʱ���:%2d--------\n\n", now_time);

		if (!job_waiting_que.size() &&
			!job_running_que.size() &&
			!job_seq.size() ) break;

		run_job();
		now_time++;
	}
}

int main() {
	srand(time(0));

	init();    //��ʼ��
	run();     //��ʼ����

	return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

const int cnt_rc = 3;
const int cnt_proc = 5;

struct PCB {
	int pid;         //进程编号
	char status;     //进程状态, 'W':就绪, 'R':运行, 'B':阻塞, 'F':完成
	
	bool is_request;         //是否有资源请求
	int request_rc[cnt_rc];  //请求资源数
};

PCB pcb[cnt_proc];  //进程

PCB* running_proc;            //正在运行的进程
vector<PCB*> waiting_que;     //就绪队列
vector<PCB*> blocking_que;    //阻塞队列
vector<PCB*> finished_que;    //完成队列

//银行家算法
int Available[cnt_rc];             //可利用资源向量
int Max[cnt_proc][cnt_rc];         //最大需求矩阵
int Allocation[cnt_proc][cnt_rc];  //分配矩阵
int Need[cnt_proc][cnt_rc];        //需求矩阵

//安全性算法
int Work[cnt_rc];        //工作向量
bool Finish[cnt_proc];   //是否能完成进程i

//输出队列
void print_que() {
	cerr << "------------------" << endl;
	cerr << "阻塞队列:" << endl;
	for (auto it : blocking_que) {
		cerr << "pid: " << it->pid << endl;
	}
	cout << endl;

	cerr << "等待队列:" << endl;
	for (auto it : waiting_que) {
		cerr << "pid: " << it->pid << endl;
	}
	cout << endl;

	cerr << "完成队列:" << endl;
	for (auto it : finished_que) {
		cerr << "pid: " << it->pid << endl;
	}
	cerr << "------------------" << endl;
}

//输出矩阵
void print_matrix() {
	cerr << "------------------" << endl;
	cerr << "Available(可利用资源向量):" << endl;
	for (int j = 0; j < cnt_rc; j++) {
		fprintf(stderr, "%3d", Available[j]);
	}
	cerr << endl << endl;

	cerr << "Max(最大需求矩阵):" << endl;

	for (int i = 0; i < cnt_proc; i++) {
		fprintf(stderr, "进程号: %2d 资源使用: ", i);
		for (int j = 0; j < cnt_rc; j++) {
			fprintf(stderr, "%3d", Max[i][j]);
		}
		cerr << endl;
	}
	cerr << endl;

	cerr << "Allocation(分配矩阵):" << endl;

	for (int i = 0; i < cnt_proc; i++) {
		fprintf(stderr, "进程号: %2d 资源使用: ", i);
		for (int j = 0; j < cnt_rc; j++) {
			fprintf(stderr, "%3d", Allocation[i][j]);
		}
		cerr << endl;
	}
	cerr << endl;

	cerr << "Need(需求矩阵):" << endl;

	for (int i = 0; i < cnt_proc; i++) {
		fprintf(stderr, "进程号: %2d 资源使用: ", i);
		for (int j = 0; j < cnt_rc; j++) {
			fprintf(stderr, "%3d", Need[i][j]);
		}
		cerr << endl;
	}
	cerr << endl;

	cerr << "------------------" << endl;
}

//初始化
void init() {
	Available[0] = 10;
	Available[1] = 15;
	Available[2] = 12;

	for (int i = 0; i < cnt_proc; i++) {
		//PCB结构初始化
		pcb[i].pid = i;
		pcb[i].status = 'W';
		pcb[i].is_request = false;
		for (int j = 0; j < cnt_rc; j++) {
			pcb[i].request_rc[j] = 0;
		}

		//资源初始化
		for (int j = 0; j < cnt_rc; j++) {
			Max[i][j] = rand() % Available[j];

			Allocation[i][j] = 0;
			Need[i][j] = Max[i][j];
		}

		waiting_que.push_back(&pcb[i]);
	}
}

//从que中取出第pos位的元素
PCB* take_out(vector<PCB*> &que, int pos) {
	if (pos >= que.size()) return NULL;
	PCB* ans = que[pos];
	vector<PCB*> tmp;
	for (auto it : que)
		if (it != ans)
			tmp.push_back(it);
	que.clear();
	for (auto it : tmp)
		que.push_back(it);
	return ans;
}

//把elem塞进que头
void push_front(vector<PCB*> &que, PCB* elem) {
	vector<PCB*> tmp;
	tmp.push_back(elem);
	for (auto it : que) tmp.push_back(it);
	que.clear();
	for (auto it : tmp) que.push_back(it);
}

//安全性算法
bool safe_algorithm() {
	cerr << "安全性算法:" << endl << endl;

	print_matrix();

	for (int j = 0; j < cnt_rc; j++)
		Work[j] = Available[j];

	for (int i = 0; i < cnt_proc; i++)
		Finish[i] = false;

	while (1) {
		int pid = -1;

		/*
			找到满足以下条件的进程:
			Finish[i] = false
			Need[i][j] <= Work[j] (0 <= j < cnt_rc)
		*/
		for (int i = 0; i < cnt_proc; i++) {
			if (Finish[i] == false) {
				bool ok = true;
				for (int j = 0; j < cnt_rc; j++) {
					if (Need[i][j] > Work[j]) {
						ok = false;
						break;
					}
				}

				if (ok) {
					pid = i;
					break;
				}
			}
		}

		if (pid == -1) break;

		cerr << "找到进程: " << pid << endl;

		//当pid获得资源后, 可顺利执行完成, 并释放资源
		for (int j = 0; j < cnt_rc; j++) {
			Work[j] += Allocation[pid][j];
		}
		Finish[pid] = true;
	}

	//检查所有进程是否处于安全状态
	for (int i = 0; i < cnt_proc; i++)
		if (Finish[i] == false)
			return false;
	return true;
}

//银行家算法
bool bank_algorithm(PCB* proc) {
	cerr << "------------------" << endl;
	cerr << "银行家算法:" << endl << endl;

	cerr << "资源请求向量:" << endl;
	for (int j = 0; j < cnt_rc; j++) {
		fprintf(stderr, "%3d", proc->request_rc[j]);
	}
	cerr << endl << endl;

	for (int j = 0; j < cnt_rc; j++) {
		if (proc->request_rc[j] > Need[proc->pid][j]) {
			cerr << "请求资源数量出错!" << endl << endl;
			cerr << "------------------" << endl;
			return false;
		}
	}

	for (int j = 0; j < cnt_rc; j++) {
		if (proc->request_rc[j] > Available[j]) {
			cerr << "无足够资源, 需等待!" << endl << endl;
			cerr << "------------------" << endl;
			return false;
		}
	}

	cerr << "试探分配资源前: " << endl;
	print_matrix();

	//试探分配资源
	for (int j = 0; j < cnt_rc; j++) {
		Available[j] -= proc->request_rc[j];
		Allocation[proc->pid][j] += proc->request_rc[j];
		Need[proc->pid][j] -= proc->request_rc[j];
	}

	if (safe_algorithm()) {
		cerr << "正式分配资源!" << endl << endl;
		cerr << "------------------" << endl;
		return true;
	}
	else {
		//恢复分配状态
		for (int j = 0; j < cnt_rc; j++) {
			Available[j] += proc->request_rc[j];
			Allocation[proc->pid][j] -= proc->request_rc[j];
			Need[proc->pid][j] += proc->request_rc[j];
		}

		cerr << "系统处于不安全状态, 需等待!" << endl;
		cerr << "------------------" << endl;
		return false;
	}
}

//进程调度
void run() {
	int time_point = 1;

	while (waiting_que.size() || blocking_que.size()) {
		cerr << "------------------" << endl;
		cerr << "时间点: " << time_point << endl;
		time_point++;

		bool checker = false;

		if (waiting_que.size() == 0 && blocking_que.size()) {
			for (int i = 0; i < blocking_que.size(); i++) {
				PCB* proc = blocking_que[i];
				//唤醒条件: 请求资源小于可利用资源
				bool ok = true;
				for (int j = 0; j < cnt_rc; j++) {
					if (proc->request_rc[j] > Available[j]) {
						ok = false;
						break;
					}
				}

				if (ok) {
					proc = take_out(blocking_que, i);
					proc->status = 'W';
					push_front(waiting_que, proc);
					checker = true;
					break;
				}
			}
		}

		if (checker == false && waiting_que.size() == 0) {
			cerr << "系统出现错误1, 关闭系统!" << endl;
			break;
		}

		running_proc = take_out(waiting_que, 0);
		running_proc->status = 'R';

		print_que();

		cerr << "正在运行的进程: " << "进程号为" << running_proc->pid << endl << endl;

		//随机请求资源
		if (running_proc->is_request == false) {
			//running_proc->is_request = true;
			for (int j = 0; j < cnt_rc; j++) {
				running_proc->request_rc[j] =
					rand() % (Need[running_proc->pid][j] + 1);
			}
		}

		//执行成功
		if (bank_algorithm(running_proc)) {
			running_proc->is_request = false;

			//检查程序是否完成
			bool ok = true;
			for (int j = 0; j < cnt_rc; j++) {
				if (Need[running_proc->pid][j]) {
					ok = false;
					break;
				}
			}

			if (ok) {
				running_proc->status = 'F';
				//归还资源给系统
				for (int j = 0; j < cnt_rc; j++) {
					Available[j] += Allocation[running_proc->pid][j];
					Allocation[running_proc->pid][j] = 0;
					if (Need[running_proc->pid][j] != 0) {
						cerr << "系统出现错误2, 关闭系统!" << endl;
						break;
					}
				}
				finished_que.push_back(running_proc);
			}
			else {
				running_proc->status = 'W';
				waiting_que.push_back(running_proc);
			}
		}
		//执行失败
		else {
			running_proc->status = 'B';
			blocking_que.push_back(running_proc);
		}
	}
}

int main() {
	srand(time(0));
	init();         //初始化
	run();          //进程调度
	print_que();    //输出队列
	system("pause");
	return 0;
}

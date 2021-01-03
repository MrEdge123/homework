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
	int pid;         //���̱��
	char status;     //����״̬, 'W':����, 'R':����, 'B':����, 'F':���
	
	bool is_request;         //�Ƿ�����Դ����
	int request_rc[cnt_rc];  //������Դ��
};

PCB pcb[cnt_proc];  //����

PCB* running_proc;            //�������еĽ���
vector<PCB*> waiting_que;     //��������
vector<PCB*> blocking_que;    //��������
vector<PCB*> finished_que;    //��ɶ���

//���м��㷨
int Available[cnt_rc];             //��������Դ����
int Max[cnt_proc][cnt_rc];         //����������
int Allocation[cnt_proc][cnt_rc];  //�������
int Need[cnt_proc][cnt_rc];        //�������

//��ȫ���㷨
int Work[cnt_rc];        //��������
bool Finish[cnt_proc];   //�Ƿ�����ɽ���i

//�������
void print_que() {
	cerr << "------------------" << endl;
	cerr << "��������:" << endl;
	for (auto it : blocking_que) {
		cerr << "pid: " << it->pid << endl;
	}
	cout << endl;

	cerr << "�ȴ�����:" << endl;
	for (auto it : waiting_que) {
		cerr << "pid: " << it->pid << endl;
	}
	cout << endl;

	cerr << "��ɶ���:" << endl;
	for (auto it : finished_que) {
		cerr << "pid: " << it->pid << endl;
	}
	cerr << "------------------" << endl;
}

//�������
void print_matrix() {
	cerr << "------------------" << endl;
	cerr << "Available(��������Դ����):" << endl;
	for (int j = 0; j < cnt_rc; j++) {
		fprintf(stderr, "%3d", Available[j]);
	}
	cerr << endl << endl;

	cerr << "Max(����������):" << endl;

	for (int i = 0; i < cnt_proc; i++) {
		fprintf(stderr, "���̺�: %2d ��Դʹ��: ", i);
		for (int j = 0; j < cnt_rc; j++) {
			fprintf(stderr, "%3d", Max[i][j]);
		}
		cerr << endl;
	}
	cerr << endl;

	cerr << "Allocation(�������):" << endl;

	for (int i = 0; i < cnt_proc; i++) {
		fprintf(stderr, "���̺�: %2d ��Դʹ��: ", i);
		for (int j = 0; j < cnt_rc; j++) {
			fprintf(stderr, "%3d", Allocation[i][j]);
		}
		cerr << endl;
	}
	cerr << endl;

	cerr << "Need(�������):" << endl;

	for (int i = 0; i < cnt_proc; i++) {
		fprintf(stderr, "���̺�: %2d ��Դʹ��: ", i);
		for (int j = 0; j < cnt_rc; j++) {
			fprintf(stderr, "%3d", Need[i][j]);
		}
		cerr << endl;
	}
	cerr << endl;

	cerr << "------------------" << endl;
}

//��ʼ��
void init() {
	Available[0] = 10;
	Available[1] = 15;
	Available[2] = 12;

	for (int i = 0; i < cnt_proc; i++) {
		//PCB�ṹ��ʼ��
		pcb[i].pid = i;
		pcb[i].status = 'W';
		pcb[i].is_request = false;
		for (int j = 0; j < cnt_rc; j++) {
			pcb[i].request_rc[j] = 0;
		}

		//��Դ��ʼ��
		for (int j = 0; j < cnt_rc; j++) {
			Max[i][j] = rand() % Available[j];

			Allocation[i][j] = 0;
			Need[i][j] = Max[i][j];
		}

		waiting_que.push_back(&pcb[i]);
	}
}

//��que��ȡ����posλ��Ԫ��
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

//��elem����queͷ
void push_front(vector<PCB*> &que, PCB* elem) {
	vector<PCB*> tmp;
	tmp.push_back(elem);
	for (auto it : que) tmp.push_back(it);
	que.clear();
	for (auto it : tmp) que.push_back(it);
}

//��ȫ���㷨
bool safe_algorithm() {
	cerr << "��ȫ���㷨:" << endl << endl;

	print_matrix();

	for (int j = 0; j < cnt_rc; j++)
		Work[j] = Available[j];

	for (int i = 0; i < cnt_proc; i++)
		Finish[i] = false;

	while (1) {
		int pid = -1;

		/*
			�ҵ��������������Ľ���:
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

		cerr << "�ҵ�����: " << pid << endl;

		//��pid�����Դ��, ��˳��ִ�����, ���ͷ���Դ
		for (int j = 0; j < cnt_rc; j++) {
			Work[j] += Allocation[pid][j];
		}
		Finish[pid] = true;
	}

	//������н����Ƿ��ڰ�ȫ״̬
	for (int i = 0; i < cnt_proc; i++)
		if (Finish[i] == false)
			return false;
	return true;
}

//���м��㷨
bool bank_algorithm(PCB* proc) {
	cerr << "------------------" << endl;
	cerr << "���м��㷨:" << endl << endl;

	cerr << "��Դ��������:" << endl;
	for (int j = 0; j < cnt_rc; j++) {
		fprintf(stderr, "%3d", proc->request_rc[j]);
	}
	cerr << endl << endl;

	for (int j = 0; j < cnt_rc; j++) {
		if (proc->request_rc[j] > Need[proc->pid][j]) {
			cerr << "������Դ��������!" << endl << endl;
			cerr << "------------------" << endl;
			return false;
		}
	}

	for (int j = 0; j < cnt_rc; j++) {
		if (proc->request_rc[j] > Available[j]) {
			cerr << "���㹻��Դ, ��ȴ�!" << endl << endl;
			cerr << "------------------" << endl;
			return false;
		}
	}

	cerr << "��̽������Դǰ: " << endl;
	print_matrix();

	//��̽������Դ
	for (int j = 0; j < cnt_rc; j++) {
		Available[j] -= proc->request_rc[j];
		Allocation[proc->pid][j] += proc->request_rc[j];
		Need[proc->pid][j] -= proc->request_rc[j];
	}

	if (safe_algorithm()) {
		cerr << "��ʽ������Դ!" << endl << endl;
		cerr << "------------------" << endl;
		return true;
	}
	else {
		//�ָ�����״̬
		for (int j = 0; j < cnt_rc; j++) {
			Available[j] += proc->request_rc[j];
			Allocation[proc->pid][j] -= proc->request_rc[j];
			Need[proc->pid][j] += proc->request_rc[j];
		}

		cerr << "ϵͳ���ڲ���ȫ״̬, ��ȴ�!" << endl;
		cerr << "------------------" << endl;
		return false;
	}
}

//���̵���
void run() {
	int time_point = 1;

	while (waiting_que.size() || blocking_que.size()) {
		cerr << "------------------" << endl;
		cerr << "ʱ���: " << time_point << endl;
		time_point++;

		bool checker = false;

		if (waiting_que.size() == 0 && blocking_que.size()) {
			for (int i = 0; i < blocking_que.size(); i++) {
				PCB* proc = blocking_que[i];
				//��������: ������ԴС�ڿ�������Դ
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
			cerr << "ϵͳ���ִ���1, �ر�ϵͳ!" << endl;
			break;
		}

		running_proc = take_out(waiting_que, 0);
		running_proc->status = 'R';

		print_que();

		cerr << "�������еĽ���: " << "���̺�Ϊ" << running_proc->pid << endl << endl;

		//���������Դ
		if (running_proc->is_request == false) {
			//running_proc->is_request = true;
			for (int j = 0; j < cnt_rc; j++) {
				running_proc->request_rc[j] =
					rand() % (Need[running_proc->pid][j] + 1);
			}
		}

		//ִ�гɹ�
		if (bank_algorithm(running_proc)) {
			running_proc->is_request = false;

			//�������Ƿ����
			bool ok = true;
			for (int j = 0; j < cnt_rc; j++) {
				if (Need[running_proc->pid][j]) {
					ok = false;
					break;
				}
			}

			if (ok) {
				running_proc->status = 'F';
				//�黹��Դ��ϵͳ
				for (int j = 0; j < cnt_rc; j++) {
					Available[j] += Allocation[running_proc->pid][j];
					Allocation[running_proc->pid][j] = 0;
					if (Need[running_proc->pid][j] != 0) {
						cerr << "ϵͳ���ִ���2, �ر�ϵͳ!" << endl;
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
		//ִ��ʧ��
		else {
			running_proc->status = 'B';
			blocking_que.push_back(running_proc);
		}
	}
}

int main() {
	srand(time(0));
	init();         //��ʼ��
	run();          //���̵���
	print_que();    //�������
	system("pause");
	return 0;
}

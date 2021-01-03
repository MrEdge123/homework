#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

struct PCB {
    int pid;             //���̱��
    double priority;     //���ȼ�, �������
    int arrive_time;     //����ʱ��
    int waiting_time;    //�ȴ�ʱ��
    int need_runtime;    //��Ҫ����ʱ��
    int already_runtime; //������ʱ��
    int status;          //״̬, 0:���� 1:���� 2:���
};

vector<PCB> pcb_list;    //�����б�

vector<PCB> waiting_queue;          //��������
bool has_proc;                      //�Ƿ����������еĽ���
PCB running_proc;                   //�������еĽ���
vector<PCB> finished_proc_list;     //��ɵĽ���

int max_arrive_time = 5;   //��󵽴�ʱ��
int max_need_time = 5;     //�������ʱ��
int max_priority = 10;     //������ȼ�
int process_cnt = 5;       //��������

//ȡ��que�еĵ�pos��Ԫ��
PCB take_out(int pos, vector<PCB>& que) {
    vector<PCB> tmp_que;
    PCB ans = que[pos];
    for (size_t i = 0; i < que.size(); i++) {
        if (i != pos)
            tmp_que.push_back(que[i]);
    }
    que.clear();
    for (auto it : tmp_que) que.push_back(it);
    return ans;
}

//�������Ƿ����
bool is_proc_end(PCB& p) {
    if (p.already_runtime >= p.need_runtime) return true;
    return false;
}

//�������ȼ�
void set_priority(PCB& it, int mode) {
    double leave_time;
    switch (mode)
    {
    case 1:    //�̽�������
        it.priority = (double)it.need_runtime - it.already_runtime;
        it.priority = max_priority - it.priority;
        break;
    case 2:    //����Ӧ������
        leave_time = (double)it.need_runtime - it.already_runtime;
        it.priority = ((double)it.waiting_time + leave_time) / leave_time;
        break;
    default:
        it.priority = 0;
        break;
    }
}

//���ɽ���
void generate_proc() {
    PCB pcb;

    pcb.pid = 0;
    pcb.priority = max_priority;
    pcb.arrive_time = 0;
    pcb.waiting_time = 0;
    pcb.need_runtime = rand() % max_need_time + 1;
    pcb.already_runtime = 0;
    pcb.status = 0;

    pcb_list.push_back(pcb);

    for (int i = 1; i < process_cnt; i++) {
        pcb.pid = i;
        pcb.priority = rand() % max_priority;
        pcb.arrive_time = rand() % max_arrive_time;
        pcb.waiting_time = 0;
        pcb.need_runtime = rand() % max_need_time + 1;
        pcb.already_runtime = 0;
        pcb.status = 0;

        pcb_list.push_back(pcb);
    }
}

bool cmp_arrive_time(PCB a, PCB b) {
    return a.arrive_time < b.arrive_time;
}

//��ʼ��, lenΪʱ�䵥λ����
void init(int len, int mode) {
    waiting_queue.clear();           //��������
    has_proc = false;                //�Ƿ����������еĽ���
    finished_proc_list.clear();      //��ɵĽ���

    running_proc.need_runtime = (int)1e9;     //Ϊ�̽������ȵ��ȳ�ʼ��
    running_proc.waiting_time = (int)-1e9;    //Ϊ����Ӧ�����ȵ��ȳ�ʼ��
    running_proc.already_runtime = len;       //Ϊʱ��Ƭ��ת��ʼ��

    set_priority(running_proc, mode);
}

//���һ�����̵���Ϣ
void print_proc(PCB& it) {
    cout << "PCB:";
    cout << " ���̱��:" << it.pid;
    cout << " ����ʱ��:" << it.arrive_time;
    if(it.status == 0) cout << " �ȴ�ʱ��:" << it.waiting_time;
    cout << " �ƻ�����ʱ��:" << it.need_runtime;
    cout << " ������ʱ��:" << it.already_runtime;
    cout << " ���ȼ�:" << it.priority;
    cout << endl;
}

//�����������
void print_waiting_que() {
    cout << "***************************" << endl;
    cout << "��������:" << endl;
    for (auto it : waiting_queue) {
        print_proc(it);
    }
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//����Ӷ���ȡ���Ľ���
void print_take_out_proc(PCB& proc) {
    cout << "***************************" << endl;
    cout << "�Ӿ�������ȡ���Ľ���:" << endl;
    print_proc(proc);
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//����������еĽ���
void print_running_proc() {
    cout << "***************************" << endl;
    cout << "�������еĽ���:" << endl;
    print_proc(running_proc);
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//�����ɵĽ���
void print_finished_proc_list() {
    cout << "***************************" << endl;
    cout << "����ɵĽ���:" << endl;
    for (auto it : finished_proc_list) {
        print_proc(it);
    }
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//��modeģʽ���е�������, mode=1:�̽�������, mode=2:����Ӧ������, mode=3:ʱ��Ƭ��ת
void run(int mode) {

    cout << "---------------------------" << endl;
    switch (mode)
    {
    case 1:
        cout << "�̽������ȵ���(��ռʽ)" << endl << endl;
        break;
    case 2:
        cout << "����Ӧ�����ȵ���" << endl << endl;
        break;
    case 3:
        cout << "ʱ��Ƭ��ת����" << endl << endl;
        break;
    default:
        break;
    }

    //ʱ�䵥λ����, Ĭ��Ϊ1
    int len = 1;
    if (mode == 3) len = 2;

    cout << "ʱ�䵥λ����: " << len << endl << endl;

    init(len, mode);    //��ʼ��

    for (int now_time = 0; now_time <= max_arrive_time + 5 * max_need_time; now_time++) {
        if (pcb_list.size() == finished_proc_list.size()) break;

        cout << "###########################" << endl;
        cout << "ʱ���: " << now_time << endl << endl;

        //��������ʱ������
        if (has_proc)
            running_proc.already_runtime++;

        if (has_proc) print_running_proc();

        //����������ĳ���
        if (has_proc && is_proc_end(running_proc)) {
            //...
            running_proc.status = 2;
            finished_proc_list.push_back(running_proc);
            print_finished_proc_list();
            has_proc = false;

            running_proc.need_runtime = (int)1e9;     //Ϊ�̽������ȵ��ȳ�ʼ��
            running_proc.waiting_time = (int)-1e9;    //Ϊ����Ӧ�����ȵ��ȳ�ʼ��
            running_proc.already_runtime = len;       //Ϊʱ��Ƭ��ת��ʼ��
            set_priority(running_proc, mode);
        }

        //�ھ������еĵȴ�ʱ������
        for (auto& it : waiting_queue) {
            it.waiting_time++;
        }
        
        bool is_print_que = false;
        
        //�ѵ���Ľ���������������
        for (auto it : pcb_list) {
            if (it.arrive_time == now_time) {

                //���ȼ�����
                set_priority(it, mode);

                waiting_queue.push_back(it);
                is_print_que = true;
            }
        }

        if (is_print_que) {
            cout << "�������񵽴��������:" << endl;
            print_waiting_que();
        }

        //�ҽ���
        int pos = -1;

        if (mode == 1 || mode == 2) {    //�̽������� / ����Ӧ������
            double max_p = running_proc.priority;
            double eps = 1e-3;

            for (size_t i = 0; i < waiting_queue.size(); i++) {
                PCB& it = waiting_queue[i];
                set_priority(it, mode);
                double p = it.priority;

                if (fabs(p - max_p) > eps && p > max_p) {
                    max_p = p;
                    pos = i;
                }
            }
        }
        else if (mode == 3) {     //ʱ��Ƭ��ת
            if (running_proc.already_runtime && 
                running_proc.already_runtime % len == 0) {

                if (waiting_queue.size()) pos = 0;
            }
        }

        //ȡ������
        if (pos != -1) {
            cout << "ȡ��ǰ�ľ�������:" << endl;
            print_waiting_que();
            print_take_out_proc(waiting_queue[pos]);
            running_proc.status = 0;
            running_proc.waiting_time = 0;
            if (has_proc) waiting_queue.push_back(running_proc);
            running_proc = take_out(pos, waiting_queue);
            running_proc.status = 1;
            running_proc.waiting_time = 0;
            has_proc = true;
            cout << "ȡ����ľ�������:" << endl;
            print_waiting_que();
        }
    }
}

int main() {
    srand((unsigned int)time(0));

    //���ɽ���
    generate_proc();

    //�Խ��̵���ʱ���������
    sort(pcb_list.begin(), pcb_list.end(), cmp_arrive_time);

    //���е���
    run(1);
    run(2);
    run(3);

    system("pause");

    return 0;
}

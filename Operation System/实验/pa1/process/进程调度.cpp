#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

struct PCB {
    int pid;             //进程编号
    double priority;     //优先级, 大的优先
    int arrive_time;     //到达时间
    int waiting_time;    //等待时间
    int need_runtime;    //需要运行时间
    int already_runtime; //已运行时间
    int status;          //状态, 0:就绪 1:运行 2:完成
};

vector<PCB> pcb_list;    //进程列表

vector<PCB> waiting_queue;          //就绪队列
bool has_proc;                      //是否有正在运行的进程
PCB running_proc;                   //正在运行的进程
vector<PCB> finished_proc_list;     //完成的进程

int max_arrive_time = 5;   //最大到达时间
int max_need_time = 5;     //最大运行时间
int max_priority = 10;     //最大优先级
int process_cnt = 5;       //进程数量

//取出que中的第pos个元素
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

//检查进程是否结束
bool is_proc_end(PCB& p) {
    if (p.already_runtime >= p.need_runtime) return true;
    return false;
}

//设置优先级
void set_priority(PCB& it, int mode) {
    double leave_time;
    switch (mode)
    {
    case 1:    //短进程优先
        it.priority = (double)it.need_runtime - it.already_runtime;
        it.priority = max_priority - it.priority;
        break;
    case 2:    //高相应比优先
        leave_time = (double)it.need_runtime - it.already_runtime;
        it.priority = ((double)it.waiting_time + leave_time) / leave_time;
        break;
    default:
        it.priority = 0;
        break;
    }
}

//生成进程
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

//初始化, len为时间单位长度
void init(int len, int mode) {
    waiting_queue.clear();           //就绪队列
    has_proc = false;                //是否有正在运行的进程
    finished_proc_list.clear();      //完成的进程

    running_proc.need_runtime = (int)1e9;     //为短进程优先调度初始化
    running_proc.waiting_time = (int)-1e9;    //为高相应比优先调度初始化
    running_proc.already_runtime = len;       //为时间片轮转初始化

    set_priority(running_proc, mode);
}

//输出一个进程的消息
void print_proc(PCB& it) {
    cout << "PCB:";
    cout << " 进程编号:" << it.pid;
    cout << " 到达时间:" << it.arrive_time;
    if(it.status == 0) cout << " 等待时间:" << it.waiting_time;
    cout << " 计划运行时间:" << it.need_runtime;
    cout << " 已运行时间:" << it.already_runtime;
    cout << " 优先级:" << it.priority;
    cout << endl;
}

//输出就绪队列
void print_waiting_que() {
    cout << "***************************" << endl;
    cout << "就绪队列:" << endl;
    for (auto it : waiting_queue) {
        print_proc(it);
    }
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//输出从队列取出的进程
void print_take_out_proc(PCB& proc) {
    cout << "***************************" << endl;
    cout << "从就绪队列取出的进程:" << endl;
    print_proc(proc);
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//输出正在运行的进程
void print_running_proc() {
    cout << "***************************" << endl;
    cout << "正在运行的进程:" << endl;
    print_proc(running_proc);
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//输出完成的进程
void print_finished_proc_list() {
    cout << "***************************" << endl;
    cout << "已完成的进程:" << endl;
    for (auto it : finished_proc_list) {
        print_proc(it);
    }
    cout << "***************************" << endl;
    cout << endl;
    //Sleep(3000);
}

//以mode模式进行调度运行, mode=1:短进程优先, mode=2:高响应比优先, mode=3:时间片轮转
void run(int mode) {

    cout << "---------------------------" << endl;
    switch (mode)
    {
    case 1:
        cout << "短进程优先调度(抢占式)" << endl << endl;
        break;
    case 2:
        cout << "高响应比优先调度" << endl << endl;
        break;
    case 3:
        cout << "时间片轮转调度" << endl << endl;
        break;
    default:
        break;
    }

    //时间单位长度, 默认为1
    int len = 1;
    if (mode == 3) len = 2;

    cout << "时间单位长度: " << len << endl << endl;

    init(len, mode);    //初始化

    for (int now_time = 0; now_time <= max_arrive_time + 5 * max_need_time; now_time++) {
        if (pcb_list.size() == finished_proc_list.size()) break;

        cout << "###########################" << endl;
        cout << "时间点: " << now_time << endl << endl;

        //程序运行时间增加
        if (has_proc)
            running_proc.already_runtime++;

        if (has_proc) print_running_proc();

        //结束运行完的程序
        if (has_proc && is_proc_end(running_proc)) {
            //...
            running_proc.status = 2;
            finished_proc_list.push_back(running_proc);
            print_finished_proc_list();
            has_proc = false;

            running_proc.need_runtime = (int)1e9;     //为短进程优先调度初始化
            running_proc.waiting_time = (int)-1e9;    //为高相应比优先调度初始化
            running_proc.already_runtime = len;       //为时间片轮转初始化
            set_priority(running_proc, mode);
        }

        //在就绪队列的等待时间增加
        for (auto& it : waiting_queue) {
            it.waiting_time++;
        }
        
        bool is_print_que = false;
        
        //把到达的进程塞进就绪队列
        for (auto it : pcb_list) {
            if (it.arrive_time == now_time) {

                //优先级计算
                set_priority(it, mode);

                waiting_queue.push_back(it);
                is_print_que = true;
            }
        }

        if (is_print_que) {
            cout << "有新任务到达就绪队列:" << endl;
            print_waiting_que();
        }

        //找进程
        int pos = -1;

        if (mode == 1 || mode == 2) {    //短进程优先 / 高相应比优先
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
        else if (mode == 3) {     //时间片轮转
            if (running_proc.already_runtime && 
                running_proc.already_runtime % len == 0) {

                if (waiting_queue.size()) pos = 0;
            }
        }

        //取出进程
        if (pos != -1) {
            cout << "取出前的就绪队列:" << endl;
            print_waiting_que();
            print_take_out_proc(waiting_queue[pos]);
            running_proc.status = 0;
            running_proc.waiting_time = 0;
            if (has_proc) waiting_queue.push_back(running_proc);
            running_proc = take_out(pos, waiting_queue);
            running_proc.status = 1;
            running_proc.waiting_time = 0;
            has_proc = true;
            cout << "取出后的就绪队列:" << endl;
            print_waiting_que();
        }
    }
}

int main() {
    srand((unsigned int)time(0));

    //生成进程
    generate_proc();

    //对进程到达时间进行排序
    sort(pcb_list.begin(), pcb_list.end(), cmp_arrive_time);

    //进行调度
    run(1);
    run(2);
    run(3);

    system("pause");

    return 0;
}

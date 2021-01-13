#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> seq_track_id;   //被访问的磁道号序列
vector<int> next_track_id;  //要访问的磁道号顺序
vector<int> offset;         //移动距离
float avg_offset;           //平均寻道时间

int track_num = 200;     //磁道数
int request_cnt = 10;    //磁道号序列长度

//输出结果
void print_res(string mode) {
	if (next_track_id.size() != offset.size()) return;

	printf("磁盘调度算法: %s\n", mode.c_str());
	printf(
		"+------------------------------------------+\n"
		"| (从100#磁道开始, 向磁道号增加的方向访问) |\n"
		"+----------------------+-------------------+\n"
		"| 被访问的下一个磁道号 | 移动距离 (磁道数) |\n"
		"+----------------------+-------------------+\n"
	);

	int SZ = offset.size();
	for (int i = 0; i < SZ; i++) {
		printf(
			"|         %3d          |        %3d        |\n"
			"+----------------------+-------------------+\n"
		, next_track_id[i], offset[i]);
	}

	printf(
		"|            平均寻道长度: %3.1f            |\n"
		"+------------------------------------------+\n"
		, avg_offset
	);

	printf("\n\n");
}

//输出请求序列
void print_seq() {
	printf("请求磁道号序列:\n");
	for (auto it : seq_track_id) {
		printf("%d ", it);
	}
	printf("\n\n");
}

//随机生成请求序列
void init_seq() {
	srand(time(0));
	for (int i = 0; i < request_cnt; i++) {
		int track_id = rand() % track_num;
		seq_track_id.push_back(track_id);
	}
	print_seq();
}

//计算移动距离和平均寻道长度
void cal_offset() {
	avg_offset = 0;

	int now = 100;
	for (auto it : next_track_id) {
		int t = abs(now - it);
		offset.push_back(t);
		avg_offset += t;
		now = it;
	}

	avg_offset /= offset.size();
}

//调度
void run(string mode) {
	next_track_id.clear();
	offset.clear();

	//当前磁道号
	int now = 100;

	vector<int> tmp_seq = seq_track_id;

	//计算访问的磁道号顺序
	if (mode == "FCFS") {
		next_track_id = tmp_seq;
	}
	else if (mode == "SSTF") {
		//对磁道号进行排序
		sort(tmp_seq.begin(), tmp_seq.end());

		//找到第一个大于等于now的磁道号位置
		int pos = 
			lower_bound(tmp_seq.begin(), tmp_seq.end(), now)
			- tmp_seq.begin();

		//双指针
		int L = pos - 1, R = pos;
		int SZ = (int)tmp_seq.size();

		//找下一个磁道号
		while (1) {
			if (L < 0 && R >= SZ) break;

			if (L < 0) {
				now = tmp_seq[R++];
			}
			else if (R >= SZ) {
				now = tmp_seq[L--];
			}
			else {
				//找最近的磁道号
				if (abs(now - tmp_seq[L]) <=
					abs(now - tmp_seq[R])) {
					now = tmp_seq[L--];
				}
				else {
					now = tmp_seq[R++];
				}
			}

			next_track_id.push_back(now);
		}
	}
	else if (mode == "SCAN") {
		//对磁道号进行排序
		sort(tmp_seq.begin(), tmp_seq.end());

		//找到第一个大于等于now的磁道号位置
		int pos =
			lower_bound(tmp_seq.begin(), tmp_seq.end(), now)
			- tmp_seq.begin();

		int SZ = tmp_seq.size();

		//磁道号小到大的方向
		for (int i = pos; i < SZ; i++) 
			next_track_id.push_back(tmp_seq[i]);

		//磁道号大到小的方向
		for (int i = pos - 1; i >= 0; i--)
			next_track_id.push_back(tmp_seq[i]);

	}
	else if (mode == "CSCAN") {
		//对磁道号进行排序
		sort(tmp_seq.begin(), tmp_seq.end());

		//找到第一个大于等于now的磁道号位置
		int pos =
			lower_bound(tmp_seq.begin(), tmp_seq.end(), now)
			- tmp_seq.begin();

		int SZ = tmp_seq.size();

		//从pos开始
		for (int i = pos; i < SZ; i++)
			next_track_id.push_back(tmp_seq[i]);

		//从0开始
		for (int i = 0; i < pos; i++)
			next_track_id.push_back(tmp_seq[i]);
	}
	else {
		printf("error!");
		return;
	}

	//计算移动距离和平均寻道长度
	cal_offset();
	print_res(mode);
}

int main() {
	init_seq();

	run("FCFS");
	run("SSTF");
	run("SCAN");
	run("CSCAN");

	return 0;
}

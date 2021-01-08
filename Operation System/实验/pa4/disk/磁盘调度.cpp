#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> seq_track_id;
vector<int> next_track_id;
vector<int> offset;
float avg_offset;

int track_num = 200;
int request_cnt = 9;

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

void print_seq() {
	printf("请求磁道号序列:\n");
	for (auto it : seq_track_id) {
		printf("%d ", it);
	}
	printf("\n\n");
}

void init_seq() {
	srand(time(0));
	for (int i = 0; i < request_cnt; i++) {
		int track_id = rand() % track_num;
		seq_track_id.push_back(track_id);
	}
	print_seq();
}

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

void run(string mode) {
	next_track_id.clear();
	offset.clear();

	int now = 100;

	if (mode == "FCFS") {
		next_track_id = seq_track_id;
	}
	else if (mode == "SSTF") {
		sort(seq_track_id.begin(), seq_track_id.end());

		int pos = 
			lower_bound(seq_track_id.begin(), seq_track_id.end(), now)
			- seq_track_id.begin();

		int L = pos - 1, R = pos;
		int SZ = (int)seq_track_id.size();

		while (1) {
			if (L < 0 && R >= SZ) break;

			if (L < 0) {
				now = seq_track_id[R++];
			}
			else if (R >= SZ) {
				now = seq_track_id[L--];
			}
			else {
				if (abs(now - seq_track_id[L]) <=
					abs(now - seq_track_id[R])) {
					now = seq_track_id[L--];
				}
				else {
					now = seq_track_id[R++];
				}
			}

			next_track_id.push_back(now);
		}
	}
	else if (mode == "SCAN") {
		sort(seq_track_id.begin(), seq_track_id.end());

		int pos =
			lower_bound(seq_track_id.begin(), seq_track_id.end(), now)
			- seq_track_id.begin();

		int SZ = seq_track_id.size();
		for (int i = pos; i < SZ; i++) 
			next_track_id.push_back(seq_track_id[i]);

		for (int i = pos - 1; i >= 0; i--)
			next_track_id.push_back(seq_track_id[i]);

	}
	else if (mode == "CSCAN") {
		sort(seq_track_id.begin(), seq_track_id.end());

		int pos =
			lower_bound(seq_track_id.begin(), seq_track_id.end(), now)
			- seq_track_id.begin();

		int SZ = seq_track_id.size();
		int END = (pos - 1 + SZ) % SZ;
		for (int i = pos % SZ; i != END; i = (i + 1) % SZ)
			next_track_id.push_back(seq_track_id[i]);

		next_track_id.push_back(seq_track_id[END]);
	}
	else {
		printf("error!");
		return;
	}

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

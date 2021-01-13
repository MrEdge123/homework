#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> seq_track_id;   //�����ʵĴŵ�������
vector<int> next_track_id;  //Ҫ���ʵĴŵ���˳��
vector<int> offset;         //�ƶ�����
float avg_offset;           //ƽ��Ѱ��ʱ��

int track_num = 200;     //�ŵ���
int request_cnt = 10;    //�ŵ������г���

//������
void print_res(string mode) {
	if (next_track_id.size() != offset.size()) return;

	printf("���̵����㷨: %s\n", mode.c_str());
	printf(
		"+------------------------------------------+\n"
		"| (��100#�ŵ���ʼ, ��ŵ������ӵķ������) |\n"
		"+----------------------+-------------------+\n"
		"| �����ʵ���һ���ŵ��� | �ƶ����� (�ŵ���) |\n"
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
		"|            ƽ��Ѱ������: %3.1f            |\n"
		"+------------------------------------------+\n"
		, avg_offset
	);

	printf("\n\n");
}

//�����������
void print_seq() {
	printf("����ŵ�������:\n");
	for (auto it : seq_track_id) {
		printf("%d ", it);
	}
	printf("\n\n");
}

//���������������
void init_seq() {
	srand(time(0));
	for (int i = 0; i < request_cnt; i++) {
		int track_id = rand() % track_num;
		seq_track_id.push_back(track_id);
	}
	print_seq();
}

//�����ƶ������ƽ��Ѱ������
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

//����
void run(string mode) {
	next_track_id.clear();
	offset.clear();

	//��ǰ�ŵ���
	int now = 100;

	vector<int> tmp_seq = seq_track_id;

	//������ʵĴŵ���˳��
	if (mode == "FCFS") {
		next_track_id = tmp_seq;
	}
	else if (mode == "SSTF") {
		//�Դŵ��Ž�������
		sort(tmp_seq.begin(), tmp_seq.end());

		//�ҵ���һ�����ڵ���now�Ĵŵ���λ��
		int pos = 
			lower_bound(tmp_seq.begin(), tmp_seq.end(), now)
			- tmp_seq.begin();

		//˫ָ��
		int L = pos - 1, R = pos;
		int SZ = (int)tmp_seq.size();

		//����һ���ŵ���
		while (1) {
			if (L < 0 && R >= SZ) break;

			if (L < 0) {
				now = tmp_seq[R++];
			}
			else if (R >= SZ) {
				now = tmp_seq[L--];
			}
			else {
				//������Ĵŵ���
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
		//�Դŵ��Ž�������
		sort(tmp_seq.begin(), tmp_seq.end());

		//�ҵ���һ�����ڵ���now�Ĵŵ���λ��
		int pos =
			lower_bound(tmp_seq.begin(), tmp_seq.end(), now)
			- tmp_seq.begin();

		int SZ = tmp_seq.size();

		//�ŵ���С����ķ���
		for (int i = pos; i < SZ; i++) 
			next_track_id.push_back(tmp_seq[i]);

		//�ŵ��Ŵ�С�ķ���
		for (int i = pos - 1; i >= 0; i--)
			next_track_id.push_back(tmp_seq[i]);

	}
	else if (mode == "CSCAN") {
		//�Դŵ��Ž�������
		sort(tmp_seq.begin(), tmp_seq.end());

		//�ҵ���һ�����ڵ���now�Ĵŵ���λ��
		int pos =
			lower_bound(tmp_seq.begin(), tmp_seq.end(), now)
			- tmp_seq.begin();

		int SZ = tmp_seq.size();

		//��pos��ʼ
		for (int i = pos; i < SZ; i++)
			next_track_id.push_back(tmp_seq[i]);

		//��0��ʼ
		for (int i = 0; i < pos; i++)
			next_track_id.push_back(tmp_seq[i]);
	}
	else {
		printf("error!");
		return;
	}

	//�����ƶ������ƽ��Ѱ������
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

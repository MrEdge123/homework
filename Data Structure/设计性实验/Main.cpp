//������
#include "AVL.cpp"
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

const int maxn = 100000;
const int mod = 20;

int elem[maxn];
int del[maxn];
int cnt = 10;

void rand_elem() {
	for (int i = 0; i < cnt; i++) elem[i] = del[i] = rand() % mod;
}

int main() {

	srand((unsigned int)time(0));
	AVL<int> tree;

	rand_elem();

	cout << "������Ԫ��:\n";
	for (int i = 0; i < cnt; i++) {
		printf("%d ", elem[i]);
	}
	printf("\n\n");

	cout << "���ڲ���Ԫ��...\n";
	for (int i = 0; i < cnt; i++) {
		tree.Insert(elem[i]);
	}
	cout << "�������!" << endl << endl;

	if (tree.Check()) cout << "����ɹ�!" << endl << endl;
	else cout << "����ʧ��!" << endl << endl;
	cout << "tree:\n";
	tree.Print();

	cout << "�������ɾ������Ԫ��...\n";
	for (int i = 0; i < cnt; i++) {
		tree.Delete(del[i]);
	}
	cout << "ɾ�����!" << endl << endl;
	cout << "tree:\n";
	tree.Print();

	int maxx = 0;

	cout << "���ϲ�����:\n";
	rand_elem();
	for (int i = 0; i < cnt; i++) tree.Insert(elem[i]);
	cout << "tree:\n";
	tree.Print();
	AVL<int> tree2;
	rand_elem();
	for (int i = 0; i < cnt; i++) tree2.Insert(elem[i]);
	cout << "tree2:\n";
	tree2.Print();
	tree.Merge_With(tree2);
	cout << "�ϲ����!" << endl << endl;
	cout << "tree:" << endl;
	tree.Print();

	AVL<int> tree3;
	tree2.Clear();
	cout << "��" << elem[cnt/2] << "��ֵ���tree:" << endl;
	tree.Break_Up(tree2, tree3, elem[cnt/2]);
	cout << "������!" << endl << endl;
	cout << "tree2:" << endl;
	tree2.Print();
	cout << "tree3:" << endl;
	tree3.Print();

	cout << "����ִ����ղ���..." << endl << endl;
	tree.Clear();
	tree2.Clear();
	tree3.Clear();
	if (tree.IsEmpty() && tree2.IsEmpty() && tree3.IsEmpty()) cout << "�ɹ�������нڵ�!" << endl << endl;
	cout << endl;

	system("pause");
	return 0;
}

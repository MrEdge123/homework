//主程序
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

	cout << "待插入元素:\n";
	for (int i = 0; i < cnt; i++) {
		printf("%d ", elem[i]);
	}
	printf("\n\n");

	cout << "正在插入元素...\n";
	for (int i = 0; i < cnt; i++) {
		tree.Insert(elem[i]);
	}
	cout << "插入完成!" << endl << endl;

	if (tree.Check()) cout << "插入成功!" << endl << endl;
	else cout << "插入失败!" << endl << endl;
	cout << "tree:\n";
	tree.Print();

	cout << "正在逐个删除所有元素...\n";
	for (int i = 0; i < cnt; i++) {
		tree.Delete(del[i]);
	}
	cout << "删除完成!" << endl << endl;
	cout << "tree:\n";
	tree.Print();

	int maxx = 0;

	cout << "待合并的树:\n";
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
	cout << "合并完成!" << endl << endl;
	cout << "tree:" << endl;
	tree.Print();

	AVL<int> tree3;
	tree2.Clear();
	cout << "以" << elem[cnt/2] << "的值拆分tree:" << endl;
	tree.Break_Up(tree2, tree3, elem[cnt/2]);
	cout << "拆分完成!" << endl << endl;
	cout << "tree2:" << endl;
	tree2.Print();
	cout << "tree3:" << endl;
	tree3.Print();

	cout << "正在执行清空操作..." << endl << endl;
	tree.Clear();
	tree2.Clear();
	tree3.Clear();
	if (tree.IsEmpty() && tree2.IsEmpty() && tree3.IsEmpty()) cout << "成功清空所有节点!" << endl << endl;
	cout << endl;

	system("pause");
	return 0;
}

#include "ƽ�������.cpp"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
using namespace std;

AVL<int> tree[105];
int top = 0;
int id =  0;
int now;
string op;
string val;
const int MOD = 1000000000;

//���س�������
void Continue() {
	printf("\n");
	printf("           ���س�������! ");
	getline(cin, op);
}

//���˵�
void Main() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"           |                  **** ���˵� ****                  |\n"
		"           |                                                    |\n"
		"           | -->1.����ģʽ               רҵ��    ��Ϣ��ȫ     |\n"
		"           | -->2.����ģʽ               �༶��    2018��2��    |\n"
		"           | -->3.����                   ѧ�ţ�    3118005414   |\n"
		"           | -->0.�˳�                   ������    ��ֹ         |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           ��������Ҫ�Ĳ������: "
	);
}

//����ģʽ
void Base_Mode() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 **** ����ģʽ ****                 |\n"
		"           |                                                    |\n"
		"           | -->1.�½���                                        |\n"
		"           | -->2.�鿴�ѽ���                                    |\n"
		"           | -->0.������һ��                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           ��������Ҫ�Ĳ������: "
	);
}

//�½���
void New_List() {
	top++;
	id++;
	tree[top].name = "list";
	tree[top].name += to_string(id);
	tree[top].Clear();
}

//�ѽ����б�
void List() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"           |                  **** �ѽ��� ****                  |\n"
		"           |                                                    |\n"
	);

	char s[100] = "           |";
	//����Ϊ16
	char blank[100] = "                                             |\n";

	for (int i = 1; i <= top; i++) {
		printf("%s -->%d: %s", s, i, tree[i].name.c_str());
		if (i >= 10) printf("%s", blank + 1 + tree[i].name.length());
		else printf("%s", blank + tree[i].name.length());
	}

	printf(
		"           |                                                    |\n"
	);

	if (top != 0) 
	printf(
		"           | -->0.������һ��                                    |\n");

	printf(
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
	);

	if (top != 0)
	printf(
		"           ������Ҫ��������ı��: "
	);
}

//�����б�
void Operator() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 ****  "
	);
	printf("%s  ****", tree[now].name.c_str());

	char blank[100] = "                       |\n";
	
	printf("%s", blank + tree[now].name.length());
	
	printf(
		"           |                                                    |\n"
		"           | -->1.����Ԫ��                                      |\n"
		"           | -->2.����Ԫ��                                      |\n"
		"           | -->3.ɾ��Ԫ��                                      |\n"
		"           | -->4.����һ����                                    |\n"
		"           | -->5.����ֵ��ֱ�                                  |\n"
		"           | -->6.��ӡ����ڲ��ṹ                              |\n"
		"           | -->7.��ձ�                                        |\n"
		"           | -->8.ɾ����                                        |\n"
		"           | -->0.������һ��                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           ��������Ҫ�Ĳ������: "
	);
}

//��ӡ���Ľṹ
void Print() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"                             ****  "
	);

	printf("%s  ****\n", tree[now].name.c_str());

	tree[now].Print();

	printf(
		"            ---------------------------------------------------- \n"
	);
}

//����ģʽ
void Test_Mode() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 **** ����ģʽ ****                 |\n"
		"           |                                                    |\n"
		"           | -->1.�Զ�������в���                              |\n"
		"           | -->2.һ�����ݹ�ģ����                              |\n"
		"           | -->0.�������˵�                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           ��������Ҫ�Ĳ������: "
	);
}

//���ݹ�ģ
void BigData_Test() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 **** ���ݹ�ģ ****                 |\n"
		"           |                                                    |\n"
		"           | -->1.100�������                                   |\n"
		"           | -->2.1000�������                                  |\n"
		"           | -->3.1��������                                   |\n"
		"           | -->4.10��������                                  |\n"
		"           | -->5.100��������                                 |\n"
		"           | -->0.������һ��                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           ��������Ҫ�Ĳ������: "
	);
}

//���������
void Rand_Elem(int* elem, int cnt, int mod) {
	if (cnt <= 10000) {
		for (int i = 0; i < cnt; i++) {
			elem[i] = rand() % mod;
		}
	}
	else {
		for (int i = 0; i < cnt; i++) {
			elem[i] = rand() * 997 % MOD;
		}
	}
	
}

//�㶯��
void Point_Flash(int cnt) {
	for (int i = 0; i < 3; i++) {
		printf(".");
		if(cnt <= 20) Sleep(500);
	}
	printf("\n");
}

//�Զ�����
void Auto_Test(int cnt = 10, int mod = 20) {
	clock_t start, end;
	clock_t rand_start, rand_end;
	clock_t rand_time = 0;

	start = clock();
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"                             **** �Զ����� ****                  \n"
		"\n"
	);

	srand((unsigned int)time(0));

	AVL<int> tree1;
	AVL<int> tree2;

	//��ʼ��
	int* elem = new int[cnt];
	rand_start = clock();
	Rand_Elem(elem, cnt, mod);
	rand_end = clock();
	rand_time += rand_end - rand_start;

	if (cnt <= 20) {
		printf("            ����������:\n");
		printf("            ");
		for (int i = 0; i < cnt; i++) printf("%d ", elem[i]);
		printf("\n");
		printf("            5����������!\n\n");
		Sleep(5000);
	}

	printf("            ���ڲ���");
	Point_Flash(cnt);
	clock_t insert_start = clock();
	for (int i = 0; i < cnt; i++) tree1.Insert(elem[i]);
	clock_t insert_end = clock();
	printf("            �������!\n");
	if (cnt <= 20) {
		printf("            tree:\n");
		tree1.Print();
		Sleep(1000);
		printf("            5�������ɾ����������!\n\n");
		Sleep(5000);
	}
	else printf("\n");

	printf("            ����ɾ��");
	Point_Flash(cnt);
	clock_t delete_start = clock();
	for (int i = 0; i < cnt; i++) tree1.Delete(elem[i]);
	clock_t delete_end = clock();
	printf("            ɾ�����!\n");
	if (cnt <= 20) {
		printf("            tree:\n");
		tree1.Print();
		Sleep(1000);
	}
	else printf("\n");
	
	printf("            ���ϲ��ı�:\n");
	rand_start = clock();
	Rand_Elem(elem, cnt, mod);
	rand_end = clock();
	rand_time += rand_end - rand_start;
	for (int i = 0; i < cnt; i++) tree1.Insert(elem[i]);
	printf("            tree1:\n");
	if (cnt <= 20) {
		tree1.Print();
		Sleep(3000);
	}

	rand_start = clock();
	Rand_Elem(elem, cnt, mod);
	rand_end = clock();
	rand_time += rand_end - rand_start;
	for (int i = 0; i < cnt; i++) tree2.Insert(elem[i]);
	printf("            tree2:\n");
	if (cnt <= 20) {
		tree2.Print();
		Sleep(3000);
	}

	printf("            ���ںϲ�������");
	Point_Flash(cnt);
	clock_t merge_start = clock();
	tree1.Merge_With(tree2);
	clock_t merge_end = clock();
	if (tree1.Check()) {
		printf("            �ϲ��ɹ�!\n");
		if (cnt <= 20) {
			printf("            tree:\n");
			tree1.Print();
		}
		else printf("\n");
	}
	else printf("            �ϲ�ʧ��!\n");
	if (cnt <= 20) {
		printf("            5����ֱ�tree!\n\n");
		Sleep(5000);
	}

	tree2.Clear();
	printf("            ��%d�ļ�ֵ��ֱ�:\n", elem[0]);
	if (cnt <= 20) Sleep(3000);

	clock_t break_start = clock();
	tree1.Break_Up(tree2, elem[0]);
	clock_t break_end = clock();

	printf("            ���ڲ��");
	Point_Flash(cnt);
	if (tree1.Check() && tree2.Check()) {
		printf("            ��ֳɹ�!\n");
		if (cnt <= 20) {
			printf("            tree1:\n");
			tree1.Print();
			Sleep(3000);

			printf("            tree2:\n");
			tree2.Print();
			Sleep(3000);
		}
		else printf("\n");
	}
	else printf("            ���ʧ��!\n");
	if (cnt <= 20) {
		printf("            5���ִ����ղ���!\n\n");
		Sleep(5000);
	}

	printf("            ����ִ����ղ���");
	Point_Flash(cnt);
	clock_t clear_start = clock();
	tree1.Clear();
	tree2.Clear();
	clock_t clear_end = clock();

	if (tree1.IsEmpty() && tree2.IsEmpty()) {
		printf("            �ɹ�������б�!\n\n");
	}
	else printf("            ���ʧ��!\n\n");

	end = clock();

	if (cnt > 20) {
		printf("            ---------------------------------------------------- \n");
		printf("            ����ʱ�䣺\t\t%.3fms\n", (double)(insert_end - insert_start) / CLK_TCK);
		printf("            ɾ��ʱ�䣺\t\t%.3fms\n", (double)(delete_end - delete_start) / CLK_TCK);
		printf("            �ϲ�ʱ�䣺\t\t%.3fms\n", (double)(merge_end - merge_start) / CLK_TCK);
		printf("            ���ʱ�䣺\t\t%.3fms\n", (double)(break_end - break_start) / CLK_TCK);
		printf("            ���ʱ�䣺\t\t%.3fms\n", (double)(clear_end - clear_start) / CLK_TCK);
		printf("            ��������ʱ�䣺\t%.3fms\n", (double)rand_time / CLK_TCK);
		printf("            ��ʱ��(�������)��\t%.3fms\n", (double)(end - start) / CLK_TCK);
		printf("            ---------------------------------------------------- \n");
		printf("\n");
	}

	printf("            �Զ����Խ���!\n\n");
	printf("            ���س�������! ");

	delete[] elem;
	getline(cin, op);
}

//����
void About() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################���� ��̬���ұ� ����################ \n"
		"            ---------------------------------------------------- \n"
		"           |                   **** ���� ****                   |\n"
		"           |                                                    |\n"
		"           |     ����̬���ұ���ڲ�ʵ��Ϊƽ�������(AVL��)������|\n"
		"           | ʵ�ּ򵥵Ĳ��ң����룬ɾ��������                   |\n"
		"           |                                                    |\n"
		"           |                                                    |\n"
		"           |                                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           ���س����������˵�! "
	);
}

//����
void Error() {
	printf("           ��������!\n");
	int cnt = 3;
	while (cnt--) {
		printf("           ��ȴ�%d�����������������!\n", cnt + 1);
		Sleep(1000);
	}
}

//�ж��ַ����Ƿ�Ϊ�Ǹ�����
bool Is_Num(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9') return false;
	}
	return true;
}

//ɾ����
void Del_List(int pos) {
	//ɾ����ʱҪ��ʱ�����ֱ��λ��
	if (now > pos) now--;

	//�ͷŽ�Ҫɾ���ı�ռ�õĿռ�
	tree[pos].Clear();

	//����"��λ"
	for (int i = pos + 1; i <= top; i++) {
		tree[i - 1] = tree[i];
	}

	//��������
	tree[top].size = 0;
	tree[top].name = "";
	top--;
}

//���ô���
void modeset(short w, short h) {
	//	�˺������ô��ڴ�СΪ w*h
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = { w, h };
	SetConsoleScreenBufferSize(hOut, size);
	SMALL_RECT rc = { 0, 0, w, h };
	SetConsoleWindowInfo(hOut, true, &rc);
	return;
}

int main() {

	//���ô��ڴ�С
	modeset(78, 30);
	
LB:
	Main();
	getline(cin, op);

	//���˵�
	if (op == "0" || op == "1" || op == "2" || op == "3") {
		//�˳�
		if (op == "0") goto End;

		//����ģʽ
		if (op == "1") {
		LB1:
			Base_Mode();
			getline(cin, op);

			if (op == "0" || op == "1" || op == "2") {
				if (op == "0") goto LB;

				//�½���
				if (op == "1") {
					New_List();
				LB1_1:
					printf("           ���½��ձ�: %s, �Ƿ��%sִ�в���? ������y/Y; ������n/N: ", tree[top].name.c_str(), tree[top].name.c_str());
					getline(cin, op);
					if (op == "y" || op == "Y") {
						now = top;
						goto LB1_2_X;
					}
					else if (op == "n" || op == "N") goto LB1_2;
					else { Error(); goto LB1_1; }
				}

				//�ѽ���
				if (op == "2") {
				LB1_2:
					List();
					if (top == 0) {
						printf("           �б�Ϊ��, �Ƿ�Ҫ�½���? ������y/Y; ������n/N, ������һ��: ");
						getline(cin, op);
						if (op == "y" || op == "Y") { New_List(); goto LB1_1; }
						else if (op == "n" || op == "N") goto LB1;
						else { Error(); goto LB1_2; }
					}
					else {
						getline(cin, op);

						if(op == "" || Is_Num(op) == false) { Error(); goto LB1_2; }

						if (op == "0") goto LB1;

						now = stoi(op);
						if (now > top) { Error(); goto LB1_2; }
						else goto LB1_2_X;
					}
				}
			}
			else { Error(); goto LB1; }
		}

		//����ģʽ
		if (op == "2") {
		LB2:
			Test_Mode();
			getline(cin, op);
			if (op == "0") goto LB;

			//�Զ��������в���
			if (op == "1") {
				Auto_Test();
				goto LB2;
			}

			//ѡ�����ݹ�ģ����
			if (op == "2") {
			LB2_2:
				BigData_Test();
				getline(cin, op);
				if (op == "0") goto LB2;

				else if (op == "1") Auto_Test(100, 10000);
				else if (op == "2") Auto_Test(1000, 100000);
				else if (op == "3") Auto_Test(10000, 1000000);
				else if (op == "4") Auto_Test(100000, 10000000);
				else if (op == "5") Auto_Test(1000000, 100000000);
				else Error(); 
				
				goto LB2_2;
			}
			else { Error(); goto LB2; }
		}

		//����
		if (op == "3") {
			About();
			getline(cin, op);
			goto  LB;
		}
	}
	else { Error(); goto LB; }

LB1_2_X:
	//��������
	Operator();
	getline(cin, op);

	if (op == "0" || op == "1" || op == "2" || op == "3" || op == "4" || op == "5" || op == "6" || op == "7" || op == "8") {
		if (op == "0") goto LB1_2;
		
		//����
		if (op == "1") {
			//�ж��Ƿ�Ϊ��
			if (tree[now].IsEmpty()) {
				printf("           ��Ϊ��, ���Ȳ�������, ���س�������! ");
				getline(cin, op);
				goto LB1_2_X;
			}
		LB1_2_X_1:
			printf("           ������Ҫ���ҵ�ֵ: ");
			getline(cin, val);

			//�ж������Ƿ���ȷ
			if (val == "") { Error(); goto LB1_2_X_1; }
			if (val[0] == '-') {
				if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_1; }
			}
			else if (Is_Num(val) == false) { Error(); goto LB1_2_X_1; }
			
			//��ʼ����
			int v = stoi(val);
			if (tree[now].IsFind(v)) printf("           %d��%s����!\n", v, tree[now].name.c_str());
			else printf("           %d����%s����!\n", v, tree[now].name.c_str());

			Continue();
			goto LB1_2_X;
		}

		//����
		if (op == "2") {
		LB1_2_X_2:
			printf("           �Ƿ�Ҫ������������? ������y/Y, ������n/N: ");
			getline(cin, op);
			if (op == "y" || op == "Y") {
			LB1_2_X_2_Y:
				printf("           �������������: ");
				getline(cin, val);

				if (val == "") { Error(); goto LB1_2_X_2_Y; }
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_2_Y; }

				//����
				int n = stoi(val);
				if (n > 20) {
					printf("           �����Դ�, �Ƿ�ȷ���ֶ�����%d������? ������y/Y, ����ֱ�ӻس�: ", n);
					getline(cin, op);
					if (op != "y" && op != "Y") goto LB1_2_X_2_Y;
				}

				printf("           ������%d������, ÿ�������ÿո����:\n", n);
				printf("           ");
				
				getline(cin, val);
				stringstream ss(val);
				//��������
				for (int i = 0; i < n; i++) {
					int v;
					ss >> v;
					if (tree[now].IsFind(v)) printf("           %d�Ѵ���!\n", v);
					tree[now].Insert(v);
				}
			}
			else if (op == "n" || op == "N") {
			LB1_2_X_2_N:
				printf("           ������Ҫ���������: ");
				getline(cin, val);

				//�ж������Ƿ���ȷ
				if (val == "") { Error(); goto LB1_2_X_2_N; }
				if (val[0] == '-') {
					if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_2_N; }
				}
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_2_N; }

				//��������
				int v = stoi(val);
				if (tree[now].IsFind(v)) printf("           %d�Ѵ���, �����ظ�����!\n", v);
				else tree[now].Insert(v);
			}
			else { Error(); goto LB1_2_X_2; }

			printf("           �������! 2�����ʾ����ڲ��ṹ...\n");
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//ɾ��
		if (op == "3") {
			//�ж��Ƿ�Ϊ��
			if (tree[now].IsEmpty()) {
				printf("           ��Ϊ��, ���Ȳ�������, ���س�������! ");
				getline(cin, op);
				goto LB1_2_X;
			}
		LB1_2_X_3:
			printf("           �Ƿ�Ҫ��������ɾ��? ������y/Y, ������n/N: ");
			getline(cin, op);
			if (op == "y" || op == "Y") {
			LB1_2_X_3_Y:
				printf("           ������ɾ������: ");
				getline(cin, val);

				if (val == "") { Error(); goto LB1_2_X_3_Y; }
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_3_Y; }

				int n = stoi(val);

				printf("           ������%d������, ÿ�������ÿո����:\n", n);
				printf("           ");

				getline(cin, val);
				stringstream ss(val);

				//ɾ������
				for (int i = 0; i < n; i++) {
					int v;
					ss >> v;
					if (tree[now].IsFind(v) == false) printf("           %d������!\n", v);
					tree[now].Delete(v);
				}
			}
			else if (op == "n" || op == "N") {
			LB1_2_X_3_N:
				printf("           ������Ҫɾ��������: ");
				getline(cin, val);

				//�ж������Ƿ���ȷ
				if (val == "") { Error(); goto LB1_2_X_3_N; }
				if (val[0] == '-') {
					if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_3_N; }
				}
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_3_N; }

				//ɾ������
				int v = stoi(val);
				if (tree[now].IsFind(v) == false) {
					printf("           %d������, �����²鿴��������!\n", v);
					Sleep(1500);
					goto LB1_2_X_6;
				}
				else tree[now].Delete(v);
			}
			else { Error(); goto LB1_2_X_3; }

			printf("           ɾ�����! 2�����ʾ����ڲ��ṹ...\n");
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//����һ����
		if (op == "4") {
			if (top == 1) {
				printf("           ��������ѡ��, ���س�������! ");
				getline(cin, op);
				goto LB1_2_X;
			}
		LB1_2_X_4:
			List();
			getline(cin, op);
			if (op == "0") goto LB1_2_X;
			if (op == "" || Is_Num(op) == false) { Error(); goto LB1_2_X_4; }

			int t = stoi(op);
			if (t > top) { Error(); goto LB1_2_X_4; }
			if (t == now) {
				printf("           ����ѡ���Լ�! ��2�������ѡ��...");
				Sleep(2000);
				goto LB1_2_X_4;
			}

		LB1_2_X_4_S:
			printf("           ȷ��ѡ��: %s����? ������y/Y, ������n/N: ", tree[t].name.c_str());
			getline(cin, op);

			if (op == "y" || op == "Y") {
				tree[now].Merge_With(tree[t]);
			}
			else if (op == "n" || op == "N") goto LB1_2_X_4;
			else { Error(); goto LB1_2_X_4_S; }

		LB1_2_X_4_S2:
			printf("           �������! �Ƿ�Ҫ������: %s? ������y/Y, ������n/N: ", tree[t].name.c_str());
			getline(cin, op);
			if (op == "y" || op == "Y") { printf("           �ѱ�����: %s, ", tree[t].name.c_str()); }
			else if (op == "n" || op == "N") {
				Del_List(t);
				printf("           ��ɾ����: %s, ", tree[t].name.c_str());
			}
			else { Error(); goto LB1_2_X_4_S2; }
			
			printf("2�����ʾ%s���ڲ��ṹ...", tree[now].name.c_str());
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//��ֱ�
		if (op == "5") {
			//�ж��Ƿ�Ϊ��
			if (tree[now].IsEmpty()) {
				printf("           ��Ϊ��, ���Ȳ�������, ���س�������! ");
				getline(cin, op);
				goto LB1_2_X;
			}
		LB1_2_X_5:
			printf("           ��ֵС�ڵ���x�����ݱ����ڱ���, ��ֵ����x�����ݴ�ŵ��±�.\n");
			printf("           �������ֵx: ");
			getline(cin, val);

			//�ж������Ƿ���ȷ
			if (val == "") { Error(); goto LB1_2_X_5; }
			if (val[0] == '-') {
				if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_5; }
			}
			else if (Is_Num(val) == false) { Error(); goto LB1_2_X_5; }

			int x = stoi(val);
		LB1_2_X_5_S:
			printf("           ȷ��Ҫ����ֵ%d��ֱ�? ������y/Y, ������n/N, ȡ�������ֱ�ӻس�: ", x);
			getline(cin, op);
			if (op == "y" || op == "Y") {}
			else if (op == "n" || op == "N") goto LB1_2_X_5;
			else if (op == "") goto LB1_2_X;
			else { Error(); goto LB1_2_X_5_S; }

			New_List();
			tree[now].Break_Up(tree[top], x);

			printf("           ��ֳɹ�! 2�����ʾ%s���ڲ��ṹ...", tree[now].name.c_str());
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//��ӡ
		if (op == "6") {
		LB1_2_X_6:
			Print(); Continue(); goto LB1_2_X; 
		}

		//��ձ�
		if (op == "7") {
			printf("           ȷ��Ҫ���: list%d ? ������y/Y, ����ֱ�ӻس�: ", now);
			getline(cin, op);
			if (op == "y" || op == "Y") {
				tree[now].Clear();
				printf("           ��ճɹ�! 2�����ʾ��Ľṹ...");
				Sleep(2000);
				goto LB1_2_X_6;
			}
			else goto LB1_2_X;
		}

		//ɾ����
		if (op == "8") {
			printf("           ȷ��Ҫɾ��: %s? ������y/Y, ����ֱ�ӻس�: ", tree[now].name.c_str());
			getline(cin, op);
			if (op == "y" || op == "Y") {
				Del_List(now);
				goto LB1_2;
			}
			else goto LB1_2_X;
		}
	}
	else { Error(); goto LB1_2_X; }

End:
	for (int i = 1; i <= top; i++) tree[i].Clear();
	return 0;
}

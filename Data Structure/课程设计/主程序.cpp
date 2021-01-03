#include "平衡二叉树.cpp"
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

//按回车键继续
void Continue() {
	printf("\n");
	printf("           按回车键继续! ");
	getline(cin, op);
}

//主菜单
void Main() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"           |                  **** 主菜单 ****                  |\n"
		"           |                                                    |\n"
		"           | -->1.基础模式               专业：    信息安全     |\n"
		"           | -->2.测试模式               班级：    2018级2班    |\n"
		"           | -->3.关于                   学号：    3118005414   |\n"
		"           | -->0.退出                   姓名：    孔止         |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           请输入想要的操作编号: "
	);
}

//基础模式
void Base_Mode() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 **** 基础模式 ****                 |\n"
		"           |                                                    |\n"
		"           | -->1.新建表                                        |\n"
		"           | -->2.查看已建表                                    |\n"
		"           | -->0.返回上一级                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           请输入想要的操作编号: "
	);
}

//新建表
void New_List() {
	top++;
	id++;
	tree[top].name = "list";
	tree[top].name += to_string(id);
	tree[top].Clear();
}

//已建表列表
void List() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"           |                  **** 已建表 ****                  |\n"
		"           |                                                    |\n"
	);

	char s[100] = "           |";
	//长度为16
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
		"           | -->0.返回上一级                                    |\n");

	printf(
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
	);

	if (top != 0)
	printf(
		"           请输入要操作对象的编号: "
	);
}

//操作列表
void Operator() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 ****  "
	);
	printf("%s  ****", tree[now].name.c_str());

	char blank[100] = "                       |\n";
	
	printf("%s", blank + tree[now].name.length());
	
	printf(
		"           |                                                    |\n"
		"           | -->1.查找元素                                      |\n"
		"           | -->2.插入元素                                      |\n"
		"           | -->3.删除元素                                      |\n"
		"           | -->4.并入一个表                                    |\n"
		"           | -->5.按键值拆分表                                  |\n"
		"           | -->6.打印表的内部结构                              |\n"
		"           | -->7.清空表                                        |\n"
		"           | -->8.删除表                                        |\n"
		"           | -->0.返回上一级                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           请输入想要的操作编号: "
	);
}

//打印树的结构
void Print() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"                             ****  "
	);

	printf("%s  ****\n", tree[now].name.c_str());

	tree[now].Print();

	printf(
		"            ---------------------------------------------------- \n"
	);
}

//测试模式
void Test_Mode() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 **** 测试模式 ****                 |\n"
		"           |                                                    |\n"
		"           | -->1.自动完成所有测试                              |\n"
		"           | -->2.一定数据规模测试                              |\n"
		"           | -->0.返回主菜单                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           请输入想要的操作编号: "
	);
}

//数据规模
void BigData_Test() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"           |                 **** 数据规模 ****                 |\n"
		"           |                                                    |\n"
		"           | -->1.100个随机数                                   |\n"
		"           | -->2.1000个随机数                                  |\n"
		"           | -->3.1万个随机数                                   |\n"
		"           | -->4.10万个随机数                                  |\n"
		"           | -->5.100万个随机数                                 |\n"
		"           | -->0.返回上一级                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           请输入想要的操作编号: "
	);
}

//生成随机数
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

//点动画
void Point_Flash(int cnt) {
	for (int i = 0; i < 3; i++) {
		printf(".");
		if(cnt <= 20) Sleep(500);
	}
	printf("\n");
}

//自动测试
void Auto_Test(int cnt = 10, int mod = 20) {
	clock_t start, end;
	clock_t rand_start, rand_end;
	clock_t rand_time = 0;

	start = clock();
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"                             **** 自动测试 ****                  \n"
		"\n"
	);

	srand((unsigned int)time(0));

	AVL<int> tree1;
	AVL<int> tree2;

	//初始化
	int* elem = new int[cnt];
	rand_start = clock();
	Rand_Elem(elem, cnt, mod);
	rand_end = clock();
	rand_time += rand_end - rand_start;

	if (cnt <= 20) {
		printf("            待插入数据:\n");
		printf("            ");
		for (int i = 0; i < cnt; i++) printf("%d ", elem[i]);
		printf("\n");
		printf("            5秒后插入数据!\n\n");
		Sleep(5000);
	}

	printf("            正在插入");
	Point_Flash(cnt);
	clock_t insert_start = clock();
	for (int i = 0; i < cnt; i++) tree1.Insert(elem[i]);
	clock_t insert_end = clock();
	printf("            插入完成!\n");
	if (cnt <= 20) {
		printf("            tree:\n");
		tree1.Print();
		Sleep(1000);
		printf("            5秒后依次删除所有数据!\n\n");
		Sleep(5000);
	}
	else printf("\n");

	printf("            正在删除");
	Point_Flash(cnt);
	clock_t delete_start = clock();
	for (int i = 0; i < cnt; i++) tree1.Delete(elem[i]);
	clock_t delete_end = clock();
	printf("            删除完成!\n");
	if (cnt <= 20) {
		printf("            tree:\n");
		tree1.Print();
		Sleep(1000);
	}
	else printf("\n");
	
	printf("            待合并的表:\n");
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

	printf("            正在合并两个表");
	Point_Flash(cnt);
	clock_t merge_start = clock();
	tree1.Merge_With(tree2);
	clock_t merge_end = clock();
	if (tree1.Check()) {
		printf("            合并成功!\n");
		if (cnt <= 20) {
			printf("            tree:\n");
			tree1.Print();
		}
		else printf("\n");
	}
	else printf("            合并失败!\n");
	if (cnt <= 20) {
		printf("            5秒后拆分表tree!\n\n");
		Sleep(5000);
	}

	tree2.Clear();
	printf("            以%d的键值拆分表:\n", elem[0]);
	if (cnt <= 20) Sleep(3000);

	clock_t break_start = clock();
	tree1.Break_Up(tree2, elem[0]);
	clock_t break_end = clock();

	printf("            正在拆分");
	Point_Flash(cnt);
	if (tree1.Check() && tree2.Check()) {
		printf("            拆分成功!\n");
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
	else printf("            拆分失败!\n");
	if (cnt <= 20) {
		printf("            5秒后执行清空操作!\n\n");
		Sleep(5000);
	}

	printf("            正在执行清空操作");
	Point_Flash(cnt);
	clock_t clear_start = clock();
	tree1.Clear();
	tree2.Clear();
	clock_t clear_end = clock();

	if (tree1.IsEmpty() && tree2.IsEmpty()) {
		printf("            成功清空所有表!\n\n");
	}
	else printf("            清空失败!\n\n");

	end = clock();

	if (cnt > 20) {
		printf("            ---------------------------------------------------- \n");
		printf("            插入时间：\t\t%.3fms\n", (double)(insert_end - insert_start) / CLK_TCK);
		printf("            删除时间：\t\t%.3fms\n", (double)(delete_end - delete_start) / CLK_TCK);
		printf("            合并时间：\t\t%.3fms\n", (double)(merge_end - merge_start) / CLK_TCK);
		printf("            拆分时间：\t\t%.3fms\n", (double)(break_end - break_start) / CLK_TCK);
		printf("            清空时间：\t\t%.3fms\n", (double)(clear_end - clear_start) / CLK_TCK);
		printf("            生成数据时间：\t%.3fms\n", (double)rand_time / CLK_TCK);
		printf("            总时间(包括输出)：\t%.3fms\n", (double)(end - start) / CLK_TCK);
		printf("            ---------------------------------------------------- \n");
		printf("\n");
	}

	printf("            自动测试结束!\n\n");
	printf("            按回车键继续! ");

	delete[] elem;
	getline(cin, op);
}

//关于
void About() {
	system("cls");
	printf(
		"\n"
		"\n"
		"            ################—— 动态查找表 ——################ \n"
		"            ---------------------------------------------------- \n"
		"           |                   **** 关于 ****                   |\n"
		"           |                                                    |\n"
		"           |     本动态查找表的内部实现为平衡二叉树(AVL树)，可以|\n"
		"           | 实现简单的查找，插入，删除操作。                   |\n"
		"           |                                                    |\n"
		"           |                                                    |\n"
		"           |                                                    |\n"
		"            ---------------------------------------------------- \n"
		"           ______________________________________________________\n"
		"\n"
		"           按回车键返回主菜单! "
	);
}

//报错
void Error() {
	printf("           操作有误!\n");
	int cnt = 3;
	while (cnt--) {
		printf("           请等待%d秒后重新输入操作编号!\n", cnt + 1);
		Sleep(1000);
	}
}

//判断字符串是否为非负整数
bool Is_Num(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9') return false;
	}
	return true;
}

//删除表
void Del_List(int pos) {
	//删除表时要及时更新现表的位置
	if (now > pos) now--;

	//释放将要删除的表占用的空间
	tree[pos].Clear();

	//进行"移位"
	for (int i = pos + 1; i <= top; i++) {
		tree[i - 1] = tree[i];
	}

	//变量赋空
	tree[top].size = 0;
	tree[top].name = "";
	top--;
}

//设置窗口
void modeset(short w, short h) {
	//	此函数设置窗口大小为 w*h
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = { w, h };
	SetConsoleScreenBufferSize(hOut, size);
	SMALL_RECT rc = { 0, 0, w, h };
	SetConsoleWindowInfo(hOut, true, &rc);
	return;
}

int main() {

	//设置窗口大小
	modeset(78, 30);
	
LB:
	Main();
	getline(cin, op);

	//主菜单
	if (op == "0" || op == "1" || op == "2" || op == "3") {
		//退出
		if (op == "0") goto End;

		//基础模式
		if (op == "1") {
		LB1:
			Base_Mode();
			getline(cin, op);

			if (op == "0" || op == "1" || op == "2") {
				if (op == "0") goto LB;

				//新建表
				if (op == "1") {
					New_List();
				LB1_1:
					printf("           已新建空表: %s, 是否对%s执行操作? 是输入y/Y; 否输入n/N: ", tree[top].name.c_str(), tree[top].name.c_str());
					getline(cin, op);
					if (op == "y" || op == "Y") {
						now = top;
						goto LB1_2_X;
					}
					else if (op == "n" || op == "N") goto LB1_2;
					else { Error(); goto LB1_1; }
				}

				//已建表
				if (op == "2") {
				LB1_2:
					List();
					if (top == 0) {
						printf("           列表为空, 是否要新建表? 是输入y/Y; 否输入n/N, 返回上一级: ");
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

		//测试模式
		if (op == "2") {
		LB2:
			Test_Mode();
			getline(cin, op);
			if (op == "0") goto LB;

			//自动测试所有操作
			if (op == "1") {
				Auto_Test();
				goto LB2;
			}

			//选择数据规模测试
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

		//关于
		if (op == "3") {
			About();
			getline(cin, op);
			goto  LB;
		}
	}
	else { Error(); goto LB; }

LB1_2_X:
	//基本操作
	Operator();
	getline(cin, op);

	if (op == "0" || op == "1" || op == "2" || op == "3" || op == "4" || op == "5" || op == "6" || op == "7" || op == "8") {
		if (op == "0") goto LB1_2;
		
		//查找
		if (op == "1") {
			//判断是否为空
			if (tree[now].IsEmpty()) {
				printf("           表为空, 请先插入数据, 按回车键返回! ");
				getline(cin, op);
				goto LB1_2_X;
			}
		LB1_2_X_1:
			printf("           请输入要查找的值: ");
			getline(cin, val);

			//判断输入是否正确
			if (val == "") { Error(); goto LB1_2_X_1; }
			if (val[0] == '-') {
				if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_1; }
			}
			else if (Is_Num(val) == false) { Error(); goto LB1_2_X_1; }
			
			//开始查找
			int v = stoi(val);
			if (tree[now].IsFind(v)) printf("           %d在%s里面!\n", v, tree[now].name.c_str());
			else printf("           %d不在%s里面!\n", v, tree[now].name.c_str());

			Continue();
			goto LB1_2_X;
		}

		//插入
		if (op == "2") {
		LB1_2_X_2:
			printf("           是否要进行批量插入? 是输入y/Y, 否输入n/N: ");
			getline(cin, op);
			if (op == "y" || op == "Y") {
			LB1_2_X_2_Y:
				printf("           请输入插入数量: ");
				getline(cin, val);

				if (val == "") { Error(); goto LB1_2_X_2_Y; }
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_2_Y; }

				//警告
				int n = stoi(val);
				if (n > 20) {
					printf("           数量稍大, 是否确定手动输入%d个数据? 是输入y/Y, 否则直接回车: ", n);
					getline(cin, op);
					if (op != "y" && op != "Y") goto LB1_2_X_2_Y;
				}

				printf("           请输入%d个数据, 每个数据用空格隔开:\n", n);
				printf("           ");
				
				getline(cin, val);
				stringstream ss(val);
				//插入数据
				for (int i = 0; i < n; i++) {
					int v;
					ss >> v;
					if (tree[now].IsFind(v)) printf("           %d已存在!\n", v);
					tree[now].Insert(v);
				}
			}
			else if (op == "n" || op == "N") {
			LB1_2_X_2_N:
				printf("           请输入要插入的数据: ");
				getline(cin, val);

				//判断输入是否正确
				if (val == "") { Error(); goto LB1_2_X_2_N; }
				if (val[0] == '-') {
					if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_2_N; }
				}
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_2_N; }

				//插入数据
				int v = stoi(val);
				if (tree[now].IsFind(v)) printf("           %d已存在, 无需重复插入!\n", v);
				else tree[now].Insert(v);
			}
			else { Error(); goto LB1_2_X_2; }

			printf("           插入完成! 2秒后显示表的内部结构...\n");
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//删除
		if (op == "3") {
			//判断是否为空
			if (tree[now].IsEmpty()) {
				printf("           表为空, 请先插入数据, 按回车键返回! ");
				getline(cin, op);
				goto LB1_2_X;
			}
		LB1_2_X_3:
			printf("           是否要进行批量删除? 是输入y/Y, 否输入n/N: ");
			getline(cin, op);
			if (op == "y" || op == "Y") {
			LB1_2_X_3_Y:
				printf("           请输入删除数量: ");
				getline(cin, val);

				if (val == "") { Error(); goto LB1_2_X_3_Y; }
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_3_Y; }

				int n = stoi(val);

				printf("           请输入%d个数据, 每个数据用空格隔开:\n", n);
				printf("           ");

				getline(cin, val);
				stringstream ss(val);

				//删除数据
				for (int i = 0; i < n; i++) {
					int v;
					ss >> v;
					if (tree[now].IsFind(v) == false) printf("           %d不存在!\n", v);
					tree[now].Delete(v);
				}
			}
			else if (op == "n" || op == "N") {
			LB1_2_X_3_N:
				printf("           请输入要删除的数据: ");
				getline(cin, val);

				//判断输入是否正确
				if (val == "") { Error(); goto LB1_2_X_3_N; }
				if (val[0] == '-') {
					if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_3_N; }
				}
				else if (Is_Num(val) == false) { Error(); goto LB1_2_X_3_N; }

				//删除数据
				int v = stoi(val);
				if (tree[now].IsFind(v) == false) {
					printf("           %d不存在, 请重新查看表内数据!\n", v);
					Sleep(1500);
					goto LB1_2_X_6;
				}
				else tree[now].Delete(v);
			}
			else { Error(); goto LB1_2_X_3; }

			printf("           删除完成! 2秒后显示表的内部结构...\n");
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//并入一个表
		if (op == "4") {
			if (top == 1) {
				printf("           无其他可选表, 按回车键返回! ");
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
				printf("           不能选择自己! 请2秒后重新选择...");
				Sleep(2000);
				goto LB1_2_X_4;
			}

		LB1_2_X_4_S:
			printf("           确定选择: %s并入? 是输入y/Y, 否输入n/N: ", tree[t].name.c_str());
			getline(cin, op);

			if (op == "y" || op == "Y") {
				tree[now].Merge_With(tree[t]);
			}
			else if (op == "n" || op == "N") goto LB1_2_X_4;
			else { Error(); goto LB1_2_X_4_S; }

		LB1_2_X_4_S2:
			printf("           并入完成! 是否要保留表: %s? 是输入y/Y, 否输入n/N: ", tree[t].name.c_str());
			getline(cin, op);
			if (op == "y" || op == "Y") { printf("           已保留表: %s, ", tree[t].name.c_str()); }
			else if (op == "n" || op == "N") {
				Del_List(t);
				printf("           已删除表: %s, ", tree[t].name.c_str());
			}
			else { Error(); goto LB1_2_X_4_S2; }
			
			printf("2秒后显示%s的内部结构...", tree[now].name.c_str());
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//拆分表
		if (op == "5") {
			//判断是否为空
			if (tree[now].IsEmpty()) {
				printf("           表为空, 请先插入数据, 按回车键返回! ");
				getline(cin, op);
				goto LB1_2_X;
			}
		LB1_2_X_5:
			printf("           键值小于等于x的数据保留在本表, 键值大于x的数据存放到新表.\n");
			printf("           请输入键值x: ");
			getline(cin, val);

			//判断输入是否正确
			if (val == "") { Error(); goto LB1_2_X_5; }
			if (val[0] == '-') {
				if (val.length() == 1 || Is_Num(string(val, 1)) == false) { Error(); goto LB1_2_X_5; }
			}
			else if (Is_Num(val) == false) { Error(); goto LB1_2_X_5; }

			int x = stoi(val);
		LB1_2_X_5_S:
			printf("           确定要按键值%d拆分表? 是输入y/Y, 否输入n/N, 取消拆分则直接回车: ", x);
			getline(cin, op);
			if (op == "y" || op == "Y") {}
			else if (op == "n" || op == "N") goto LB1_2_X_5;
			else if (op == "") goto LB1_2_X;
			else { Error(); goto LB1_2_X_5_S; }

			New_List();
			tree[now].Break_Up(tree[top], x);

			printf("           拆分成功! 2秒后显示%s的内部结构...", tree[now].name.c_str());
			Sleep(2000);
			goto LB1_2_X_6;
		}

		//打印
		if (op == "6") {
		LB1_2_X_6:
			Print(); Continue(); goto LB1_2_X; 
		}

		//清空表
		if (op == "7") {
			printf("           确定要清空: list%d ? 是输入y/Y, 否则直接回车: ", now);
			getline(cin, op);
			if (op == "y" || op == "Y") {
				tree[now].Clear();
				printf("           清空成功! 2秒后显示表的结构...");
				Sleep(2000);
				goto LB1_2_X_6;
			}
			else goto LB1_2_X;
		}

		//删除表
		if (op == "8") {
			printf("           确定要删除: %s? 是输入y/Y, 否则直接回车: ", tree[now].name.c_str());
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

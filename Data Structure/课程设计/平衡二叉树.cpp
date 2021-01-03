#include <iostream>
#include <assert.h>
#include <string>
#define max(a, b) (a > b ? a : b)
using namespace std;

template<class KeyType>
class AVL {
public:
	struct Node {
		KeyType key;       //键值
		short lh, rh;      //lh:左子树高度  rh:右子树高度
		Node* lchild;      //左孩子
		Node* rchild;      //右孩子

		Node() {
			key = 0;
			lh = rh = 0;
			lchild = rchild = NULL;
		}
	};

	Node* head;
	int size;
	string name;

	AVL() {
		head = NULL;
		size = 0;
	}

	/*
	AVL树的关键内部操作:

	Search: 查找
	Updata_h: 更新节点高度
	L_Rotate: 左旋
	R_Rotate: 右旋
	L_Balance: 平衡左子树
	R_Balance: 平衡右子树
	*/

	//搜索递归函数: 搜索键值为key的节点
	Node* Search(Node* p, KeyType& key) {
		if (p == NULL) return NULL;
		if (key == p->key) return p;

		if (key < p->key) return Search(p->lchild, key);
		else return Search(p->rchild, key);
	}

	//更新p节点左子树和右子树的高度
	void Update_h(Node* p) {
		if (p->lchild == NULL) p->lh = 0;
		else p->lh = max(p->lchild->lh, p->lchild->rh) + 1;    //更新左子树的高度

		if (p->rchild == NULL) p->rh = 0;
		else p->rh = max(p->rchild->lh, p->rchild->rh) + 1;    //更新右子树的高度
	}

	//右旋: p:根节点, parent:p的双亲节点
	void R_Rotate(Node* p, Node* parent) {
		Node* top = parent;

		Node* lc = p->lchild;

		//主要操作
		p->lchild = lc->rchild;
		lc->rchild = p;

		//更新p节点左子树的高度, lc节点右子树的高度
		Update_h(p);
		Update_h(lc);

		//特殊情况判断
		if (p == head) head = lc;

		//更新p的双亲节点信息
		if (top == NULL) return;
		if (top->lchild == p) top->lchild = lc;
		else top->rchild = lc;
	}

	//左旋: p:根节点, parent:p的双亲节点
	void L_Rotate(Node* p, Node* parent) {
		Node* top = parent;

		Node* rc = p->rchild;

		//主要操作
		p->rchild = rc->lchild;
		rc->lchild = p;

		//更新p节点左子树的高度, rc节点右子树的高度
		Update_h(p);
		Update_h(rc);

		//特殊情况判断
		if (p == head) head = rc;

		//更新p的双亲节点信息
		if (top == NULL) return;
		if (top->lchild == p) top->lchild = rc;
		else top->rchild = rc;
	}

	//平衡左子树: p:最小失衡子树的根节点, parent:p的双亲节点
	void L_Balance(Node* p, Node* parent) {
		Update_h(p);

		if (p->lh - p->rh == 2) {        //p的左子树高
			if (p->lchild->lh >= p->lchild->rh) {    //LL: 在p的左子树的左孩子插入节点
				R_Rotate(p, parent);
			}
			else {                       //LR: 在p的左子树的右孩子插入节点
				L_Rotate(p->lchild, p);
				R_Rotate(p, parent);
			}
		}
	}

	//平衡右子树: p:最小失衡子树的根节点, parent:p的双亲节点
	void R_Balance(Node* p, Node* parent) {
		Update_h(p);

		if (p->rh - p->lh == 2) {        //p的右子树高
			if (p->rchild->rh >= p->rchild->lh) {    //RR: 在p的右子树的右孩子插入节点
				L_Rotate(p, parent);
			}
			else {                       //RL: 在p的右子树的左孩子插入节点
				R_Rotate(p->rchild, p);
				L_Rotate(p, parent);
			}
		}
	}

	/*
	AVL树的基本操作:

	IsEmpty: 判空
	Clear: 清空
	IsFind: 查找
	Insert: 插入
	Delete: 删除
	*/

	//判断树是否为空
	bool IsEmpty() {
		return head == NULL;
	}

	//清空以p为根节点的树
	void Clear(Node* p) {
		if (p == NULL) return;

		Clear(p->lchild);
		Clear(p->rchild);
		delete p;
	}

	//清空树
	void Clear() {
		Clear(head);
		head = NULL;
		size = 0;
	}

	//查找树中是否存在键值key
	bool IsFind(KeyType& key) {
		return Search(head, key) != NULL;
	}

	//插入递归函数: p:当前节点, New:要插入的新节点, parent:p的双亲节点
	void Insert(Node* p, Node* New, Node* parent) {
		if (New->key < p->key) {
			if (p->lchild == NULL) {
				p->lchild = New;    //插入新节点
				p->lh++;            //更新高度
				return;
			}

			Insert(p->lchild, New, p);     //插入到左子树
			L_Balance(p, parent);          //平衡左子树
		}
		else {
			if (p->rchild == NULL) {
				p->rchild = New;    //插入新节点
				p->rh++;            //更新高度
				return;
			}

			Insert(p->rchild, New, p);     //插入到右子树
			R_Balance(p, parent);          //平衡右子树
		}
	}

	//插入键值
	void Insert(KeyType key) {
		//如果存在就不插入
		if (IsFind(key)) return;

		//创建新节点
		Node* New = new Node;
		New->key = key;

		//判断是否为空树
		if (head == NULL) head = New;
		else Insert(head, New, NULL);

		//更新树的大小
		size++;
	}

	//删除递归函数: p:当前节点, key:要删除的键值, parent:p的双亲节点
	void Delete(Node* p, KeyType key, Node* parent) {
		if (key < p->key) {
			Delete(p->lchild, key, p);
			R_Balance(p, parent);    //左子树节点被删, 平衡右子树
		}
		else if (key > p->key) {
			Delete(p->rchild, key, p);
			L_Balance(p, parent);    //右子树节点被删, 平衡左子树
		}
		//找到键值
		else {
			//p为根节点时的特殊处理
			if (p == head) {
				//只有单个节点
				if (p->lchild == NULL && p->rchild == NULL) {
					delete head;
					head = NULL;
					return;
				}

				//只有左子树
				if (p->rchild == NULL) {
					Node* t = head->lchild;
					delete head;
					head = t;
					return;
				}

				//只有右子树
				if (p->lchild == NULL) {
					Node* t = head->rchild;
					delete head;
					head = t;
					return;
				}

			}

			//叶子节点
			if (p->lchild == NULL && p->rchild == NULL) {
				//将双亲节点的孩子指针置空
				if (parent->lchild == p) parent->lchild = NULL;
				else parent->rchild = NULL;

				delete p;
				return;
			}

			//只有左子树
			else if (p->rchild == NULL) {
				Node* top = parent;  //p的双亲节点

				//将双亲节点的孩子指针, 指向左子树根节点
				if (top->lchild == p) top->lchild = p->lchild;
				else top->rchild = p->lchild;

				delete p;
				return;
			}

			//只有右子树
			else if (p->lchild == NULL) {
				Node* top = parent;

				//将双亲节点的孩子指针, 指向右子树根节点
				if (top->lchild == p) top->lchild = p->rchild;
				else top->rchild = p->rchild;

				delete p;
				return;
			}

			//左右子树都有, 找右子树的最小值覆盖, 然后删除最小值节点
			else {
				Node* now = p->rchild;
				while (now->lchild != NULL) now = now->lchild;

				p->key = now->key;
				Delete(p->rchild, now->key, p);

				L_Balance(p, parent);    //右子树节点被删, 平衡左子树
			}
		}
	}

	//删除键值
	void Delete(KeyType key) {
		//键值不存在
		if (IsFind(key) == false) return;

		//删除键值
		Delete(head, key, NULL);

		//更新树的大小
		size--;
	}

	/*
	AVL树的其他操作:

	Print: 显示AVL树结构
	Merge_With: 合并两个AVL树
	Break_Up: 按键值分成两个AVL树
	Check: 检查树的结构
	*/

	//打印递归函数
	void Print(Node* p, int h) {
		if (p == NULL) return;

		cout << "            ";
		for (int i = 0; i < h; i++) cout << "\t";
		cout << p->key << endl;

		Print(p->lchild, h + 1);
		Print(p->rchild, h + 1);
	}

	//打印AVL树(凹入表)
	void Print() {
		cout << endl;
		Print(head, 0);
		cout << endl;
	}

	//把节点为p的AVL树放进顺序表
	void Push_In_List(Node* p, int& cnt, Node** list) {
		if (p == NULL) return;

		Push_In_List(p->lchild, cnt, list);
		list[cnt++] = p;
		Push_In_List(p->rchild, cnt, list);
	}

	//由有序顺序表建立AVL树
	Node* Build(int l, int r, Node** list) {
		if (l > r) return NULL;

		int mid = (l + r) / 2;

		Node* lc = Build(l, mid - 1, list);
		Node* rc = Build(mid + 1, r, list);

		Node* now = new Node;   //创建新节点
		*now = *(list[mid]);    //复制新节点

		now->lchild = lc;
		now->rchild = rc;

		Update_h(now);

		return now;
	}

	//把a并入现今的AVL树(不会破坏a结构)
	void Merge_With(AVL& a) {
		if (a.head == head) return;

		//创建顺序表
		Node** list1 = new Node * [size];
		Node** list2 = new Node * [a.size];
		int cnt1, cnt2;
		cnt1 = cnt2 = 0;

		//先把节点按升序放进顺序表
		Push_In_List(head, cnt1, list1);
		Push_In_List(a.head, cnt2, list2);

		//创建新的顺序表
		Node** list = new Node * [cnt1 + cnt2];

		//合并两个顺序表
		int pos1, pos2, pos;
		pos1 = pos2 = pos = 0;
		while (pos1 < cnt1 && pos2 < cnt2) {
			if (list1[pos1]->key < list2[pos2]->key) list[pos++] = list1[pos1++];
			else {
				if (list1[pos1]->key == list2[pos2]->key) pos1++;
				list[pos++] = list2[pos2++];
			}
		}

		while (pos1 < cnt1) list[pos++] = list1[pos1++];
		while (pos2 < cnt2) list[pos++] = list2[pos2++];

		//保留旧树的根
		Node* old = head;

		//创建新的AVL树
		head = Build(0, pos - 1, list);
		size = pos;

		//释放旧树的根的内存
		Clear(old);

		//释放顺序表占用的内存
		delete[] list1;
		delete[] list2;
		delete[] list;
	}

	//根据键值x, 把AVL树大于x的部分, 分裂到空树b
	void Break_Up(AVL& b, KeyType x) {
		if (b.head != NULL) return;

		//创建顺序表
		Node** list = new Node * [size];
		int cnt = 0;

		//把节点按升序放入顺序表
		Push_In_List(head, cnt, list);

		//折半查找小于等于x的最大key
		int l, r, mid;
		l = 0, r = size - 1;
		while (l < r) {
			mid = (l + r) / 2;
			if (list[mid]->key < x) l = mid + 1;
			else r = mid;
		}
		mid = l;
		if (list[mid]->key > x) mid--;

		//保留旧树的根
		Node* old = head;

		//把小于等于x的节点放到树a, 大于x的节点放到树b
		head = Build(0, mid, list);
		b.head = Build(mid + 1, size - 1, list);

		//确定树的大小
		b.size = size - (mid + 1);
		size = mid + 1;

		//释放旧树的根的内存
		Clear(old);
		
		//释放顺序表占用的内存
		delete[] list;
	}

	//检查递归函数
	bool Check(Node* p, int& cnt, KeyType* key) {
		if (p == NULL) return true;

		bool ok = true;

		if (p->lh - p->rh <= -2 && p->lh - p->rh >= 2) return false;

		ok = Check(p->lchild, cnt, key);
		if (ok == false) return false;
		key[cnt++] = p->key;

		ok = Check(p->rchild, cnt, key);
		if (ok == false) return false;

		return true;
	}

	//检查是否为平衡二叉树
	bool Check() {
		int cnt = 0;
		KeyType* key = new KeyType[size + 5];

		if (Check(head, cnt, key) == false) {
			delete[] key;
			return false;
		}

		bool ok = true;
		for (int i = 0; i < cnt - 1; i++) {
			if ((key[i] < key[i + 1]) == false) {
				ok = false;
				break;
			}
		}

		delete[] key;
		return ok;
	}
};
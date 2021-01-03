#include <iostream>
#include <assert.h>
#define max(a, b) (a > b ? a : b)
using namespace std;

template<class KeyType>
class AVL {
public:
	struct Node {
		KeyType key;
		short lh, rh;
		Node* lchild;
		Node* rchild;
		Node* parent;

		Node() {
			key = 0;
			lh = rh = 0;
			parent = lchild = rchild = NULL;
		}
	};

	Node* head;
	int size;

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

	//搜索键值为key的节点
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

	//右旋
	void R_Rotate(Node* p) {
		Node* top = p->parent;

		Node* lc = p->lchild;

		//主要操作
		p->lchild = lc->rchild;
		lc->rchild = p;

		//更新对应的双亲节点
		lc->parent = top;
		p->parent = lc;
		if (p->lchild != NULL) p->lchild->parent = p;

		//更新p节点左子树的高度, lc节点右子树的高度
		Update_h(p);
		Update_h(lc);
		/*
		if (p->lchild != NULL) p->lh = max(p->lchild->lh, p->lchild->rh) + 1;
		else p->lh = 0;
		lc->rh = max(p->lh, p->rh) + 1;
		*/

		if (p == head) head = lc;

		//更新顶点双亲节点信息
		if (top == NULL) return;
		if (top->lchild == p) top->lchild = lc;
		else top->rchild = lc;
	}

	//左旋
	void L_Rotate(Node* p) {
		Node* top = p->parent;

		Node* rc = p->rchild;

		//主要操作
		p->rchild = rc->lchild;
		rc->lchild = p;

		//更新对应的双亲节点
		rc->parent = top;
		p->parent = rc;
		if (p->rchild != NULL) p->rchild->parent = p;

		//更新p节点左子树的高度, rc节点右子树的高度
		Update_h(p);
		Update_h(rc);
		/*
		if (p->rchild != NULL) p->rh = max(p->rchild->lh, p->rchild->rh) + 1;
		else p->rh = 0;
		rc->lh = max(p->lh, p->rh) + 1;
		*/

		if (p == head) head = rc;

		//更新顶点双亲节点信息
		if (top == NULL) return;
		if (top->lchild == p) top->lchild = rc;
		else top->rchild = rc;
	}

	//平衡左子树
	void L_Balance(Node* p) {
		Update_h(p);

		if (p->lh - p->rh == 2) {        //p的左子树高
			if (p->lchild->lh >= p->lchild->rh) {    //LL: 在p的左子树的左孩子插入节点
				R_Rotate(p);
			}
			else {                       //LR: 在p的左子树的右孩子插入节点
				L_Rotate(p->lchild);
				R_Rotate(p);
			}
		}
	}

	//平衡右子树
	void R_Balance(Node* p) {
		Update_h(p);

		if (p->rh - p->lh == 2) {        //p的右子树高
			if (p->rchild->rh >= p->rchild->lh) {    //RR: 在p的右子树的右孩子插入节点
				L_Rotate(p);
			}
			else {                       //RL: 在p的右子树的左孩子插入节点
				R_Rotate(p->rchild);
				L_Rotate(p);
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
	}

	//查找树中是否存在键值key
	bool IsFind(KeyType& key) {
		return Search(head, key) != NULL;
	}

	//插入递归函数
	void Insert(Node* p, Node* New) {
		if (New->key < p->key) {
			if (p->lchild == NULL) {
				New->parent = p;
				p->lchild = New;
				p->lh++;
				return;
			}

			Insert(p->lchild, New);     //插入到左子树
			L_Balance(p);    //平衡左子树
		}
		else {
			if (p->rchild == NULL) {
				New->parent = p;
				p->rchild = New;
				p->rh++;
				return;
			}

			Insert(p->rchild, New);     //插入到右子树
			R_Balance(p);    //平衡右子树
		}
	}

	//插入键值
	void Insert(KeyType key) {
		if (IsFind(key)) return;

		Node* New = new Node;
		New->key = key;

		if (head == NULL) head = New;
		else Insert(head, New);

		size++;
	}

	//删除递归函数
	void Delete(Node* p, KeyType key) {
		if (key < p->key) {
			Delete(p->lchild, key);
			R_Balance(p);    //左子树节点被删, 平衡右子树
		}
		else if (key > p->key) {
			Delete(p->rchild, key);
			L_Balance(p);    //右子树节点被删, 平衡左子树
		}
		else {
			//p为根节点时的特殊处理
			if (p == head) {   
				if (p->lchild == NULL && p->rchild == NULL) {  //只有单个节点
					delete head;
					head = NULL;
					return;
				}

				if (p->rchild == NULL) {  //只有左子树
					head->lchild->parent = NULL;
					Node* t = head->lchild;
					delete head;
					head = t;
					return;
				}

				if (p->lchild == NULL) {  //只有右子树
					head->rchild->parent = NULL;
					Node* t = head->rchild;
					delete head;
					head = t;
					return;
				}

			}

			//叶子节点
			if (p->lchild == NULL && p->rchild == NULL) {   
				//将双亲节点的孩子指针置空
				if (p->parent->lchild == p) p->parent->lchild = NULL;
				else p->parent->rchild = NULL;

				delete p;
				return;
			}

			//只有左子树
			if (p->rchild == NULL) {    
				Node* top = p->parent;  //p的双亲节点

				//将双亲节点的孩子指针, 指向左子树根节点
				if (top->lchild == p) top->lchild = p->lchild;
				else top->rchild = p->lchild;

				//将左子树的根节点双亲指针, 指向p的双亲节点
				p->lchild->parent = top;

				delete p;
				return;
			}

			//只有右子树
			if (p->lchild == NULL) {    
				Node* top = p->parent;

				//将双亲节点的孩子指针, 指向右子树根节点
				if (top->lchild == p) top->lchild = p->rchild;
				else top->rchild = p->rchild;

				//将右子树的根节点双亲指针, 指向p的双亲节点
				p->rchild->parent = top;

				delete p;
				return;
			}

			//左右子树都有, 找右子树的最小值覆盖, 然后删除最小值节点
			Node* now = p->rchild;
			while (now->lchild != NULL) now = now->lchild;

			p->key = now->key;
			Delete(p->rchild, now->key);

			L_Balance(p);    //右子树节点被删, 平衡左子树
		}
	}

	//删除键值
	void Delete(KeyType key) {
		if (IsFind(key) == false) return;
		Delete(head, key);
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

		for (int i = 0; i < h; i++) cout << "\t";
		cout << p->key << endl;

		Print(p->lchild, h+1);
		Print(p->rchild, h+1);
	}

	//打印AVL树(凹入表)
	void Print() {
		cout << endl;
		Print(head, 0);
		cout << endl;
	}

	//把节点为p的AVL树放进顺序表
	void Push_In_List(Node* p, int& cnt, Node** list){
		if (p == NULL) return;

		Push_In_List(p->lchild, cnt, list);
		list[cnt++] = p;
		Push_In_List(p->rchild, cnt, list);
	}

	//由有序顺序表建立AVL树
	Node* Build(int l, int r, Node** list) {
		if (l > r) return NULL;

		int mid = (l + r) / 2;    //以list[mid]作为根

		//递归建树
		Node* lc = Build(l, mid - 1, list);
		Node* rc = Build(mid + 1, r, list);

		Node* now = new Node;   //创建新节点
		*now = *(list[mid]);    //复制新节点

		now->lchild = lc;
		now->rchild = rc;
		if(lc != NULL) lc->parent = now;
		if(rc != NULL) rc->parent = now;

		Update_h(now);	  //更新当前节点的高度

		return now;
	}

	//把a并入现今的AVL树
	void Merge_With(AVL& a) {
		if (a.head == head) return;

		//创建顺序表
		Node** list1 = new Node*[size];
		Node** list2 = new Node*[a.size];
		int cnt1, cnt2;
		cnt1 = cnt2 = 0;

		//先把节点按升序放进顺序表
		Push_In_List(head, cnt1, list1);
		Push_In_List(a.head, cnt2, list2);

		//创建新的顺序表
		Node** list = new Node*[cnt1 + cnt2];

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
		head = Build(0, pos-1, list);
		head->parent = NULL;
		size = pos;

		//释放旧树的根的内存
		Clear(old);

		//释放顺序表占用的内存
		delete[] list1;
		delete[] list2;
		delete[] list;
	}

	//根据键值x, 把AVL树分成两个树到空树a, 空树b
	void Break_Up(AVL& a, AVL& b, KeyType x) {
		if (a.head != NULL || b.head != NULL) return;

		//创建顺序表
		Node** list = new Node*[size];
		int cnt = 0;

		//把节点按升序放入顺序表
		Push_In_List(head, cnt, list);

		//折半查找小于等于x的最大key
		int l, r, mid;
		l = 0, r = size-1;
		while (l < r) {
			mid = (l + r) / 2;
			if (list[mid]->key < x) l = mid + 1;
			else r = mid;
		}
		mid = l;
		if (list[mid]->key > x) mid--;
		
		//确定树的大小
		a.size = mid + 1;
		b.size = size - a.size;

		//把小于等于x的节点放到树a, 大于x的节点放到树b
		a.head = Build(0, mid, list);
		b.head = Build(mid + 1, size - 1, list);

		//把根节点的双亲节点置空
		if(a.head != NULL) a.head->parent = NULL;
		if(b.head != NULL) b.head->parent = NULL;
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

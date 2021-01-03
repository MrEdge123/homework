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
	AVL���Ĺؼ��ڲ�����:

	Search: ����
	Updata_h: ���½ڵ�߶�
	L_Rotate: ����
	R_Rotate: ����
	L_Balance: ƽ��������
	R_Balance: ƽ��������
	*/

	//������ֵΪkey�Ľڵ�
	Node* Search(Node* p, KeyType& key) {
		if (p == NULL) return NULL;    
		if (key == p->key) return p;   

		if (key < p->key) return Search(p->lchild, key);
		else return Search(p->rchild, key);
	}

	//����p�ڵ����������������ĸ߶�
	void Update_h(Node* p) {
		if (p->lchild == NULL) p->lh = 0;
		else p->lh = max(p->lchild->lh, p->lchild->rh) + 1;    //�����������ĸ߶�

		if (p->rchild == NULL) p->rh = 0;
		else p->rh = max(p->rchild->lh, p->rchild->rh) + 1;    //�����������ĸ߶�
	}

	//����
	void R_Rotate(Node* p) {
		Node* top = p->parent;

		Node* lc = p->lchild;

		//��Ҫ����
		p->lchild = lc->rchild;
		lc->rchild = p;

		//���¶�Ӧ��˫�׽ڵ�
		lc->parent = top;
		p->parent = lc;
		if (p->lchild != NULL) p->lchild->parent = p;

		//����p�ڵ��������ĸ߶�, lc�ڵ��������ĸ߶�
		Update_h(p);
		Update_h(lc);
		/*
		if (p->lchild != NULL) p->lh = max(p->lchild->lh, p->lchild->rh) + 1;
		else p->lh = 0;
		lc->rh = max(p->lh, p->rh) + 1;
		*/

		if (p == head) head = lc;

		//���¶���˫�׽ڵ���Ϣ
		if (top == NULL) return;
		if (top->lchild == p) top->lchild = lc;
		else top->rchild = lc;
	}

	//����
	void L_Rotate(Node* p) {
		Node* top = p->parent;

		Node* rc = p->rchild;

		//��Ҫ����
		p->rchild = rc->lchild;
		rc->lchild = p;

		//���¶�Ӧ��˫�׽ڵ�
		rc->parent = top;
		p->parent = rc;
		if (p->rchild != NULL) p->rchild->parent = p;

		//����p�ڵ��������ĸ߶�, rc�ڵ��������ĸ߶�
		Update_h(p);
		Update_h(rc);
		/*
		if (p->rchild != NULL) p->rh = max(p->rchild->lh, p->rchild->rh) + 1;
		else p->rh = 0;
		rc->lh = max(p->lh, p->rh) + 1;
		*/

		if (p == head) head = rc;

		//���¶���˫�׽ڵ���Ϣ
		if (top == NULL) return;
		if (top->lchild == p) top->lchild = rc;
		else top->rchild = rc;
	}

	//ƽ��������
	void L_Balance(Node* p) {
		Update_h(p);

		if (p->lh - p->rh == 2) {        //p����������
			if (p->lchild->lh >= p->lchild->rh) {    //LL: ��p�������������Ӳ���ڵ�
				R_Rotate(p);
			}
			else {                       //LR: ��p�����������Һ��Ӳ���ڵ�
				L_Rotate(p->lchild);
				R_Rotate(p);
			}
		}
	}

	//ƽ��������
	void R_Balance(Node* p) {
		Update_h(p);

		if (p->rh - p->lh == 2) {        //p����������
			if (p->rchild->rh >= p->rchild->lh) {    //RR: ��p�����������Һ��Ӳ���ڵ�
				L_Rotate(p);
			}
			else {                       //RL: ��p�������������Ӳ���ڵ�
				R_Rotate(p->rchild);
				L_Rotate(p);
			}
		}
	}

	/*
	AVL���Ļ�������:

	IsEmpty: �п�
	Clear: ���
	IsFind: ����
	Insert: ����
	Delete: ɾ��
	*/

	//�ж����Ƿ�Ϊ��
	bool IsEmpty() {
		return head == NULL;
	}

	//�����pΪ���ڵ����
	void Clear(Node* p) {
		if (p == NULL) return;

		Clear(p->lchild);
		Clear(p->rchild);
		delete p;
	}

	//�����
	void Clear() {
		Clear(head);
		head = NULL;
	}

	//���������Ƿ���ڼ�ֵkey
	bool IsFind(KeyType& key) {
		return Search(head, key) != NULL;
	}

	//����ݹ麯��
	void Insert(Node* p, Node* New) {
		if (New->key < p->key) {
			if (p->lchild == NULL) {
				New->parent = p;
				p->lchild = New;
				p->lh++;
				return;
			}

			Insert(p->lchild, New);     //���뵽������
			L_Balance(p);    //ƽ��������
		}
		else {
			if (p->rchild == NULL) {
				New->parent = p;
				p->rchild = New;
				p->rh++;
				return;
			}

			Insert(p->rchild, New);     //���뵽������
			R_Balance(p);    //ƽ��������
		}
	}

	//�����ֵ
	void Insert(KeyType key) {
		if (IsFind(key)) return;

		Node* New = new Node;
		New->key = key;

		if (head == NULL) head = New;
		else Insert(head, New);

		size++;
	}

	//ɾ���ݹ麯��
	void Delete(Node* p, KeyType key) {
		if (key < p->key) {
			Delete(p->lchild, key);
			R_Balance(p);    //�������ڵ㱻ɾ, ƽ��������
		}
		else if (key > p->key) {
			Delete(p->rchild, key);
			L_Balance(p);    //�������ڵ㱻ɾ, ƽ��������
		}
		else {
			//pΪ���ڵ�ʱ�����⴦��
			if (p == head) {   
				if (p->lchild == NULL && p->rchild == NULL) {  //ֻ�е����ڵ�
					delete head;
					head = NULL;
					return;
				}

				if (p->rchild == NULL) {  //ֻ��������
					head->lchild->parent = NULL;
					Node* t = head->lchild;
					delete head;
					head = t;
					return;
				}

				if (p->lchild == NULL) {  //ֻ��������
					head->rchild->parent = NULL;
					Node* t = head->rchild;
					delete head;
					head = t;
					return;
				}

			}

			//Ҷ�ӽڵ�
			if (p->lchild == NULL && p->rchild == NULL) {   
				//��˫�׽ڵ�ĺ���ָ���ÿ�
				if (p->parent->lchild == p) p->parent->lchild = NULL;
				else p->parent->rchild = NULL;

				delete p;
				return;
			}

			//ֻ��������
			if (p->rchild == NULL) {    
				Node* top = p->parent;  //p��˫�׽ڵ�

				//��˫�׽ڵ�ĺ���ָ��, ָ�����������ڵ�
				if (top->lchild == p) top->lchild = p->lchild;
				else top->rchild = p->lchild;

				//���������ĸ��ڵ�˫��ָ��, ָ��p��˫�׽ڵ�
				p->lchild->parent = top;

				delete p;
				return;
			}

			//ֻ��������
			if (p->lchild == NULL) {    
				Node* top = p->parent;

				//��˫�׽ڵ�ĺ���ָ��, ָ�����������ڵ�
				if (top->lchild == p) top->lchild = p->rchild;
				else top->rchild = p->rchild;

				//���������ĸ��ڵ�˫��ָ��, ָ��p��˫�׽ڵ�
				p->rchild->parent = top;

				delete p;
				return;
			}

			//������������, ������������Сֵ����, Ȼ��ɾ����Сֵ�ڵ�
			Node* now = p->rchild;
			while (now->lchild != NULL) now = now->lchild;

			p->key = now->key;
			Delete(p->rchild, now->key);

			L_Balance(p);    //�������ڵ㱻ɾ, ƽ��������
		}
	}

	//ɾ����ֵ
	void Delete(KeyType key) {
		if (IsFind(key) == false) return;
		Delete(head, key);
		size--;
	}

	/*
	AVL������������:

	Print: ��ʾAVL���ṹ
	Merge_With: �ϲ�����AVL��
	Break_Up: ����ֵ�ֳ�����AVL��
	Check: ������Ľṹ
	*/

	//��ӡ�ݹ麯��
	void Print(Node* p, int h) {
		if (p == NULL) return;

		for (int i = 0; i < h; i++) cout << "\t";
		cout << p->key << endl;

		Print(p->lchild, h+1);
		Print(p->rchild, h+1);
	}

	//��ӡAVL��(�����)
	void Print() {
		cout << endl;
		Print(head, 0);
		cout << endl;
	}

	//�ѽڵ�Ϊp��AVL���Ž�˳���
	void Push_In_List(Node* p, int& cnt, Node** list){
		if (p == NULL) return;

		Push_In_List(p->lchild, cnt, list);
		list[cnt++] = p;
		Push_In_List(p->rchild, cnt, list);
	}

	//������˳�����AVL��
	Node* Build(int l, int r, Node** list) {
		if (l > r) return NULL;

		int mid = (l + r) / 2;    //��list[mid]��Ϊ��

		//�ݹ齨��
		Node* lc = Build(l, mid - 1, list);
		Node* rc = Build(mid + 1, r, list);

		Node* now = new Node;   //�����½ڵ�
		*now = *(list[mid]);    //�����½ڵ�

		now->lchild = lc;
		now->rchild = rc;
		if(lc != NULL) lc->parent = now;
		if(rc != NULL) rc->parent = now;

		Update_h(now);	  //���µ�ǰ�ڵ�ĸ߶�

		return now;
	}

	//��a�����ֽ��AVL��
	void Merge_With(AVL& a) {
		if (a.head == head) return;

		//����˳���
		Node** list1 = new Node*[size];
		Node** list2 = new Node*[a.size];
		int cnt1, cnt2;
		cnt1 = cnt2 = 0;

		//�Ȱѽڵ㰴����Ž�˳���
		Push_In_List(head, cnt1, list1);
		Push_In_List(a.head, cnt2, list2);

		//�����µ�˳���
		Node** list = new Node*[cnt1 + cnt2];

		//�ϲ�����˳���
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

		//���������ĸ�
		Node* old = head;

		//�����µ�AVL��
		head = Build(0, pos-1, list);
		head->parent = NULL;
		size = pos;

		//�ͷž����ĸ����ڴ�
		Clear(old);

		//�ͷ�˳���ռ�õ��ڴ�
		delete[] list1;
		delete[] list2;
		delete[] list;
	}

	//���ݼ�ֵx, ��AVL���ֳ�������������a, ����b
	void Break_Up(AVL& a, AVL& b, KeyType x) {
		if (a.head != NULL || b.head != NULL) return;

		//����˳���
		Node** list = new Node*[size];
		int cnt = 0;

		//�ѽڵ㰴�������˳���
		Push_In_List(head, cnt, list);

		//�۰����С�ڵ���x�����key
		int l, r, mid;
		l = 0, r = size-1;
		while (l < r) {
			mid = (l + r) / 2;
			if (list[mid]->key < x) l = mid + 1;
			else r = mid;
		}
		mid = l;
		if (list[mid]->key > x) mid--;
		
		//ȷ�����Ĵ�С
		a.size = mid + 1;
		b.size = size - a.size;

		//��С�ڵ���x�Ľڵ�ŵ���a, ����x�Ľڵ�ŵ���b
		a.head = Build(0, mid, list);
		b.head = Build(mid + 1, size - 1, list);

		//�Ѹ��ڵ��˫�׽ڵ��ÿ�
		if(a.head != NULL) a.head->parent = NULL;
		if(b.head != NULL) b.head->parent = NULL;
	}

	//���ݹ麯��
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

	//����Ƿ�Ϊƽ�������
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

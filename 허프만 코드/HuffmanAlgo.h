#pragma once
#include <iostream>
#include <string>
#include <deque>
using namespace std;

struct Node //��� ����ü
{
	char symbol;	//���� ��ȣ
	int freq;		//��ȣ�� �󵵼��� �ǹ�
	Node* left;		//left child
	Node* right;	//right child
	Node* parent;	//parent node
	string code;	//�ο��� �ڵ�
	Node(int frq, char s = ' ', Node* l = NULL, Node* r = NULL, Node* p = NULL)
		:symbol(s), freq(frq), left(l), right(r), parent(p), code("") {}	//Node�� ������ 
	bool isLeft()	//left child ���� �Ǵ�
	{
		return parent->left == this;	//�θ����� left�� �ڽ��̸� true
	}
	bool isRight()	//right child ���� �Ǵ�
	{
		return !isLeft();				//isLeft()�� false�� ������ right child�� �ǹ�
	}
	void setLeft(Node* l)		//left child ���� parameter= Node* l
	{
		if (left == NULL)		//left�� ���� �� 
			left=l;				//left = l
		else{					//������ left�� �ִٸ� 
			delete left;		//���� left�� ����� 
			left = l;			//l�� left�� �Ѵ�.
		}
	}
	void setRight(Node* r)		//right child ���� parameter= Node* r
	{
		if (right == NULL)		//right�� ���� �� 
			right = r;			//right = r
		else{					//������ right�� �ִٸ� 
			delete right;		//���� right�� ����� 
			right = r;			//r�� right�� �Ѵ�.
		}
	}
	void setCode(string c)		//���� �ڵ� ���� �Լ� string c�� parameter�� �־��ش�.
	{
		if (parent->code == "")	//�θ� ����� ���� �ڵ尡 �ƹ��͵� ���ٸ� 
			code = c;			//c�� ���� �ڵ�� ����
		else                    //�θ��� ���� �ڵ尡 �ִٸ� 
		code =parent->code + c;	//�θ��� ���� �ڵ忡 c�� �����δ�. 
	}
	void setParent(Node* p)		//�θ� ��� ���� 
	{
		if (parent == NULL)		//����ó��
			parent = p;
		else {
			delete parent;
			parent = p;
		}
	}
	bool isExternal()			//�ܺ� ������� �Ǵ�
	{
		return (left == NULL && right == NULL);	//left child�� right child ��� NULL �̸� �ܺ� ���
	}
	bool isInternal()			//���� ������� �Ǵ�
	{
		return !isExternal();					//�ܺγ�尡 �ƴϸ� true ����
	}
	bool hasLeft()				//left child�� ���� �ִ��� �Ǵ�
	{
		return left != NULL;	//left child�� NULL�� �ƴϸ� true ����
	}
	bool hasRight()				//right child�� ���� �ִ��� �Ǵ�
	{
		return right != NULL;	//right child�� NULL�� �ƴϸ� true ����
	}
	string Code()				//���� �ڵ� ����
	{
		return code;			//code ����
	}
};
class PQ						//�켱���� ť ����
{
	friend class HuffmanEncoder;		//HuffmanEncoder Ŭ�������� PQ Ŭ������ �������� ������ �� �ְ� friend ������ ���־���.
private:						
	deque<Node*>myq;			//������ ����� deque �ڷᱸ���� Node*�� ���� �� �ִ� myq ����
public:
	PQ(){}						//������
	int size() const			//������ ���
	{
		return myq.size();		//myq�� ������ ����
	}
	bool empty() const			//������� Ȯ��
	{
		return size() == 0;		//size�� 0�̸� true ����
	}
	Node* find(char Symbol)		//�Է��� ���� ��ȣ�� �����͸� ����
	{
		for (int i = 0; i < myq.size(); i++)	//myq�� size��ŭ �ݺ���
		{
			if (myq[i]->symbol == Symbol) return myq[i];	//���� ��ȣ�� ã���� �� ������ ��ȯ
		}						//for���� ������ ���Դ�=>�ش� ���� ��ȣ�� ���ٴ� �ǹ�
		return NULL;			//���� NULL ����
	}
	Node* min()					//�� ���� ������ ����
	{
		try {if (myq.size() == 0)throw string("�� ť�Դϴ�. min�Լ� ����");}//���� ó��
		catch (const string& ex)
		{cout << ex << endl; exit(0);}
		return myq.front();		//myq�� front ����
	}
	Node* max()					//�� ���� ������ ����
	{
		try {if (myq.size() == 0)throw string("�� ť�Դϴ�. max�Լ� ����");}//���� ó��
		catch (const string& ex){cout << ex << endl; exit(0);}
		return myq.back();		//myq�� back ����
	}
	void removeMin()			//�ּ� ���� ���� �Լ�
	{
		try { if (myq.size() == 0)throw string("�� ť�Դϴ�. removeMIn�Լ� ����"); }//���� ó��
		catch (const string& ex){cout << ex << endl; exit(0);}

		Node* temp = myq.front();	//Node* temp�� �ּ� ������ myq.front() �Ҵ�
		myq.pop_front();		//pop_front=> myq �ڷᱸ������ min�� ���ش�.
		delete temp;			//temp�� delete �������ν� ������ �ּ� ������ �����Ҵ� ����
	}
	void swap(Node* p, Node* q)	//p�����Ϳ� q������ swap �Լ� 
	{
		try { if (p == NULL || q == NULL) throw string("�������� swap����! swap�Լ� ����"); }//���� ó��
		catch (const string& ex) { cout << ex << endl; exit(0); }
		int tf = p->freq; char ts = p->symbol;							 //����Ī �Ҷ� �ӽ÷� ���� �����ص� ������ ����
		Node* tl = p->left; Node* tr = p->right; Node* paren = p->parent;//����Ī �Ҷ� �ӽ÷� ���� �����ص� ������ ����

		if (p->isInternal())	//p�� internal ����� 
		{
			if (p->hasLeft()) p->left->parent = q;	//p�� leftchild�� �ִٸ� p->left->parent�� q�� �������ش�.
			if (p->hasRight()) p->right->parent = q;//p�� rightchild�� �ִٸ� p->right->parent�� q�� �������ش�.
		}
		if (q->isInternal())	//q�� internal ����� 
		{
			if (q->hasLeft())q->left->parent = p;	//q�� leftchild�� �ִٸ� q->left->parent�� p�� �������ش�.
			if (q->hasRight())q->right->parent = p;	//q�� leftchild�� �ִٸ� q->right->parent�� p�� �������ش�.
		}
													//�� �ڽĳ����� �θ������ ���� ����Ī ���ִ� �۾�
		p->freq = q->freq;		//p�� �󵵼�= q�� �󵵼�
		p->symbol = q->symbol;	//p�� ���� ��ȣ= q�� ���� ��ȣ

		p->right = q->right;	//p�� right ��� = q�� right
		p->left = q->left;		//p�� left ��� = q�� left
		p->parent = q->parent;	//p�� parent ��� = q�� parent

		q->freq = tf;			//q�� �󵵼��� ���� p�� �󵵼�
		q->symbol = ts;			//q�� ���� ��ȣ�� ���� p�� ���� ��ȣ
		q->left = tl;			//q�� left ��� = ���� p�� left 
		q->right = tr;			//q�� right ���= ���� p�� right 
		q->parent = paren;		//q�� parent ���= ���� p�� parent
	}
	void sort()					//���� �Լ�
	{
		for (int i = 0; i < myq.size(); i++)	//myq�� ������ ��ŭ �ݺ�
		{
			if (i == myq.size() - 1) break;		//�� ������ ���ұ��� ������ ���°� �̻��� ���� �� break
			if (myq[i]->freq > myq[i + 1]->freq)	//�ռ� ����� �󵵼��� ���� �󵵼� ���� Ŭ �� �� ������ ���� ���� �� 
			{
				swap(myq[i], myq[i + 1]);		//myq[i]�� myq[i+1]������ swap �Լ��� �̿��Ͽ� swap ���ش�. 
			}
		}
	}
	void insert(char Symbol)	//���� ��ȣ ���� �Լ� =>���԰� ���ÿ� ������ �������ش�. 
	{							//������ �ִ� ���� ��ȣ�� ��� �󵵼��� ���������ش�.
		if (Symbol == 32) return;	//���� (����)�� ��� �ǳ� �ڴ�.
		if (find(Symbol) == NULL)//�Է��� ���� ��ȣ�� ���� ��� => ������ ������ find(Node* p)�Լ��� ��� �Ͽ���.
		{
			Node* newNode = new Node(1, Symbol);	//Node* �� newNode�� �����Ҵ� �Ͽ� 
			myq.push_front(newNode);				//myq�� '��'���� �־��ش�. �󵵼��� 1�̶� �ּҿ��ҿ� ���� �ǹ��̹Ƿ� ������ �־��ش�.
		}
		else{					//�Է¹��� ���� ��ȣ�� ���� PQ�� ���� �� 
			for (int i = 0; i < myq.size(); i++)	//�ݺ��� ���� 
			{
				if (myq[i]->symbol == Symbol)		//i��° myq�� ���� ��ȣ�� �Է¹��� Symbol�̸� 
				{
					if (i == myq.size() - 1)		//������ ����ε� ���� �� 
					{
						myq[i]->freq++;				//�ش� ���� ��ȣ�� ���� ����� �󵵼��� 1 ����
					}
					else if (myq[i]->freq == myq[i + 1]->freq)	//���� ��ȣ�� i��°�� ���� ������
					{											//i��° ����� �󵵼��� i+1��° ����� �󵵼��� ������ 
						myq[i]->freq++;							//�󵵼� ���� ���Ŀ� �󵵼��� ���� ������ �ٲ��� �ϹǷ� 
						sort();									//���� �Լ��� sort()�Լ� ���� 
						break;									//�󵵼� ����, ���� ���Ŀ� break
					}
					else if (myq[i]->freq < myq[i + 1]->freq)	//i��° ����� �󵵼��� i+1��° ����� �󵵼� ���� ������ 
					{											//i��° ����� �󵵼��� 1 �������ѵ� i+1��° ����� �󵵼� ���� Ŀ���� �����Ƿ� 
						myq[i]->freq++;							//i��° ����� �󵵼� 1 ����
						break;									//���� break
					}
				}
				else continue;
			}
		}
	}
	void remove(Node* p)			//p ������ ���� �Լ�
	{
		try{if (p == NULL)throw string("���� ����Դϴ�. remove�Լ� ����!");}//���� ó��
		catch (const string& ex){cout << ex << endl; exit(0);}
		deque<Node*> ::iterator it;	//erase�� ���� ���ͷ����� ����
		it = myq.begin();			//it�� myq.begin
		for (int i = 0; i < myq.size(); i++)	//�ݺ�
		{
			if (myq[i] == p && i == myq.size() - 1)	//myq[i]�� ������ ����� �� 
			{
				delete myq[i];		//��带 delete �ϰ� 
				myq.pop_back();		//pop ���ش�.
			}
			else if (myq[i] == p)	//myq[i]�� p�̸� 
			{
				delete myq[i];		//��带 delete �ϰ� 
				myq.erase(it + i, it + i + 1); break;	//erase�Լ��� �� ��尡 �ִ� �ڸ��� �����ش�.
			}
		}
		cout << "���� ����Դϴ�." << endl;	//�ش��ϴ� ��尡 ���� �� 
	}
	int Freq(char Symbol)			//�Է¹��� ���� ��ȣ�� ���� �󵵼� ��� �Լ� 
	{
		try { if (find(Symbol) == NULL) throw string("���� ����Դϴ�. Freq�Լ� ����"); } //���� ó��
		catch (const string& ex) { cout << ex << endl; exit(0); }

		return find(Symbol)->freq;	//find()�Լ��� �ش� Symbol�� 
	}
	int Freq(Node* p)				//�Է� ���� p�������� �󵵼� ��� �Լ� 
	{
		try { if (p == NULL) throw string("���� ����Դϴ�. Freq�Լ� ����"); }	//���� ó��
		catch (const string& ex) { cout << ex << endl; exit(0); }

		return p->freq;				//p�� �󵵼� ����
	}
	void print()					//��� �Լ� 
	{
		for (int i = 0; i < myq.size(); i++)	//�� �տ��� ���� ���
		{
			cout << myq[i]->symbol << "�� �󵵼�: " << myq[i]->freq  << endl;
		}
	}
};

class HuffmanEncoder{				//������ �˰����� ������ Ʈ�� �� �Լ� Ŭ���� 
private:							//������ ��� 
	PQ pq;							//PQ�� ��ü pq
	Node* Root;						//��Ʈ ���
	deque<Node*> strList;			//���ڵ� �� ��ȣ�� ���� �ڵ� �з��� �ڷᱸ��
public:
	HuffmanEncoder(PQ prioQ)		//������ ->�켱���� ť prioQ�� �޾Ƽ� �̸� ���ڵ� �Ѵ�.
	{
		pq = prioQ;					//������ ��� pq=prioQ
		while (pq.size() > 1)		//pq�� ũ�Ⱑ 1�� �ɶ� ���� �� ť�� ��� �ϳ��� ���� �� ���� �ݺ�
		{
			Node* tl = pq.min(); pq.myq.pop_front();	//���Ӱ� ������ Node* tl= pq�� min, pq�� �ּ� ���Ҹ� pop���ش�.
			Node* tr = pq.min(); pq.myq.pop_front();	//���Ӱ� ������ Node* tr= pq�� min, pq�� (���� ó���� pq�� ������ �� )�ι� ° �ּ� ���Ҹ� pop���ش�.
			Node* r = new Node(tl->freq + tr->freq, ' ', tl, tr);	//���Ӱ� r ��带 ����, r�� �󵵼��� tl�� tr�� �󵵼��� ���̴�. tl�� tr�� �� r�� left, right�� ����.
			tl->setParent(r); tr->setParent(r);			//tl�� �θ��� =r, tr�� �θ��� = r
			pq.myq.push_front(r);						//r ��带 �켱���� ť�� �����Ѵ�.
			pq.sort();									//���� ť�� �������ش�. r���� r�� ��Ʈ ����� Ʈ���� ����̴�.
		}
		Root = pq.myq.front();		//Root�� myq�� �� ��
		preorderEncoding(Root);		//���ڵ� ���� �Լ�
		putList(Root);				//������ ��� strList�� Ʈ���� ���� ��ȣ��� �󵵼�, �����ڵ带 ������ ��带 �������ִ� �Լ�
	}
	void preorderEncoding(Node* p)	//�Է¹��� ��带 ��Ʈ�� �ϴ� Ʈ��(���� Ʈ��)�� �����ڵ带 �ο��ϴ� �Լ�
	{
		try { if (p == NULL)throw string("���� ����Դϴ�. preEncoding�Լ� ����!"); }//���� ó��
		catch (const string& ex) { cout << ex << endl; exit(0); }
		if (p != Root)				//p�� ��Ʈ��尡 �ƴϸ� 
		{
			if (p->isLeft())		//�����̸� 0 �ο�
			{
				p->code = p->parent->code + "0";	//left child�� ��� �θ� ����� �����ڵ忡 0�� �߰��ϸ� �ȴ�.
			}
			else if (p->isRight())	//�������̸� 1 �ο�
			{
				p->code = p->parent->code + "1";	//right child�� ��� �θ� ����� �����ڵ忡 1�� �߰��ϸ� �ȴ�.
			}
		}
		if (p->isInternal())		//p�� �ڽĳ�尡 ������ 
		{
			preorderEncoding(p->left);	//��������� left child�� preorderEncoding() �Լ��� �ְ� �����Ѵ�.
			preorderEncoding(p->right);	//��������� right child�� preorderEncoding() �Լ��� �ְ� �����Ѵ�.
		}
	}
	void putList(Node* p)			//p ��� �����͸� �ٽ� ��ũ�� �ִ´�.
	{
		try { if (p == NULL)throw string("���� ����Դϴ�. putList�Լ� ����!"); }//���� ó��
		catch (const string& ex) { cout << ex << endl; exit(0); }
		if (p->isExternal())		//p�� �ܺ� ����� 
			strList.push_back(p);	//���� ������� �� �տ� ��ġ�Ѵ�.
		else if (p->isInternal())	//p�� �ڽĳ�尡 ������ 
		{
			putList(p->left);		//��������� left child�� putList() �Լ��� �ְ� �����Ѵ�.
			putList(p->right);		//��������� right child�� putList() �Լ��� �ְ� �����Ѵ�.
		}
	}
	string FindCode(char Symbol)	//�Է��� ���ڿ� ���� ���� �ڵ� ���
	{
		for (int i = 0; i < strList.size(); i++)	//strList�� ������ ��ŭ �ݺ�
		{
			if (strList[i]->symbol == Symbol) return strList[i]->code;	
		}											//�ش� ���� ��ȣ�� ã���� �� ���� ��ȣ�� ���� ���� �ڵ� ���� 
		cout << "�ش� ���ں�ȣ�� ã�� ���߽��ϴ�." << endl; exit(0);
	}
	void Conclusion(char sen[])		//�Է� ���� ������ ���� �ڵ�� ����ϴ� �Լ�
	{
		for (int i = 0; i < strlen(sen); i++)	//�Է� ���� ������ ���� ��ŭ �ݺ�
		{
			if (sen[i] == 32)continue;			//�Է� ���� ������ char �����Ͱ� ���� (����)�̸� �Ѿ��.

			cout<<FindCode(sen[i])<<" ";		//FindCode�� sen[i]�� �־������ν� �ش� ���ڿ� ���� ���� �ڵ带 ����Ѵ�.
		}
	}
	Node* root()					//��Ʈ��� ���
	{
		return Root;				//��Ʈ��� ���
	}
	void setRoot(Node* p)			//��Ʈ��� ����
	{
		Root = p;					//��Ʈ��� = p
	}
	void preorder(Node* p)			//���� ��ȸ�� ���
	{
		if (p->isExternal())		//�ܺ� ����̸� 
			cout << p->symbol << " �� �󵵼�: " << p->freq << ", ���ڵ� ���: " << p->code << endl;
		else if (p->isInternal())	//���� ����̸� ->���� ��ȣ�� ���ǵ��� ���� ��� �̹Ƿ� �ڽ� ����� �Ѿ��.
		{
			preorder(p->left);		//��������� left child�� ���ؼ��� preorder()����
			preorder(p->right);		//��������� right child�� ���ؼ��� preorder()����
		}
	}
	~HuffmanEncoder()//�Ҹ���
	{
		DeleteNode(Root); 
	}
	void DeleteNode(Node* p)//������ȸ ������ �۵��ϴ� �����Ҵ� ���� �Լ�
	{
		if (p->isInternal())//�ڽĳ�尡 �ִٸ� 
		{
			if (p->hasLeft())
			{DeleteNode(p->left); }//��������� left child���� ���� ����
			else if (p->hasRight())
			{DeleteNode(p->right); }//��������� right child ����
		}
		else//�ڽĳ�尡 ���ٸ� 
		{
			if (p->isLeft())
			{
				p->parent->left = NULL;
				delete p;
			}
			else if (p->isRight())
			{
				p->parent->right = NULL;
				delete p;
			}
		}
	}
	int size()
	{	return pq.myq.size();}
};
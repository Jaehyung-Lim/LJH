#include <iostream>
#include "Tree_Vector_child_V.h"
#include <vector>
#include <string>
using namespace std;

//////////////////////////////////////////////////Position Adt/////////////////////////////////////////////////////////
tree::Position::Position(string _name, Position* p)	//������
	:name(_name), parent(p), cSize(0)//initializer
{
	child.push_back(NULL);							//child�� NULL�����͸� �־��ش� ->�ڳడ ������ �ǹ�(������ �̹Ƿ�)
	if (p == NULL)dpth = 0;							//�θ� null�̶�� ����=0
	else dpth = p->dpth + 1;						//�θ� �ִٸ�, ����= �θ��� ����+1
}
tree::Position::Position()							//������
	:name("default name"), parent(NULL), cSize(0), dpth(0)//initializer
{
	 child.push_back(NULL);							//child�� NULL�� �־��ش� ->�ڳడ ������ �ǹ� 
}
tree::Position* tree::Position::Parent() const		//�θ� ������(Position ���)
{
	return parent;									//�θ� ���
}
bool tree::Position::isExternal() const				//leafNode���� Ȯ��
{
	return child.back() == NULL;					//child�� back�� Null-> �ڳడ ����-> true
}
bool tree::Position::isInternal() const				//�ڳడ �ִ��� Ȯ��
{
	return !isExternal();							//External�� �ƴ� �� true
}
bool tree::Position::isRoot() const					//Root���� Ȯ��
{
	return parent == NULL;							//�θ� NULL�̸� Root����̴�
}
int tree::Position::getChildSize() const			//�ڽ� ��� ���� ���
{
	return cSize;									//cSize ����
}
int tree::Position::depth() const					//���� ���
{
	return dpth;									//dpth ����
}
string tree::Position::getname() const				//�̸� ���
{
	return name;									//name ����
}
///////////////////////////////////////////////////tree Adt////////////////////////////////////////////////////////////
tree::tree()	//������
	:sz(0), root(NULL)								//member initializer 
{	
	//Ʈ���� ������Ƿ� ������=0, root=NULL
}
int tree::size() const								//Ʈ���� ũ�� ���
{
	return sz;										//sz ����
}
bool tree::empty() const							//������� Ȯ���ϴ� �Լ�
{
	return sz == 0;									//sz=0�̸� true ���
}
tree::Position* tree::Root() const					//root������ ��� �Լ�
{
	try{ if (sz == 0) throw string("��Ʈ�� �����ϴ�!Root�Լ� ����. �����մϴ�. ");}
	catch (const string& ex) { cout << ex << endl; exit(1); }			//���ܻ��� ó��

	return root;									//root ���
}
void tree::sameNameCheck(Position* p, const string& _name)const	//p�� ��Ʈ ����
{
	if (p->name == _name)										//p�� �̸��� �־��� �̸��� ���� �� 
	{
		cout << "���� �̸��� �ڽĳ�尡 �ֽ��ϴ�. insertChildOf() ����!! �����մϴ�" << endl;
		exit(1);												//���� ����
	}
	else if (p->isInternal())									//�θ����� �̸��� ���� ���� �� 
	{
		for (int i = 0; i < p->cSize; i++)
		{
			sameNameCheck(p->child[i], _name);					//����� ����
		}
	}															//external�̰�, �̸��� �ٸ��� ���� Ȯ�� �� �ʿ䰡 ����
}
void tree::insertChildOf(Position* p, const string& _child)		//p�θ� ����� �ڽ����� _child �̸��� ���� �ڽĳ�� ����
{
	sameNameCheck(p, _child);			//���� �̸��� �ִ��� üŷ =>����ó��!!!!

	tree::Position* newChild = new tree::Position(_child, p);	//���ο� ��� ����
	if (p->cSize==0)											//p�� external ����� �� 
	{
		p->child.pop_back();									//child���Ϳ� back���� ����ִ� NULL�����͸� pop���ش�
		p->child.push_back(newChild);							//�� ���� ���� �������� newChild �����͸� push���ش�
	}
	else														//������ �ڽĳ�尡 ���� �� 
	{
		p->child.push_back(newChild);							//�ܼ��� push�� ���ָ� �ȴ�
	}
	p->cSize++;													//p����� �ڽ� �������� cSize + 1
	sz++;														//Ʈ���� �������� sz + 1
}
void tree::insertChildOf(Position* p, Position* son)			//p�θ� ��忡 �̹� �������ִ� son��带 ����
{
	sameNameCheck(p, son->name);		//���� �̸��� �ִ��� üŷ =>����ó��!!!!
	if (p->cSize == 0)											//p�� external ����� �� 
	{
		p->child.pop_back();									//child���Ϳ� back���� ����ִ� NULL�����͸� pop���ش�
		p->child.push_back(son);								//�� ���� �ڽĳ��� ���� son�� push �Ѵ�
	}
	else														//������ �ڽĳ�尡 ���� �� 
	{
		p->child.push_back(son);								//�׳� son�� push�� ���ָ� �ȴ�
	}
	son->parent = p;											//son�� parent�� p�� �Ѵ�
	son->dpth=p->dpth+1;										//�ڽĳ���� ���̴� �θ����� +1�̹Ƿ� 
	p->cSize++;													//p�� �ڽĳ�尡 �߰������Ƿ� cSize 1�߰�
	sz++;														//Ʈ���� ������ 1����
}
void tree::insert(Position* p, const string& pname, const string& son)  //p�� ��Ʈ ���� 
																//=>pname�� �̸��� ���� �ִ� �θ� ��忡 son�̸��� �ڽ��� ����
{																//���� �̸� ���ܴ� insertChildOf()�Լ����� ����ǹǷ� ���⼭ ���� �ʿ䰡 ����.
	if (p->name == pname)										//�̸��� ���� �� 
	{
		insertChildOf(p, son);									//�����ε��� insertChildOf(Position* p, const string& son)�� ����ȴ°�
	}
	else if (p->isInternal())									//�̸� �ٸ���, �ڽ��� ���� �� �ڽĵ�� �� ������ ���� �ڽ�
	{
		for (int i = 0; i < p->cSize; i++)						//�ڽ��� �� ��ŭ �ݺ�
		{
			insert(p->child[i], pname, son);					//��������� insert�Լ� �ݺ�=>void�� �̱� ������
		}														//�̸��� ���� �θ��带 ã���� �ڵ����� �Լ��� ����ȴ�
	}															//���� Ʈ���� ��� ���� �ÿ� �̸� �ߺ� ���� �����Ƿ�, 
}																//�ߺ��� ���� ����� �� �ʿ䰡 ����
void tree::DeleteOf(Position* p)								//DelteOf()�Լ�=> p����, p��� ������ �� ����
{
	try { if (p == NULL)throw string("NULL�����ʹ� ���� �� �����ϴ�!. Deleteof() �Լ����� ���� �߻�"); }
	catch (const string& ex) {cout << ex << endl; exit(1);}		//����ó��=> NULL������ ���ﶧ �߻��ϴ� ���� ����
	if (p->isInternal())										//�ش� ���� �� �ڽĵ� ���� ���� �ϰ� ���������� Internal ������ ���� �ϴ°�
	{
		for (int i = 0; i < p->cSize; i++)						//��������� DeleteOf�Լ� ����
		{
			DeleteOf(p->child[i]);								//������� ��������, �̹� �ڳడ �� ���������Ѵ�
		}
		DeleteOf(p);											//���Ŀ� �ڱ� �ڽ� ����=>��ġ postorder�� ����
	}
	else if (p->isExternal())									//p�� ��Ʈ�� �ƴϰ� External��� �� �� =>�� ��� �ϳ��� �������ָ� �ȴ�
	{															//child���Ϳ���, p�� back�̳� front�� �ƴ� �� ó��?? =>���ͷ����� ������ �̿��Ѵ�
		if (p->isRoot())										//External�ε� root�̸�
		{
			delete root;										//��Ʈ�� �����ְ� ������.
			sz--;												//Ʈ���� ������ 1 ����
		}
		else if (p->parent->cSize == 1)							//������ ���� �� �ڱ� ȥ�ڸ� �ִ� ���
		{
			p->parent->child.pop_back();						//p�� �θ��� �ڽ��� ���°� �̹Ƿ�, p->parent�� child�� pop
			p->parent->child.push_back(NULL);					//������ �����Ƿ�, child���Ϳ��� �ٽ� NULL�� �����ϹǷ�, NULL push =>�ٸ� �Լ����� ��� NULL������ �����ϹǷ�
			p->parent->cSize--;									//p�� �θ��� �ڽ� ������ - 1
			delete p;											//p���� �ٸ� ������ ������ �������Ƿ�, delete ���ش�
			sz--;												//Ʈ���� ������ 1 ����
		}
		else if (p->parent->cSize>1)							//�ֺ��� ������ ���� �� ��, p�� back�̳� front�� �ƴ� �� ó��??
		{														// =>begin�� end�Լ�, erase�Լ��� ����Ͽ� �ش� ���� ��ȣ�� �������ش�
			int count = 0;										//p�� p->parent->child�� ���° �������� Ȯ�ο� �ѹ�
			for (int i = 0; i < p->parent->cSize; i++)			//�θ� ����� �ڽ� �� ��ŭ �ݺ�
			{
				if (p->parent->child[i] == p) break;			//p->parent->child[i]�� �����Ϸ��� p�̸� break
				else count++;									//�׷��� ������ count 1����
			}
			p->parent->child.erase(p->parent->child.begin() + count, p->parent->child.begin() + count + 1);
																//������� �ϴ� ������ ���Ҹ� 1�� �����ش� =>count�� ���ڸ� �˰�, begin, end�� �ȴ�
			p->parent->cSize--;									//�θ��� �ڽ� ������ - 1
			delete p;											//p���� �ٸ� ������ ������ �������Ƿ�, delete ���ش�
			sz--;												//Ʈ���� ������ 1 ����
		}
	}
}
void tree::DeleteOf(Position* p, const string& node_name)		//��ͷ� ����: �̸� �Է½� �ش��ϴ� ������ ���� �ڽ� ������ ���� ����
{
	if (p->name == node_name)									//������� �ϴ� ����� �̸��� ���� �� 
		DeleteOf(p);											//Deleteof(p) �Լ� ����
	else if (p->isInternal())									//p�� �̸��� �ٸ���, �ڽ��� ���� �� �ڽĳ��鵵 Ȯ��
	{
		for (int i = 0; i < p->cSize; i++)						//�ڽ��� �� ��ŭ �ݺ�
		{
			DeleteOf(p->child[i], node_name);					//��������� �ݺ� ����
		}
	}
}
void tree::setRoot()	
{
	try{if (root != NULL) throw string("�̹� ��Ʈ�� �ֽ��ϴ�!!! setRoot�Լ� ����/// ���� �����մϴ�!!");}
	catch (const string& ex) { cout << ex << endl; exit(1); }	//��Ʈ�� �̹� ���� �� ����ó��

	string str;
	cout << "��Ʈ�� �����մϴ�. �̸��� �Է����ּ���" << endl;
	cin >> str;
	delete root;												//�����ڿ��� ������� root ��� delete
	root = new tree::Position(str, NULL);						//�Է¹��� str�� name�� ���� ���ο� ��� ����											
	sz++;														//���� ������ 0���� 1�� ����
}
void tree::setRoot(Position* p)
{
	try { if (root != NULL)throw string("Root�� �̹� �ֽ��ϴ�! setRoot() �Լ����� ���� �߻�"); }
	catch (const string& ex) {cout << ex << endl; exit(1);}		//��Ʈ�� �̹� ���� �� ����ó��
	delete root;												//�����ڿ��� ������� root ��� delete
	root = p;													//root�� �Է����� p
	sz++;														//���� ������0 ���� 1�� ����
}
void tree::setRoot(const string& _name)
{
	try { if (root != NULL)throw string("Root�� �̹� �ֽ��ϴ�! setRoot() �Լ����� ���� �߻�"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//����ó��

	delete root;												//�����ڿ��� ������� root ��� delete
	root = new tree::Position(_name, NULL);						//�Է¹��� �̸��� root��� ����
	sz++;														//���� ������ 0���� 1�� ����
}
void tree::preorder(Position* p) const							//������ȸ�� ���� �����ֱ�
{
	try { if (sz<1) throw string("Root�� ������ϴ� preorder�Լ� ����!!!"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//NULL�� p�� �Է����־��� ���� ����ó��

	cout << p->name << " ";										//�̸��� ��� =>������ȸ�̹Ƿ� ���� ������ش�

	if (p->isInternal())										//�ڽĳ�尡 ���� �� ��������� �ݺ�
	{
		for (int i = 0; i < p->cSize; i++)						//�ڽ��� �� ��ŭ
			preorder(p->child[i]);								//�Լ� ����
	}
}
void tree::postorder(Position* p)const							//������ȸ�� ���� �����ֱ�
{
	try { if (p == NULL) throw string("Root�� ������ϴ� ����!!!"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//NULL�� p�� �Է����־��� ���� ����ó��

	if (p->isInternal())										//�ڽĳ�尡 ���� �� ��������� �ݺ�
	{
		for (int i = 0; i < p->cSize; i++)						//�ڽ��� �� ��ŭ
			postorder(p->child[i]);								//�Լ� ����
	}
	cout << p->name << " ";										//p->name ���
}
int tree::depth(Position* p) const								//Ʈ�������� int ��ȯ�� ���� ��� �Լ�
{
	if (p->isRoot()) return 0;
	else return 1 + depth(p->parent);
}
void tree::depth_name(Position* p,const string& _name)const		//�̸� �Է½� �� ������� Ȯ���ϴ� �Լ�=>����� ����
{																//p�� root�� �־��ش�
	try { if (p == NULL) throw string("Root�� ������ϴ�. depth_nam()e �Լ� ����!!!"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//���ܻ���

	if (p->name == _name)										//�Է����� ����� �̸��� �Է����� �̸��� ���ٸ�
		cout <<"�Է��� ����� " <<p->dpth<<" ����Դϴ�." << endl;	//��� ���
	else if (p->isInternal())									//�̸��� �ٸ���, �ڽĳ�带 �Լ��� �Ķ���ͷ� �ϴ� ��� ȣ��		
	{
		for (int i = 0; i < p->cSize; i++)						//�ݺ���
			depth_name(p->child[i], _name);						//��������� ���� ��� �Լ� ȣ��
	}
}


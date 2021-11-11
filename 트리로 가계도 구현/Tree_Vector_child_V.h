#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class tree
{
public:
	class Position		
	{
		friend class tree;
	private:
		////////////////////////////////////////////////////////////////////////////////////////////
		vector<Position* >child;							//child��� ���� �����̳� �ȿ� Position* �ڷ����� ���������ν� �ڳ���� ���� �� �ְ� �ߴ�.
		int cSize;											//�ڽ� ����� ����
		///////////////////////////////////////////////////////////////////////////////////////////
	public:
		Position(std::string =" nullstr", Position* =NULL);	//������
		Position();											//������
		Position* Parent() const;							//�θ� ������ ���
		bool isRoot() const;								//��Ʈ������� Ȯ��
		bool isExternal() const;							//leaf������� Ȯ��
		bool isInternal() const;							//�ڽĳ�尡 �ִ��� Ȯ��
		int getChildSize() const;							//�ڽĳ�尡 �������
		int depth() const;									//���� ���̰� �� ����
		string getname() const;								//����� �̸� ���
	private:
		std::string name;									//����� �̸�
		int dpth;											//����: �׻� �θ����� dpth+1 root�� �� 0	
		Position* parent;									//�θ� ���
	};
public:
	friend class tree::Position;
	tree();													//Ʈ�� ������
	int size() const;										//Ʈ���� ������ ���
	bool empty() const;										//Ʈ���� ������� Ȯ��
	Position* Root() const;									//root ���

	void sameNameCheck(Position*, const string&)const;		//���Խ� ���� �̸��� �ִ��� Ȯ�� �� ���̴�.

	void insertChildOf(Position*,const string&);			//���� �Է��ؼ� �߰��ϴ°�
	void insertChildOf(Position*, Position*);				//�̹� ������� �ִ� ������ �߰�
	void insert(Position*, const string& parent, const string& son);   //�̸����� ����
	
	void DeleteOf(Position*);								//��� ���� �Լ�
	void DeleteOf(Position*, const string&);				//�̸��� �Է¹޾Ƽ� ����
	void setRoot();											//Root���� �Լ�: ���� �Լ� ������ �Է�
	void setRoot(Position*);								//����� ���� ��带 Root��
	void setRoot(const string&);							//string�Է½� Root��

	void preorder(Position* ) const;						//������ȸ ���
	void postorder(Position*)const;							//������ȸ ���

	void depth_name(Position*,const string&)const;			//�̸� �Է½� ��� ���
	int depth(Position*)const;								//int ��ȯ�� ��� ��� �Լ�
	
	

private:
	int sz;													//����� ��
	Position* root;											//root ���
};


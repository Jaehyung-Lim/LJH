#include <iostream>
#include "Tree_Vector_child_V.h"
#include <vector>
using namespace std;

int main()
{
	
	tree t1;
	//tree::Position* node1 = new tree::Position("�����Ҿƹ���", NULL);	 t1.setRoot(node1);		//�����ͷ� Root ����
	t1.setRoot("�����Ҿƹ���");								//�̸����� Root ����
	t1.insert(t1.Root(), "�����Ҿƹ���", "�Ҿƹ���");
	t1.insert(t1.Root(), "�����Ҿƹ���", "�����Ҿƹ���");
	t1.insert(t1.Root(), "�Ҿƹ���", "�ƺ�");
	t1.insert(t1.Root(), "�Ҿƹ���", "�����ƺ�");
	t1.insert(t1.Root(), "�Ҿƹ���", "���");
	t1.insert(t1.Root(), "�����Ҿƹ���", "ū���");
	t1.insert(t1.Root(), "�����Ҿƹ���", "��°���");
	t1.insert(t1.Root(), "�ƺ�", "������");
	t1.insert(t1.Root(), "�ƺ�", "�Ӽ���");
	t1.insert(t1.Root(), "�����ƺ�", "�ӿ���");
	t1.insert(t1.Root(), "�����ƺ�", "������");
	t1.insert(t1.Root(), "���", "������");
	t1.insert(t1.Root(), "���", "��ä��");
	t1.insert(t1.Root(), "��°���", "������");
	t1.insert(t1.Root(), "��°���", "�����");				//4��� ���� �Է�
	
	int ce = 0;//��ȣ ����
	string con_name = "nullstr";							//�Է¿� string����  
	string parent_name = "nullstr";							//�Է¿� string����
	string son_name = "nullstr";							//�Է¿� string����
	for (;;){
		cout << "����: 1.���� ���� 2.��� Ȯ�� 3.���� 4.���� 5.�ΚM�� Ȯ��////�׿�.����" << endl;
		cin >> ce;											//��ȣ �Է�
		if (ce == 1)
		{
			cout << endl;
			t1.preorder(t1.Root()); cout << endl << endl;;//������ȸ��
		}
		else if (ce == 2)
		{
			cout <<endl<< "������ ����� Ȯ���Ͻðڽ��ϱ�? �̸��� �Է��� �ֽʽÿ�" << endl;
			cin >> con_name;								//�̸��Է�
			t1.depth_name(t1.Root(), con_name); cout << endl;//�Լ� ����
		}
		else if (ce == 3)
		{
			cout <<endl<< "������ �θ����� �̸���, ���Ե� �ڳ��� �̸��� �Է��� �ֽʽÿ�." << endl;
			cout << endl;
			cin >> parent_name >> son_name;					//�θ��� �̸��� �ڳ��� �̸��� ������� �Է�
			t1.insert(t1.Root(), parent_name, son_name);	//string���� ���� 
		}
		else if (ce == 4)
		{
			cout <<endl<< "������ ����� �̸��� �Է��� �ֽʽÿ�" << endl;
			cin >> con_name;								//������ �̸� �Է�
			t1.DeleteOf(t1.Root(), con_name);				//���� �Լ�
		}
		else if (ce == 5)
		{
			cout << endl << "���� ���� �ο����� ���մϴ�: " << endl;
			cout << t1.size() << " �� �Դϴ�." << endl;
		}
		else
		{
			cout <<endl<< "�����մϴ�." << endl;			//����
			exit(1);
		}
	}
	return 0;
}

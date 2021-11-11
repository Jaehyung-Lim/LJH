#include <iostream>
#include"HuffmanAlgo.h"
#include <string>
using namespace std;

int main()
{
	PQ pq;//�켱���� ť ����

	char sentence[1000];//�ִ� 1000������ ������ �Է� �޴´�. ���������� ���� ����
	cin.getline(sentence, 1000);//������� ���� �޾ƾ� �ϹǷ� getline�� ����Ѵ�.
	for (int i = 0; i < strlen(sentence); i++)//������ ���̸�ŭ �ݺ�
	{
		pq.insert(sentence[i]);	//pq�� ���ڵ��� ����
	}
	HuffmanEncoder bt(pq);//������ ���ڴ� ��ü bt�� ����-> ���ڴ��� pq�� ���ڷ� �־��ش�. ->�����ڿ� ���� ���ڵ� �ǰ�, ���� �ڵ� �ο�
	bt.preorder(bt.root());//���ں� �󵵼�, ��ȣ�� �����ش�.
	cout << endl;
	cout << "���ڵ����:" << endl;
	bt.Conclusion(sentence);	//�Է¹��� ������ ���ڵ��� ���� �ڵ�� �ٽ� ���
	return 0;
}


#include <iostream>
using namespace std;

void InitNext(int[], char[]);
void RevisedInitNext(int[], char[]);
void displayNext(int[],int);
int main(){
	cout << "12171841 ������" << endl;
	////////////////////////////////////////////////////////////////////
	char p1[100]="AABBAA"; 
	char p2[100]="ABAABAB"; 
	char p3[100]="ABABABAC";  //���� p1,p2,p3 ����
	
	int n1 = strlen(p1);	  //next �迭 ũ�⸦ �������� �Ҵ��ϱ� ���� ũ�⸦ ���Ѵ�.
	int n2 = strlen(p2);
	int n3 = strlen(p3);
	int* Renext1 = new int[n1];		//���� �� ReInitNext�� ���� ���� �迭

	int* Renext2 = new int[n2];		//���� �� ReInitNext�� ���� ���� �迭		

	int* Renext3 = new int[n3];		//���� �� ReInitNext�� ���� ���� �迭
	//////////////////////////////////////////
	cout << "\n-----���� 1-----\nPattern: AABBAA\n\n";
	RevisedInitNext(Renext1, p1);
	displayNext(Renext1, n1);

	cout << "\n-----���� 2-----\nPattern: ABAABAB\n\n";
	RevisedInitNext(Renext2, p2);
	displayNext(Renext2, n2);

	cout << "\n-----���� 3-----\nPattern: ABABABAC\n\n";
	RevisedInitNext(Renext3, p3);
	displayNext(Renext3, n3);
	///////////////////////////////////////////
	delete[] Renext1; delete[]Renext2; delete[]Renext3;
	cout << "\n12171841 ������\n";
	return 0;
}
//���� �Ǳ� �� 
void InitNext(int next[], char p[]) {
	int M = strlen(p);//i�� ���� ���� �� ������ ������ M�� �ʿ� �ϴ�. ���� �Էµ� ���� p�� ���̸� M���� ����
	next[0] = -1;	  //next[0]�� ���� �׻� -1�� �Ѵ�. �迭���� ��ġ���� ���� ��, 0������ ����� �ϴ� ����, netx[0]�� -1�̱� ������ 1 �߰��� 0 ��, �ٽ� �� ó������ �� �ؾ��Ѵٴ� �ǹ�.
	for (int i = 0, j = -1; i < M; i++, j++) {//i�� ������ ���� ù��° �ε����� 0, j�� ���� i��° �ε������� ����ġ �߻��ÿ�, ��� �ε����� �����ϴ����� ���� ������ ��� �����̴�.
		next[i] = j;//next[i]�� j���� �־������ν�, i��°�� �ε������� ����ġ �߻���, j�ε����� ���Ϻ��� �ٽ� ���϶�� �ǹ̸� ���´�. 
		while (j >= 0 && p[i] != p[j]) { //j�� 0 �̻��̿��� �ϸ�, p[i]�� p[j]�� ����ġ �߻���, 
			j = next[j]; //������ ������ �ξ���, j��° �ε����� �����ϱ� ������, j�� next[j]���� �����ϰ�, while���� ����ɶ� ���� �ݺ��Ѵ�.
		}//j�� 0���� �۾��� �� -1�� ���´ٸ� �� ó������ �ٽ� ���Ѵٴ� �ǹ��̰�, p[i]�� p[j]�� ��ġ�ؼ� while���� ����ƴٸ�, p[i]�� p[j]�� ��ġ�ϱ� ������ �� ���� �ε����� ���Ѵ�.
	}
}
//���� �ǰ� �� �� 
void RevisedInitNext(int next[], char p[]) { //������ ���� 
	int M = strlen(p);
	next[0] = -1;
	for (int i = 0, j = -1; i < M; i++, j++) {
		if (p[i] == p[j]) next[i] = next[j]; //����ġ�� �߻��ߴµ� �� �ٽ� �̵��� �ε����� ���� ���� ���� ���̸�, �̵������� �ǹ̰� ���� ������ next[i] ���� next[j]�� �־��ش�.
		else next[i] = j;//����ġ�� �� ���������� �־��ش�.                                           -> ������ ����ġ �Ͽ� �̵� �ߴµ�, ���� �����̱� ������ ����ġ �ϸ� �ǹ̰� ���� �����̴�.
		while (j >= 0 && p[i] != p[j]) {//j�� 0 �̻��̿��� �ϸ�, p[i]�� p[j]�� ����ġ �߻���, 
			j = next[j]; //������ ������ �ξ���, j��° �ε����� �����ϱ� ������, j�� next[j]���� �����ϰ�, while���� ����ɶ� ���� �ݺ��Ѵ�.
		}//j�� 0���� �۾��� �� -1�� ���´ٸ� �� ó������ �ٽ� ���Ѵٴ� �ǹ��̰�, p[i]�� p[j]�� ��ġ�ؼ� while���� ����ƴٸ�, p[i]�� p[j]�� ��ġ�ϱ� ������ �� ���� �ε����� ���Ѵ�.
	}
}
void displayNext(int a[],int sz) {
	printf("-------------\nNext[j]:  j  \n-------------\n");
	for (int i = 0; i < sz; i++) { 
		printf("Next[%d]: %2d  ", i, a[i]); 
		printf("=>%d �ε������� ����ġ �߻��� Next[%d]�� %2d �ε����� ���� �ٽ� ���Ѵ�.", i, i, a[i]);
		if (a[i] == -1)printf("=>-1�ε����� �ٽ� 0�ε����� ����.");
		printf("\n");
	}
	printf("\n");
}

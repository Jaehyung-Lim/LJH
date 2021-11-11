#include<iostream>
#include <iomanip>
using namespace std;

#define INF 1000000 //W,D�迭���� ����� ���Ѵ븦 100������ ����
int w[6][6] = { //w�迭 �� ��, ���� 0��° ���� ������� �ʴ´�. 
	{             },
	{0, 0, 1, INF,1 ,5},
	{0, 9, 0, 3, 2,INF},
	{0,INF,INF,0,4,INF},
	{0, INF, INF, 2, 0, 3},
	{0,3,INF,INF,INF,0}
};

void floyd2(int n, int** W, int** D, int** P){
	for (int i = 1; i <= n; i++)//1�࿡�� n�����
		for (int j = 1; j <= n; j++) {//1������ n������ 
			D[i][j] = W[i][j];//�ʱ� D�迭�� W �迭�� ���� �մϴ�.
			P[i][j] = 0;//Path �迭 0���� �ʱ�ȭ
		}

	for (int k = 1; k <= n; k++) {//k�� 1���� n����  
		for (int i = 1; i <= n; i++) {//1�࿡�� n����� 
			for (int j = 1; j <= n; j++) {//1������ n������
				if (D[i][j] > D[i][k] + D[k][j]) {//k�� ��ġ�� ��ΰ� �� ���� ���� �� 
					P[i][j] = k;//Path �Լ����� k ��带 ��ģ�ٴ� �ǹ��� k�� ����
					D[i][j] = D[i][k] + D[k][j];//D[i][j]�� ������ i->k, k->j�� ��θ� ���Ѵ�.
				}
			}
		}
	}
}
void path(int** Path, int q, int r) { //path �Լ�
	if (Path[q][r] != 0) { //path�� 0�� �ƴ� �� 
		path(Path, q, Path[q][r]);//��������� ���� ������ �̵�
		cout << " v" << Path[q][r] << " ->";//���
		path(Path, Path[q][r], r);//��������� ������ ������ �̵�
	}
}
int main() {
	cout << "12171841 ������" << endl;
	int n = 5;
	int** D = new int* [n + 1];
	int** p = new int* [n + 1];
	int** W = new int* [n + 1];
	
	for (int i = 1; i <= n; i++) { 
		D[i] = new int[n + 1]; 
		p[i] = new int[n + 1]; 
		W[i] = new int[n + 1];
	}
	//2���� �迭 ���� �Ҵ� 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			W[i][j] = w[i][j]; //W���� w�� �־��ݴϴ�.

	floyd2(n, W, D, p);
	

	/////////////////////////////////////////��º�
	cout << "D[i][j]:" << endl;
	for (int i = 1; i <=n; i++) {
		for (int j = 1; j <= n; j++) {
			cout <<setw(2) <<D[i][j] << " ";
		}cout << endl;
	}
	cout << endl << "Path[i][j]: " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout <<setw(2)<< p[i][j] << " ";
		}cout << endl;
	}
	cout << endl;
	int start[3] = { 5,1,2 };
	int end[3] = { 3,3,5 };
	for (int i = 0; i < 3; i++) {
		printf("path(%d,%d)���: : v%d ->", start[i], end[i], start[i]); 
		path(p, start[i], end[i]); //path �Լ� ���� start[i]->end[i] ���� ���� ���
		printf(" v%d\n\n", end[i]);
		printf("path(%d,%d) ���: %d\n\n", start[i], end[i], D[start[i]][end[i]]);
	}

	for (int i = 1; i <= n; i++) { delete[] D[i]; delete[] p[i]; delete[] W[i]; }
	delete[]D; delete[]p; delete[]W;//�����Ҵ� ���� 
	return 0;
}
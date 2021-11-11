#include<iostream>
#include <iomanip>
using namespace std;

#define INF 1000000 //W,D배열에서 사용할 무한대를 100만으로 정의
int w[6][6] = { //w배열 각 행, 열의 0번째 항은 사용하지 않는다. 
	{             },
	{0, 0, 1, INF,1 ,5},
	{0, 9, 0, 3, 2,INF},
	{0,INF,INF,0,4,INF},
	{0, INF, INF, 2, 0, 3},
	{0,3,INF,INF,INF,0}
};

void floyd2(int n, int** W, int** D, int** P){
	for (int i = 1; i <= n; i++)//1행에서 n행까지
		for (int j = 1; j <= n; j++) {//1열에서 n열까지 
			D[i][j] = W[i][j];//초기 D배열을 W 배열과 같게 합니다.
			P[i][j] = 0;//Path 배열 0으로 초기화
		}

	for (int k = 1; k <= n; k++) {//k는 1부터 n까지  
		for (int i = 1; i <= n; i++) {//1행에서 n행까지 
			for (int j = 1; j <= n; j++) {//1열에서 n열까지
				if (D[i][j] > D[i][k] + D[k][j]) {//k를 거치는 경로가 더 값이 작을 때 
					P[i][j] = k;//Path 함수에는 k 노드를 거친다는 의미의 k를 저장
					D[i][j] = D[i][k] + D[k][j];//D[i][j]는 기존의 i->k, k->j의 경로를 더한다.
				}
			}
		}
	}
}
void path(int** Path, int q, int r) { //path 함수
	if (Path[q][r] != 0) { //path가 0이 아닐 때 
		path(Path, q, Path[q][r]);//재귀적으로 왼쪽 항으로 이동
		cout << " v" << Path[q][r] << " ->";//출력
		path(Path, Path[q][r], r);//재귀적으로 오른쪽 항으로 이동
	}
}
int main() {
	cout << "12171841 임재형" << endl;
	int n = 5;
	int** D = new int* [n + 1];
	int** p = new int* [n + 1];
	int** W = new int* [n + 1];
	
	for (int i = 1; i <= n; i++) { 
		D[i] = new int[n + 1]; 
		p[i] = new int[n + 1]; 
		W[i] = new int[n + 1];
	}
	//2차원 배열 동적 할당 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			W[i][j] = w[i][j]; //W값에 w를 넣어줍니다.

	floyd2(n, W, D, p);
	

	/////////////////////////////////////////출력부
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
		printf("path(%d,%d)경로: : v%d ->", start[i], end[i], start[i]); 
		path(p, start[i], end[i]); //path 함수 실행 start[i]->end[i] 노드로 가는 경우
		printf(" v%d\n\n", end[i]);
		printf("path(%d,%d) 비용: %d\n\n", start[i], end[i], D[start[i]][end[i]]);
	}

	for (int i = 1; i <= n; i++) { delete[] D[i]; delete[] p[i]; delete[] W[i]; }
	delete[]D; delete[]p; delete[]W;//동적할당 해제 
	return 0;
}
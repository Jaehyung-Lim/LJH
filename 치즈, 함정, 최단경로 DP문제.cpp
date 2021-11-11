#include <iostream>
#include <iomanip>
using namespace std;

//출발 8,0, 도착 0,8 -> 행렬로 
int cheese[9][9] = {
{0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0},
{0, 1, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0} };
int cheeseWtihTrap[9][9] = {
{0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, -1, 0},
{1, 0, -1, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 1, -1, 0, 0, 0},
{0, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, 1, -1, 0},
{0, 1, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0} };

int N[9][9];//단순 치즈의 최대값
int N_T[9][9];//쥐덫이 있을 때의 최대값

int Max(int a, int b) {
	if (a >= b)return a;
	else return b;
}
int main() {
	cout << "12171841 임재형" << endl << endl;
	//일반 치즈 문제 
	for (int i = 7; i >=0; i--) N[i][0] = N[i + 1][0]+cheese[i][0]; //0열은 아랫쪽에서의 최대값에 치즈 개수를 더한 것이다.
	for (int j =0; j <=7; j++)N[8][j+1] = N[8][j]+cheese[8][j+1];   //8행은 왼쪽에서의 최대값에 치즈 개수를 더한 것이다. 

	for (int i = 7; i>=0; i--){ //7행 1열부터 시작해서 0행 8열까지 간다.
		for (int j = 1; j <=8; j++) {
			N[i][j] = Max(N[i][j - 1], N[i + 1][j]) + cheese[i][j];//i행 j열에서의 최대값은 
		}														   //i행 j-1열의 최대값과 i-1행 j열의 최대값 중에 더 큰 값 + i행 j열 치즈의 개수
	}
	cout << "덫이 없는 경우 " << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)cout << N[i][j] << "  ";
		cout << endl;
	}
	cout <<"Max: "<< N[0][8] << endl;

	//쥐덫이 포함된 치즈 문제 
	int posR=0,posC=0;//덫이 나온 위치를 기억할 변수 
	for (int i = 7; i >= 0; i--) {
		if (cheeseWtihTrap[i][0]!=-1) N_T[i][0] = N[i + 1][0] + cheeseWtihTrap[i][0]; //덫이 아니라면 이전 최대값에 현재 치즈의 개수를 더한다.
		else {				
			N_T[i][0]= -1;			
			posR = i; //덫이 나오면 위치를 기억하고 루프를 멈춘다.
			break;
		}
	}
	for (int j = 0; j <= 7; j++) {
		if (cheeseWtihTrap[8][j+1]!=-1) N_T[8][j + 1] = N_T[8][j] + cheeseWtihTrap[8][j + 1];//덫이 아니라면 이전 최대값에 현재 치즈의 개수를 더한다.
		else {
			N_T[8][j + 1] = -1;
			posC = j;//덫이 나오면 위치를 기억하고 루프를 멈춘다.
			break;
		}
	}
	if (posR!=0) { //덫이 나왔다면, 해당 행부터 0행까지 모두 0으로 초기화
		for (int i = posR+1; i >= 0; i--)N_T[i][0] = 0; 
	}
	if (posC!=0) { //덫이 나왔다면, 해당 열부터 8열까지 모두 0으로 초기화
		for (int j = posC+1; j <= 7; j++)N_T[8][j + 1] = 0;
	}
	for (int i = 7; i >= 0; i--) {
		for (int j = 1; j <= 8; j++) {
			if (cheeseWtihTrap[i][j] != -1) {
				if (N_T[i][j - 1] == -1 && N_T[i + 1][j] == -1)N_T[i][j] = 0; 
				//둘다 트랩일 때  밑은 둘중에 하나가 트랩일 때 결국 더 큰 값으로
				else N_T[i][j] = Max(N_T[i][j-1], N_T[i+1][j]) + cheeseWtihTrap[i][j];
				//둘중에 하나만 트랩일 경우엔 트랩은 -1이므로, 트랩이 아닌 것 보다 항상 작기 때문에
				//큰 값을 더하면 트랩이 아닌 것이 더해지게 된다.
			}																		  
			else {//해당 칸이 -1일 때 
				N_T[i][j] = -1;
			}
		}
	}
	cout << "\n덫이 있는 경우" << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)cout<<setw(2) << N_T[i][j] << " ";
		cout << endl;
	}
	cout << "Max: " << N_T[0][8] << endl << endl;
	cout << "12171841 임재형" << endl;
	return 0;
}
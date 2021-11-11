#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int Data[1000001]; int tmp[1000001];
int a[1000001];

void divide(int, int);
void merge(int, int);
void checkSort(int[], int);

int main() {
	int m;
	cin >> m;//배열의 크기 입력
	for (int i = 0; i < m; i++) {
		cin >> a[i];
		Data[i] = a[i];
	}
	int pos = 0;	//최소 값의 위치를 기억할 변수 pos
	for (int i = 0; i < m; i++) { //삽입 정렬
		int Min = a[i];//unsorted된 배열의 첫번째 원소를 Min으로 한다.
		for (int j = i + 1; j < m; j++) {
			if (a[j] < Min) { //Min보다 a[j] 가 작으면 Min의 값을 a[j]로 변경, 해당 위치 pos로 기억
				Min = a[j];
				pos = j;
			}
		}
		if (Min != a[i]) { //Min이 바뀐 경우에만 swap 실행 
			int tmp = a[i];
			a[i] = Min;
			a[pos] = tmp;//기억해둔 pos에 의해 a[pos]를 가장 처음 Min이라 설정한 a[i]값과 swap
		}
	}
	cout << "1번\n선택 정렬의 결과: ";
	for (int i = 0; i < m; i++) {
		cout << a[i] << " ";
	}cout << endl;

	divide(0, m - 1);//합병 정렬 배열의 0번~ n-1까지 원소를 넣어 줬으므로 

	cout << "2번\n합병 정렬의 결과: ";
	for (int i = 0; i < m; i++) {
		cout << Data[i] << " ";
	}cout << endl;
	//////////////////////////////////////////////////////////////////////////////////////////
	srand(time(NULL));
	time_t start, end;
	cout << "3번\n배열의 크기 입력";
	int n;
	cin >> n; //배열의 크기 

	for (int i = 0; i < n; i++) {
		 a[i]=(rand()%n)+1;//난수 생성 및 배열의 값에 넣어준다.
		Data[i] = a[i];
	}
	//선택 정렬 시작
	int Pos = 0;	//최소 값의 위치를 기억할 변수 pos
	start = clock();
	for (int i = 0; i < n; i++) { //삽입 정렬
		int Min = a[i];//unsorted된 배열의 첫번째 원소를 Min으로 한다.
		for (int j = i + 1; j < n; j++) {
			if (a[j] < Min) { //Min보다 a[j] 가 작으면 Min의 값을 a[j]로 변경, 해당 위치 pos로 기억
				Min = a[j];
				Pos = j;
			}
		}
		if (Min != a[i]) { //Min이 바뀐 경우에만 swap 실행 
			int tmp = a[i];
			a[i] = Min;
			a[Pos] = tmp;//기억해둔 pos에 의해 a[pos]를 가장 처음 Min이라 설정한 a[i]값과 swap
		}
	}
	end = clock();
	cout << "4번\n선택 정렬:" << end - start << "ms" << endl;

	start = clock();
	divide(0, n-1);//합병 정렬
	end = clock();
	cout << "합병 정렬:" << end - start << "ms" << endl;

	cout << "5번\n";
	cout << "합병 정렬 정렬 결과: ";
	checkSort(Data, n);
	cout << "선택 정렬 정렬 결과: ";
	checkSort(a, n);

	return 0;
}

void divide(int lt, int rt) {
	if (lt < rt) { //왼쪽 인수가 오른쪽 인수보다 작을 때 실행 즉 하나의 원소만 남은 경우는 실행 x
		int mid = (lt + rt) / 2; //가운데 index인 mid를 정의
		divide(lt, mid);//배열의 왼쪽 부분 (lt~mid)까지 다시 divide
		divide(mid + 1, rt); //배열의 오른쪽 부분 (mid+1~rt)까지 다시 divide
		merge(lt, rt);//합병 함수
	}
}
void merge(int lt, int rt) {
	int mid = (lt + rt) / 2;	//가운데 index인 mid 정의
	int	pos1 = lt;	//나눠진 배열 중, 왼쪽 배열의 index pos1를 lt로 정의
	int pos2 = mid + 1;	//나눠진 배열 중, 오른쪽 배열의 index pos2를 mid+1로 정의
	int pos3 = lt;	//배열을 정렬 해야하므로, 정렬될 임시 배열의 index는 맨 처음부터여야 하므로, lt로 정의
	while (pos1 <= mid && pos2 <= rt) { //왼쪽 배열의 index가 mid이하이고, 오른쪽 배열의 index가 rt 이하일 땐 아직 두 배열의 합병이 끝나지 않은 것
		if (Data[pos1] < Data[pos2]) tmp[pos3++] = Data[pos1++];//왼쪽 배열의 index의 값이 오른쪽 배열 index의 값 보다 작으므로 값을 tmp배열에 넣어주고,값을 넣어준 pos1와 pos3 ++
		else tmp[pos3++] = Data[pos2++];//오른쪽 배열의 index의 값이 왼쪽 배열 index의 값 보다 작으므로 값을 tmp배열에 넣어주고,값을 넣어준 pos2와 pos3 ++
	}
	while (pos1 <= mid) tmp[pos3++] = Data[pos1++];//오른쪽 배열이 먼저 정렬된 배열로 들어갈 때 남은 왼쪽 배열의 원소들을 tmp 배열에넣어준다. 그리고 각 index++
	while (pos2 <= rt) tmp[pos3++] = Data[pos2++];//왼쪽 배열이 먼저 정렬된 배열로 들어갈 때 남은 오른쪽 배열의 원소들을 tmp 배열에넣어준다. 그리고 각 index++
	for (int i = lt; i <= rt; i++) Data[i] = tmp[i];// 정렬된 tmp배열의 값을 lt부터 rt까지 Data 배열의 값을 바꿔주므로 정렬이 된다.
}
void checkSort(int A[], int n) {
	int sorted;
	sorted = false;

	for (int i = 0; i < n; i++) {
		if (A[i] <= A[i + 1]) sorted = true; 
		if (!sorted) break;
	}
	if (sorted) cout << "Sorting complete!" << endl;
	else cout << "Error durint sorting..." << endl;
}
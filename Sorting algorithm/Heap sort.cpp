#include <iostream>
#include <ctime>
using namespace std;

void swap(int[], int, int);

void Maxheapify(int[], int, int);
void Maxheapsort(int[], int);

void Minheapify(int[], int, int);
void Minheapsort(int[], int);

void checkSorted_ascending(int[], int);
void checkSorted_descending(int[], int);

int main() {
	int maxarr[11] = { -1,6,2,8,1,3,9,4,5,10,7 };
	int minarr[11] = { -1,6,2,8,1,3,9,4,5,10,7 };
	///////////////////////////////////////////////
	cout << "----------1,2번: 정상 작동 확인----------" << endl << endl;
	Maxheapsort(maxarr, 10);//lastnode는 10
	Minheapsort(minarr, 10);//lastnode는 10
	cout << "Max heap으로 정렬: " << endl;
	for (int i = 1; i <= 10; i++)cout << maxarr[i] << " ";
	cout << endl;
	cout << "Min heap으로 정렬: " << endl;
	for (int i = 1; i <= 10; i++)cout << minarr[i] << " ";
	cout << endl << endl;
	////////////////////////////////////////////////
	cout << "----------4,5번: 정렬의 시간 측정----------" << endl << endl;
	time_t start, end;
	srand(time(NULL));
	int n, lastnode;
	cout << "랜덤 숫자 개수 입력: ";
	cin >> n;
	cout << endl;

	int* maxA = new int[n + 1];
	int* minA = new int[n + 1];

	for (int i = 1; i <= n; i++) {
		maxA[i] = rand() % n;
		minA[i] = maxA[i];
	}

	lastnode = n;
	
	start = clock();
	Maxheapsort(maxA, lastnode);
	end = clock();
	cout << "Max heap sort: " << end - start << "ms" << endl;

	start = clock();
	Minheapsort(minA, lastnode);
	end = clock();
	cout << "Min heap sort: " << end - start << "ms" << endl << endl;
	/////////////////////////////////
	cout << "----------5번: 정렬 확인----------" << endl << endl;
	cout << "maxA 배열: "; checkSorted_ascending(maxA, n);
	cout << "minA 배열: "; checkSorted_descending(minA, n);
	cout << "\n\n----------------------------------------------\n\n";
	cout << "12171841 임재형" << endl;

	delete[] maxA;
	delete[] minA;
	return 0;
}
void swap(int arr[], int n, int m) { //swap function
	int tmp = arr[n];
	arr[n] = arr[m];
	arr[m] = tmp;
}
void Minheapify(int a[], int h, int m) { //h: 루트 노드 인덱스  m:last node index -> heapify는 특정 원소가 빠지고, h로 올라온 원소를 원래 자리로 맞게끔 찾아가게 하는 알고리즘
	int j = h;      //j에 루트 노드의 인덱스

	for (j = 2 * h; j <= m; j *= 2) { //->j는 항상 짝수야
		if (j < m && a[j] > a[j + 1])j++; //일부러 j=2*h로 시작하여 왼쪽 자식의 인덱스에서 비교, j가 lastnode보다 작으면, 오른쪽 자식도 있는 것. 
										  //마지막 노드가 왼쪽 자식일 경우, j는 항상 짝수인 것에 물려서 j<m의 조건은 마지막 노드에 와서 항상 만족 하지 않는 조건-> j 값 증가 x
										  //오른쪽 자식이 더 작은 경우 j를 해당 자식과 바꿔야 하므로, j++ 
		if (a[j / 2] <= a[j]) return; //부모 노드가 자식 노드보다 작은 경우 -> 만족 한 상태=>이미 힙 상태인 트리에 루트 노드 만 내려주는 것 이므로, return 해주는 것  
		else {      //부모노드가 더 큰 경우, 큰 자식의 값인 a[j]를 부모 노드인 a[j/2] 값과 swap
			swap(a, j, j / 2);
		}
	}//루프를 빠져 나왔어 -> j가 m초과인 상태로 나온 것. => m초과인 수를 k라고 했을 때, a[k/2]까지 값을 넣어주고, a[k] 자리가 비어있는 상태에서, k가 2배가 되어 나온 것
	//따라서 a[k/2]의 자리가 현재 비어있는 상태, 즉 제일 작은 값이었던, v를 넣어주는 것이다.
}
void Minheapsort(int a[], int m) {  //힙은 최대힙 이지만, 정렬은 1부터 해야하는 것

	int n = m; //n에 lastnode의 인덱스 값. -> n은 노드의 개수를 의미 
	//최대 값은 가장 밑으로 보내줘야 하므로, 
	for (int i = n / 2; i >= 1; i--) {  //n은 lastnode, i는 lastnode의 부모노드
		Minheapify(a, i, n);// 아래에서 부터 힙으로 만든다.
	}
	for (int i = n - 1; i >= 1; i--) {
		swap(a, 1, i + 1); //n이 정렬이 안 된것들 중, i+1의 인덱스가 lastnode이므로, i+1 (n)과 1을 바꿔준다. 이후 lastnode가 n-1인 힙을 heapify한다.
		Minheapify(a, 1, i);//다시 힙으로 만들어 준다.
	}
}
void Maxheapify(int a[], int h, int m) { //h: 루트 노드 인덱스  m:last node index -> Maxheapify는 특정 원소가 빠지고, h로 올라온 원소를 원래 자리로 맞게끔 찾아가게 하는 알고리즘
	int j = h;      //j에 루트 노드의 인덱스

	for (j = 2 * h; j <= m; j *= 2) { //->j는 항상 짝수야
		if (j < m && a[j] < a[j + 1])j++; //일부러 j=2*h로 시작하여 왼쪽 자식의 인덱스에서 비교, j가 lastnode보다 작으면, 오른쪽 자식도 있는 것. 
										  //마지막 노드가 왼쪽 자식일 경우, j는 항상 짝수인 것에 물려서 j<m의 조건은 마지막 노드에 와서 항상 만족 하지 않는 조건-> j 값 증가 x
										  //오른쪽 자식이 더 큰 경우 j를 해당 자식과 바꿔야 하므로, j++ 
		if (a[j / 2] >= a[j]) return; //부모 노드가 자식 노드보다 큰 경우 -> 만족 한 상태=>이미 힙 상태인 트리에 루트 노드 만 내려주는 것 이므로, return 해주는 것  
		else {              //부모노드가 더 작은 경우, 큰 자식의 값인 a[j]를 부모 노드인 a[j/2] 값과 swap
			swap(a, j, j / 2);
		}
	}//루프를 빠져 나왔어 -> j가 m초과인 상태로 나온 것. => m초과인 수를 k라고 했을 때, a[k/2]까지 값을 넣어주고, a[k] 자리가 비어있는 상태에서, k가 2배가 되어 나온 것
	//따라서 a[k/2]의 자리가 현재 비어있는 상태, 즉 제일 작은 값이었던, v를 넣어주는 것이다.
}
void Maxheapsort(int a[], int m) {  //힙은 최대힙 이지만, 정렬은 1부터 해야하는 것

	int n = m; //n에 lastnode의 인덱스 값. -> n은 노드의 개수를 의미 
	//최대 값은 가장 밑으로 보내줘야 하므로, 
	for (int i = n / 2; i >= 1; i--) {  //n은 lastnode, i는 lastnode의 부모노드
		Maxheapify(a, i, n);// 아래에서 부터 힙으로 만든다.
	}
	for (int i = n - 1; i >= 1; i--) {
		swap(a, 1, i + 1); //n이 정렬이 안 된것들 중, i+1의 인덱스가 lastnode이므로, i+1 (n)과 1을 바꿔준다. 이후 lastnode가 n-1인 힙을 Maxheapify한다.
		Maxheapify(a, 1, i); //힙으로 만든다.
	}
}
void checkSorted_ascending(int a[], int n) {
	bool flag = true;
	for (int i = 1; i < n; i++) {
		if (a[i] > a[i + 1]) {
			flag = false;
			break;
		}
	}
	if (flag)cout << "Max heap 오름차순 정렬 성공" << endl;
	else cout << "정렬 실패" << endl;
}
void checkSorted_descending(int a[], int n) {
	bool flag = true;
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i + 1]) {
			flag = false;
			break;
		}
	}
	if (flag)cout << "Min heap 내림차순 정렬 성공" << endl;
	else cout << "정렬 실패" << endl;
}
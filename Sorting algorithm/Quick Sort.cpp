#include <iostream>
#include <ctime>
using namespace std;
void swap(int&, int&);
void Qsort(int[], int, int);
void midQsort(int[], int, int);
void checksort(int[],int);
int main() {
	//////1번 질문 /////////
	int* a1 = new int[11];					//배열 동적할당
	cout << "1.\n10개 원소 입력" << endl;
	for (int i = 1; i <= 10; i++)cin >> a1[i];
	Qsort(a1, 1,10);						//퀵소트 실행
	cout << "퀵 소트 결과: ";
	for (int i = 1; i <= 10; i++)cout << a1[i] << " ";
	cout << endl << endl;
	///////2번 질문////////////////////////
	cout << "2.\n10개 원소 입력(중간값 선택 퀵 소트)" << endl;
	for (int i = 1; i <= 10; i++)cin >> a1[i];
	midQsort(a1, 1, 10);					//분할 퀵소트 실행
	cout << "중간값 선택 퀵 소트 결과: ";
	for (int i = 1; i <= 10; i++)cout << a1[i] << " ";
	cout << endl<<endl;
	delete[] a1;							//메모리 해제 
	///////3,4번 랜덤한 10만개 숫자//////////////////////
	time_t start, end;
	srand((unsigned int)time(NULL));//난수 생성
	int n; 
	cout << "3,4\n랜덤한 숫자의 개수 입력" << endl;
	cin >> n;
	int* a = new int[n+1];//단순 퀵 소트용 배열
	int* b = new int[n+1];//분할 퀵 소트용 배열
	for (int i = 1; i <= n; i++) {
		a[i] = rand() % n + 1;
		b[i] = a[i];
	}

	//단순 퀵 소트
	start = clock();//시간 측정 시작
	Qsort(a, 1, n);//단순 퀵 소트
	end = clock();//측정 종료
	cout << "\n단순 퀵 소트: " << end - start << " ms" << endl;

	//분할 퀵소트
	start = clock();//시간 측정 시작
	midQsort(b, 1, n);//분할 퀵 소트
	end = clock();//측정 종료
	cout << "분할 퀵 소트: " << end - start << " ms" << endl<<endl;
	////////////5번///////////////
	cout << "5.\n단순 퀵소트: ";
	checksort(a, n);//배열의 정렬 확인
	cout << "분할 퀵소트: ";
	checksort(b, n);//배열의 정렬 확인
	cout << endl << endl;
	delete[]a;
	delete[]b;
	cout << "12171841 임재형" << endl;
	return 0;
}
void swap(int& a, int& b) { //레퍼런스를 이용한 스왑 함수
	int tmp = a;
	a = b;
	b = tmp;
}
void Qsort(int arr[], int a, int b) { //퀵 소트 
	if (a >= b)return;//분할된 개수가 하나 일 때 리턴
	int l = a;//l은 a 즉 배열의 시작점을 의미
	int r = b - 1;//r은 피벗 바로 이전 인덱스를 의미
	int p = arr[b];
	while (l <= r) {//l이 r이하일 때 
		while (l <= r && arr[l] <= p)l++; //l이 r 이하이고, arr[l]이 피벗보다 큰 값을 찾을 때 까지 l의 값을 증가 시킨다.
		while (l <= r && arr[r] >= p)r--;//l이 r 이하이고, arr[r]이 피벗보다 작은 값을 찾을 때 까지 r의 값을 감소 시킨다.
		if (l < r)swap(arr[l],arr[r]);//위의 루프가 멈췄는데 l<r이란 의미는, 서로 교차되기 전에 피벗보다 크고, 작은 값을 만족 하는 배열의 인덱스를 찾은 것이다.
	}								  //위 l과 r의 인덱스의 배열 값들 끼리 교환한다.
	swap(arr[l],arr[b]);//while(l<=r)을 끝냈다는 것은, l과 r이 교차했단 것이고, 이 떄 l의 인덱스를 가진 배열의 값과 피벗을 교환한다.
	Qsort(arr, a, l - 1);//맨 처음인 a와 l-1까지 분할해서 퀵 소트 재귀적으로 실행 (arr[l]과 피벗을 바꿨기 때문에, l-1까지 하는 것이다.)
	Qsort(arr, l + 1, b);//맨 피벗과 바꾼 l 다음인 l+1부터 맨 끝인 b까지로 분할해서 퀵소트를 재귀적으로 실행 
}
void midQsort(int arr[], int a, int b) { //분할 퀵 소트 
	int l, r, m,p;//변수 선언
	if (b - a > 2) {			//원소의 개수가 3개 이상일 때 실행 
		m = (a + b) / 2;//m는 a와 b의 중간 값
		if (arr[a] > arr[m])swap(arr[a], arr[m]);//왼쪽의 값이 가운데 값 보다 크면 swap
		if (arr[a] > arr[b])swap(arr[a], arr[b]);//왼쪽의 값이 오른쪽의 값보다 크면 swap
		if (arr[m] > arr[b])swap(arr[m], arr[b]);//가운데 값이 오른쪽 값보다 크면 swap
		swap(arr[m], arr[b-1]);//결과적으로 셋중에서 가운데 값이 arr[m]에 위치하게 되고, 이 값을 피벗의 값으로 해준다..

		l = a; r = b - 1; p = arr[b - 1];//l은 배열의 맨 왼쪽 인덱스, r은 피벗의 바로 이전 인덱스, p=arr[b-1]는 피벗으로 해준다. 
		while (1) {
			while (arr[++l] < p);//l의 인덱스를 증가시키면서 피벗의 값보다 커질 때 까지 실행
			while (arr[--r] > p);//r의 인덱스를 감소시키면서 피벗의 값보다 작아질 때 까지 실행 
			if (l >= r)break;//l의 값이 r의 값과 교차하면 break한다.
			swap(arr[l], arr[r]);//ㅣ의 값이 r보다 작고, arr[l]이 피벗 보다 크고, arr[r]의 값이 피벗보다 작을 때 둘의 값을 바꿔준다.
		}
		swap(arr[l], arr[b - 1]);//l의 값과 r의 값이 교차하여 break된 이후이므로, arr[l]의 값과 arr[b-1]의 값을 swap
		midQsort(arr, a, l - 1);//a인덱스부터 l-1인덱스까지 재귀함수를 실행해준다.
		midQsort(arr, l + 1, b);//l+1인덱스부터 b인덱스까지 재귀함수를 실행해준다.
	}
	//원소가 1개일 때나 2개일 때 실행 되는데, 어차피 1개일 땐 둘이 같으므로, 실행 x, 원소 2개일 때 앞의 원소가 더 크면 뒤의 원소와 swap
	else if (arr[a] > arr[b])swap(arr[a], arr[b]);
}
void checksort(int a[],int n) {
	int i, sorted;
	sorted = true;
	for (int i = 1; i <= n; i++) {
		if (a[i] > a[i + 1])sorted = false;
		if (!sorted)break;
	}
	if (!sorted)cout << "Sorting complete!" << endl;
	else cout << "Error during srting" << endl;
}
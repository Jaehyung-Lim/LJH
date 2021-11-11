#include <iostream>
#include <ctime>
using namespace std;
void swap(int&, int&);
void Qsort(int[], int, int);
void midQsort(int[], int, int);
void checksort(int[],int);
int main() {
	//////1�� ���� /////////
	int* a1 = new int[11];					//�迭 �����Ҵ�
	cout << "1.\n10�� ���� �Է�" << endl;
	for (int i = 1; i <= 10; i++)cin >> a1[i];
	Qsort(a1, 1,10);						//����Ʈ ����
	cout << "�� ��Ʈ ���: ";
	for (int i = 1; i <= 10; i++)cout << a1[i] << " ";
	cout << endl << endl;
	///////2�� ����////////////////////////
	cout << "2.\n10�� ���� �Է�(�߰��� ���� �� ��Ʈ)" << endl;
	for (int i = 1; i <= 10; i++)cin >> a1[i];
	midQsort(a1, 1, 10);					//���� ����Ʈ ����
	cout << "�߰��� ���� �� ��Ʈ ���: ";
	for (int i = 1; i <= 10; i++)cout << a1[i] << " ";
	cout << endl<<endl;
	delete[] a1;							//�޸� ���� 
	///////3,4�� ������ 10���� ����//////////////////////
	time_t start, end;
	srand((unsigned int)time(NULL));//���� ����
	int n; 
	cout << "3,4\n������ ������ ���� �Է�" << endl;
	cin >> n;
	int* a = new int[n+1];//�ܼ� �� ��Ʈ�� �迭
	int* b = new int[n+1];//���� �� ��Ʈ�� �迭
	for (int i = 1; i <= n; i++) {
		a[i] = rand() % n + 1;
		b[i] = a[i];
	}

	//�ܼ� �� ��Ʈ
	start = clock();//�ð� ���� ����
	Qsort(a, 1, n);//�ܼ� �� ��Ʈ
	end = clock();//���� ����
	cout << "\n�ܼ� �� ��Ʈ: " << end - start << " ms" << endl;

	//���� ����Ʈ
	start = clock();//�ð� ���� ����
	midQsort(b, 1, n);//���� �� ��Ʈ
	end = clock();//���� ����
	cout << "���� �� ��Ʈ: " << end - start << " ms" << endl<<endl;
	////////////5��///////////////
	cout << "5.\n�ܼ� ����Ʈ: ";
	checksort(a, n);//�迭�� ���� Ȯ��
	cout << "���� ����Ʈ: ";
	checksort(b, n);//�迭�� ���� Ȯ��
	cout << endl << endl;
	delete[]a;
	delete[]b;
	cout << "12171841 ������" << endl;
	return 0;
}
void swap(int& a, int& b) { //���۷����� �̿��� ���� �Լ�
	int tmp = a;
	a = b;
	b = tmp;
}
void Qsort(int arr[], int a, int b) { //�� ��Ʈ 
	if (a >= b)return;//���ҵ� ������ �ϳ� �� �� ����
	int l = a;//l�� a �� �迭�� �������� �ǹ�
	int r = b - 1;//r�� �ǹ� �ٷ� ���� �ε����� �ǹ�
	int p = arr[b];
	while (l <= r) {//l�� r������ �� 
		while (l <= r && arr[l] <= p)l++; //l�� r �����̰�, arr[l]�� �ǹ����� ū ���� ã�� �� ���� l�� ���� ���� ��Ų��.
		while (l <= r && arr[r] >= p)r--;//l�� r �����̰�, arr[r]�� �ǹ����� ���� ���� ã�� �� ���� r�� ���� ���� ��Ų��.
		if (l < r)swap(arr[l],arr[r]);//���� ������ ����µ� l<r�̶� �ǹ̴�, ���� �����Ǳ� ���� �ǹ����� ũ��, ���� ���� ���� �ϴ� �迭�� �ε����� ã�� ���̴�.
	}								  //�� l�� r�� �ε����� �迭 ���� ���� ��ȯ�Ѵ�.
	swap(arr[l],arr[b]);//while(l<=r)�� ���´ٴ� ����, l�� r�� �����ߴ� ���̰�, �� �� l�� �ε����� ���� �迭�� ���� �ǹ��� ��ȯ�Ѵ�.
	Qsort(arr, a, l - 1);//�� ó���� a�� l-1���� �����ؼ� �� ��Ʈ ��������� ���� (arr[l]�� �ǹ��� �ٲ�� ������, l-1���� �ϴ� ���̴�.)
	Qsort(arr, l + 1, b);//�� �ǹ��� �ٲ� l ������ l+1���� �� ���� b������ �����ؼ� ����Ʈ�� ��������� ���� 
}
void midQsort(int arr[], int a, int b) { //���� �� ��Ʈ 
	int l, r, m,p;//���� ����
	if (b - a > 2) {			//������ ������ 3�� �̻��� �� ���� 
		m = (a + b) / 2;//m�� a�� b�� �߰� ��
		if (arr[a] > arr[m])swap(arr[a], arr[m]);//������ ���� ��� �� ���� ũ�� swap
		if (arr[a] > arr[b])swap(arr[a], arr[b]);//������ ���� �������� ������ ũ�� swap
		if (arr[m] > arr[b])swap(arr[m], arr[b]);//��� ���� ������ ������ ũ�� swap
		swap(arr[m], arr[b-1]);//��������� ���߿��� ��� ���� arr[m]�� ��ġ�ϰ� �ǰ�, �� ���� �ǹ��� ������ ���ش�..

		l = a; r = b - 1; p = arr[b - 1];//l�� �迭�� �� ���� �ε���, r�� �ǹ��� �ٷ� ���� �ε���, p=arr[b-1]�� �ǹ����� ���ش�. 
		while (1) {
			while (arr[++l] < p);//l�� �ε����� ������Ű�鼭 �ǹ��� ������ Ŀ�� �� ���� ����
			while (arr[--r] > p);//r�� �ε����� ���ҽ�Ű�鼭 �ǹ��� ������ �۾��� �� ���� ���� 
			if (l >= r)break;//l�� ���� r�� ���� �����ϸ� break�Ѵ�.
			swap(arr[l], arr[r]);//���� ���� r���� �۰�, arr[l]�� �ǹ� ���� ũ��, arr[r]�� ���� �ǹ����� ���� �� ���� ���� �ٲ��ش�.
		}
		swap(arr[l], arr[b - 1]);//l�� ���� r�� ���� �����Ͽ� break�� �����̹Ƿ�, arr[l]�� ���� arr[b-1]�� ���� swap
		midQsort(arr, a, l - 1);//a�ε������� l-1�ε������� ����Լ��� �������ش�.
		midQsort(arr, l + 1, b);//l+1�ε������� b�ε������� ����Լ��� �������ش�.
	}
	//���Ұ� 1���� ���� 2���� �� ���� �Ǵµ�, ������ 1���� �� ���� �����Ƿ�, ���� x, ���� 2���� �� ���� ���Ұ� �� ũ�� ���� ���ҿ� swap
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
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
	cout << "----------1,2��: ���� �۵� Ȯ��----------" << endl << endl;
	Maxheapsort(maxarr, 10);//lastnode�� 10
	Minheapsort(minarr, 10);//lastnode�� 10
	cout << "Max heap���� ����: " << endl;
	for (int i = 1; i <= 10; i++)cout << maxarr[i] << " ";
	cout << endl;
	cout << "Min heap���� ����: " << endl;
	for (int i = 1; i <= 10; i++)cout << minarr[i] << " ";
	cout << endl << endl;
	////////////////////////////////////////////////
	cout << "----------4,5��: ������ �ð� ����----------" << endl << endl;
	time_t start, end;
	srand(time(NULL));
	int n, lastnode;
	cout << "���� ���� ���� �Է�: ";
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
	cout << "----------5��: ���� Ȯ��----------" << endl << endl;
	cout << "maxA �迭: "; checkSorted_ascending(maxA, n);
	cout << "minA �迭: "; checkSorted_descending(minA, n);
	cout << "\n\n----------------------------------------------\n\n";
	cout << "12171841 ������" << endl;

	delete[] maxA;
	delete[] minA;
	return 0;
}
void swap(int arr[], int n, int m) { //swap function
	int tmp = arr[n];
	arr[n] = arr[m];
	arr[m] = tmp;
}
void Minheapify(int a[], int h, int m) { //h: ��Ʈ ��� �ε���  m:last node index -> heapify�� Ư�� ���Ұ� ������, h�� �ö�� ���Ҹ� ���� �ڸ��� �°Բ� ã�ư��� �ϴ� �˰���
	int j = h;      //j�� ��Ʈ ����� �ε���

	for (j = 2 * h; j <= m; j *= 2) { //->j�� �׻� ¦����
		if (j < m && a[j] > a[j + 1])j++; //�Ϻη� j=2*h�� �����Ͽ� ���� �ڽ��� �ε������� ��, j�� lastnode���� ������, ������ �ڽĵ� �ִ� ��. 
										  //������ ��尡 ���� �ڽ��� ���, j�� �׻� ¦���� �Ϳ� ������ j<m�� ������ ������ ��忡 �ͼ� �׻� ���� ���� �ʴ� ����-> j �� ���� x
										  //������ �ڽ��� �� ���� ��� j�� �ش� �ڽİ� �ٲ�� �ϹǷ�, j++ 
		if (a[j / 2] <= a[j]) return; //�θ� ��尡 �ڽ� ��庸�� ���� ��� -> ���� �� ����=>�̹� �� ������ Ʈ���� ��Ʈ ��� �� �����ִ� �� �̹Ƿ�, return ���ִ� ��  
		else {      //�θ��尡 �� ū ���, ū �ڽ��� ���� a[j]�� �θ� ����� a[j/2] ���� swap
			swap(a, j, j / 2);
		}
	}//������ ���� ���Ծ� -> j�� m�ʰ��� ���·� ���� ��. => m�ʰ��� ���� k��� ���� ��, a[k/2]���� ���� �־��ְ�, a[k] �ڸ��� ����ִ� ���¿���, k�� 2�谡 �Ǿ� ���� ��
	//���� a[k/2]�� �ڸ��� ���� ����ִ� ����, �� ���� ���� ���̾���, v�� �־��ִ� ���̴�.
}
void Minheapsort(int a[], int m) {  //���� �ִ��� ������, ������ 1���� �ؾ��ϴ� ��

	int n = m; //n�� lastnode�� �ε��� ��. -> n�� ����� ������ �ǹ� 
	//�ִ� ���� ���� ������ ������� �ϹǷ�, 
	for (int i = n / 2; i >= 1; i--) {  //n�� lastnode, i�� lastnode�� �θ���
		Minheapify(a, i, n);// �Ʒ����� ���� ������ �����.
	}
	for (int i = n - 1; i >= 1; i--) {
		swap(a, 1, i + 1); //n�� ������ �� �Ȱ͵� ��, i+1�� �ε����� lastnode�̹Ƿ�, i+1 (n)�� 1�� �ٲ��ش�. ���� lastnode�� n-1�� ���� heapify�Ѵ�.
		Minheapify(a, 1, i);//�ٽ� ������ ����� �ش�.
	}
}
void Maxheapify(int a[], int h, int m) { //h: ��Ʈ ��� �ε���  m:last node index -> Maxheapify�� Ư�� ���Ұ� ������, h�� �ö�� ���Ҹ� ���� �ڸ��� �°Բ� ã�ư��� �ϴ� �˰���
	int j = h;      //j�� ��Ʈ ����� �ε���

	for (j = 2 * h; j <= m; j *= 2) { //->j�� �׻� ¦����
		if (j < m && a[j] < a[j + 1])j++; //�Ϻη� j=2*h�� �����Ͽ� ���� �ڽ��� �ε������� ��, j�� lastnode���� ������, ������ �ڽĵ� �ִ� ��. 
										  //������ ��尡 ���� �ڽ��� ���, j�� �׻� ¦���� �Ϳ� ������ j<m�� ������ ������ ��忡 �ͼ� �׻� ���� ���� �ʴ� ����-> j �� ���� x
										  //������ �ڽ��� �� ū ��� j�� �ش� �ڽİ� �ٲ�� �ϹǷ�, j++ 
		if (a[j / 2] >= a[j]) return; //�θ� ��尡 �ڽ� ��庸�� ū ��� -> ���� �� ����=>�̹� �� ������ Ʈ���� ��Ʈ ��� �� �����ִ� �� �̹Ƿ�, return ���ִ� ��  
		else {              //�θ��尡 �� ���� ���, ū �ڽ��� ���� a[j]�� �θ� ����� a[j/2] ���� swap
			swap(a, j, j / 2);
		}
	}//������ ���� ���Ծ� -> j�� m�ʰ��� ���·� ���� ��. => m�ʰ��� ���� k��� ���� ��, a[k/2]���� ���� �־��ְ�, a[k] �ڸ��� ����ִ� ���¿���, k�� 2�谡 �Ǿ� ���� ��
	//���� a[k/2]�� �ڸ��� ���� ����ִ� ����, �� ���� ���� ���̾���, v�� �־��ִ� ���̴�.
}
void Maxheapsort(int a[], int m) {  //���� �ִ��� ������, ������ 1���� �ؾ��ϴ� ��

	int n = m; //n�� lastnode�� �ε��� ��. -> n�� ����� ������ �ǹ� 
	//�ִ� ���� ���� ������ ������� �ϹǷ�, 
	for (int i = n / 2; i >= 1; i--) {  //n�� lastnode, i�� lastnode�� �θ���
		Maxheapify(a, i, n);// �Ʒ����� ���� ������ �����.
	}
	for (int i = n - 1; i >= 1; i--) {
		swap(a, 1, i + 1); //n�� ������ �� �Ȱ͵� ��, i+1�� �ε����� lastnode�̹Ƿ�, i+1 (n)�� 1�� �ٲ��ش�. ���� lastnode�� n-1�� ���� Maxheapify�Ѵ�.
		Maxheapify(a, 1, i); //������ �����.
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
	if (flag)cout << "Max heap �������� ���� ����" << endl;
	else cout << "���� ����" << endl;
}
void checkSorted_descending(int a[], int n) {
	bool flag = true;
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i + 1]) {
			flag = false;
			break;
		}
	}
	if (flag)cout << "Min heap �������� ���� ����" << endl;
	else cout << "���� ����" << endl;
}
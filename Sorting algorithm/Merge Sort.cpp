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
	cin >> m;//�迭�� ũ�� �Է�
	for (int i = 0; i < m; i++) {
		cin >> a[i];
		Data[i] = a[i];
	}
	int pos = 0;	//�ּ� ���� ��ġ�� ����� ���� pos
	for (int i = 0; i < m; i++) { //���� ����
		int Min = a[i];//unsorted�� �迭�� ù��° ���Ҹ� Min���� �Ѵ�.
		for (int j = i + 1; j < m; j++) {
			if (a[j] < Min) { //Min���� a[j] �� ������ Min�� ���� a[j]�� ����, �ش� ��ġ pos�� ���
				Min = a[j];
				pos = j;
			}
		}
		if (Min != a[i]) { //Min�� �ٲ� ��쿡�� swap ���� 
			int tmp = a[i];
			a[i] = Min;
			a[pos] = tmp;//����ص� pos�� ���� a[pos]�� ���� ó�� Min�̶� ������ a[i]���� swap
		}
	}
	cout << "1��\n���� ������ ���: ";
	for (int i = 0; i < m; i++) {
		cout << a[i] << " ";
	}cout << endl;

	divide(0, m - 1);//�պ� ���� �迭�� 0��~ n-1���� ���Ҹ� �־� �����Ƿ� 

	cout << "2��\n�պ� ������ ���: ";
	for (int i = 0; i < m; i++) {
		cout << Data[i] << " ";
	}cout << endl;
	//////////////////////////////////////////////////////////////////////////////////////////
	srand(time(NULL));
	time_t start, end;
	cout << "3��\n�迭�� ũ�� �Է�";
	int n;
	cin >> n; //�迭�� ũ�� 

	for (int i = 0; i < n; i++) {
		 a[i]=(rand()%n)+1;//���� ���� �� �迭�� ���� �־��ش�.
		Data[i] = a[i];
	}
	//���� ���� ����
	int Pos = 0;	//�ּ� ���� ��ġ�� ����� ���� pos
	start = clock();
	for (int i = 0; i < n; i++) { //���� ����
		int Min = a[i];//unsorted�� �迭�� ù��° ���Ҹ� Min���� �Ѵ�.
		for (int j = i + 1; j < n; j++) {
			if (a[j] < Min) { //Min���� a[j] �� ������ Min�� ���� a[j]�� ����, �ش� ��ġ pos�� ���
				Min = a[j];
				Pos = j;
			}
		}
		if (Min != a[i]) { //Min�� �ٲ� ��쿡�� swap ���� 
			int tmp = a[i];
			a[i] = Min;
			a[Pos] = tmp;//����ص� pos�� ���� a[pos]�� ���� ó�� Min�̶� ������ a[i]���� swap
		}
	}
	end = clock();
	cout << "4��\n���� ����:" << end - start << "ms" << endl;

	start = clock();
	divide(0, n-1);//�պ� ����
	end = clock();
	cout << "�պ� ����:" << end - start << "ms" << endl;

	cout << "5��\n";
	cout << "�պ� ���� ���� ���: ";
	checkSort(Data, n);
	cout << "���� ���� ���� ���: ";
	checkSort(a, n);

	return 0;
}

void divide(int lt, int rt) {
	if (lt < rt) { //���� �μ��� ������ �μ����� ���� �� ���� �� �ϳ��� ���Ҹ� ���� ���� ���� x
		int mid = (lt + rt) / 2; //��� index�� mid�� ����
		divide(lt, mid);//�迭�� ���� �κ� (lt~mid)���� �ٽ� divide
		divide(mid + 1, rt); //�迭�� ������ �κ� (mid+1~rt)���� �ٽ� divide
		merge(lt, rt);//�պ� �Լ�
	}
}
void merge(int lt, int rt) {
	int mid = (lt + rt) / 2;	//��� index�� mid ����
	int	pos1 = lt;	//������ �迭 ��, ���� �迭�� index pos1�� lt�� ����
	int pos2 = mid + 1;	//������ �迭 ��, ������ �迭�� index pos2�� mid+1�� ����
	int pos3 = lt;	//�迭�� ���� �ؾ��ϹǷ�, ���ĵ� �ӽ� �迭�� index�� �� ó�����Ϳ��� �ϹǷ�, lt�� ����
	while (pos1 <= mid && pos2 <= rt) { //���� �迭�� index�� mid�����̰�, ������ �迭�� index�� rt ������ �� ���� �� �迭�� �պ��� ������ ���� ��
		if (Data[pos1] < Data[pos2]) tmp[pos3++] = Data[pos1++];//���� �迭�� index�� ���� ������ �迭 index�� �� ���� �����Ƿ� ���� tmp�迭�� �־��ְ�,���� �־��� pos1�� pos3 ++
		else tmp[pos3++] = Data[pos2++];//������ �迭�� index�� ���� ���� �迭 index�� �� ���� �����Ƿ� ���� tmp�迭�� �־��ְ�,���� �־��� pos2�� pos3 ++
	}
	while (pos1 <= mid) tmp[pos3++] = Data[pos1++];//������ �迭�� ���� ���ĵ� �迭�� �� �� ���� ���� �迭�� ���ҵ��� tmp �迭���־��ش�. �׸��� �� index++
	while (pos2 <= rt) tmp[pos3++] = Data[pos2++];//���� �迭�� ���� ���ĵ� �迭�� �� �� ���� ������ �迭�� ���ҵ��� tmp �迭���־��ش�. �׸��� �� index++
	for (int i = lt; i <= rt; i++) Data[i] = tmp[i];// ���ĵ� tmp�迭�� ���� lt���� rt���� Data �迭�� ���� �ٲ��ֹǷ� ������ �ȴ�.
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
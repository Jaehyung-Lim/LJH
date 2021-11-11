#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//data: ���� �迭
//size: data�� �������� ����
//p: ������ �ִ� �ڸ���
//k: ���-> 10���� �̹Ƿ�, 10

void rxSort(int* data, int size, int p, int k) {
	int* counts, //Ư�� �ڸ����� ���ڵ��� ī��Ʈ
		* temp; //���ĵ� �迭�� ���� �ӽ� ���
	int index, pval, i, j, n;
	if ((counts = (int*)malloc(k * sizeof(int))) == NULL)return;
	if ((temp = (int*)malloc(size * sizeof(int))) == NULL) return;
	for (n = 0; n < p; n++) {
		for (i = 0; i < k; i++) counts[i] = 0; 
		pval = (int)pow((double)k, (double)n);
		for (j = 0; j < size; j++) {
			index = (int)(data[j] / pval) % k;
			counts[index] = counts[index] + 1;
		}
		for (i = 1; i < k; i++)counts[i] = counts[i] + counts[i - 1];
		for (j = size - 1; j >= 0; j--) {
			index = (int)(data[j] / pval) % k;
			temp[counts[index] - 1] = data[j];
			counts[index] = counts[index] - 1;
		}
		memcpy(data, temp, size * sizeof(int));
	}
}
#define size 8
#define p 3
#define k 10
int data[8] = { 170,45,75,90,2,24,802,66 };

void main() {
	int i;
	printf("���� �� ���\n ");
	for (i = 0; i < size; i++)printf("%d ", data[i]); 
	printf("\n\n");

	rxSort(data, size, p, k);

	printf("���� ���� ���\n ");
	for (i = 0; i < size; i++)printf("%d ", data[i]);
	printf("\n\n12171841 ������\n");
}
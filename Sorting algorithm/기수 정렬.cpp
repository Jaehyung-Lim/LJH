#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//data: 정수 배열
//size: data의 정수들의 개수
//p: 숫자의 최대 자리수
//k: 기수-> 10진수 이므로, 10

void rxSort(int* data, int size, int p, int k) {
	int* counts, //특정 자리에서 숫자들의 카운트
		* temp; //정렬된 배열을 담을 임시 장소
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
	printf("정렬 전 출력\n ");
	for (i = 0; i < size; i++)printf("%d ", data[i]); 
	printf("\n\n");

	rxSort(data, size, p, k);

	printf("정렬 이후 출력\n ");
	for (i = 0; i < size; i++)printf("%d ", data[i]);
	printf("\n\n12171841 임재형\n");
}
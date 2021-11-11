#include <iostream>
using namespace std;

void InitNext(int[], char[]);
void RevisedInitNext(int[], char[]);
void displayNext(int[],int);
int main(){
	cout << "12171841 임재형" << endl;
	////////////////////////////////////////////////////////////////////
	char p1[100]="AABBAA"; 
	char p2[100]="ABAABAB"; 
	char p3[100]="ABABABAC";  //패턴 p1,p2,p3 정의
	
	int n1 = strlen(p1);	  //next 배열 크기를 동적으로 할당하기 위한 크기를 구한다.
	int n2 = strlen(p2);
	int n3 = strlen(p3);
	int* Renext1 = new int[n1];		//개선 후 ReInitNext의 값을 받을 배열

	int* Renext2 = new int[n2];		//개선 후 ReInitNext의 값을 받을 배열		

	int* Renext3 = new int[n3];		//개선 후 ReInitNext의 값을 받을 배열
	//////////////////////////////////////////
	cout << "\n-----예제 1-----\nPattern: AABBAA\n\n";
	RevisedInitNext(Renext1, p1);
	displayNext(Renext1, n1);

	cout << "\n-----예제 2-----\nPattern: ABAABAB\n\n";
	RevisedInitNext(Renext2, p2);
	displayNext(Renext2, n2);

	cout << "\n-----예제 3-----\nPattern: ABABABAC\n\n";
	RevisedInitNext(Renext3, p3);
	displayNext(Renext3, n3);
	///////////////////////////////////////////
	delete[] Renext1; delete[]Renext2; delete[]Renext3;
	cout << "\n12171841 임재형\n";
	return 0;
}
//개선 되기 전 
void InitNext(int next[], char p[]) {
	int M = strlen(p);//i의 값을 비교할 때 패턴의 길이인 M이 필요 하다. 따라서 입력된 패턴 p의 길이를 M으로 정의
	next[0] = -1;	  //next[0]의 값은 항상 -1로 한다. 배열에서 일치하지 않을 때, 0번으로 가라고 하는 것은, netx[0]즉 -1이기 때문에 1 추가한 0 즉, 다시 맨 처음부터 비교 해야한다는 의미.
	for (int i = 0, j = -1; i < M; i++, j++) {//i는 패턴의 가장 첫번째 인덱스인 0, j는 현재 i번째 인덱스에서 불일치 발생시에, 어느 인덱스로 가야하는지에 대한 정보를 담는 변수이다.
		next[i] = j;//next[i]에 j값을 넣어줌으로써, i번째의 인덱스에서 불일치 발생시, j인덱스의 패턴부터 다시 비교하라는 의미를 갖는다. 
		while (j >= 0 && p[i] != p[j]) { //j는 0 이상이여야 하며, p[i]와 p[j]의 불일치 발생시, 
			j = next[j]; //기존에 저장해 두었던, j번째 인덱스로 가야하기 때문에, j에 next[j]값을 저장하고, while문이 종료될때 까지 반복한다.
		}//j가 0보다 작아진 즉 -1이 나온다면 맨 처음부터 다시 비교한다는 의미이고, p[i]와 p[j]가 일치해서 while문이 종료됐다면, p[i]와 p[j]는 일치하기 때문에 그 다음 인덱스를 비교한다.
	}
}
//개선 되고 난 후 
void RevisedInitNext(int next[], char p[]) { //개선의 조건 
	int M = strlen(p);
	next[0] = -1;
	for (int i = 0, j = -1; i < M; i++, j++) {
		if (p[i] == p[j]) next[i] = next[j]; //불일치가 발생했는데 또 다시 이동한 인덱스의 패턴 값이 같은 값이면, 이동시켜준 의미가 없기 때문에 next[i] 값에 next[j]를 넣어준다.
		else next[i] = j;//불일치할 땐 정상적으로 넣어준다.                                           -> 어차피 불일치 하여 이동 했는데, 같은 문자이기 떄문에 불일치 하면 의미가 없기 때문이다.
		while (j >= 0 && p[i] != p[j]) {//j는 0 이상이여야 하며, p[i]와 p[j]의 불일치 발생시, 
			j = next[j]; //기존에 저장해 두었던, j번째 인덱스로 가야하기 때문에, j에 next[j]값을 저장하고, while문이 종료될때 까지 반복한다.
		}//j가 0보다 작아진 즉 -1이 나온다면 맨 처음부터 다시 비교한다는 의미이고, p[i]와 p[j]가 일치해서 while문이 종료됐다면, p[i]와 p[j]는 일치하기 때문에 그 다음 인덱스를 비교한다.
	}
}
void displayNext(int a[],int sz) {
	printf("-------------\nNext[j]:  j  \n-------------\n");
	for (int i = 0; i < sz; i++) { 
		printf("Next[%d]: %2d  ", i, a[i]); 
		printf("=>%d 인덱스에서 불일치 발생시 Next[%d]인 %2d 인덱스로 가서 다시 비교한다.", i, i, a[i]);
		if (a[i] == -1)printf("=>-1인덱스는 다시 0인덱스로 간다.");
		printf("\n");
	}
	printf("\n");
}

#include <iostream>
using namespace std;
#define NUM 53 //공백,소문자,대문자 포함 
int skip[NUM];
int index(char);
void InitSkip(char[]);
int MisChar(char[], char[]);
int main() {
	cout << "12171841 임재형" << endl << endl;
	char t[100] = "VISION QUESTION ONION CAPTION GRADUATION EDUCATION";
	char p[50] = "ATION";
	int pos = 0,pre_pos=0;//위치를 기억할 변수 pos, pre_pos를 선언한다.
	char* text = t;//포인터 변수에 문자열의 가장 첫번 주소를 기억하게 한다.
	//t의 의미는 &t[0]이므로, 가능하다.
	while (1) {
		pos = MisChar(p, text)+pos;
		//일치가 발생했을 때의 위치를 기억할 pos에 함수의 리턴값과 기존 pre_pos값을 더해준다.
		if (pre_pos==pos)break;//pos와 pre_pos가 같으면 text가 0이기 때문에 더이상 일치하는 패턴이 없다는 것이므로 루프 종료
		printf("패턴 발생 위치: %d\n", pos);
		pos = pos + 1;//찾은 위치 그 다음 위치에서부터 다시 문자열 탐색을 위해 1을 증가시킨다.
		//M이 아닌 1을 증가시키는 이유는, AAAAAAAAA의 텍스트에선 AA패턴을 찾을 때, 0,1,2 --- 이런식으로 나오기 때문에, 1을 증가시켰다.
		pre_pos = pos;//pre_pos에 pos값을 넣어준다.
		text = text + pos;//text를 pos만큼 이동한 배열에서부터 시작하는 배열로 다시 정의한다.
	}
	cout<<endl << "12171841 임재형" << endl;
	return 0;
}
int index(char t) {//index는 그 문자의 알파엣이 알파벳의 순서에서 몇번째 인덱스인지 알려주려는 것 (대,소문자 따로 구분)
	if (t == 0)return 0;
	else return t-64;
}
void InitSkip(char p[]) {
	int M = strlen(p);
	for (int i = 0; i < NUM; i++)skip[i] = M;//모든 skip 배열을 M으로 초기화 해준다.
	for (int i = 0; i < M; i++)skip[index(p[i])] = M - i - 1;
	//이후, p[i]는 오른쪽에서 얼마나 움직였을 때 나오는 문자인지를 알 수 있게, M-i-1을 skip 배열의 값으로 해준다.
}
int MisChar(char p[], char t[]) {
	int M = strlen(p), N = strlen(t), k,i,j;
	if (N == 0)return 0;//텍스트의 길이가 0이면 곧바로 0을 리턴해준다.
	InitSkip(p);
	for (i = M - 1, j = M - 1; j >= 0; i--, j--) {//i는 텍스트에서, j는 패턴에서의 문자 확인 제어 변수. 시작점은 패턴의 가장 우측에서 부터 비교한는 것이므로 i,j=M-1  
		while (t[i] != p[j]) {//i,j에서 패턴과 텍스트의 문자가 일치하지 않으면 두가지의 경우로 볼 수 있다. (M-j>k, M-j<=k)
			k = skip[index(t[i])];//k에는 t[i]가 패턴에서 문자열의 끝에서 부터오른쪽으로 부터 얼마나 이동했을 때 나오는 문자 인지 확인한다.
			if (M-j > k)i = i + M - j;//M-j는 패턴에서, 오른쪽에서 얼마나 왼쪽으로 이동했는지의 거리를 의미한다.
			//M-j>k일땐 텍스에서 불일치가 M-j 보다 작게 움직이면 계속 발생하기 때문에 해당 텍스트에서 더 큰 값인 M-j만큼 건너 뛰어야 한다는 것이다.
			else //M-j<k인 경우엔 텍스트에서 해당 문자가 k 보다 작게 움직였을 때 계속 불일치가 발생하기 때문에 
				i = i + k;//해당 텍스트에서 더 큰 값인 k칸 만큼 건너 뛰어 주는 것이다. 
			if (i >= N)//텍스트에서의 i의 위치가 N 이상이라는 것은 텍스트의 범위를 넘어간 것이고, 즉 찾지 못했을때 이다.
				return N;//따라서 텍스트의 길이인 N을 출력해준다.
			j=M - 1;//그렇지 않으면 j는 다시 M-1로 초기화 해준다.
		}
	}
	return i + 1;
}

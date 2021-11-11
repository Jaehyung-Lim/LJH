#include <iostream>
#include"HuffmanAlgo.h"
#include <string>
using namespace std;

int main()
{
	PQ pq;//우선순위 큐 선언

	char sentence[1000];//최대 1000글자의 문장을 입력 받는다. 유동적으로 변경 가능
	cin.getline(sentence, 1000);//띄워쓰기 까지 받아야 하므로 getline을 사용한다.
	for (int i = 0; i < strlen(sentence); i++)//문장의 길이만큼 반복
	{
		pq.insert(sentence[i]);	//pq에 문자들을 삽입
	}
	HuffmanEncoder bt(pq);//허프만 인코더 객체 bt를 생성-> 인코더에 pq를 인자로 넣어준다. ->생성자에 의해 인코딩 되고, 이진 코드 부여
	bt.preorder(bt.root());//문자별 빈도수, 부호를 보여준다.
	cout << endl;
	cout << "인코딩결과:" << endl;
	bt.Conclusion(sentence);	//입력받은 문장을 인코딩된 이진 코드로 다시 출력
	return 0;
}


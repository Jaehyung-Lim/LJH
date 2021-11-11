#include <iostream>
#include "Tree_Vector_child_V.h"
#include <vector>
using namespace std;

int main()
{
	
	tree t1;
	//tree::Position* node1 = new tree::Position("증조할아버지", NULL);	 t1.setRoot(node1);		//포인터로 Root 설정
	t1.setRoot("증조할아버지");								//이름으로 Root 설정
	t1.insert(t1.Root(), "증조할아버지", "할아버지");
	t1.insert(t1.Root(), "증조할아버지", "작은할아버지");
	t1.insert(t1.Root(), "할아버지", "아빠");
	t1.insert(t1.Root(), "할아버지", "작은아빠");
	t1.insert(t1.Root(), "할아버지", "고모");
	t1.insert(t1.Root(), "작은할아버지", "큰당숙");
	t1.insert(t1.Root(), "작은할아버지", "둘째당숙");
	t1.insert(t1.Root(), "아빠", "임재형");
	t1.insert(t1.Root(), "아빠", "임수민");
	t1.insert(t1.Root(), "작은아빠", "임예린");
	t1.insert(t1.Root(), "작은아빠", "임재현");
	t1.insert(t1.Root(), "고모", "김현일");
	t1.insert(t1.Root(), "고모", "김채윤");
	t1.insert(t1.Root(), "둘째당숙", "임재후");
	t1.insert(t1.Root(), "둘째당숙", "임재웅");				//4대손 족보 입력
	
	int ce = 0;//번호 선택
	string con_name = "nullstr";							//입력용 string변수  
	string parent_name = "nullstr";							//입력용 string변수
	string son_name = "nullstr";							//입력용 string변수
	for (;;){
		cout << "선택: 1.족보 보기 2.대손 확인 3.삽입 4.삭제 5.인숸수 확인////그외.종료" << endl;
		cin >> ce;											//번호 입력
		if (ce == 1)
		{
			cout << endl;
			t1.preorder(t1.Root()); cout << endl << endl;;//전위순회로
		}
		else if (ce == 2)
		{
			cout <<endl<< "누구의 대손을 확인하시겠습니까? 이름을 입력해 주십시오" << endl;
			cin >> con_name;								//이름입력
			t1.depth_name(t1.Root(), con_name); cout << endl;//함수 실행
		}
		else if (ce == 3)
		{
			cout <<endl<< "삽입할 부모노드의 이름과, 삽입될 자녀의 이름을 입력해 주십시오." << endl;
			cout << endl;
			cin >> parent_name >> son_name;					//부모의 이름과 자녀의 이름을 순서대로 입력
			t1.insert(t1.Root(), parent_name, son_name);	//string으로 삽입 
		}
		else if (ce == 4)
		{
			cout <<endl<< "삭제할 노드의 이름을 입력해 주십시오" << endl;
			cin >> con_name;								//삭제할 이름 입력
			t1.DeleteOf(t1.Root(), con_name);				//삭제 함수
		}
		else if (ce == 5)
		{
			cout << endl << "족보 구성 인원수를 구합니다: " << endl;
			cout << t1.size() << " 명 입니다." << endl;
		}
		else
		{
			cout <<endl<< "종료합니다." << endl;			//종료
			exit(1);
		}
	}
	return 0;
}

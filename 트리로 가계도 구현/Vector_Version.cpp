#include <iostream>
#include "Tree_Vector_child_V.h"
#include <vector>
#include <string>
using namespace std;

//////////////////////////////////////////////////Position Adt/////////////////////////////////////////////////////////
tree::Position::Position(string _name, Position* p)	//생성자
	:name(_name), parent(p), cSize(0)//initializer
{
	child.push_back(NULL);							//child에 NULL포인터를 넣어준다 ->자녀가 없음을 의미(생성자 이므로)
	if (p == NULL)dpth = 0;							//부모가 null이라면 깊이=0
	else dpth = p->dpth + 1;						//부모가 있다면, 깊이= 부모의 깊이+1
}
tree::Position::Position()							//생성자
	:name("default name"), parent(NULL), cSize(0), dpth(0)//initializer
{
	 child.push_back(NULL);							//child에 NULL을 넣어준다 ->자녀가 없음을 의미 
}
tree::Position* tree::Position::Parent() const		//부모 포인터(Position 출력)
{
	return parent;									//부모 출력
}
bool tree::Position::isExternal() const				//leafNode인지 확인
{
	return child.back() == NULL;					//child의 back이 Null-> 자녀가 없다-> true
}
bool tree::Position::isInternal() const				//자녀가 있는지 확인
{
	return !isExternal();							//External이 아닐 때 true
}
bool tree::Position::isRoot() const					//Root인지 확인
{
	return parent == NULL;							//부모가 NULL이면 Root노드이다
}
int tree::Position::getChildSize() const			//자식 노드 개수 출력
{
	return cSize;									//cSize 리턴
}
int tree::Position::depth() const					//깊이 출력
{
	return dpth;									//dpth 리턴
}
string tree::Position::getname() const				//이름 출력
{
	return name;									//name 리턴
}
///////////////////////////////////////////////////tree Adt////////////////////////////////////////////////////////////
tree::tree()	//생성자
	:sz(0), root(NULL)								//member initializer 
{	
	//트리가 비었으므로 사이즈=0, root=NULL
}
int tree::size() const								//트리의 크기 출력
{
	return sz;										//sz 리턴
}
bool tree::empty() const							//비었는지 확인하는 함수
{
	return sz == 0;									//sz=0이면 true 출력
}
tree::Position* tree::Root() const					//root포인터 출력 함수
{
	try{ if (sz == 0) throw string("루트가 없습니다!Root함수 오류. 종료합니다. ");}
	catch (const string& ex) { cout << ex << endl; exit(1); }			//예외사항 처리

	return root;									//root 출력
}
void tree::sameNameCheck(Position* p, const string& _name)const	//p는 루트 고정
{
	if (p->name == _name)										//p의 이름과 넣어준 이름이 같을 때 
	{
		cout << "같은 이름의 자식노드가 있습니다. insertChildOf() 오류!! 종료합니다" << endl;
		exit(1);												//강제 종료
	}
	else if (p->isInternal())									//부모노드의 이름이 같지 않을 때 
	{
		for (int i = 0; i < p->cSize; i++)
		{
			sameNameCheck(p->child[i], _name);					//재귀적 실행
		}
	}															//external이고, 이름이 다르면 굳이 확인 할 필요가 없다
}
void tree::insertChildOf(Position* p, const string& _child)		//p부모 노드의 자식으로 _child 이름을 가진 자식노드 삽입
{
	sameNameCheck(p, _child);			//같은 이름이 있는지 체킹 =>예외처리!!!!

	tree::Position* newChild = new tree::Position(_child, p);	//새로운 노드 생성
	if (p->cSize==0)											//p가 external 노드일 때 
	{
		p->child.pop_back();									//child벡터에 back으로 들어있던 NULL포인터를 pop해준다
		p->child.push_back(newChild);							//그 다음 새로 생성해준 newChild 포인터를 push해준다
	}
	else														//기존에 자식노드가 있을 때 
	{
		p->child.push_back(newChild);							//단순히 push만 해주면 된다
	}
	p->cSize++;													//p노드의 자식 사이즈인 cSize + 1
	sz++;														//트리의 사이즈인 sz + 1
}
void tree::insertChildOf(Position* p, Position* son)			//p부모 노드에 이미 생성돼있는 son노드를 삽입
{
	sameNameCheck(p, son->name);		//같은 이름이 있는지 체킹 =>예외처리!!!!
	if (p->cSize == 0)											//p가 external 노드일 때 
	{
		p->child.pop_back();									//child벡터에 back으로 들어있던 NULL포인터를 pop해준다
		p->child.push_back(son);								//그 다음 자식노드로 해줄 son을 push 한다
	}
	else														//기존에 자식노드가 있을 때 
	{
		p->child.push_back(son);								//그냥 son을 push만 해주면 된다
	}
	son->parent = p;											//son의 parent를 p로 한다
	son->dpth=p->dpth+1;										//자식노드의 깊이는 부모노드의 +1이므로 
	p->cSize++;													//p에 자식노드가 추가됐으므로 cSize 1추가
	sz++;														//트리의 사이즈 1증가
}
void tree::insert(Position* p, const string& pname, const string& son)  //p는 루트 고정 
																//=>pname의 이름을 갖고 있는 부모 노드에 son이름의 자식을 삽입
{																//같은 이름 예외는 insertChildOf()함수에서 실행되므로 여기서 적을 필요가 없다.
	if (p->name == pname)										//이름이 같을 때 
	{
		insertChildOf(p, son);									//오버로딩한 insertChildOf(Position* p, const string& son)이 실행된는것
	}
	else if (p->isInternal())									//이름 다르고, 자식이 있을 때 자식들로 들어가 없으면 다음 자식
	{
		for (int i = 0; i < p->cSize; i++)						//자식의 수 만큼 반복
		{
			insert(p->child[i], pname, son);					//재귀적으로 insert함수 반복=>void형 이기 떄문에
		}														//이름이 같은 부모노드를 찾으면 자동으로 함수가 종료된다
	}															//또한 트리에 노드 삽입 시에 이름 중복 방지 했으므로, 
}																//중복에 대한 고려를 할 필요가 없다
void tree::DeleteOf(Position* p)								//DelteOf()함수=> p포함, p노드 밑으로 다 삭제
{
	try { if (p == NULL)throw string("NULL포인터는 지울 수 없습니다!. Deleteof() 함수에서 에러 발생"); }
	catch (const string& ex) {cout << ex << endl; exit(1);}		//예외처리=> NULL포인터 지울때 발생하는 오류 방지
	if (p->isInternal())										//해당 노드와 그 자식들 전부 삭제 하고 마지막으로 Internal 노드까지 삭제 하는거
	{
		for (int i = 0; i < p->cSize; i++)						//재귀적으로 DeleteOf함수 실행
		{
			DeleteOf(p->child[i]);								//여기까지 끝났으면, 이미 자녀가 다 없어져야한다
		}
		DeleteOf(p);											//이후에 자기 자신 삭제=>마치 postorder의 순서
	}
	else if (p->isExternal())									//p가 루트가 아니고 External노드 일 때 =>이 노드 하나만 삭제해주면 된다
	{															//child벡터에서, p가 back이나 front가 아닐 떄 처리?? =>이터레이터 개념을 이용한다
		if (p->isRoot())										//External인데 root이면
		{
			delete root;										//루트만 지워주고 끝낸다.
			sz--;												//트리의 사이즈 1 감소
		}
		else if (p->parent->cSize == 1)							//형제가 없을 때 자기 혼자만 있는 경우
		{
			p->parent->child.pop_back();						//p의 부모의 자식을 빼는것 이므로, p->parent의 child를 pop
			p->parent->child.push_back(NULL);					//형제가 없으므로, child벡터에는 다시 NULL이 들어가야하므로, NULL push =>다른 함수에서 모두 NULL유무로 제어하므로
			p->parent->cSize--;									//p의 부모의 자식 사이즈 - 1
			delete p;											//p노드는 다른 노드와의 연결이 끊겼으므로, delete 해준다
			sz--;												//트리의 사이즈 1 감소
		}
		else if (p->parent->cSize>1)							//주변에 형제가 있을 때 즉, p가 back이나 front가 아닐 떄 처리??
		{														// =>begin과 end함수, erase함수를 사용하여 해당 원소 번호만 삭제해준다
			int count = 0;										//p가 p->parent->child의 몇번째 원소인지 확인용 넘버
			for (int i = 0; i < p->parent->cSize; i++)			//부모 노드의 자식 수 만큼 반복
			{
				if (p->parent->child[i] == p) break;			//p->parent->child[i]가 삭제하려는 p이면 break
				else count++;									//그렇지 않으면 count 1증가
			}
			p->parent->child.erase(p->parent->child.begin() + count, p->parent->child.begin() + count + 1);
																//지우려고 하는 벡터의 원소만 1개 지워준다 =>count의 숫자를 알고, begin, end를 안다
			p->parent->cSize--;									//부모의 자식 사이즈 - 1
			delete p;											//p노드는 다른 노드와의 연결이 끊겼으므로, delete 해준다
			sz--;												//트리의 사이즈 1 감소
		}
	}
}
void tree::DeleteOf(Position* p, const string& node_name)		//재귀로 구현: 이름 입력시 해당하는 포인터 포함 자식 노드까지 전부 삭제
{
	if (p->name == node_name)									//지우려고 하는 노드의 이름이 같을 때 
		DeleteOf(p);											//Deleteof(p) 함수 실행
	else if (p->isInternal())									//p의 이름이 다른데, 자식이 있을 때 자식노드들도 확인
	{
		for (int i = 0; i < p->cSize; i++)						//자식의 수 만큼 반복
		{
			DeleteOf(p->child[i], node_name);					//재귀적으로 반복 실행
		}
	}
}
void tree::setRoot()	
{
	try{if (root != NULL) throw string("이미 루트가 있습니다!!! setRoot함수 에러/// 강제 종료합니다!!");}
	catch (const string& ex) { cout << ex << endl; exit(1); }	//루트가 이미 있을 때 예외처리

	string str;
	cout << "루트를 설정합니다. 이름을 입력해주세요" << endl;
	cin >> str;
	delete root;												//생성자에서 만들었던 root 노드 delete
	root = new tree::Position(str, NULL);						//입력받은 str의 name을 가진 새로운 노드 생성											
	sz++;														//기존 사이즈 0에서 1로 증가
}
void tree::setRoot(Position* p)
{
	try { if (root != NULL)throw string("Root가 이미 있습니다! setRoot() 함수에서 에러 발생"); }
	catch (const string& ex) {cout << ex << endl; exit(1);}		//루트가 이미 있을 때 예외처리
	delete root;												//생성자에서 만들었던 root 노드 delete
	root = p;													//root에 입력해준 p
	sz++;														//기존 사이즈0 에서 1로 증가
}
void tree::setRoot(const string& _name)
{
	try { if (root != NULL)throw string("Root가 이미 있습니다! setRoot() 함수에서 에러 발생"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//예외처리

	delete root;												//생성자에서 만들었던 root 노드 delete
	root = new tree::Position(_name, NULL);						//입력받은 이름의 root노드 생성
	sz++;														//기존 사이즈 0에서 1로 증가
}
void tree::preorder(Position* p) const							//전위순회로 족보 보여주기
{
	try { if (sz<1) throw string("Root가 비었습니다 preorder함수 오류!!!"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//NULL인 p를 입력해주었을 때의 예외처리

	cout << p->name << " ";										//이름을 출력 =>전위순회이므로 먼저 출력해준다

	if (p->isInternal())										//자식노드가 있을 때 재귀적으로 반복
	{
		for (int i = 0; i < p->cSize; i++)						//자식의 수 만큼
			preorder(p->child[i]);								//함수 실행
	}
}
void tree::postorder(Position* p)const							//후위순회로 족보 보여주기
{
	try { if (p == NULL) throw string("Root가 비었습니다 오류!!!"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//NULL인 p를 입력해주었을 때의 예외처리

	if (p->isInternal())										//자식노드가 있을 때 재귀적으로 반복
	{
		for (int i = 0; i < p->cSize; i++)						//자식의 수 만큼
			postorder(p->child[i]);								//함수 실행
	}
	cout << p->name << " ";										//p->name 출력
}
int tree::depth(Position* p) const								//트리에서의 int 반환형 깊이 출력 함수
{
	if (p->isRoot()) return 0;
	else return 1 + depth(p->parent);
}
void tree::depth_name(Position* p,const string& _name)const		//이름 입력시 몇 대손인지 확인하는 함수=>재귀적 구현
{																//p는 root를 넣어준다
	try { if (p == NULL) throw string("Root가 비었습니다. depth_nam()e 함수 오류!!!"); }
	catch (const string& ex) { cout << ex << endl; exit(1); }	//예외사항

	if (p->name == _name)										//입력해준 노드이 이름과 입력해준 이름이 같다면
		cout <<"입력한 사람은 " <<p->dpth<<" 대손입니다." << endl;	//대손 출력
	else if (p->isInternal())									//이름이 다르고, 자식노드를 함수이 파라미터로 하는 재귀 호출		
	{
		for (int i = 0; i < p->cSize; i++)						//반복문
			depth_name(p->child[i], _name);						//재귀적으로 깊이 출력 함수 호출
	}
}


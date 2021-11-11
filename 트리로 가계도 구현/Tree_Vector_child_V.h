#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class tree
{
public:
	class Position		
	{
		friend class tree;
	private:
		////////////////////////////////////////////////////////////////////////////////////////////
		vector<Position* >child;							//child라는 벡터 컨테이너 안에 Position* 자료형을 저장함으로써 자녀들을 담을 수 있게 했다.
		int cSize;											//자식 노드의 개수
		///////////////////////////////////////////////////////////////////////////////////////////
	public:
		Position(std::string =" nullstr", Position* =NULL);	//생성자
		Position();											//생성자
		Position* Parent() const;							//부모 포인터 출력
		bool isRoot() const;								//루트노드인지 확인
		bool isExternal() const;							//leaf노드인지 확인
		bool isInternal() const;							//자식노드가 있는지 확인
		int getChildSize() const;							//자식노드가 몇명인지
		int depth() const;									//현재 깊이가 몇 인지
		string getname() const;								//노드의 이름 출력
	private:
		std::string name;									//노드의 이름
		int dpth;											//깊이: 항상 부모노드의 dpth+1 root일 떈 0	
		Position* parent;									//부모 노드
	};
public:
	friend class tree::Position;
	tree();													//트리 생성자
	int size() const;										//트리의 사이즈 출력
	bool empty() const;										//트리가 비었는지 확인
	Position* Root() const;									//root 출력

	void sameNameCheck(Position*, const string&)const;		//삽입시 같은 이름이 있는지 확인 할 것이다.

	void insertChildOf(Position*,const string&);			//직접 입력해서 추가하는것
	void insertChildOf(Position*, Position*);				//이미 만들어져 있는 포지션 추가
	void insert(Position*, const string& parent, const string& son);   //이름으로 삽입
	
	void DeleteOf(Position*);								//노드 삭제 함수
	void DeleteOf(Position*, const string&);				//이름을 입력받아서 삭제
	void setRoot();											//Root설정 함수: 직접 함수 내에서 입력
	void setRoot(Position*);								//만들어 놓은 노드를 Root로
	void setRoot(const string&);							//string입력시 Root로

	void preorder(Position* ) const;						//전위순회 출력
	void postorder(Position*)const;							//후위순회 출력

	void depth_name(Position*,const string&)const;			//이름 입력시 대손 출력
	int depth(Position*)const;								//int 반환형 대손 출력 함수
	
	

private:
	int sz;													//노드의 수
	Position* root;											//root 노드
};


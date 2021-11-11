#pragma once
#include <iostream>
#include <string>
#include <deque>
using namespace std;

struct Node //노드 구조체
{
	char symbol;	//문자 부호
	int freq;		//부호면 빈도수를 의미
	Node* left;		//left child
	Node* right;	//right child
	Node* parent;	//parent node
	string code;	//부여할 코드
	Node(int frq, char s = ' ', Node* l = NULL, Node* r = NULL, Node* p = NULL)
		:symbol(s), freq(frq), left(l), right(r), parent(p), code("") {}	//Node의 생성자 
	bool isLeft()	//left child 여부 판단
	{
		return parent->left == this;	//부모노드의 left가 자신이면 true
	}
	bool isRight()	//right child 여부 판단
	{
		return !isLeft();				//isLeft()가 false가 나오면 right child란 의미
	}
	void setLeft(Node* l)		//left child 설정 parameter= Node* l
	{
		if (left == NULL)		//left가 없을 때 
			left=l;				//left = l
		else{					//기존의 left가 있다면 
			delete left;		//기존 left를 지우고 
			left = l;			//l을 left로 한다.
		}
	}
	void setRight(Node* r)		//right child 설정 parameter= Node* r
	{
		if (right == NULL)		//right가 없을 때 
			right = r;			//right = r
		else{					//기존의 right가 있다면 
			delete right;		//기존 right를 지우고 
			right = r;			//r를 right로 한다.
		}
	}
	void setCode(string c)		//이진 코드 설정 함수 string c를 parameter로 넣어준다.
	{
		if (parent->code == "")	//부모 노드의 이진 코드가 아무것도 없다면 
			code = c;			//c를 이진 코드로 설정
		else                    //부모의 이진 코드가 있다면 
		code =parent->code + c;	//부모의 이진 코드에 c를 덧붙인다. 
	}
	void setParent(Node* p)		//부모 노드 설정 
	{
		if (parent == NULL)		//예외처리
			parent = p;
		else {
			delete parent;
			parent = p;
		}
	}
	bool isExternal()			//외부 노드인지 판단
	{
		return (left == NULL && right == NULL);	//left child와 right child 모두 NULL 이면 외부 노드
	}
	bool isInternal()			//내부 노드인지 판단
	{
		return !isExternal();					//외부노드가 아니면 true 리턴
	}
	bool hasLeft()				//left child를 갖고 있는지 판단
	{
		return left != NULL;	//left child가 NULL이 아니면 true 리턴
	}
	bool hasRight()				//right child를 갖고 있는지 판단
	{
		return right != NULL;	//right child가 NULL이 아니면 true 리턴
	}
	string Code()				//이진 코드 리턴
	{
		return code;			//code 리턴
	}
};
class PQ						//우선순위 큐 구현
{
	friend class HuffmanEncoder;		//HuffmanEncoder 클래스에서 PQ 클래스에 자유로이 접근할 수 있게 friend 설정을 해주었다.
private:						
	deque<Node*>myq;			//데이터 멤버로 deque 자료구조에 Node*를 넣을 수 있는 myq 선언
public:
	PQ(){}						//생성자
	int size() const			//사이즈 출력
	{
		return myq.size();		//myq의 사이즈 리턴
	}
	bool empty() const			//비었는지 확인
	{
		return size() == 0;		//size가 0이면 true 리턴
	}
	Node* find(char Symbol)		//입력한 문자 부호의 포인터를 리턴
	{
		for (int i = 0; i < myq.size(); i++)	//myq의 size만큼 반복문
		{
			if (myq[i]->symbol == Symbol) return myq[i];	//문자 부호를 찾으면 그 포인터 반환
		}						//for문을 끝내고 나왔다=>해당 문자 부호가 없다는 의미
		return NULL;			//따라서 NULL 리턴
	}
	Node* min()					//맨 앞의 포인터 리턴
	{
		try {if (myq.size() == 0)throw string("빈 큐입니다. min함수 오류");}//예외 처리
		catch (const string& ex)
		{cout << ex << endl; exit(0);}
		return myq.front();		//myq의 front 리턴
	}
	Node* max()					//맨 뒤의 포인터 리턴
	{
		try {if (myq.size() == 0)throw string("빈 큐입니다. max함수 오류");}//예외 처리
		catch (const string& ex){cout << ex << endl; exit(0);}
		return myq.back();		//myq의 back 리턴
	}
	void removeMin()			//최소 원소 삭제 함수
	{
		try { if (myq.size() == 0)throw string("빈 큐입니다. removeMIn함수 오류"); }//예외 처리
		catch (const string& ex){cout << ex << endl; exit(0);}

		Node* temp = myq.front();	//Node* temp에 최소 원소인 myq.front() 할당
		myq.pop_front();		//pop_front=> myq 자료구조에서 min을 빼준다.
		delete temp;			//temp를 delete 해줌으로써 기존의 최소 원소의 동적할당 해제
	}
	void swap(Node* p, Node* q)	//p포인터와 q포인터 swap 함수 
	{
		try { if (p == NULL || q == NULL) throw string("널포인터 swap오류! swap함수 오류"); }//예외 처리
		catch (const string& ex) { cout << ex << endl; exit(0); }
		int tf = p->freq; char ts = p->symbol;							 //스위칭 할때 임시로 값을 저장해둘 변수들 선언
		Node* tl = p->left; Node* tr = p->right; Node* paren = p->parent;//스위칭 할때 임시로 값을 저장해둘 변수들 선언

		if (p->isInternal())	//p가 internal 노드라면 
		{
			if (p->hasLeft()) p->left->parent = q;	//p가 leftchild가 있다면 p->left->parent를 q로 설정해준다.
			if (p->hasRight()) p->right->parent = q;//p가 rightchild가 있다면 p->right->parent를 q로 설정해준다.
		}
		if (q->isInternal())	//q가 internal 노드라면 
		{
			if (q->hasLeft())q->left->parent = p;	//q가 leftchild가 있다면 q->left->parent를 p로 설정해준다.
			if (q->hasRight())q->right->parent = p;	//q가 leftchild가 있다면 q->right->parent를 p로 설정해준다.
		}
													//즉 자식노드들의 부모노드까지 같이 스위칭 해주는 작업
		p->freq = q->freq;		//p의 빈도수= q의 빈도수
		p->symbol = q->symbol;	//p의 문자 부호= q의 문자 부호

		p->right = q->right;	//p의 right 노드 = q의 right
		p->left = q->left;		//p의 left 노드 = q의 left
		p->parent = q->parent;	//p의 parent 노드 = q의 parent

		q->freq = tf;			//q의 빈도수는 기존 p의 빈도수
		q->symbol = ts;			//q의 문자 부호는 기존 p의 문자 부호
		q->left = tl;			//q의 left 노드 = 기존 p의 left 
		q->right = tr;			//q의 right 노드= 기존 p의 right 
		q->parent = paren;		//q의 parent 노드= 기존 p의 parent
	}
	void sort()					//정렬 함수
	{
		for (int i = 0; i < myq.size(); i++)	//myq의 사이즈 만큼 반복
		{
			if (i == myq.size() - 1) break;		//즉 마지막 원소까지 정렬의 상태가 이상이 없을 때 break
			if (myq[i]->freq > myq[i + 1]->freq)	//앞선 노드의 빈도수가 뒤의 빈도수 보다 클 때 즉 순서가 맞지 않을 때 
			{
				swap(myq[i], myq[i + 1]);		//myq[i]와 myq[i+1]노드들을 swap 함수를 이용하여 swap 해준다. 
			}
		}
	}
	void insert(char Symbol)	//문자 부호 삽입 함수 =>삽입과 동시에 정렬을 실행해준다. 
	{							//기존에 있는 문자 부호의 경우 빈도수만 증가시켜준다.
		if (Symbol == 32) return;	//공백 (띄어쓰기)의 경우 건너 뛴다.
		if (find(Symbol) == NULL)//입력한 문자 부호가 없는 경우 => 위에서 정의한 find(Node* p)함수를 사용 하였다.
		{
			Node* newNode = new Node(1, Symbol);	//Node* 인 newNode를 동적할당 하여 
			myq.push_front(newNode);				//myq에 '앞'으로 넣어준다. 빈도수가 1이라 최소원소와 같은 의미이므로 앞으로 넣어준다.
		}
		else{					//입력받은 문자 부호가 기존 PQ에 있을 때 
			for (int i = 0; i < myq.size(); i++)	//반복문 실행 
			{
				if (myq[i]->symbol == Symbol)		//i번째 myq의 문자 부호가 입력받은 Symbol이면 
				{
					if (i == myq.size() - 1)		//마지막 노드인데 같을 때 
					{
						myq[i]->freq++;				//해당 문자 부호를 갖는 노드의 빈도수만 1 증가
					}
					else if (myq[i]->freq == myq[i + 1]->freq)	//문자 부호가 i번째의 노드와 같은데
					{											//i번째 노드의 빈도수와 i+1번째 노드의 빈도수와 같으면 
						myq[i]->freq++;							//빈도수 증가 이후에 빈도수에 대한 순서가 바뀌어야 하므로 
						sort();									//정렬 함수인 sort()함수 실행 
						break;									//빈도수 증가, 정렬 이후에 break
					}
					else if (myq[i]->freq < myq[i + 1]->freq)	//i번째 노드의 빈도수가 i+1번째 노드의 빈도수 보다 작으면 
					{											//i번째 노드의 빈도수를 1 증가시켜도 i+1번째 노드의 빈도수 보다 커지지 않으므로 
						myq[i]->freq++;							//i번째 노드의 빈도수 1 증가
						break;									//이후 break
					}
				}
				else continue;
			}
		}
	}
	void remove(Node* p)			//p 포인터 삭제 함수
	{
		try{if (p == NULL)throw string("없는 노드입니다. remove함수 오류!");}//예외 처리
		catch (const string& ex){cout << ex << endl; exit(0);}
		deque<Node*> ::iterator it;	//erase를 위한 이터레이터 선언
		it = myq.begin();			//it에 myq.begin
		for (int i = 0; i < myq.size(); i++)	//반복
		{
			if (myq[i] == p && i == myq.size() - 1)	//myq[i]가 마지막 노드일 떄 
			{
				delete myq[i];		//노드를 delete 하고 
				myq.pop_back();		//pop 해준다.
			}
			else if (myq[i] == p)	//myq[i]가 p이면 
			{
				delete myq[i];		//노드를 delete 하고 
				myq.erase(it + i, it + i + 1); break;	//erase함수로 그 노드가 있던 자리만 지워준다.
			}
		}
		cout << "없는 노드입니다." << endl;	//해당하는 노드가 없을 때 
	}
	int Freq(char Symbol)			//입력받은 문자 부호에 대한 빈도수 출력 함수 
	{
		try { if (find(Symbol) == NULL) throw string("없는 노드입니다. Freq함수 오류"); } //예외 처리
		catch (const string& ex) { cout << ex << endl; exit(0); }

		return find(Symbol)->freq;	//find()함수로 해당 Symbol의 
	}
	int Freq(Node* p)				//입력 받은 p포인터의 빈도수 출력 함수 
	{
		try { if (p == NULL) throw string("없는 노드입니다. Freq함수 오류"); }	//예외 처리
		catch (const string& ex) { cout << ex << endl; exit(0); }

		return p->freq;				//p의 빈도수 리턴
	}
	void print()					//출력 함수 
	{
		for (int i = 0; i < myq.size(); i++)	//맨 앞에서 부터 출력
		{
			cout << myq[i]->symbol << "의 빈도수: " << myq[i]->freq  << endl;
		}
	}
};

class HuffmanEncoder{				//허프만 알고리즘을 수행할 트리 및 함수 클래스 
private:							//데이터 멤버 
	PQ pq;							//PQ의 객체 pq
	Node* Root;						//루트 노드
	deque<Node*> strList;			//인코딩 후 부호별 이진 코드 분류할 자료구조
public:
	HuffmanEncoder(PQ prioQ)		//생성자 ->우선순우 큐 prioQ를 받아서 이를 인코딩 한다.
	{
		pq = prioQ;					//데이터 멤버 pq=prioQ
		while (pq.size() > 1)		//pq의 크기가 1이 될때 까지 즉 큐에 노드 하나만 남을 때 까지 반복
		{
			Node* tl = pq.min(); pq.myq.pop_front();	//새롭게 선언한 Node* tl= pq의 min, pq의 최소 원소를 pop해준다.
			Node* tr = pq.min(); pq.myq.pop_front();	//새롭게 선언한 Node* tr= pq의 min, pq의 (가장 처음의 pq와 비교했을 때 )두번 째 최소 원소를 pop해준다.
			Node* r = new Node(tl->freq + tr->freq, ' ', tl, tr);	//새롭게 r 노드를 선언, r의 빈도수는 tl과 tr의 빈도수의 합이다. tl과 tr은 각 r의 left, right로 들어간다.
			tl->setParent(r); tr->setParent(r);			//tl의 부모노드 =r, tr의 부모노드 = r
			pq.myq.push_front(r);						//r 노드를 우선순위 큐에 삽입한다.
			pq.sort();									//이후 큐를 정렬해준다. r노드는 r이 루트 노드인 트리의 노드이다.
		}
		Root = pq.myq.front();		//Root는 myq의 맨 앞
		preorderEncoding(Root);		//인코딩 실행 함수
		putList(Root);				//데이터 멤버 strList에 트리의 문자 부호들과 빈도수, 이진코드를 저장한 노드를 삽입해주는 함수
	}
	void preorderEncoding(Node* p)	//입력받은 노드를 루트로 하는 트리(서브 트리)에 이진코드를 부여하는 함수
	{
		try { if (p == NULL)throw string("없는 노드입니다. preEncoding함수 오류!"); }//예외 처리
		catch (const string& ex) { cout << ex << endl; exit(0); }
		if (p != Root)				//p가 루트노드가 아니면 
		{
			if (p->isLeft())		//왼쪽이면 0 부여
			{
				p->code = p->parent->code + "0";	//left child의 경우 부모 노드의 이진코드에 0을 추가하면 된다.
			}
			else if (p->isRight())	//오른쪽이면 1 부여
			{
				p->code = p->parent->code + "1";	//right child의 경우 부모 노드의 이진코드에 1을 추가하면 된다.
			}
		}
		if (p->isInternal())		//p에 자식노드가 있으면 
		{
			preorderEncoding(p->left);	//재귀적으로 left child를 preorderEncoding() 함수에 넣고 실행한다.
			preorderEncoding(p->right);	//재귀적으로 right child를 preorderEncoding() 함수에 넣고 실행한다.
		}
	}
	void putList(Node* p)			//p 노드 포인터를 다시 데크에 넣는다.
	{
		try { if (p == NULL)throw string("없는 노드입니다. putList함수 오류!"); }//예외 처리
		catch (const string& ex) { cout << ex << endl; exit(0); }
		if (p->isExternal())		//p가 외부 노드라면 
			strList.push_back(p);	//삽입 순서대로 맨 앞에 위치한다.
		else if (p->isInternal())	//p에 자식노드가 있으면 
		{
			putList(p->left);		//재귀적으로 left child를 putList() 함수에 넣고 실행한다.
			putList(p->right);		//재귀적으로 right child를 putList() 함수에 넣고 실행한다.
		}
	}
	string FindCode(char Symbol)	//입력한 문자에 대한 이진 코드 출력
	{
		for (int i = 0; i < strList.size(); i++)	//strList의 사이즈 만큼 반복
		{
			if (strList[i]->symbol == Symbol) return strList[i]->code;	
		}											//해당 문자 부호를 찾으면 그 문자 부호에 대한 이진 코드 리턴 
		cout << "해당 문자부호를 찾지 못했습니다." << endl; exit(0);
	}
	void Conclusion(char sen[])		//입력 받은 문장을 이진 코드로 출력하는 함수
	{
		for (int i = 0; i < strlen(sen); i++)	//입력 받은 문장의 길이 만큼 반복
		{
			if (sen[i] == 32)continue;			//입력 받은 문장의 char 데이터가 공백 (띄어쓰기)이면 넘어간다.

			cout<<FindCode(sen[i])<<" ";		//FindCode에 sen[i]를 넣어줌으로써 해당 문자에 대한 이진 코드를 출력한다.
		}
	}
	Node* root()					//루트노드 출력
	{
		return Root;				//루트노드 출력
	}
	void setRoot(Node* p)			//루트노드 설정
	{
		Root = p;					//루트노드 = p
	}
	void preorder(Node* p)			//전위 순회로 출력
	{
		if (p->isExternal())		//외부 노드이면 
			cout << p->symbol << " 의 빈도수: " << p->freq << ", 인코딩 결과: " << p->code << endl;
		else if (p->isInternal())	//내부 노드이면 ->문자 부호가 정의되지 않은 노드 이므로 자식 노드들로 넘어간다.
		{
			preorder(p->left);		//재귀적으로 left child에 대해서도 preorder()실행
			preorder(p->right);		//재귀적으로 right child에 대해서도 preorder()실행
		}
	}
	~HuffmanEncoder()//소멸자
	{
		DeleteNode(Root); 
	}
	void DeleteNode(Node* p)//후위순회 순서로 작동하는 동적할당 해제 함수
	{
		if (p->isInternal())//자식노드가 있다면 
		{
			if (p->hasLeft())
			{DeleteNode(p->left); }//재귀적으로 left child에서 부터 삭제
			else if (p->hasRight())
			{DeleteNode(p->right); }//재귀적으로 right child 삭제
		}
		else//자식노드가 없다면 
		{
			if (p->isLeft())
			{
				p->parent->left = NULL;
				delete p;
			}
			else if (p->isRight())
			{
				p->parent->right = NULL;
				delete p;
			}
		}
	}
	int size()
	{	return pq.myq.size();}
};
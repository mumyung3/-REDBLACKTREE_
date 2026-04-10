#include "RedBlackTree.h"
#include "stdio.h"
stNODE::stNODE(int value) : iData(value) {
	Color = NODE_COLOR::RED;
}

RedBlackTree::RedBlackTree(): root(NIL) {
	NIL->pLeft = NIL;
	NIL->pParent = NIL;
	NIL->pRight = NIL;
	NIL->Color = BLACK;
}

void RedBlackTree::Insert(const int& value) {
	
	stNODE* newNode = CreateNodeWithNIL(value);

	if (root == NIL) {
		newNode->Color = BLACK;
		root = newNode;

		return;
	}

	stNODE* current = root;
	while (true) {
		if (value < current->iData) {
			if (current->pLeft == NIL) {
				current->pLeft = newNode;
				newNode->pParent = current;
				InsertFix(newNode);

				return;
			}
			current = current->pLeft;
		}
		else {
			if (current->pRight == NIL) {
				current->pRight = newNode;
				newNode->pParent = current;
				InsertFix(newNode);

				return;
			}
			current = current->pRight;
		}
	}




}
bool RedBlackTree::Find(const int& value) {
	stNODE* current = root;

	while (current != NIL) {
		if (current->iData == value) {
			return true;
		}
		if (current->iData > value) {
			if (current->pLeft == NIL) {
				return false;
			}
			current = current->pLeft;
		}
		else {
			if (current->pRight == NIL) {
				return false;
			}
			current = current->pRight;
		}
	}

	return false;
}

void RedBlackTree::inorder_check(stNODE* node)
{
	if (node == NIL)	return;
	// 전위
	inorder_check(node->pLeft);
	// 중위
	wprintf(L"%d -", node->iData);
	inorder_check(node->pRight);

	// 후위
}

stNODE* RedBlackTree::CreateNodeWithNIL(const int& value)
{
	stNODE* newNode = new stNODE(value);
	newNode->pLeft = NIL;
	newNode->pRight = NIL;
	newNode->pParent = NIL;
	return newNode;
}

void RedBlackTree::RotateRight(stNODE* node)
{
	// C.pParent  = N
	stNODE* C = node->pLeft->pRight;
	// A.pRight = N
	stNODE* A = node->pLeft;
	// N.pParent = A
	stNODE* N = node;
	// N.pLeft =C

	// root 가 바뀔시 A가 루트
	if (root == N) {
		root = A;
	}
	else if(N->pParent->pLeft == N){
		N->pParent->pLeft = A;
	}
	else {
		N->pParent->pRight = A;

	}

	//A.pParent = N.pParent
	A->pParent = N->pParent;

	C->pParent = N;
	A->pRight = N;
	N->pParent = A;
	N->pLeft = C;
	
	
}

void RedBlackTree::RotateLeft(stNODE* node)
{

	stNODE* N = node;
	stNODE* D = node->pRight;
	stNODE* E = node->pRight->pLeft;
	

	if (root == N) {
		root = D;
	}
	else if (N->pParent->pLeft == N) {
		N->pParent->pLeft = D;
	}
	else {
		N->pParent->pRight = D;

	}

	//D.pParent = N.pParent
	D->pParent = N->pParent;

	//D.pLeft = N
	D->pLeft = N;
	//E.pParent = N
	E->pParent = N;
	//N.pParent = D
	N->pParent = D;
	//N.pRight = E
	N->pRight = E;


}
// 새로 추가된 노드는 끝단 노드
void RedBlackTree::InsertFix(stNODE* node)
{
	// 부모가 블랙이면 문제 x
	
	// 부모
	stNODE* parent = node->pParent;
	// 할아버지
	stNODE* GrandParent = parent->pParent;
	if (parent->Color != RED) {
		return;
	}
	// 할아버지 노드가 NIL이면 루트까지온 거같음.
	if (GrandParent == NIL) {
		// 부모와 내가 red이면 부모는 루트일테니 부모만 블랙으로 바꾼다.
		if (parent->Color == RED && node->Color == RED) {
			parent->Color = BLACK;
		}
		return;
	}


	stNODE* uncle{};
	// 삼촌 (부모가 할아버지의 왼쪽인지 오른쪽인지 구분)	
	if (GrandParent->pLeft == parent) {
		uncle = GrandParent->pRight;
	}
	else {
		uncle = GrandParent->pLeft;
	}

	// 문제가 되기 시작한 시점 부모가 레드 일때 위반
	if (parent->Color != RED) return;

	// 1. 부모 레드, 삼촌도 레드 case.1
	if (parent->Color == RED && uncle->Color == RED) {

		parent->Color = BLACK;
		uncle->Color = BLACK;
		GrandParent->Color = RED;
		//  할아버지 상단 다시 확인
		InsertFix(GrandParent);
		return;
	}
	


	// 2. 부모 레드, 삼촌 블랙, 나는 부모의 오른쪽 레드 case.2
	if (parent->pRight == node) {
		if (GrandParent->pRight == uncle) {
			RotateLeft(parent);
			node = parent;
			parent = node->pParent;
		}
	}
	else{
		if (GrandParent->pLeft == uncle) {
			RotateRight(parent);
			node = parent;
			parent = node->pParent;
		}
	}

	//case.3
	parent->Color = BLACK;
	GrandParent->Color = RED;
	if (GrandParent->pRight == parent) {
		RotateLeft(GrandParent);
	}
	else {
		RotateRight(GrandParent);
	}
	
	return;


}

void RedBlackTree::Validate(stNODE* node, int& prev)
{
	if (node == NIL) return;
	Validate(node->pLeft, prev);

	// 1. 오름차순 확인
	if (prev != -1 && node->iData < prev)
		wprintf(L"[오류] 정렬 위반: %d <= %d\n", node->iData, prev);
	prev = node->iData;

	// 2. RED-RED 위반 확인
	if (node->Color == RED && node->pParent->Color == RED)
		wprintf(L"[오류] RED-RED 위반: %d\n", node->iData);

	Validate(node->pRight, prev);
}
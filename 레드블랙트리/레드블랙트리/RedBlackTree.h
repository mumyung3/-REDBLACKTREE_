#pragma once


enum NODE_COLOR {
	BLACK = 0,
	RED
};

struct stNODE {
	stNODE* pParent{};
	stNODE* pLeft{};
	stNODE* pRight{};

	NODE_COLOR Color{};

	int iData; // key, value
	stNODE(int value);
};

class RedBlackTree
{
private:
public:
	//전역 닐노드
	inline static stNODE* NIL = new stNODE(0);
	stNODE* root{};
public:
	RedBlackTree();

	void Insert(const int& value);

	bool Find(const int& value);

	void inorder_check(stNODE* node);

	stNODE* CreateNodeWithNIL(const int& value);

	// 우회전
	void RotateRight(stNODE* node);
	// 좌회전
	void RotateLeft(stNODE* node);
	// 레드 블랙 트리 규칙

	void InsertFix(stNODE* node);
	// ai 검증
	void Validate(stNODE* node, int& prev);
};


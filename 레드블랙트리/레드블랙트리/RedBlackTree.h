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
	//Àü¿ª ´Ò³ëµå
	inline static stNODE* NIL = new stNODE(0);
	stNODE* root{};
public:
	RedBlackTree();

	void Insert(const int& value);

	bool Find(const int& value);

	void inorder_check(stNODE* node);

	stNODE* CreateNodeWithNIL(const int& value);
};


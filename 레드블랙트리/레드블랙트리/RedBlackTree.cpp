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
				return;
			}
			current = current->pLeft;
		}
		else {
			if (current->pRight == NIL) {
				current->pRight = newNode;
				newNode->pParent = current;
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

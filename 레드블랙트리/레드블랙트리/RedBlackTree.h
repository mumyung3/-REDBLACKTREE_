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
	stNODE(int value) : iData(value) {
		Color = NODE_COLOR::RED;
	}

};

class RedBlackTree
{
private:
	stNODE* root{};
public:
	RedBlackTree() :root(nullptr) {}

	void Insert(const int& value) {
		stNODE* newNode = new stNODE(value);

		if (!root) {
			newNode->Color = BLACK;
			root = newNode;

			return;
		}

		stNODE* current = root;
		while (true) {
			if (value < current->iData) {
				if (!current->pLeft) {
					current->pLeft = newNode;
					newNode->pParent = current;
					return;
				}
				current = current->pLeft;
			}
			else {
				if (!current->pRight) {
					current->pRight = newNode;
					newNode->pParent = current;
					return;
				}
				current = current->pRight;
			}
		}
	}

	bool Find(const int& value) {
		stNODE* current = root;

		while (current) {
			if (current->iData == value) {
				return true;
			}
			if (current->iData > value) {
				if (!current->pLeft) {
					return false;
				}
				current = current->pLeft;
			}
			else {
				if (!current->pRight) {
					return false;
				}
				current = current->pRight;
			}
		}

		return false;
	}
};


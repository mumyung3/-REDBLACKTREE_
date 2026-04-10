#include <iostream>
#include "RedBlackTree.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
int arr[1000]{};
int idx = 0;
void inorder_check(stNODE* node);
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	srand((unsigned)time(nullptr));
	RedBlackTree tree;

	// bst 검증 테스트
	/*/
	int count = 0;
	while (count < 1000) {
		int val = rand() % 10000 + 1;
		tree.Insert(val);
		arr[count] = val;
		count++;
	}
	
	std::sort(arr, arr+1000);

	inorder_check(tree.root);
	wprintf(L" 통과 \n");
	//*/





	return 0;
}

void inorder_check(stNODE* node) {

	if (node == RedBlackTree::NIL)	return;
	// 전위
	inorder_check(node->pLeft);

	if (node->iData != arr[idx]) {
		wprintf(L" 틀림! BST: %d, 배열 : %d \n", node->iData, arr[idx]);
		__debugbreak();
	}
	idx++;

	inorder_check(node->pRight);

}
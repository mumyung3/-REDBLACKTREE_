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

	// 회전 테스트
	/*/
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);

	// 회전 전 inorder
	wprintf(L"회전 전: ");
	tree.inorder_check(tree.root);  // root 접근용 getter 필요

	// 강제 회전
	tree.RotateLeft(tree.root);

	// 회전 후 inorder
	wprintf(L"\n회전 후: ");
	tree.inorder_check(tree.root);
	//*/

	//*/
	for (int i = 0; i < 1000; i++)
		tree.Insert(rand() % 10000);

	int prev = -1;
	tree.Validate(tree.root, prev);
	wprintf(L"검증 완료\n");
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
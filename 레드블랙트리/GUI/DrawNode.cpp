#include "DrawNode.h"
void DrawNode::DrawingNode(HDC hdc, stNODE* node, int x, int y, int hGap)
{
	if (!node || node == RedBlackTree::NIL) return;

	SelectObject(hdc, g_hLinePen);
	// 자식으로 선 그리기
	if (node->pLeft != RedBlackTree::NIL) {
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x - hGap, y + 80);
		DrawingNode(hdc, node->pLeft, x - hGap, y + 80, hGap / 2);
	}
	if (node->pRight != RedBlackTree::NIL) {
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + hGap, y + 80);
		DrawingNode(hdc, node->pRight, x + hGap, y + 80, hGap / 2);
	}

	// 현재 노드 그리기
	SelectObject(hdc, node->Color == RED ? g_hRedBrush : g_hBlackBrush);
	Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);


	// 반투명 텍스트 배경
	SetTextColor(hdc, node->Color == RED ? RGB(0, 0, 0) :
		RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	// 해당 값 텍스트로 출력
	SelectObject(hdc, g_Font);

	wchar_t buf[32]{};
	swprintf_s(buf, L"%d", node->iData);

	// 텍스트 중앙 정렬
	SIZE textSize;
	GetTextExtentPoint32W(hdc, buf, wcslen(buf), &textSize);
	TextOutW(hdc, x - textSize.cx / 2, y - textSize.cy / 2, buf, wcslen(buf));


}

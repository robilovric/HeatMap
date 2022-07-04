
// HeatMapView.cpp : implementation of the CHeatMapView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HeatMap.h"
#endif

#include "HeatMapDoc.h"
#include "HeatMapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHeatMapView

IMPLEMENT_DYNCREATE(CHeatMapView, CView)

BEGIN_MESSAGE_MAP(CHeatMapView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CHeatMapView construction/destruction

CHeatMapView::CHeatMapView() noexcept
{
	// TODO: add construction code here
}

CHeatMapView::~CHeatMapView()
{
}


BOOL CHeatMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHeatMapView drawing

void CHeatMapView::InitializeCells()
{
	int numRows = GetRows();
	int numColumns = GetColumns();
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numColumns; ++j) {
			_matrixRow.push_back(0);
		}
		_cellColorMatrix.push_back(_matrixRow);
		_matrixRow.clear();
		_matrixRow.shrink_to_fit();
	}
}

void CHeatMapView::UpdateCellColor(int row, int col)
{
	_cellColorMatrix[row][col] += 1;
}


int CHeatMapView::GetRows()
{
	return rows;
}

int CHeatMapView::GetColumns()
{
	return columns;
}

COLORREF CHeatMapView::GetCellColor(int row, int col)
{
	switch (_cellColorMatrix[row][col])
	{
	case 0:
		return RGB(0, 0, 255); // za debug svrhe sam maka iz bijele boje 
	case 1:
		return RGB(51, 255, 153); //prozirno zelena
	case 2:
		return RGB(0, 255, 0); //zelena
	case 3:
		return RGB(255, 51, 153); //roskasta
	case 4:
		return RGB(255, 0, 0); // crvena
	default:
		break; //proširit ću spektar poslje
	}
	return RGB(0, 0, 0);
}

CRect CHeatMapView::CreateRect(int left, int top)
{
	return { left, top, left + _cellSize.x, top + _cellSize.y };
}

void CHeatMapView::OnInitialUpdate()
{
	InitializeCells();
}

void CHeatMapView::SetCellSize()
{
	//GetClientRect(&rect);
	int X = GetSystemMetrics(SM_CXSCREEN);
	int Y = GetSystemMetrics(SM_CYSCREEN);
	_cellSize.y = Y / rows;
	_cellSize.x = X / columns;
}

void CHeatMapView::OnDraw(CDC* pDC)
{
	CHeatMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int numRows = GetRows();
	int numColumns = GetColumns();

	SetCellSize();
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numColumns; ++j) {
			CBrush brush;
			brush.CreateSolidBrush(GetCellColor(i, j));
			pDC->FillRect(CreateRect(j * _cellSize.x, i * _cellSize.y), &brush);
		}
	}

}

void CHeatMapView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHeatMapView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHeatMapView diagnostics

#ifdef _DEBUG
void CHeatMapView::AssertValid() const
{
	CView::AssertValid();
}

void CHeatMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHeatMapDoc* CHeatMapView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHeatMapDoc)));
	return (CHeatMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CHeatMapView message handlers


void CHeatMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonDown(nFlags, point);
	int row = point.y / _cellSize.y;
	int col = point.x / _cellSize.x;
	UpdateCellColor(row, col);
	InvalidateRect(CreateRect(col * _cellSize.x, row * _cellSize.y));

}


void CHeatMapView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	Invalidate();


}

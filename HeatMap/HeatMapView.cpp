
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
#include "CMatrixDlg.h"
#include "CModeDlg.h"

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
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TOOLS_MATRIX, &CHeatMapView::OnToolsMatrix)
	ON_COMMAND(ID_TOOLS_MODE, &CHeatMapView::OnToolsMode)
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
	GetDocument()->_lastCell.x = -1;
	GetDocument()->_lastCell.y = -1;
	int numRows = GetRows();
	int numColumns = GetColumns();
	GetDocument()->_cellColorMatrix.clear(); //necessary when we call fuction from Matrix dialog handler
	GetDocument()->_cellColorMatrix.resize(numRows, std::vector<UINT>(numColumns, 0));
}

void CHeatMapView::UpdateCellColor(int row, int col)
{
	GetDocument()->_cellColorMatrix[row][col] += 1;
}


int CHeatMapView::GetRows()
{
	return GetDocument()->_rows;
}

int CHeatMapView::GetColumns()
{
	return GetDocument()->_columns;
}

COLORREF CHeatMapView::GetCellColor(int row, int col)
{
	switch (GetDocument()->_cellColorMatrix[row][col])
	{
	case 0:
		return RGB(255, 255, 255); // za debug svrhe sam maka iz bijele boje 
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
	return { left, top, left + GetDocument()->_cellSize.x, top + GetDocument()->_cellSize.y };
}

void CHeatMapView::OnInitialUpdate()
{
	InitializeCells();
}

void CHeatMapView::SetCellSize(int width, int height)
{
	GetDocument()->_cellSize.x = width / GetDocument()->_columns;
	GetDocument()->_cellSize.y = height / GetDocument()->_rows;
}

void CHeatMapView::AdjustMatrix(int row, int col)
{
	std::vector<std::vector<unsigned int>> _cellColorMatrixTemp;
	if (row >= GetDocument()->_rows && col >= GetDocument()->_columns)
	{
		_cellColorMatrixTemp.resize(row+1, std::vector<UINT>(col+1, 0));
	}
	else if (row >= GetDocument()->_rows && col < GetDocument()->_columns) {
		_cellColorMatrixTemp.resize(row + 1, std::vector<UINT>(GetDocument()->_columns, 0));
	}
	else {
		_cellColorMatrixTemp.resize(GetDocument()->_rows, std::vector<UINT>(col+1, 0));
	}
	for (int i = 0; i < GetDocument()->_rows; ++i) {
		for (int j = 0; j < GetDocument()->_columns; ++j) {
			_cellColorMatrixTemp[i][j] = GetDocument()->_cellColorMatrix[i][j];
		}
	}

	GetDocument()->_cellColorMatrix.swap(_cellColorMatrixTemp);
	_cellColorMatrixTemp.clear();
	_cellColorMatrixTemp.shrink_to_fit();
	AdjustRowsAndColumns(row, col);
}

void CHeatMapView::AdjustRowsAndColumns(int row, int col)
{
	if (row >= GetDocument()->_rows && col >= GetDocument()->_columns) {
		GetDocument()->_rows += ++row - GetDocument()->_rows;
		GetDocument()->_columns += ++col - GetDocument()->_columns;
	}
	else if (row >= GetDocument()->_rows && col < GetDocument()->_columns) {
		GetDocument()->_rows += ++row - GetDocument()->_rows;
	}
	else
	{
		GetDocument()->_columns += ++col - GetDocument()->_columns;
	}
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

	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numColumns; ++j) {
			CBrush brush;
			brush.CreateSolidBrush(GetCellColor(i, j));
			pDC->FillRect(CreateRect(j * GetDocument()->_cellSize.x, i * GetDocument()->_cellSize.y), &brush);
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
	int row = point.y / GetDocument()->_cellSize.y;
	int col = point.x / GetDocument()->_cellSize.x;
	if (row >= GetDocument()->_rows || col >= GetDocument()->_columns) {
		AdjustMatrix(row, col);
		UpdateCellColor(row, col);
		InvalidateRect(CreateRect(col * GetDocument()->_cellSize.x, row * GetDocument()->_cellSize.y));
		Invalidate();
		return;
	}
	UpdateCellColor(row, col);
	InvalidateRect(CreateRect(col * GetDocument()->_cellSize.x, row * GetDocument()->_cellSize.y));

	CView::OnLButtonDown(nFlags, point); //dali je ovo potrebno?
}


void CHeatMapView::OnSize(UINT nType, int cx, int cy)
{
	// TODO: Add your message handler code here
	switch (nType)
	{
	case SIZE_MAXIMIZED:
		SetCellSize(cx, cy);
		Invalidate();
		break;
	case SIZE_RESTORED:
		SetCellSize(cx, cy);
		Invalidate();
		break;
	default:
		break;
	}

	CView::OnSize(nType, cx, cy);

}


void CHeatMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int row = point.y / GetDocument()->_cellSize.y;
	int col = point.x / GetDocument()->_cellSize.x;
	if (row >= GetDocument()->_rows || col >= GetDocument()->_columns) {
		AdjustMatrix(row, col);
		UpdateCellColor(row, col);
		InvalidateRect(CreateRect(col * GetDocument()->_cellSize.x, row * GetDocument()->_cellSize.y));
		return;
	}
	if (row != GetDocument()->_lastCell.x || col != GetDocument()->_lastCell.y) {
		GetDocument()->_lastCell.x = row; GetDocument()->_lastCell.y = col;
		UpdateCellColor(row, col);
		InvalidateRect(CreateRect(col * GetDocument()->_cellSize.x, row * GetDocument()->_cellSize.y));
	}

	CView::OnMouseMove(nFlags, point); //i ovo takodjer? jer to bude po defaultu izgenerirano kad dodam handler
}

void CHeatMapView::OnToolsMatrix()
{
	// TODO: Add your command handler code here
	CMatrixDlg dlg;
	dlg.m_Rows = GetDocument()->_rows;
	dlg.m_Columns = GetDocument()->_columns;
	if (dlg.DoModal() == IDOK) {
		GetDocument()->_rows = dlg.m_Rows;
		GetDocument()->_columns = dlg.m_Columns;
		InitializeCells();
		GetClientRect(GetDocument()->rect);
		SetCellSize(GetDocument()->rect.right, GetDocument()->rect.bottom);
		Invalidate();
	}

}


void CHeatMapView::OnToolsMode()
{
	// TODO: Add your command handler code here
	CModeDlg dlg;
	dlg.DoModal();
}

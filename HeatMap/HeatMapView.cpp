
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
END_MESSAGE_MAP()

// CHeatMapView construction/destruction

CHeatMapView::CHeatMapView() noexcept
{
	// TODO: add construction code here
	SetRows();     //dali je primjereno ove funkcije pozivati ovdje u konstruktoru view-a 
	SetColumns();  // builda se program no cim se digne prozor bude runtime error koji se žali da pada assert u afxwin2.inl linija 86 nešto sam zbrlja s window-om ocito
	InitializeCells(); //i nesvida mi se što je rect.bottom inicijalno 0 gdje bi bilo zgodno primjeniti SetViewportExtEx() mozda odmah u konstrukoru ovjde takoder?
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
	for (int i = 0; i < GetRows(); ++i) {
		for (int j = 0; j < GetColumns(); ++j) {
			_cellColorMatrix.push_back(_rgb);
		}
	}
}

void CHeatMapView::UpdateCellColor(int idCell)
{
	_cellColorMatrix[idCell][0] = _rgb[0] - 20;

}

void CHeatMapView::SetRows()
{
	GetClientRect(&rect);
	rows = rect.bottom / _cellSize;
}

void CHeatMapView::SetColumns()
{
	GetClientRect(&rect);
	columns = rect.right / _cellSize;
}

int CHeatMapView::GetRows()
{
	return rows;
}

int CHeatMapView::GetColumns()
{
	return columns;
}

COLORREF CHeatMapView::GetCellColor(int idCell)
{
	return RGB(_cellColorMatrix[idCell][0], _cellColorMatrix[idCell][1], _cellColorMatrix[idCell][2]);
}

CRect CHeatMapView::CreateRect(int left, int top)
{
	return { left, top, left + _cellSize, top + _cellSize };
}

void CHeatMapView::OnDraw(CDC* pDC)
{
	CHeatMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	GetClientRect(&rect);
	SetRows(); SetColumns();

	for (int i = 0; i < GetRows(); ++i) {
		for (int j = 0; j < GetColumns(); ++j) {
			int cellID = i * columns + j;
			brush.CreateSolidBrush(GetCellColor(cellID));
			pDC->FillRect(CreateRect(j * _cellSize, i * _cellSize), &brush);
		}
	}
	DeleteObject(brush);
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

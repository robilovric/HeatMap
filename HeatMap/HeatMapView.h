
// HeatMapView.h : interface of the CHeatMapView class
//

#pragma once 
#include<vector>


class CHeatMapView : public CView
{
protected: // create from serialization only
	CHeatMapView() noexcept;
	DECLARE_DYNCREATE(CHeatMapView)

// Attributes
public:
	CHeatMapDoc* GetDocument() const;
	CRect rect;
//custom members and functions 
private:
	std::vector<std::vector<unsigned int>> _cellColorMatrix;
	std::vector<unsigned int> _matrixRow;
	POINT _cellSize;
	POINT _lastCell;
	int rows = 60;
	int columns = 120;
public:
	void InitializeCells();
	void UpdateCellColor(int row, int col);
	int GetRows();
	int GetColumns();
	COLORREF GetCellColor(int row, int col);
	CRect CreateRect(int left, int top);
	void OnInitialUpdate() override;
	void SetCellSize(int width, int height);
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CHeatMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnToolsMatrix();
};

#ifndef _DEBUG  // debug version in HeatMapView.cpp
inline CHeatMapDoc* CHeatMapView::GetDocument() const
   { return reinterpret_cast<CHeatMapDoc*>(m_pDocument); }
#endif


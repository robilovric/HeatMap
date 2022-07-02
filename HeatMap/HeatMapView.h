
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
	std::vector<std::vector<unsigned int>> _cellColorMatrixLog;
	std::vector<unsigned int> _matrixRow;
	int _cellSize = 100;
	int rows;
	int columns;
	bool isResize;
	bool isInitialOnSize = true;
public:
	void InitializeCells();
	void UpdateCellColor(int row, int col);
	void SetColumns();;
	void SetRows();
	int GetRows();
	int GetColumns();
	COLORREF GetCellColor(int row, int col);
	CRect CreateRect(int left, int top);
	void OnInitialUpdate() override;
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
};

#ifndef _DEBUG  // debug version in HeatMapView.cpp
inline CHeatMapDoc* CHeatMapView::GetDocument() const
   { return reinterpret_cast<CHeatMapDoc*>(m_pDocument); }
#endif


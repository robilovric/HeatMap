
// HeatMapView.h : interface of the CHeatMapView class
//

#pragma once


class CHeatMapView : public CView
{
protected: // create from serialization only
	CHeatMapView() noexcept;
	DECLARE_DYNCREATE(CHeatMapView)

// Attributes
public:
	CHeatMapDoc* GetDocument() const;

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
};

#ifndef _DEBUG  // debug version in HeatMapView.cpp
inline CHeatMapDoc* CHeatMapView::GetDocument() const
   { return reinterpret_cast<CHeatMapDoc*>(m_pDocument); }
#endif


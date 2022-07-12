
// HeatMapDoc.h : interface of the CHeatMapDoc class
//


#pragma once
#include<vector>

class CHeatMapDoc : public CDocument
{
protected: // create from serialization only
	CHeatMapDoc() noexcept;
	DECLARE_DYNCREATE(CHeatMapDoc)

// Attributes
public:
	CRect rect;
	std::vector<std::vector<UINT>> _cellColorMatrix;
	POINT _cellSize;
	POINT _lastCell{ -1, -1 };
	int _rows = 15;
	int _columns = 20;
	int _mode;
	int max_value = 1;

// Operations
public:
	void InitializeCells();
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CHeatMapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

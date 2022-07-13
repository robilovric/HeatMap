
// HeatMapDoc.cpp : implementation of the CHeatMapDoc class
//

#include "pch.h"
#include "framework.h"
#include "afx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HeatMap.h"
#endif

#include "HeatMapDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHeatMapDoc

IMPLEMENT_DYNCREATE(CHeatMapDoc, CDocument)

BEGIN_MESSAGE_MAP(CHeatMapDoc, CDocument)
END_MESSAGE_MAP()


// CHeatMapDoc construction/destruction

CHeatMapDoc::CHeatMapDoc() noexcept
{

}

CHeatMapDoc::~CHeatMapDoc()
{
}

void CHeatMapDoc::InitializeCells()
{
	_cellColorMatrix.clear(); //necessary when we call fuction from Matrix dialog handler
	_cellColorMatrix.resize(_rows, std::vector<UINT>(_columns, 0));
}

BOOL CHeatMapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitializeCells();
	return TRUE;
}




// CHeatMapDoc serialization

void CHeatMapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << magic_number;
		ar << _rows;
		ar << _columns;
		for (int i = 0; i < _rows; ++i) {
			for (int j = 0; j < _columns; ++j) {
				ar << _cellColorMatrix[i][j];
			}
		}
	}
	else
	{
		int verifyFormat;
		CString invalidFormat;
		ar >> verifyFormat;
		ar >> _rows;
		ar >> _columns;
		if (verifyFormat != magic_number || _rows > rows_max || _columns > columns_max) {
			throw new CArchiveException(CArchiveException::badIndex);
		}
		_cellColorMatrix.clear();
		_cellColorMatrix.resize(_rows, std::vector<UINT>(_columns, 0));
		for (int i = 0; i < _rows; ++i) {
			for (int j = 0; j < _columns; ++j) {
				ar >> _cellColorMatrix[i][j];
			}
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHeatMapDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CHeatMapDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHeatMapDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHeatMapDoc diagnostics

#ifdef _DEBUG
void CHeatMapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHeatMapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHeatMapDoc commands

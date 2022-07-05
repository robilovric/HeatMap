// CMatrixDlg.cpp : implementation file
//

#include "pch.h"
#include "HeatMap.h"
#include "CMatrixDlg.h"
#include "afxdialogex.h"


// CMatrixDlg dialog

IMPLEMENT_DYNAMIC(CMatrixDlg, CDialog)

CMatrixDlg::CMatrixDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_MATRIX, pParent)
	, m_Rows(0)
	, m_Columns(0)
{

}

CMatrixDlg::~CMatrixDlg()
{
}

void CMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROWS, m_Rows);
	DDV_MinMaxInt(pDX, m_Rows, 10, 10000);
	DDX_Text(pDX, IDC_EDIT_COLUMNS, m_Columns);
	DDV_MinMaxInt(pDX, m_Columns, 10, 10000);
}


BEGIN_MESSAGE_MAP(CMatrixDlg, CDialog)
END_MESSAGE_MAP()


// CMatrixDlg message handlers

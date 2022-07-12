// CModeDlg.cpp : implementation file
//

#include "pch.h"
#include "HeatMap.h"
#include "CModeDlg.h"
#include "afxdialogex.h"
#include "afxdd_.h"
#include "afxwin.h"
#include "HeatMapDoc.h"


// CModeDlg dialog

IMPLEMENT_DYNAMIC(CModeDlg, CDialog)

CModeDlg::CModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_MODE, pParent)
{
	
}

CModeDlg::~CModeDlg()
{
}

void CModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_MODES, newMode);
}


BEGIN_MESSAGE_MAP(CModeDlg, CDialog)
END_MESSAGE_MAP()


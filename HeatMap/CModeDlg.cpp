// CModeDlg.cpp : implementation file
//

#include "pch.h"
#include "HeatMap.h"
#include "CModeDlg.h"
#include "afxdialogex.h"


// CModeDlg dialog

IMPLEMENT_DYNAMIC(CModeDlg, CDialog)

CModeDlg::CModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_MODE, pParent)
{
	//m_Mode.SetCurSel(2);
}

CModeDlg::~CModeDlg()
{
}

void CModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODES, m_Mode);
}


BEGIN_MESSAGE_MAP(CModeDlg, CDialog)
END_MESSAGE_MAP()


// CModeDlg message handlers

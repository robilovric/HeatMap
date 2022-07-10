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
	, m_CurrentMode(_T(""))
{
	
}

CModeDlg::~CModeDlg()
{
}

void CModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODES, m_Mode);
	DDX_Text(pDX, IDC_EDIT_CURRENT_MODE, m_CurrentMode);
}


BEGIN_MESSAGE_MAP(CModeDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_MODES, &CModeDlg::OnSelchangeComboModes)
END_MESSAGE_MAP()


// CModeDlg message handlers


void CModeDlg::OnSelchangeComboModes()
{
	// TODO: Add your control notification handler code here

	newMode = m_Mode.GetCurSel();

	//m_Mode.GetLBText(newMode, m_CurrentMode);
	//m_Mode.SetCueBanner(m_CurrentMode);

}

#pragma once


// CMatrixDlg dialog

class CMatrixDlg : public CDialog
{
	DECLARE_DYNAMIC(CMatrixDlg)

public:
	CMatrixDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMatrixDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MATRIX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

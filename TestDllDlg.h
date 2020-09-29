// TestDllDlg.h : header file
//

#include "afxwin.h"
#include "BDialog.h"
//#include "CPictureWindow.h"
#if !defined(AFX_TESTDLLDLG_H__A193823B_281D_4560_B6E0_35D428C9022A__INCLUDED_)
#define AFX_TESTDLLDLG_H__A193823B_281D_4560_B6E0_35D428C9022A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDllDlg dialog

class CTestDllDlg : public CBDialog
{
// Construction
public:
    //CPictureWindow objPictureWindow;
    CTestDllDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
    //{{AFX_DATA(CTestDllDlg)
    enum { IDD = IDD_TESTDLL_DIALOG };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTestDllDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    CBitmap m_bmpBack;
    CBrush m_brushBack;
    CBitmap m_bmpEarth;
    HICON m_hIcon;
    UINT m_DeviveHandle;
    int m_ReadSptype;
    CString m_Testlog;
    // Generated message map functions
    //{{AFX_MSG(CTestDllDlg)
    virtual BOOL OnInitDialog();

    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnDropdownComboCom();
    afx_msg void OnBnClickedBtnVer();
    afx_msg void OnBnClickedBtnConnect();
    afx_msg void OnBnClickedBtnSettime();
    afx_msg void OnBnClickedBtnCSV();
    afx_msg void OnBnClickedBtnDisconnect();
    CEdit m_EditMessage;
    afx_msg void OnBnClickedBtnReadCalibration();
    afx_msg void OnBnClickedBtnWaveLenPixel();
    afx_msg void OnBnClickedBtnReadSCAN();
    void SetLogText(CString str);
	afx_msg void OnCbnSelchangeComboCom();
    afx_msg void OnCbnSelchangeComboCom2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
    afx_msg void OnEnChangeEditWaveLen();
    afx_msg void OnEnChangeEditPixel();
    CButton Scan;
    CButton Calibration;
    CButton CSV;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLLDLG_H__A193823B_281D_4560_B6E0_35D428C9022A__INCLUDED_)

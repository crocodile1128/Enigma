// EnigmaDlg.h : header file
//

#if !defined(AFX_ENIGMADLG_H__026DBD20_CEE3_494C_9CF4_F417A00BFD0D__INCLUDED_)
#define AFX_ENIGMADLG_H__026DBD20_CEE3_494C_9CF4_F417A00BFD0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEnigmaDlg dialog

class CEnigmaDlg : public CDialog
{
// Construction
public:
	CEnigmaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEnigmaDlg)
	enum { IDD = IDD_ENIGMA_DIALOG };
	CTabCtrl	m_tab;
	CString	m_input;
	CString	m_output;
	CString	m_rot1;
	CString	m_rot2;
	CString	m_rot3;
	int		m_rset;
	CString	m_pset;
	CString	m_paste;
	CString	m_type;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnigmaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	char Enc(char m);
	void HideAll();
	void ChangeTab(int i);
	void InitPosSettings();
	void RotorSettings();
	void PlugSettings();
	int count;
	void Roll(int i);
	// Generated message map functions
	//{{AFX_MSG(CEnigmaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonA();
	afx_msg void OnButtonB();
	afx_msg void OnButtonC();
	afx_msg void OnButtonD();
	afx_msg void OnButtonE();
	afx_msg void OnButtonF();
	afx_msg void OnButtonG();
	afx_msg void OnButtonH();
	afx_msg void OnButtonI();
	afx_msg void OnButtonJ();
	afx_msg void OnButtonK();
	afx_msg void OnButtonL();
	afx_msg void OnButtonM();
	afx_msg void OnButtonN();
	afx_msg void OnButtonO();
	afx_msg void OnButtonP();
	afx_msg void OnButtonQ();
	afx_msg void OnButtonR();
	afx_msg void OnButtonS();
	afx_msg void OnButtonT();
	afx_msg void OnButtonU();
	afx_msg void OnButtonV();
	afx_msg void OnButtonW();
	afx_msg void OnButtonX();
	afx_msg void OnButtonY();
	afx_msg void OnButtonZ();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonApply();
	afx_msg void OnButtonPaste();
	afx_msg void OnButtonClear();
	afx_msg void OnChangeEditType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENIGMADLG_H__026DBD20_CEE3_494C_9CF4_F417A00BFD0D__INCLUDED_)

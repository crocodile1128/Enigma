// Enigma.h : main header file for the ENIGMA application
//

#if !defined(AFX_ENIGMA_H__DC9EB4D4_DB31_4A9A_8275_10CA319717B5__INCLUDED_)
#define AFX_ENIGMA_H__DC9EB4D4_DB31_4A9A_8275_10CA319717B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEnigmaApp:
// See Enigma.cpp for the implementation of this class
//

class CEnigmaApp : public CWinApp
{
public:
	CEnigmaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnigmaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEnigmaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENIGMA_H__DC9EB4D4_DB31_4A9A_8275_10CA319717B5__INCLUDED_)

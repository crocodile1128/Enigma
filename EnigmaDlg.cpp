// EnigmaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Enigma.h"
#include "EnigmaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// Elements ofEnigma
int plugboard[26]	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
int rotor[5][26]	={	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
						{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
						{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
						{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
						{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25} };
int srotor[5][26]	={	{ 1,19,10,14, 0,20, 8,16, 7,22, 4,11, 5,17, 9,12,23,18, 2,25, 6,24,13,21, 3,15},
						{20, 1, 6, 4,15, 3,14,12,23, 5,16, 2,22,19,11,18,25,24,13, 7,10, 8,21, 9, 0,17},
						{ 8,18, 0,17,20,22,10, 3,13,11, 4,23, 5,24, 9,12,25,16,19, 6,15,21, 2, 7, 1,14},
						{11, 1,10, 4, 5,19,20, 8,22,25,24,14, 0,17, 9,16, 7,12,23,18, 2,13,21, 3,15, 6},
						{19,11, 4,15,20, 1,24, 6, 2,22,14,25, 3,13, 5,18, 7, 0,17,10, 8,12,23,21, 9,16} };
int reflector[26]	={24, 2, 1, 5,21, 3,17,11,20,22,12, 7,10,14,13,19,25,6,23,15, 8, 4, 9,18, 0,16};
int rot1=0, rot2=1, rot3=2;
char r1,r2,r3;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnigmaDlg dialog

CEnigmaDlg::CEnigmaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnigmaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnigmaDlg)
	m_input = _T("");
	m_output = _T("");
	m_rot1 = _T("");
	m_rot2 = _T("");
	m_rot3 = _T("");
	m_rset = 321;
	m_pset = _T("AZ BC DJ EG RP KL IM FO HN QS");
	m_paste = _T("ABCD");
	m_type = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnigmaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnigmaDlg)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_input);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_output);
	DDX_Text(pDX, IDC_EDIT_ROT1, m_rot1);
	DDX_Text(pDX, IDC_EDIT_ROT2, m_rot2);
	DDX_Text(pDX, IDC_EDIT_ROT3, m_rot3);
	DDX_Text(pDX, IDC_EDIT_RSET, m_rset);
	DDX_Text(pDX, IDC_EDIT_PSET, m_pset);
	DDX_Text(pDX, IDC_EDIT_PASTE, m_paste);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_type);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEnigmaDlg, CDialog)
	//{{AFX_MSG_MAP(CEnigmaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_A, OnButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, OnButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, OnButtonC)
	ON_BN_CLICKED(IDC_BUTTON_D, OnButtonD)
	ON_BN_CLICKED(IDC_BUTTON_E, OnButtonE)
	ON_BN_CLICKED(IDC_BUTTON_F, OnButtonF)
	ON_BN_CLICKED(IDC_BUTTON_G, OnButtonG)
	ON_BN_CLICKED(IDC_BUTTON_H, OnButtonH)
	ON_BN_CLICKED(IDC_BUTTON_I, OnButtonI)
	ON_BN_CLICKED(IDC_BUTTON_J, OnButtonJ)
	ON_BN_CLICKED(IDC_BUTTON_K, OnButtonK)
	ON_BN_CLICKED(IDC_BUTTON_L, OnButtonL)
	ON_BN_CLICKED(IDC_BUTTON_M, OnButtonM)
	ON_BN_CLICKED(IDC_BUTTON_N, OnButtonN)
	ON_BN_CLICKED(IDC_BUTTON_O, OnButtonO)
	ON_BN_CLICKED(IDC_BUTTON_P, OnButtonP)
	ON_BN_CLICKED(IDC_BUTTON_Q, OnButtonQ)
	ON_BN_CLICKED(IDC_BUTTON_R, OnButtonR)
	ON_BN_CLICKED(IDC_BUTTON_S, OnButtonS)
	ON_BN_CLICKED(IDC_BUTTON_T, OnButtonT)
	ON_BN_CLICKED(IDC_BUTTON_U, OnButtonU)
	ON_BN_CLICKED(IDC_BUTTON_V, OnButtonV)
	ON_BN_CLICKED(IDC_BUTTON_W, OnButtonW)
	ON_BN_CLICKED(IDC_BUTTON_X, OnButtonX)
	ON_BN_CLICKED(IDC_BUTTON_Y, OnButtonY)
	ON_BN_CLICKED(IDC_BUTTON_Z, OnButtonZ)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, OnButtonPaste)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_EN_CHANGE(IDC_EDIT_TYPE, OnChangeEditType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnigmaDlg message handlers

BOOL CEnigmaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Set tab
	m_tab.InsertItem(0,"Keyboard");
	m_tab.InsertItem(1,"Settings");
	// Hide all yellow light bulb
	HideAll();
	// Auto select tab0
	ChangeTab(0);
	// Set count
	count=1;
	// Set plugboard
	PlugSettings();
	RotorSettings();
	// Show Rotors
	UpdateData(1);
	r1=rotor[rot1][0]+'A';
	r2=rotor[rot2][0]+'A';
	r3=rotor[rot3][0]+'A';
	m_rot1=r1;
	m_rot2=r2;
	m_rot3=r3;
	OnButtonPaste();
	OnButtonClear();
	UpdateData(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEnigmaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEnigmaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEnigmaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CEnigmaDlg::HideAll()
{
	for(int i=1055;i<1081;i++) GetDlgItem(i)->ShowWindow(SW_HIDE);
}

void CEnigmaDlg::InitPosSettings()
{
	int j;
	for(j=0;j<26&&rotor[rot1][0]!=(m_rot1[0]-'A');j++) Roll(rot1);
	for(j=0;j<26&&rotor[rot2][0]!=(m_rot2[0]-'A');j++) Roll(rot2);
	for(j=0;j<26&&rotor[rot3][0]!=(m_rot3[0]-'A');j++) Roll(rot3);

	UpdateData(1);
	r1=rotor[rot1][0]+'A';
	r2=rotor[rot2][0]+'A';
	r3=rotor[rot3][0]+'A';
	m_rot1=r1;
	m_rot2=r2;
	m_rot3=r3;
	count=1;
	UpdateData(0);
}
/*//Debug
//char S1[10],S2[1000];
TRACE("%s  %s\n",S1,m_rot1);
		S2[0]=0;
		sprintf(S2,"[ %d",rotor[rot1][0]);
		for(k=1;k<26;k++)
			sprintf(S2,"%s, %d",S2,rotor[rot1][k]);
		sprintf(S2,"%s]",S2);
TRACE("Rotor(%d) = %s\n",rot1,S2);*/
void CEnigmaDlg::PlugSettings()
{
	int i,j;
	int p,q,tmp;
	j=0;
	m_pset+=' ';
	for(i=0;i<strlen(m_pset);i++){
		if(m_pset[i]==' '&&m_pset[i-1]!=' '&&m_pset[i-2]!=' '){
			// find p,q (p <-> q)
			p = m_pset[i-2] - 'A';
			q = m_pset[i-1] - 'A';
			tmp = plugboard[p];
			plugboard[p]=plugboard[q];
			plugboard[q]=tmp;
		}
	}
}

void CEnigmaDlg::RotorSettings()
{
	rot3=m_rset/100-1;
	rot2=(m_rset%100)/10-1;
	rot1=(m_rset%10)-1;
}
void CEnigmaDlg::Roll(int i)
{
	int j,tmp1,tmp2;
	UpdateData(1);
	tmp1=rotor[i][0];
	tmp2=srotor[i][0];
	for(j=0;j<25;j++) {rotor[i][j]=rotor[i][j+1]; srotor[i][j]=srotor[i][j+1];}
	rotor[i][j]=tmp1;
	srotor[i][j]=tmp2;
	UpdateData(0);
/*Debug
	char S1[500];
	sprintf(S1,"[ %d",srotor[i][0]);
	for(j=1;j<26;j++)
		sprintf(S1,"%s, %d",S1,srotor[i][j]);
	sprintf("%s]",S1);
TRACE("Rotor(%d) = %s\n",i,S1);
*/
}

char CEnigmaDlg::Enc(char m)
{
	/* caeser cipher
	int key=3;
	return 'A'+(m+key-'A')%26;
	*/
	int x,i,j,k,in,ref;
	// Plugboard-forward
	in=plugboard[m-'A'];
	
	// Rotors-forward
	for(i=0;i<26;i++) if(in==srotor[rot1][i]) break;
	for(j=0;j<26;j++) if(rotor[rot2][i]==srotor[rot2][j]) break;
	for(k=0;k<26;k++) if(rotor[rot3][j]==srotor[rot3][k]) break;
TRACE("Forward === m=%c, in=%c, r1=%c, r2=%c, r3=%c\n",m,in+65,i+65,j+65,k+65);
	// Reflector
	ref=reflector[k];

	// Rotors-backward
	for(i=0;i<26;i++) if(srotor[rot3][ref]==rotor[rot3][i]) break;
	for(j=0;i<26;j++) if(srotor[rot2][i]==rotor[rot2][j]) break;
	// Plugboard-backward
	m=plugboard[srotor[rot1][j]]+'A';
TRACE("Backward === ref=%c, r3=%c, r2=%c, r1=%c\n\n",ref+65,i+65,j+65,srotor[rot1][j]+65);
	// Rotors change
	Roll(rot1); 
	count++;
	if(count%26==0) Roll(rot2); 
	if(count%676==0) Roll(rot3);

	// Show Rotors
	r1=rotor[rot1][0]+'A';
	r2=rotor[rot2][0]+'A';
	r3=rotor[rot3][0]+'A';
	m_rot1=r1;
	m_rot2=r2;
	m_rot3=r3;

	return m;
}

void CEnigmaDlg::ChangeTab(int i)
{
	switch(i){
	case 0:
		for(i=1001;i<1027;i++) GetDlgItem(i)->ShowWindow(SW_SHOW);
		for(i=1029;i<1055;i++) GetDlgItem(i)->ShowWindow(SW_SHOW);
		for(i=1081;i<1085;i++) GetDlgItem(i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ROT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ROT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ROT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ROT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ROT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ROT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PASTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PASTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_PASTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_CLEAR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TYPE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_RSET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_RSET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PSET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PSET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_APPLY)->ShowWindow(SW_SHOW);
		break;
	case 1:
		for(i=1001;i<1027;i++) GetDlgItem(i)->ShowWindow(SW_HIDE);
		for(i=1029;i<1055;i++) GetDlgItem(i)->ShowWindow(SW_HIDE);
		for(i=1081;i<1085;i++) GetDlgItem(i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ROT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ROT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ROT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ROT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ROT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ROT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PASTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PASTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_PASTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_CLEAR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TYPE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_RSET)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_RSET)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PSET)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PSET)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_APPLY)->ShowWindow(SW_SHOW);
		break;
	}
}


void CEnigmaDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==1128){
		UpdateData(1);
		HideAll();
		UpdateData(0);
	}
	CDialog::OnTimer(nIDEvent);
}

void CEnigmaDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i;
	i=m_tab.GetCurSel();
	UpdateData(1);
	ChangeTab(i);
	UpdateData(0);
	*pResult = 0;
}


void CEnigmaDlg::OnButtonApply() 
{
	InitPosSettings();
	RotorSettings();
	PlugSettings();
}

void CEnigmaDlg::OnButtonPaste() 
{
	int i;
	for(i=0;i<strlen(m_paste);i++){
		switch(m_paste[i]){
		case 'A': OnButtonA(); break;
		case 'a': OnButtonA(); break;
		case 'B': OnButtonB(); break;
		case 'b': OnButtonB(); break;
		case 'C': OnButtonC(); break;
		case 'c': OnButtonC(); break;
		case 'D': OnButtonD(); break;
		case 'd': OnButtonD(); break;
		case 'E': OnButtonE(); break;
		case 'e': OnButtonE(); break;
		case 'F': OnButtonF(); break;
		case 'f': OnButtonF(); break;
		case 'G': OnButtonG(); break;
		case 'g': OnButtonG(); break;
		case 'H': OnButtonH(); break;
		case 'h': OnButtonH(); break;
		case 'I': OnButtonI(); break;
		case 'i': OnButtonI(); break;
		case 'J': OnButtonJ(); break;
		case 'j': OnButtonJ(); break;
		case 'K': OnButtonK(); break;
		case 'k': OnButtonK(); break;
		case 'L': OnButtonL(); break;
		case 'l': OnButtonL(); break;
		case 'M': OnButtonM(); break;
		case 'm': OnButtonM(); break;
		case 'N': OnButtonN(); break;
		case 'n': OnButtonN(); break;
		case 'O': OnButtonO(); break;
		case 'o': OnButtonO(); break;
		case 'P': OnButtonP(); break;
		case 'p': OnButtonP(); break;
		case 'Q': OnButtonQ(); break;
		case 'q': OnButtonQ(); break;
		case 'R': OnButtonR(); break;
		case 'r': OnButtonR(); break;
		case 'S': OnButtonS(); break;
		case 's': OnButtonS(); break;
		case 'T': OnButtonT(); break;
		case 't': OnButtonT(); break;
		case 'U': OnButtonU(); break;
		case 'u': OnButtonU(); break;
		case 'V': OnButtonV(); break;
		case 'v': OnButtonV(); break;
		case 'W': OnButtonW(); break;
		case 'w': OnButtonW(); break;
		case 'X': OnButtonX(); break;
		case 'x': OnButtonX(); break;
		case 'Y': OnButtonY(); break;
		case 'y': OnButtonY(); break;
		case 'Z': OnButtonZ(); break;
		case 'z': OnButtonZ(); break;
		}
	}
}

void CEnigmaDlg::OnButtonClear() 
{
	UpdateData(1);
	m_paste="";
	m_type="";
	m_input="";
	m_output="";
	UpdateData(0);
}

void CEnigmaDlg::OnButtonA() 
{
	char m = 'A';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonB() 
{
	char m = 'B';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonC() 
{
	char m = 'C';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonD() 
{
	char m = 'D';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonE() 
{
	char m = 'E';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonF() 
{
	char m = 'F';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonG() 
{
	char m = 'G';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonH() 
{
	char m = 'H';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonI() 
{
	char m = 'I';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonJ() 
{
	char m = 'J';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonK() 
{
	char m = 'K';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonL() 
{
	char m = 'L';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonM() 
{
	char m = 'M';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonN() 
{
	char m = 'N';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonO() 
{
	char m = 'O';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonP() 
{
	char m = 'P';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonQ() 
{
	char m = 'Q';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonR() 
{
	char m = 'R';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonS() 
{
	char m = 'S';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonT() 
{
	char m = 'T';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonU() 
{
	char m = 'U';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonV() 
{
	char m = 'V';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonW() 
{
	char m = 'W';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonX() 
{
	char m = 'X';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonY() 
{
	char m = 'Y';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnButtonZ() 
{
	char m = 'Z';
	char e;
	UpdateData(1);
	e = Enc(m);
	m_input += m;
	m_output += e;
	GetDlgItem(e+1055-'A')->ShowWindow(SW_SHOW);
	UpdateData(0);
	SetTimer(1128,200,0);
}

void CEnigmaDlg::OnChangeEditType() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	int i;
	UpdateData(1);UpdateData(0);
	i=strlen(m_type);
	switch(m_type[i-1]){
	case 'A': OnButtonA(); break;
	case 'a': OnButtonA(); break;
	case 'B': OnButtonB(); break;
	case 'b': OnButtonB(); break;
	case 'C': OnButtonC(); break;
	case 'c': OnButtonC(); break;
	case 'D': OnButtonD(); break;
	case 'd': OnButtonD(); break;
	case 'E': OnButtonE(); break;
	case 'e': OnButtonE(); break;
	case 'F': OnButtonF(); break;
	case 'f': OnButtonF(); break;
	case 'G': OnButtonG(); break;
	case 'g': OnButtonG(); break;
	case 'H': OnButtonH(); break;
	case 'h': OnButtonH(); break;
	case 'I': OnButtonI(); break;
	case 'i': OnButtonI(); break;
	case 'J': OnButtonJ(); break;
	case 'j': OnButtonJ(); break;
	case 'K': OnButtonK(); break;
	case 'k': OnButtonK(); break;
	case 'L': OnButtonL(); break;
	case 'l': OnButtonL(); break;
	case 'M': OnButtonM(); break;
	case 'm': OnButtonM(); break;
	case 'N': OnButtonN(); break;
	case 'n': OnButtonN(); break;
	case 'O': OnButtonO(); break;
	case 'o': OnButtonO(); break;
	case 'P': OnButtonP(); break;
	case 'p': OnButtonP(); break;
	case 'Q': OnButtonQ(); break;
	case 'q': OnButtonQ(); break;
	case 'R': OnButtonR(); break;
	case 'r': OnButtonR(); break;
	case 'S': OnButtonS(); break;
	case 's': OnButtonS(); break;
	case 'T': OnButtonT(); break;
	case 't': OnButtonT(); break;
	case 'U': OnButtonU(); break;
	case 'u': OnButtonU(); break;
	case 'V': OnButtonV(); break;
	case 'v': OnButtonV(); break;
	case 'W': OnButtonW(); break;
	case 'w': OnButtonW(); break;
	case 'X': OnButtonX(); break;
	case 'x': OnButtonX(); break;
	case 'Y': OnButtonY(); break;
	case 'y': OnButtonY(); break;
	case 'Z': OnButtonZ(); break;
	case 'z': OnButtonZ(); break;
	}

}

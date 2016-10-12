// SiliconMultimeterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SiliconMultimeter.h"
#include "SiliconMultimeterDlg.h"
#include "SiliconMultimeterHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSiliconMultimeterDlg dialog




CSiliconMultimeterDlg::CSiliconMultimeterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSiliconMultimeterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSiliconMultimeterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSiliconMultimeterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSiliconMultimeterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSiliconMultimeterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSiliconMultimeterDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSiliconMultimeterDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSiliconMultimeterDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CSiliconMultimeterDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CSiliconMultimeterDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CSiliconMultimeterDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CSiliconMultimeterDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CSiliconMultimeterDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CSiliconMultimeterDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CSiliconMultimeterDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CSiliconMultimeterDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CSiliconMultimeterDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CSiliconMultimeterDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CSiliconMultimeterDlg::OnBnClickedButton16)
END_MESSAGE_MAP()


// CSiliconMultimeterDlg message handlers

BOOL CSiliconMultimeterDlg::OnInitDialog()
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

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSiliconMultimeterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSiliconMultimeterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSiliconMultimeterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSiliconMultimeterDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->ConnetComAuto();
	if (bResult)
	{
		OutputDebugString(L"Success connect com!\n");
	}else{
		OutputDebugString(L"Fault connect com!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	char *strRecv = SiliconMultimeterHelp::Instance()->SetContinueDump();
	if (strRecv)
	{
		OutputDebugStringA(strRecv);
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetStopDump();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	char *strRecv = SiliconMultimeterHelp::Instance()->SetOneTimeDump();
	if (strRecv)
	{
		OutputDebugStringA(strRecv);
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetManualMode();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetAutoMode();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetLockValue();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetUnLockValue();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetZeroTest();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetExitZeroTest();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetStartREC();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetStopREC();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetSHIFTFunc();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton14()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetHZFunc();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton15()
{
	// TODO: Add your control notification handler code here
	bool bResult = SiliconMultimeterHelp::Instance()->SetClearMemory();
	if (bResult)
	{
		OutputDebugString(L"Success!\n");
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

void CSiliconMultimeterDlg::OnBnClickedButton16()
{
	// TODO: Add your control notification handler code here
	char *strRecv = SiliconMultimeterHelp::Instance()->SetDownload();
	if (strRecv)
	{
		OutputDebugStringA(strRecv);
	}else{
		OutputDebugString(L"Fault!\n");
	}
}

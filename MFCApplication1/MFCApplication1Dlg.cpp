
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strDisplay = _T("0");
	m_strExpression = _T("");
	m_dwFirstOperand = 0;
	m_dwSecondOperand = 0;
	m_strOperation = _T("");
	m_bNewNumber = TRUE;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN0, &CMFCApplication1Dlg::OnBnClickedBtn0)
	ON_BN_CLICKED(IDC_BTN1, &CMFCApplication1Dlg::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN2, &CMFCApplication1Dlg::OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN3, &CMFCApplication1Dlg::OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN4, &CMFCApplication1Dlg::OnBnClickedBtn4)
	ON_BN_CLICKED(IDC_BTN5, &CMFCApplication1Dlg::OnBnClickedBtn5)
	ON_BN_CLICKED(IDC_BTN6, &CMFCApplication1Dlg::OnBnClickedBtn6)
	ON_BN_CLICKED(IDC_BTN7, &CMFCApplication1Dlg::OnBnClickedBtn7)
	ON_BN_CLICKED(IDC_BTN8, &CMFCApplication1Dlg::OnBnClickedBtn8)
	ON_BN_CLICKED(IDC_BTN9, &CMFCApplication1Dlg::OnBnClickedBtn9)
	ON_BN_CLICKED(IDC_BTN_DOT, &CMFCApplication1Dlg::OnBnClickedBtnDot)
	ON_BN_CLICKED(IDC_BTN_ADD, &CMFCApplication1Dlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SUB, &CMFCApplication1Dlg::OnBnClickedBtnSub)
	ON_BN_CLICKED(IDC_BTN_MUL, &CMFCApplication1Dlg::OnBnClickedBtnMul)
	ON_BN_CLICKED(IDC_BTN_DIV, &CMFCApplication1Dlg::OnBnClickedBtnDiv)
	ON_BN_CLICKED(IDC_BTN_EQ, &CMFCApplication1Dlg::OnBnClickedBtnEq)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CMFCApplication1Dlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	UpdateDisplay();
	UpdateExpression();

	SetFocus();

	SetTimer(1, 100, NULL);

	return FALSE;
}

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	short state;
	bool shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;

	state = GetAsyncKeyState('0');
	if (state & 0x8000) { AppendDigit(_T("0")); }

	state = GetAsyncKeyState('1');
	if (state & 0x8000) { AppendDigit(_T("1")); }

	state = GetAsyncKeyState('2');
	if (state & 0x8000) { AppendDigit(_T("2")); }

	state = GetAsyncKeyState('3');
	if (state & 0x8000) { AppendDigit(_T("3")); }

	state = GetAsyncKeyState('4');
	if (state & 0x8000) { AppendDigit(_T("4")); }

	state = GetAsyncKeyState('5');
	if (state & 0x8000) { AppendDigit(_T("5")); }

	state = GetAsyncKeyState('6');
	if (state & 0x8000) { AppendDigit(_T("6")); }

	state = GetAsyncKeyState('7');
	if (state & 0x8000) { AppendDigit(_T("7")); }

	state = GetAsyncKeyState('8');
	if (state & 0x8000) { 
		if (shiftPressed)
			SetOperation(_T("*"));
		else
			AppendDigit(_T("8"));
	}

	state = GetAsyncKeyState('9');
	if (state & 0x8000) { AppendDigit(_T("9")); }

	state = GetAsyncKeyState(VK_OEM_PLUS);
	if (state & 0x8000) { 
		if (shiftPressed)
			SetOperation(_T("+"));
		else
			OnBnClickedBtnEq();
	}

	state = GetAsyncKeyState(VK_OEM_MINUS);
	if (state & 0x8000) { SetOperation(_T("-")); }

	state = GetAsyncKeyState(VK_OEM_5);
	if (state & 0x8000) { SetOperation(_T("/")); }

	state = GetAsyncKeyState(VK_ADD);
	if (state & 0x8000) { SetOperation(_T("+")); }

	state = GetAsyncKeyState(VK_SUBTRACT);
	if (state & 0x8000) { SetOperation(_T("-")); }

	state = GetAsyncKeyState(VK_MULTIPLY);
	if (state & 0x8000) { SetOperation(_T("*")); }

	state = GetAsyncKeyState(VK_DIVIDE);
	if (state & 0x8000) { SetOperation(_T("/")); }

	state = GetAsyncKeyState(VK_RETURN);
	if (state & 0x8000) { OnBnClickedBtnEq(); }

	state = GetAsyncKeyState(VK_ESCAPE);
	if (state & 0x8000) { OnBnClickedBtnClear(); }

	state = GetAsyncKeyState(VK_BACK);
	if (state & 0x8000) {
		if (!m_strDisplay.IsEmpty() && !m_bNewNumber)
		{
			m_strDisplay.Delete(m_strDisplay.GetLength() - 1);
			if (!m_strExpression.IsEmpty())
				m_strExpression.Delete(m_strExpression.GetLength() - 1);
			if (m_strDisplay.IsEmpty())
				m_strDisplay = _T("0");
			UpdateDisplay();
			UpdateExpression();
		}
	}

	state = GetAsyncKeyState(VK_OEM_PERIOD);
	if (state & 0x8000) { OnBnClickedBtnDot(); }

	state = GetAsyncKeyState('=');
	if (state & 0x8000) { OnBnClickedBtnEq(); }

	CDialog::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::OnOK()
{
}

void CMFCApplication1Dlg::OnCancel()
{
	CDialog::OnCancel();
}


void CMFCApplication1Dlg::UpdateDisplay()
{
	GetDlgItem(IDC_DISPLAY)->SetWindowText(m_strDisplay);
}

void CMFCApplication1Dlg::UpdateExpression()
{
	GetDlgItem(IDC_EXPRESSION)->SetWindowText(m_strExpression);
}

void CMFCApplication1Dlg::AppendDigit(LPCTSTR szDigit)
{
	if (m_bNewNumber)
	{
		m_strDisplay = szDigit;
		m_bNewNumber = FALSE;
	}
	else
	{
		if (m_strDisplay == _T("0") && _tcscmp(szDigit, _T("0")) == 0)
			return;
		if (m_strDisplay == _T("0"))
			m_strDisplay = szDigit;
		else
			m_strDisplay += szDigit;
	}
	m_strExpression += szDigit;
	UpdateDisplay();
	UpdateExpression();
}

void CMFCApplication1Dlg::SetOperation(LPCTSTR szOp)
{
	m_dwFirstOperand = _tstof(m_strDisplay);
	m_strOperation = szOp;
	m_bNewNumber = TRUE;
	m_strExpression += szOp;
	UpdateExpression();
}


LRESULT CMFCApplication1Dlg::HandleKeyDown(WPARAM wParam)
{
	BOOL bHandled = FALSE;

	if (wParam >= '0' && wParam <= '9')
	{
		CString szDigit;
		szDigit.Format(_T("%c"), wParam);
		AppendDigit(szDigit);
		bHandled = TRUE;
	}
	else
	{
		switch (wParam)
		{
		case VK_ADD:
			SetOperation(_T("+"));
			bHandled = TRUE;
			break;
		case VK_SUBTRACT:
		case '-':
			SetOperation(_T("-"));
			bHandled = TRUE;
			break;
		case VK_MULTIPLY:
		case '*':
			SetOperation(_T("*"));
			bHandled = TRUE;
			break;
		case VK_DIVIDE:
		case '/':
			SetOperation(_T("/"));
			bHandled = TRUE;
			break;
		case VK_RETURN:
			OnBnClickedBtnEq();
			bHandled = TRUE;
			break;
		case VK_ESCAPE:
			OnBnClickedBtnClear();
			bHandled = TRUE;
			break;
		case VK_BACK:
			if (!m_strDisplay.IsEmpty() && !m_bNewNumber)
			{
				m_strDisplay.Delete(m_strDisplay.GetLength() - 1);
				if (!m_strExpression.IsEmpty())
					m_strExpression.Delete(m_strExpression.GetLength() - 1);
				if (m_strDisplay.IsEmpty())
					m_strDisplay = _T("0");
				UpdateDisplay();
				UpdateExpression();
			}
			bHandled = TRUE;
			break;
		case VK_OEM_PERIOD:
		case '.':
			OnBnClickedBtnDot();
			bHandled = TRUE;
			break;
		case '=':
			OnBnClickedBtnEq();
			bHandled = TRUE;
			break;
		}
	}

	return bHandled ? 1 : 0;
}

LRESULT CMFCApplication1Dlg::WindowProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		LRESULT result = HandleKeyDown(wParam);
		if (result == 1)
			return 1;
	}
	return CDialog::WindowProc(msg, wParam, lParam);
}


void CMFCApplication1Dlg::OnBnClickedBtn0() { AppendDigit(_T("0")); }
void CMFCApplication1Dlg::OnBnClickedBtn1() { AppendDigit(_T("1")); }
void CMFCApplication1Dlg::OnBnClickedBtn2() { AppendDigit(_T("2")); }
void CMFCApplication1Dlg::OnBnClickedBtn3() { AppendDigit(_T("3")); }
void CMFCApplication1Dlg::OnBnClickedBtn4() { AppendDigit(_T("4")); }
void CMFCApplication1Dlg::OnBnClickedBtn5() { AppendDigit(_T("5")); }
void CMFCApplication1Dlg::OnBnClickedBtn6() { AppendDigit(_T("6")); }
void CMFCApplication1Dlg::OnBnClickedBtn7() { AppendDigit(_T("7")); }
void CMFCApplication1Dlg::OnBnClickedBtn8() { AppendDigit(_T("8")); }
void CMFCApplication1Dlg::OnBnClickedBtn9() { AppendDigit(_T("9")); }

void CMFCApplication1Dlg::OnBnClickedBtnDot()
{
	if (m_bNewNumber)
	{
		m_strDisplay = _T("0.");
		m_strExpression += _T("0.");
		m_bNewNumber = FALSE;
	}
	else if (m_strDisplay.Find(_T('.')) == -1)
	{
		m_strDisplay += _T(".");
		m_strExpression += _T(".");
	}
	UpdateDisplay();
	UpdateExpression();
}

void CMFCApplication1Dlg::OnBnClickedBtnAdd() { SetOperation(_T("+")); }
void CMFCApplication1Dlg::OnBnClickedBtnSub() { SetOperation(_T("-")); }
void CMFCApplication1Dlg::OnBnClickedBtnMul() { SetOperation(_T("*")); }
void CMFCApplication1Dlg::OnBnClickedBtnDiv() { SetOperation(_T("/")); }

void CMFCApplication1Dlg::OnBnClickedBtnEq()
{
	if (m_strOperation.IsEmpty())
		return;

	m_dwSecondOperand = _tstof(m_strDisplay);
	double result = 0;

	m_strExpression += _T("=");

	if (m_strOperation == _T("+"))
		result = m_dwFirstOperand + m_dwSecondOperand;
	else if (m_strOperation == _T("-"))
		result = m_dwFirstOperand - m_dwSecondOperand;
	else if (m_strOperation == _T("*"))
		result = m_dwFirstOperand * m_dwSecondOperand;
	else if (m_strOperation == _T("/"))
	{
		if (m_dwSecondOperand != 0)
			result = m_dwFirstOperand / m_dwSecondOperand;
		else
		{
			m_strDisplay = _T("Error");
			m_strExpression = _T("Error");
			UpdateDisplay();
			UpdateExpression();
			m_strOperation = _T("");
			m_bNewNumber = TRUE;
			return;
		}
	}

	CString strResult;
	strResult.Format(_T("%g"), result);

	m_strExpression += strResult;

	m_strDisplay = strResult;
	m_strOperation = _T("");
	m_bNewNumber = TRUE;
	UpdateDisplay();
	UpdateExpression();
}

void CMFCApplication1Dlg::OnBnClickedBtnClear()
{
	m_strDisplay = _T("0");
	m_strExpression = _T("");
	m_dwFirstOperand = 0;
	m_dwSecondOperand = 0;
	m_strOperation = _T("");
	m_bNewNumber = TRUE;
	UpdateDisplay();
	UpdateExpression();
}

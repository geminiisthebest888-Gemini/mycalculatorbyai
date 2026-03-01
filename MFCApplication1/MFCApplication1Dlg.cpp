
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGradientButton implementation
CGradientButton::CGradientButton()
{
	m_bMouseOver = FALSE;
	m_bTracking = FALSE;
}

BEGIN_MESSAGE_MAP(CGradientButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CGradientButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CGradientButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		m_bTracking = TRUE;
		m_tme.cbSize = sizeof(TRACKMOUSEEVENT);
		m_tme.dwFlags = TME_LEAVE;
		m_tme.hwndTrack = m_hWnd;
		_TrackMouseEvent(&m_tme);
	}

	if (!m_bMouseOver)
	{
		m_bMouseOver = TRUE;
		Invalidate();
	}

	CButton::OnMouseMove(nFlags, point);
}

void CGradientButton::OnMouseLeave()
{
	m_bMouseOver = FALSE;
	m_bTracking = FALSE;
	Invalidate();
	CButton::OnMouseLeave();
}

void CGradientButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;

	BOOL pressed = (state & ODS_SELECTED);
	BOOL disabled = (state & ODS_DISABLED);

	int radius = 15;

	// Colors - light blue to darker blue
	COLORREF topColor, bottomColor;
	if (disabled)
	{
		topColor = RGB(200, 200, 200);
		bottomColor = RGB(180, 180, 180);
	}
	else if (pressed || m_bMouseOver)
	{
		// Darker blue when hovered or pressed
		topColor = RGB(100, 150, 220);
		bottomColor = RGB(50, 100, 180);
	}
	else
	{
		// Light blue when normal
		topColor = RGB(200, 230, 255);
		bottomColor = RGB(150, 200, 250);
	}

	// Draw gradient fill
	Graphics graphics(pDC->m_hDC);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	Rect gdiRect(rect.left, rect.top, rect.Width(), rect.Height());
	LinearGradientBrush brush(gdiRect, 
		Color(255, GetRValue(topColor), GetGValue(topColor), GetBValue(topColor)),
		Color(255, GetRValue(bottomColor), GetGValue(bottomColor), GetBValue(bottomColor)),
		LinearGradientModeVertical);

	graphics.FillRectangle(&brush, gdiRect);

	// Draw rounded border using GraphicsPath
	GraphicsPath path;
	int borderRadius = 15;
	INT smooth = 50;
	path.AddArc(rect.left, rect.top, borderRadius, borderRadius, 180, 90);
	path.AddArc(rect.right - borderRadius, rect.top, borderRadius, borderRadius, 270, 90);
	path.AddArc(rect.right - borderRadius, rect.bottom - borderRadius, borderRadius, borderRadius, 0, 90);
	path.AddArc(rect.left, rect.bottom - borderRadius, borderRadius, borderRadius, 90, 90);
	path.CloseFigure();

	Pen borderPen(Color(255, 80, 80, 80), 2);
	graphics.DrawPath(&borderPen, &path);

	// Draw text
	CString text;
	GetWindowText(text);
	if (!text.IsEmpty())
	{
		CFont* pFont = GetFont();
		CFont* pOldFont = pDC->SelectObject(pFont);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(disabled ? RGB(128, 128, 128) : RGB(0, 0, 0));
		UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		pDC->DrawText(text, &rect, format);
		pDC->SelectObject(pOldFont);
	}
}


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
	m_bAfterEquals = FALSE;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_KEYUP()
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

	// Set font size to 24 for all buttons
	CFont* pFont = new CFont();
	pFont->CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	int btnIds[] = { IDC_BTN0, IDC_BTN1, IDC_BTN2, IDC_BTN3, IDC_BTN4,
		IDC_BTN5, IDC_BTN6, IDC_BTN7, IDC_BTN8, IDC_BTN9,
		IDC_BTN_DOT, IDC_BTN_ADD, IDC_BTN_SUB, IDC_BTN_MUL, IDC_BTN_DIV,
		IDC_BTN_EQ, IDC_BTN_CLEAR };
	for (int i = 0; i < 17; i++)
	{
		GetDlgItem(btnIds[i])->SetFont(pFont);
	}

	// Subclass buttons to use gradient style
	m_btn0.SubclassDlgItem(IDC_BTN0, this);
	m_btn1.SubclassDlgItem(IDC_BTN1, this);
	m_btn2.SubclassDlgItem(IDC_BTN2, this);
	m_btn3.SubclassDlgItem(IDC_BTN3, this);
	m_btn4.SubclassDlgItem(IDC_BTN4, this);
	m_btn5.SubclassDlgItem(IDC_BTN5, this);
	m_btn6.SubclassDlgItem(IDC_BTN6, this);
	m_btn7.SubclassDlgItem(IDC_BTN7, this);
	m_btn8.SubclassDlgItem(IDC_BTN8, this);
	m_btn9.SubclassDlgItem(IDC_BTN9, this);
	m_btnDot.SubclassDlgItem(IDC_BTN_DOT, this);
	m_btnAdd.SubclassDlgItem(IDC_BTN_ADD, this);
	m_btnSub.SubclassDlgItem(IDC_BTN_SUB, this);
	m_btnMul.SubclassDlgItem(IDC_BTN_MUL, this);
	m_btnDiv.SubclassDlgItem(IDC_BTN_DIV, this);
	m_btnEq.SubclassDlgItem(IDC_BTN_EQ, this);
	m_btnClear.SubclassDlgItem(IDC_BTN_CLEAR, this);

	// Also set font for display edit boxes
	GetDlgItem(IDC_DISPLAY)->SetFont(pFont);
	GetDlgItem(IDC_EXPRESSION)->SetFont(pFont);

	UpdateDisplay();
	UpdateExpression();

	SetFocus();

	SetTimer(1, 100, NULL);

	return FALSE;
}

void CMFCApplication1Dlg::OnOK()
{
}

void CMFCApplication1Dlg::OnCancel()
{
	CDialog::OnCancel();
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

	state = GetAsyncKeyState(VK_OEM_2);
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

void CMFCApplication1Dlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bHandled = FALSE;

	if (nChar >= '0' && nChar <= '9')
	{
		CString szDigit;
		szDigit.Format(_T("%c"), nChar);
		AppendDigit(szDigit);
		bHandled = TRUE;
	}
	else
	{
		switch (nChar)
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

	if (!bHandled)
		CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
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
	if (m_bAfterEquals)
	{
		m_strDisplay = szDigit;
		m_strExpression = szDigit;
		m_bAfterEquals = FALSE;
		m_bNewNumber = FALSE;
	}
	else if (m_bNewNumber)
	{
		m_strDisplay = szDigit;
		m_bNewNumber = FALSE;
		m_strExpression += szDigit;
	}
	else
	{
		if (m_strDisplay == _T("0") && _tcscmp(szDigit, _T("0")) == 0)
			return;
		if (m_strDisplay == _T("0"))
			m_strDisplay = szDigit;
		else
			m_strDisplay += szDigit;
		m_strExpression += szDigit;
	}
	UpdateDisplay();
	UpdateExpression();
}

void CMFCApplication1Dlg::SetOperation(LPCTSTR szOp)
{
	if (m_bAfterEquals)
	{
		m_strExpression = m_strDisplay;
	}
	m_dwFirstOperand = _tstof(m_strDisplay);
	m_strOperation = szOp;
	m_bNewNumber = TRUE;
	m_bAfterEquals = FALSE;
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
	if (m_bAfterEquals)
	{
		m_strDisplay = _T("0.");
		m_strExpression = _T("0.");
		m_bAfterEquals = FALSE;
		m_bNewNumber = FALSE;
	}
	else if (m_bNewNumber)
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
	m_bAfterEquals = TRUE;
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
	m_bAfterEquals = FALSE;
	UpdateDisplay();
	UpdateExpression();
}

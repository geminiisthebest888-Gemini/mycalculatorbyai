
// MFCApplication1Dlg.h : header file
//

#pragma once

#include <GdiPlus.h>
using namespace Gdiplus;

// Custom gradient button class
class CGradientButton : public CButton
{
public:
	CGradientButton();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	BOOL m_bMouseOver;
	BOOL m_bTracking;

	TRACKMOUSEEVENT m_tme;

protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialog
{
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);
	virtual ~CMFCApplication1Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	CFont* m_pFont;
	CString m_strDisplay;
	CString m_strExpression;
	double m_dwFirstOperand;
	double m_dwSecondOperand;
	CString m_strOperation;
	BOOL m_bNewNumber;
	BOOL m_bAfterEquals;

	CGradientButton m_btn0, m_btn1, m_btn2, m_btn3, m_btn4;
	CGradientButton m_btn5, m_btn6, m_btn7, m_btn8, m_btn9;
	CGradientButton m_btnDot, m_btnAdd, m_btnSub, m_btnMul, m_btnDiv, m_btnEq, m_btnClear;

	void UpdateDisplay();
	void UpdateExpression();
	void AppendDigit(LPCTSTR szDigit);
	void SetOperation(LPCTSTR szOp);
	LRESULT HandleKeyDown(WPARAM wParam);
	LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtn0();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn3();
	afx_msg void OnBnClickedBtn4();
	afx_msg void OnBnClickedBtn5();
	afx_msg void OnBnClickedBtn6();
	afx_msg void OnBnClickedBtn7();
	afx_msg void OnBnClickedBtn8();
	afx_msg void OnBnClickedBtn9();
	afx_msg void OnBnClickedBtnDot();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSub();
	afx_msg void OnBnClickedBtnMul();
	afx_msg void OnBnClickedBtnDiv();
	afx_msg void OnBnClickedBtnEq();
	afx_msg void OnBnClickedBtnClear();
	DECLARE_MESSAGE_MAP()
};

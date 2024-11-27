
// MatrixChainView.h : interface of the CMatrixChainView class
//

#pragma once

class CMatrixChainView : public CView
{
protected: // create from serialization only
	CMatrixChainView() noexcept;
	DECLARE_DYNCREATE(CMatrixChainView)

// Attributes
public:
	CMatrixChainDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMatrixChainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMatrixchainRun();
	CString m_matrixName;
	CString m_matrixSize;
	int matrixChainProc();
	int superBest[27][27] = { 0 };
	char name[30]={};
	int cost[27][27] = { 0 };
	int best[27][27] = { 0 };
	
	int  size[30]={0};
	int bestAns = 0;
	int matrixEdge=0;
	CString recur(int l, int r, CString s);
	CString output;
	CString recur2(int left, int right, CString s);
};

#ifndef _DEBUG  // debug version in MatrixChainView.cpp
inline CMatrixChainDoc* CMatrixChainView::GetDocument() const
   { return reinterpret_cast<CMatrixChainDoc*>(m_pDocument); }
#endif


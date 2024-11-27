
// MatrixChainView.cpp : implementation of the CMatrixChainView class
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MatrixChain.h"
#endif

#include "MatrixChainDoc.h"
#include "MatrixChainView.h"
#include "dialogWindow.h"
#include <string>
#include <vector>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMatrixChainView

IMPLEMENT_DYNCREATE(CMatrixChainView, CView)

BEGIN_MESSAGE_MAP(CMatrixChainView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_MATRIXCHAIN_RUN, &CMatrixChainView::OnMatrixchainRun)
END_MESSAGE_MAP()

// CMatrixChainView construction/destruction

CMatrixChainView::CMatrixChainView() noexcept
{
	// TODO: add construction code here

}

CMatrixChainView::~CMatrixChainView()
{
}

BOOL CMatrixChainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMatrixChainView drawing

void CMatrixChainView::OnDraw(CDC* pDC)
{
	CMatrixChainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CString Buffer;
	Buffer.Format(L"所需乘法次數:%d次",bestAns);
	pDC->TextOut(0, 0, Buffer);
	pDC->TextOut(0, 20, output);
}	


// CMatrixChainView printing

BOOL CMatrixChainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMatrixChainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMatrixChainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMatrixChainView diagnostics

#ifdef _DEBUG
void CMatrixChainView::AssertValid() const
{
	CView::AssertValid();
}

void CMatrixChainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMatrixChainDoc* CMatrixChainView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatrixChainDoc)));
	return (CMatrixChainDoc*)m_pDocument;
}
#endif //_DEBUG


// CMatrixChainView message handlers


void CMatrixChainView::OnMatrixchainRun()
{
	// TODO: Add your command handler code here
	dialogWindow dW;
	dW.matrixName = m_matrixName;
	dW.matrixSize = m_matrixSize;
	if (dW.DoModal() == IDOK) {
		m_matrixName=dW.matrixName;
		m_matrixSize=dW.matrixSize;
		matrixChainProc();
	}
}


int CMatrixChainView::matrixChainProc()
{
	// TODO: Add your implementation code here.
	CMatrixChainDoc* pDoc = GetDocument();
	string str1;
	str1 = CT2A(m_matrixName.GetString());
	for (int i = 0; i < str1.length(); i++)
		name[i] = str1[i];
	matrixEdge = str1.length();

	int npos = 0;
	vector<CString> temp2;
	while (1) {
		CString temp;
		temp = m_matrixSize.Tokenize(L",", npos);
		if (npos==-1)
			break;
		temp2.push_back(temp);
	}

	vector<CString> temp3;
	for (int i = 0; i < temp2.size(); i++) {
		npos = 0;
		temp3.clear();
		while(1){
			CString temp;
			temp = temp2[i].Tokenize(L"*", npos);
			if (npos==-1)
				break;
			temp3.push_back(temp);
		}
		size[i] = _wtoi(temp3[0]);
		if (i == temp2.size() - 1)
			size[i + 1] = _wtoi(temp3[1]);
	}
	
	
	for (int i = 0; i < matrixEdge; i++)
		for (int j = i + 1; j < matrixEdge+1; j++)
			cost[i][j] = INT_MAX;
	for (int i = 0; i < matrixEdge+1; i++)
		cost[i][i] = 0;

	for (int j = 1; j <= matrixEdge-1; j++) {
		for(int i=1;i<= matrixEdge-j;i++)
			for (int k = i + 1; k <= i + j; k++) {
				int tmp = cost[i][k-1] + cost[k][i+j] + (size[i-1] * size[k-1] * size[i + j]);
				if (tmp < cost[i][i+j]) {
					cost[i][i + j] = tmp;
					best[i][i + j] = k-2;
					//superBest[i][i + j] = k-1;
				}
			}
	}
	output = L"("+recur(0, matrixEdge-1 , m_matrixName)+L")";
	bestAns = cost[1][matrixEdge];


	pDoc->UpdateAllViews(NULL);
	return 0;
}


CString CMatrixChainView::recur(int left, int right, CString s)
{
	// TODO: Add your implementation code here.
	if (left == right)
		return s.Mid(left, 1);
	int m = best[left+1][right+1];
	CString Left = recur(left, m, s);
	CString Right = recur(m + 1, right, s);
	if (Left.GetLength() > 1) Left = L"(" + Left + L")";
	if (Right.GetLength() > 1) Right = L"(" + Right + L")";
	return Left + Right;
}


CString CMatrixChainView::recur2(int left,int right, CString s)
{
	// TODO: Add your implementation code here.

	if (left == right)
		return s.Mid(left, 1);
	int m = superBest[left + 1][right + 1];
	CString L = recur2(left, m-2, s), R = recur2(m-1, right, s);
	if (L.GetLength() > 1) L = L"(" + L + L")";
	if (R.GetLength() > 1) R = L"(" + R + L")";
	return L + R;
}

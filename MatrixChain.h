
// MatrixChain.h : main header file for the MatrixChain application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMatrixChainApp:
// See MatrixChain.cpp for the implementation of this class
//

class CMatrixChainApp : public CWinApp
{
public:
	CMatrixChainApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMatrixChainApp theApp;

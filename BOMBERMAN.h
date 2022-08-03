
// BOMBERMAN.h : main header file for the BOMBERMAN application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBOMBERMANApp:
// See BOMBERMAN.cpp for the implementation of this class
//

class CBOMBERMANApp : public CWinApp
{
public:
	CBOMBERMANApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBOMBERMANApp theApp;

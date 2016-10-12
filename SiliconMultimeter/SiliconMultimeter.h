// SiliconMultimeter.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSiliconMultimeterApp:
// See SiliconMultimeter.cpp for the implementation of this class
//

class CSiliconMultimeterApp : public CWinApp
{
public:
	CSiliconMultimeterApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSiliconMultimeterApp theApp;
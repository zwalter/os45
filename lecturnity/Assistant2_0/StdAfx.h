// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma message "Fail on Build... This project is dead. Use 'Studio'...

#if !defined(AFX_STDAFX_H__5DCEF29C_8386_4039_918A_41DB18676998__INCLUDED_)
#define AFX_STDAFX_H__5DCEF29C_8386_4039_918A_41DB18676998__INCLUDED_

#pragma warning(disable: 4018 4244 4996)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0500		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0500		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif	


#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0500 // Change this to the appropriate value to target Windows Me or later.
#endif
					

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#if _MSC_VER > 1200 //MFC 7.0
#include <..\src\mfc\afximpl.h>	// MFC Global data
#else
#include <..\src\afximpl.h>	    // MFC Global data
#endif

#include <gdiplus.h>
#include <XTToolkitPro.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5DCEF29C_8386_4039_918A_41DB18676998__INCLUDED_)


// server1.h : main header file for the SERVER1 application

#if !defined(AFX_SERVER1_H__8BA80188_402F_4B6C_A57D_26200B8730D1__INCLUDED_)
#define AFX_SERVER1_H__8BA80188_402F_4B6C_A57D_26200B8730D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//extern struct filesendinfo zmfile[10];
/////////////////////////////////////////////////////////////////////////////
// CServer1App:
// See server1.cpp for the implementation of this class


//文件信息。
//需要注意的是：此结构体类型的一个变量的尺寸并不一定就是其所有数据成员的大小之和，因为涉及到
//数据对齐的问题，所以，有可能会多出几个字节来。确定结构体的大小的最简单的方法就是用
//sizeof关键字测定一下其大小，绝对准确。
struct filesendinfo
{
	char name[100];
	int length;//INT，32位的数据。所以，应该占四个字节。
	int date;
};

extern struct filesendinfo zmfile[10];

class CServer1App : public CWinApp
{
public:
	CServer1App();
	CString m_strIp;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServer1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CServer1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVER1_H__8BA80188_402F_4B6C_A57D_26200B8730D1__INCLUDED_)

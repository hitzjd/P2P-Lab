
// MainFrm.h : interface of the CMainFrame class

#include "charbar.h"
/////////////////////////////////////////////////////////////////////////////
#define WM_ADDLIST WM_USER+3
#define WM_DELETELIST WM_USER+4
#if !defined(AFX_MAINFRM_H__B6C145B1_EC81_4224_9A31_9AD7D225CC0C__INCLUDED_)
#define AFX_MAINFRM_H__B6C145B1_EC81_4224_9A31_9AD7D225CC0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Online.h"
//#define WM_AGE1 WM_USER+8
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
//
COnLine  m_wndOnline;
charbar m_sendbar;//·¢ËÍ´°¿Ú
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	CStatusBar  m_wndStatusBar;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnRemoveMember(WPARAM wParam, LPARAM lParam);
	afx_msg void OnAddMember(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B6C145B1_EC81_4224_9A31_9AD7D225CC0C__INCLUDED_)

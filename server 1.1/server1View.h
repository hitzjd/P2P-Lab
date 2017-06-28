
// server1View.h : interface of the CServer1View class
//

#include "MainFrm.h"
#include "server1Doc.h"
#include "mysocket.h"
#include "OnlineList.h"
#if !defined(AFX_SERVER1VIEW_H__2AB7A691_0610_454E_9C46_CFDDF1CF7F02__INCLUDED_)
#define AFX_SERVER1VIEW_H__2AB7A691_0610_454E_9C46_CFDDF1CF7F02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
//��ȫ�ֺ���listenthread����������������server1View.cpp�ļ��оͿ���ʹ����������ˡ�
DWORD WINAPI listenthread(LPVOID lpparam);

extern char nameph[10][255];
 
class CServer1View : public CRichEditView
{
protected: // create from serialization only
	CServer1View();
	DECLARE_DYNCREATE(CServer1View)

 
public:
	//�Ҳ£�������������׽��������������족�ģ������������������ļ��õġ�
	mysocket* listensocket;
	mysocket* chatsocket;
	
	CString fname;
	CString fnamepath;
	CServer1Doc* GetDocument();
	CHARFORMAT cfm;//��������RichEdit�ؼ���character formatting attributes��
	int count;//����zmfile������±ꡣ
// Operations
	BOOL m_bStarted;//������¼ �������Ƿ��Ѿ������ˡ�
	BOOL m_chat;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServer1View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL
 
// Implementation
public:
	SOCKET m_sListening;//�����׽��֣������ļ����䣬�������졣
void Message(LPCTSTR lpszMessage,COLORREF clr);
	void recevied();
	void accept();
	virtual ~CServer1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CServer1View)
	afx_msg void OnDestroy();
	afx_msg void OnServerStart();
	afx_msg int addfile();//added by author
	afx_msg LRESULT addmessage(WPARAM wParam, LPARAM lParam);//added by author
	afx_msg void OnSend();
	afx_msg LRESULT OnKSend(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in server1View.cpp
	inline CServer1Doc* CServer1View::GetDocument()
	{ return (CServer1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVER1VIEW_H__2AB7A691_0610_454E_9C46_CFDDF1CF7F02__INCLUDED_)

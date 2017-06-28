
#if !defined(AFX_MYSOCKET_H__22D4A0FD_FBEB_499A_9CF7_C7E72489E91B__INCLUDED_)
#define AFX_MYSOCKET_H__22D4A0FD_FBEB_499A_9CF7_C7E72489E91B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mysocket.h : header file

// mysocket command target
class CServer1View;
//派生了一个异步的套接字类
class mysocket : public CAsyncSocket
{

// Attributes　新的套接字
public:
	CServer1View* CSView;
	char m_buf[255];
// Operations
public:
	mysocket(CServer1View* Ciew);
	virtual ~mysocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(mysocket)
	//}}AFX_VIRTUAL
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	// Generated message map functions
	//{{AFX_MSG(mysocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__22D4A0FD_FBEB_499A_9CF7_C7E72489E91B__INCLUDED_)

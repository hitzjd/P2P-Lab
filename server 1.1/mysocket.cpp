
// mysocket.cpp : implementation file

#include "stdafx.h"
#include "server1.h"
#include "mysocket.h"
#include "server1View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern mysocket* chatsocket;
/////////////////////////////////////////////////////////////////////////////
// mysocket

mysocket::mysocket(CServer1View* Ciew)
{
	CSView=Ciew;
}

mysocket::~mysocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(mysocket, CAsyncSocket)
	//{{AFX_MSG_MAP(mysocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0
void mysocket::OnReceive(int nErrorCode) 
{
	CAsyncSocket::OnReceive(nErrorCode);
	this->Receive(&m_buf,255);

	CString aaa;
	aaa.Format("%s",m_buf);
CSView->Message((LPCTSTR)aaa,RGB(255,0,0));

}
void mysocket::OnAccept(int nErrorCode) 
{
CAsyncSocket::OnAccept(nErrorCode);
 
CSView->accept();
}

/////////////////////////////////////////////////////////////////////////////
// mysocket member functions

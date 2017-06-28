
// mysocket.cpp: implementation of the mysocket class.

#include "stdafx.h"
#include "client1.h"
#include "mysocket.h"
#include "client1View.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
mysocket::mysocket(CClient1View* view2)
{
view=view2;
}

mysocket::~mysocket()
{

}
void mysocket::OnReceive(int nErrorCode) 
{
	
	this->Receive(&m_buf,255);

	CString aaa;
	aaa.Format("%s",m_buf);
//AfxMessageBox(aaa);
view->Message((LPCTSTR)aaa,RGB(0,0,0));
	//this->getpa

}
void mysocket::OnSend(int nErrorCode) 
{

}

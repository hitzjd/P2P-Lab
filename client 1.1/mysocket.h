//Download by http://www.NewXing.com
// mysocket.h: interface for the mysocket class.

#if !defined(AFX_MYSOCKET_H__81129324_3BCD_4730_9FAA_94BBCEADD030__INCLUDED_)
#define AFX_MYSOCKET_H__81129324_3BCD_4730_9FAA_94BBCEADD030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CClient1View;

class mysocket : public CAsyncSocket
{
public:
	CClient1View* view;
	char m_buf[255];
	mysocket(CClient1View* view2);
	virtual ~mysocket();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

#endif // !defined(AFX_MYSOCKET_H__81129324_3BCD_4730_9FAA_94BBCEADD030__INCLUDED_)

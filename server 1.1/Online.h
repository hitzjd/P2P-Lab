
// Online.h: interface for the COnline class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_)
#define AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OnlineList.h"
//The CDialogBar class provides the functionality of a Windows modeless dialog box in a control bar. A dialog bar resembles a dialog box in that it contains standard Windows controls that the user can tab between. Another similarity is that you create a dialog template to represent the dialog bar.
//�Ҳ£������Ӧ����λ���ӵ��·����������Ӵ���֮һ�ģ��Ǹ�������ʾ�������ļ��б����Ӵ��ڡ�
//��Ҫע����ǣ��������Ӵ��ڶ��ǿ������Ӵ��ڣ���������������Ӵ��ڡ�
class COnLine : public CDialogBar
{
// Construction
public:
	COnlineList* m_ListCtrl;//�˳�Ա�������������ƴ˴����е�List�ؼ��õġ�
	COnLine();   // standard constructor
	~COnLine();
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COnLine)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddExStyle();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_)

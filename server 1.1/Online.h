
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
//我猜，此类对应的是位于视的下方的那两个子窗口之一的，那个用来显示“在线文件列表”的子窗口。
//需要注意的是：那两个子窗口都是框架类的子窗口，而并不是视类的子窗口。
class COnLine : public CDialogBar
{
// Construction
public:
	COnlineList* m_ListCtrl;//此成员变量是用来控制此窗口中的List控件用的。
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

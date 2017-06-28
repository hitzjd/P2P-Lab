
// charbar.cpp : implementation file
#include "stdafx.h"
#include "server1.h"
#include "charbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// charbar

charbar::charbar()
{
}

charbar::~charbar()
{
}


BEGIN_MESSAGE_MAP(charbar, CDialogBar)
	//{{AFX_MSG_MAP(charbar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BOOL charbar::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	
		if(GetFocus()->GetDlgCtrlID()==IDC_SEND ||GetFocus()->GetDlgCtrlID()==IDC_EDIT1)
		{
			AfxGetMainWnd()->SendMessageToDescendants(WM_KSEND);
		//	AfxMessageBox("down");
			return TRUE;
			}
	return CDialogBar::PreTranslateMessage(pMsg);
}
/////////////////////////////////////////////////////////////////////////////
// charbar message handlers

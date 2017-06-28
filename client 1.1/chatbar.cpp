
// chatbar.cpp : implementation file

#include "stdafx.h"
#include "client1.h"
#include "chatbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// chatbar

chatbar::chatbar()
{
}

chatbar::~chatbar()
{
}


BEGIN_MESSAGE_MAP(chatbar, CDialogBar)
	//{{AFX_MSG_MAP(chatbar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BOOL chatbar::PreTranslateMessage(MSG* pMsg) 
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
// chatbar message handlers

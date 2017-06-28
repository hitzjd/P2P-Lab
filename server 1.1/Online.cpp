//Download by http://www.NewXing.com
// Online.cpp: implementation of the COnline class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************

/****************************************************************/
#include "stdafx.h"
#include "server1.h"
#include "Online.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COnLine::COnLine()
{
}

COnLine::~COnLine()
{
	delete m_ListCtrl;
}

BEGIN_MESSAGE_MAP(COnLine, CDialogBar)
	//{{AFX_MSG_MAP(COnLine)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnLine message handlers
int COnLine::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
	rect.left += 10;
	rect.top += 15;
	rect.right -= 10;
	rect.bottom -= 10;
	
	m_ListCtrl = new COnlineList;
	if (!m_ListCtrl->Create(WS_CHILD |WS_VISIBLE|LVS_REPORT,
		rect, this, IDC_LIST1))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}
	m_ListCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);

int i,j;

	static struct
	{
		LPSTR psztext;
		int ui;
	}columns[]={
		_T("文件名"),LVCFMT_LEFT,
_T("大小"),LVCFMT_CENTER,
_T("时间"),LVCFMT_CENTER,
	};
	for( i=0,j=260;i<sizeof(columns)/sizeof(columns[0])-1;i++,j-=10)   
		m_ListCtrl->InsertColumn(i,columns[i].psztext,columns[i].ui,j);
m_ListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	return 0;
}

void COnLine::AddExStyle()
{
 
}



void COnLine::OnSize(UINT nType, int cx, int cy) 
{
 
	if(m_ListCtrl->m_hWnd)
		m_ListCtrl->SetWindowPos(this,0,0,cx-15,cy-25,SWP_NOZORDER|SWP_NOMOVE);
	// /TODO: Add your message handler code here

}

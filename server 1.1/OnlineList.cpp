
// OnlineList.cpp : implementation file
//

#include "stdafx.h"
#include "server1.h"
#include "OnlineList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnlineList

COnlineList::COnlineList()
{
}

COnlineList::~COnlineList()
{
}


BEGIN_MESSAGE_MAP(COnlineList, CListCtrl)
	//{{AFX_MSG_MAP(COnlineList)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnlineList message handlers

int COnlineList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

    //加载脸部图案

//	SetBkColor(RGB(0,128,128));

	return 0;
}

void COnlineList::AddItem(filesendinfo* seinfo)
{
	LVITEM			lvi;

	lvi.mask = LVIF_TEXT | LVIF_IMAGE;
	lvi.iItem = GetItemCount();
  //  lvi.iImage = i;
	lvi.iSubItem = 0;
//	lvi.s=0;
	lvi.pszText = "";
	lvi.cchTextMax = 64;
	InsertItem(&lvi);
	SetItemText(lvi.iItem,0,seinfo->name);
CString aaa;
aaa.Format("%d k",seinfo->length/1000);
SetItemText(lvi.iItem,1,aaa.GetBuffer(0));
aaa.ReleaseBuffer();
//	SetItemText(lvi.iItem,2,name);
//	SetItemText(lvi.iItem,3,(char *)m_csPath);
//	SetItemText(lvi.iItem,4,(char *)m_csAttrib);
SetHotItem(lvi.iItem);			//标注当前项目
	EnsureVisible(lvi.iItem,true);	//滚动影响的卷轴
	Update(lvi.iItem);
//strcpy(name1[lvi.iItem],name2);
//strcpy(name1[lvi.iItem+1],"none");
//strcpy(nameph[lvi.iItem],namepath);
//AfxMessageBox(name1[lvi.iItem]);
}

void COnlineList::Remove(char *name)
{
	CString str;
	for(int i = 0; i < GetItemCount(); i++){
		str = GetItemText(i,0);
		if(strcmp(str, name) == 0){
			DeleteItem(i);
			break;
		}
	}
}


void COnlineList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(this->GetItemCount()>10){
		AfxMessageBox("同时最多只支持10个文件");
		
	}
	else{
	CString str;
	int iSel = pNMListView->iItem;
	if (iSel >= 0 ){
		str = GetItemText(iSel,0);
		CWnd* pParentWnd = GetParent();
		while (pParentWnd != NULL){ 
			if (pParentWnd->IsFrameWnd()){
				break;
			}
			pParentWnd = pParentWnd->GetParent();
		}
		if (pParentWnd != NULL)
	       pParentWnd->SendMessage(WM_DBCLICKITEM, 0, (LPARAM)&str);
	}
	}
	*pResult = 0;
}

void COnlineList::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void COnlineList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

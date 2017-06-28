//Download by http://www.NewXing.com
// MainFrm.cpp : implementation of the CMainFrame class
//
/*****************************************************************

//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com

/****************************************************************/
#include "stdafx.h"
#include "server1.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
//	ON_MESSAGE(WM_DELETELIST, OnRemoveMember)
	ON_MESSAGE(WM_ADDLIST, OnAddMember)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//add begin
	//�Ҳ£�����Ĵ����ǣ���������λ���ӵ��·����������Ӵ��ڡ���Ϊ�ڴ��������У���ָ����WS_CHILD���͡�
	//��Ҫע����ǣ��������Ӵ��ڶ��ǿ������Ӵ��ڣ���������������Ӵ��ڡ�
	//���Ӵ���ָ���˶Ի���ģ����ԴIDD_DIALOG1 !
	//����������ʾ�������ļ��б����Ӵ��ڡ�
	if (!m_wndOnline.Create(this, IDD_DIALOG1, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
	 | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED,IDD_ABOUTBOX))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}
	//���Ӵ���ָ���˶Ի���ģ����ԴIDD_DIALOG2 !
	if (!m_sendbar.Create(this, IDD_DIALOG2, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, IDD_ABOUTBOX))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}
	//add end

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	
	//add begin
	//ûʲô�ر�Ķ�����
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_sendbar.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_sendbar, AFX_IDW_DOCKBAR_BOTTOM);
	m_sendbar.SetWindowText(_TEXT("���ʹ���"));

	

	m_wndOnline.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndOnline, AFX_IDW_DOCKBAR_BOTTOM);
	m_wndOnline.SetWindowText(_TEXT("�����б�"));

	
   //ShowControlBar(&m_wndOnline,TRUE,TRUE);
	//add end

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//add begin
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	cs.cx=GetSystemMetrics(SM_CXSCREEN);
	cs.cy=GetSystemMetrics(SM_CYSCREEN);
	//add end
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

 


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//add begin
void CMainFrame::OnAddMember(WPARAM wParam, LPARAM lParam)
{
	//filesendinfo�������Զ����һ���ṹ��
	filesendinfo* pStr = (filesendinfo*)wParam;
	//����COnlineList::AddItem����������һ�������Լ���д���ࡣ
	m_wndOnline.m_ListCtrl->AddItem(pStr);
}
//add end

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
 
	// �յģ�
	
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

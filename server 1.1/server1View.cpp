
// server1View.cpp : implementation of the CServer1View class
//

#include "stdafx.h"
#include "server1.h"
//#include "OnlineList.h"
#include "server1Doc.h"
#include "CntrItem.h"
#include "server1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServer1View

IMPLEMENT_DYNCREATE(CServer1View, CRichEditView)

BEGIN_MESSAGE_MAP(CServer1View, CRichEditView)
	//{{AFX_MSG_MAP(CServer1View)
	ON_WM_DESTROY()
	ON_COMMAND(ID_STAR, OnServerStart)
	ON_COMMAND(ID_ADD, addfile)
	ON_MESSAGE(WM_AGE1, addmessage)
	ON_COMMAND(IDC_SEND, OnSend)
	ON_MESSAGE(WM_KSEND,OnKSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServer1View construction/destruction
LRESULT CServer1View::OnKSend(WPARAM wParam,LPARAM lParam)
{
	OnSend();
	return 0;
}

//此函数对应于聊天子窗口中的“发送”按钮。
void CServer1View::OnSend() 
{	
	//发消息
    CMainFrame* pWnd=(CMainFrame*)AfxGetMainWnd();
	CEdit* pEdit=(CEdit*)pWnd->m_sendbar.GetDlgItem(IDC_EDIT1);
	CString temp;
	pEdit->GetWindowText(temp);
	if(temp.IsEmpty())
	{
		MessageBox("不能发送空信息!!!","警告");
		pEdit->SetFocus();
		return;
	}
	
	if(!m_chat)
	{
		MessageBox("暂无客户端！！！","警告");
		pEdit->SetFocus();
		return;
	}
	temp="服务端: "+temp;
	temp=temp+"\n";
	Message((LPCTSTR)temp,RGB(255,0,0));
	chatsocket->Send(temp.GetBuffer(0),255);

	temp.ReleaseBuffer();
	pWnd->m_sendbar.GetDlgItem(IDC_EDIT1)->SetFocus();
	pEdit->SetWindowText("");
}

CServer1View::CServer1View()
	: m_chat(FALSE)
	, m_bStarted(FALSE)
	, count(0)
{
	// TODO: add construction code here
	//zmfile全局变量(是一个结构体数组)是由头文件server1.h引入这里的。
	strcpy(zmfile[0].name,"none");
}

//显示信息
LRESULT CServer1View::addmessage(WPARAM wParam, LPARAM lParam)
{
//	MessageBox("aaa");
	LPCTSTR pStr = (LPCTSTR)wParam;
	Message(pStr,RGB(0,0,0));
	return 1;
}

CServer1View::~CServer1View()
{
}

BOOL CServer1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

//CRichEditView::OnInitialUpdate  Called by the framework after the view is first attached to the document, but before the view is initially displayed.
void CServer1View::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	//add begin
	cfm.cbSize=sizeof(cfm);
	cfm.bCharSet=GB2312_CHARSET;
	cfm.crTextColor=RGB(0,0,0);//黑色
	cfm.dwMask=CFM_CHARSET | CFM_COLOR ;
	cfm.dwEffects=0;
	//CRichEditView::GetRichEditCtrl  Call this function to retrieve the CRichEditCtrl object associated with the CRichEditView object.
	//此函数的原型是：CRichEditCtrl& GetRichEditCtrl( ) const; 我对此函数比较熟悉，在微软的WordPad程序中经常用到此函数。
	//CRichEditCtrl::SetDefaultCharFormat  Sets the character formatting attributes for new text in this CRichEditCtrl object.
	GetRichEditCtrl().SetDefaultCharFormat(cfm);
	//add end

	SetMargins(CRect(720, 720, 720, 720));
}

void CServer1View::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
	CRichEditView::OnDestroy();
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
	{
		pActiveItem->Deactivate();
		ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	}

}


/////////////////////////////////////////////////////////////////////////////
// CServer1View diagnostics

#ifdef _DEBUG
void CServer1View::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CServer1View::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CServer1Doc* CServer1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServer1Doc)));
	return (CServer1Doc*)m_pDocument;
}
#endif //_DEBUG

//用此函数，在RichEdit控件中的文本的最后位置，插入指定颜色的一个字符串。
void CServer1View::Message(LPCTSTR lpszMessage,COLORREF clr)
{
	//在窗口中显示聊天信息
	cfm.cbSize=sizeof(cfm);
	cfm.crTextColor=clr;
	cfm.dwMask=CFM_COLOR;
	CString strTemp = lpszMessage;
	
	int len = GetWindowTextLength();
	//因为在上面的一句代码中，已经将len的值设定为整个文本串的长度，所以，下面的这一句代码的
	//作用就是：将当前位置设定到RichEdit控件中的整个文本串的最后。
	GetRichEditCtrl().SetSel(len,len);
	//这一句的作用是：设置以后新添加的文本的颜色。
	GetRichEditCtrl().SetSelectionCharFormat(cfm);
	//替换选中的文本，但是由于并没有文本被选中，所以，这一句代码的作用其实就是：
	//在当前位置插入一个串。
	GetRichEditCtrl().ReplaceSel(strTemp);
}

BOOL  CServer1View::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		if(GetFocus()->GetDlgCtrlID()==IDC_SEND ||GetFocus()->GetDlgCtrlID()==IDC_EDIT1)
		{
		//	AfxGetMainWnd()->SendMessageToDescendants(WM_KSEND);
			AfxMessageBox("down");
			return TRUE;
		}
	}	   

	return CRichEditView::PreTranslateMessage(pMsg);
}

//加文件到服务器中
int CServer1View::addfile()
{
	//If your application is an OLE server, call this function to retrieve a pointer to the active main window of the application instead of directly referring to the m_pMainWnd member of the application object.
	//If your application is not an OLE server, then calling this function is equivalent to directly referring to the m_pMainWnd member of your application object.
	//m_wndOnline是CMainFrame类的成员。
	//超过8个，就是9个了。
	if(((CMainFrame*)::AfxGetMainWnd())->m_wndOnline.m_ListCtrl->GetItemCount()>8)
	{
		AfxMessageBox("同时最多只支持9个文件");
		return 0;		
	}

	CFileDialog cfiledlg(TRUE,NULL,NULL);

	if(cfiledlg.DoModal()==IDCANCEL)//IDOK
		return 0;
	//fnamepath是CServer1View类的数据成员。
	fnamepath=cfiledlg.GetPathName();

	CFile myFile;
	//在CFile::CFile 的解释页中找到下面的解释：
	//CFile::modeRead   Opens the file for reading only. 
	//CFile::typeBinary   Sets binary mode (used in derived classes only).有什么用？？？
	//CFile::shareDenyNone   Opens the file without denying other processes read or write access to the file. Create fails if the file has been opened in compatibility mode by any other process. 
	myFile.Open(fnamepath, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone); 
	//CFile::GetLength  Obtains the current logical length of the file in bytes, not the amount.
	//保存文件长度到zmfile数组的第count个元素中。
	zmfile[count].length=myFile.GetLength();//文件的logical length跟amount有什么不同？
	myFile.Close();
 
	//这个for循环是用来搜索List控件，看看用户这一次选择要打开的文件，是否已经在List中存在了。
	//如果已经存在了，就提前退出for循环。
	for(int j=0;j<((CMainFrame*)::AfxGetMainWnd())->m_wndOnline.m_ListCtrl->GetItemCount();j++)
	{
		if(nameph[j]==fnamepath)
			break;
	}
	//条件成立，就说明是提前退出上面的for循环的。
	if((j+1)<=((CMainFrame*)::AfxGetMainWnd())->m_wndOnline.m_ListCtrl->GetItemCount())
	{
		AfxMessageBox("文件同名，不可加入！");
		return 0;
	}

	if(zmfile[count].length<=0)
	{
		AfxMessageBox("文件大小为零，不可加入！");
		return 0;
	}

	//如果服务器还没启动，则
	if(!m_bStarted)
	{
		::MessageBox(NULL,"服务器还没启动，请先启动服务器，然后再添加文件！","",0);
		return 0;
	}

	//保存文件名到zmfile数组的第count个元素中。
	strcpy(zmfile[count].name,cfiledlg.GetFileName());

	//向主窗口发送WM_ADDLIST自定义消息，这样，会导致CMainFrame::OnAddMember消息处理函数被调用。
	AfxGetMainWnd()->SendMessage(WM_ADDLIST, (LPARAM)&zmfile[count],1);

	CString aaa;
	aaa.Format("加入文件  %s",zmfile[count].name);
	aaa+='\n';
	//在RichEdit控件中的文本的末尾，插入黑色的字符串aaa。
	Message(aaa,RGB(0,0,0));

	//下面的这句代码，是用来初始化数组中下一个可用元素，文件名设置为“none”，路径设置为
	//上一个数组元素的文件的路径，对，就应该这么设计。
	strcpy(zmfile[count+1].name,"none");

	//这个二维数组nameph是用来存储加到List控件中的文件的全路径用的。
	//Attention：此数组的下标用的是count，而并不是count+1，这跟上一句代码是不同的！
	strcpy(nameph[count],fnamepath);

	//对，因为刚刚添加了一个新的元素，所以数组元素的下标要增加一个值。
	count++;

	return 1;
}

void CServer1View::OnServerStart() 
{
	BOOL bReturn=0;
	//如果服务器尚没被启动，则
	if(!m_bStarted)
	{
		//启动服务器

		listensocket=new mysocket(this);
		//CAsyncSocket::Create  Call the Create member function after constructing a socket object to create the Windows socket and attach it.
		//Return Value  Nonzero if the function is successful; otherwise 0, and a specific error code can be retrieved by calling GetLastError.
		//第一个参数：A well-known port to be used with the socket, or 0 if you want Windows Sockets to select a port. 
		//bReturn=listensocket->Create(8888);//这个端口是用来接受来自客户端的聊天请求用的。
		bReturn=listensocket->Create(7777);//这个端口是用来接受来自客户端的聊天请求用的.
		if(bReturn==0)
			::MessageBox(NULL,"执行 listensocket->Create(8888); 出错","",0);
		//CAsyncSocket::Listen  Call this member function to listen for incoming connection requests.
		//Return Value  Nonzero if the function is successful; otherwise 0, and a specific error code can be retrieved by calling GetLastError. 
		bReturn=listensocket->Listen();
		if(bReturn==0)
			::MessageBox(NULL,"执行 listensocket->Listen(); 出错","",0);
		CMainFrame* pWnd=(CMainFrame*)AfxGetMainWnd();
		CServer1App* pApp=(CServer1App*)AfxGetApp();
		DWORD dwthread;
		sockaddr_in local;
		//socket1是一个局部变量。需要注意的是：虽然此变量是一个局部变量，但是，此变量所指向的
		//新创建的socket却并不是一个局部的对象，除非你调用closesocket函数关闭它，否则它会
		//一直存在，直至进程结束。
		//经过考证，发现SOCKET原来就是UINT_PTR数据类型，这是一个无符号指针类型。
//		SOCKET socket1;
		int rc=0;
		local.sin_family=AF_INET;
		//作者所设置的端口是1028，结果，我发现出错，所以，我决定，改成3962试试看。成功了！
		local.sin_port=htons(3962);
		//IP地址设置成INADDR_ANY，表示：要让系统自动获取本机的IP地址。
		local.sin_addr.S_un.S_addr=INADDR_ANY;
		//调用WinSock API函数，创建了一个流式的socket，就保存在上数5行代码处定义的局部变量中。
		//If no error occurs, socket function returns a descriptor referencing the new socket. Otherwise, a value of INVALID_SOCKET is returned, and a specific error code can be retrieved by calling WSAGetLastError.
		//不过，我感到奇怪的是，为什么不接着使用mysocket类，却改用WinSock API函数呢？
		//答：上面的mysocket类是用来聊天用的，是异步的；而下面的socket是用来传送文件用的，是同步的socket；
		m_sListening=socket(AF_INET,SOCK_STREAM,0);
		if(m_sListening==INVALID_SOCKET)
			::MessageBox(NULL,"执行 socket(AF_INET,SOCK_STREAM,0); 出错","",0);
		//执行到下面一句出错了，返回的是错误信息，为什么出错呢？
		//答：因为发生了端口冲突。我把端口号改成3962就不出错了。
		//调用WinSock API函数，The bind function associates a local address with a socket.
		//If no error occurs, bind returns zero. Otherwise, it returns SOCKET_ERROR, and a specific error code can be retrieved by calling WSAGetLastError.
		rc=bind(m_sListening,(LPSOCKADDR)&local,sizeof(local));
		//如果绑定IP地址和端口出错，则
		//		if(!(rc==SOCKET_ERROR))//测试代码
		if(rc==SOCKET_ERROR)
		{
			int iErrorCode;
			char str1[100];
			CString aaa;
			aaa="Bind错误\n";
			iErrorCode=WSAGetLastError();//WSAENETDOWN
			/*
			// MessageId: WSAEADDRINUSE
			//
			// MessageText:
			//
			//  Only one usage of each socket address (protocol/network address/port) is normally permitted.
			//
			#define WSAEADDRINUSE                    10048L
			*/
			sprintf(str1,"bind函数返回的错误代码是:%d",iErrorCode);
			::MessageBox(NULL,str1,"",0);
			//因为用来显示出错信息的View窗口是MainFrame窗口的子窗口，所以，就用了这么一个名字(xxxDescendants)
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			aaa.ReleaseBuffer();
			return;//added by yjk
		}

		HANDLE hThread; 
		//The CreateThread function creates a thread to execute within the virtual address space of the calling process. 
		//线程函数是：listenthread；传给线程函数的参数是：m_sListening；
		//最后的一个参数是：[out] Pointer to a variable that receives the thread identifier. 
		//dwthread是本函数内定义的局部变量。
		//启动一个新线程，其参数m_sListening就是监听socket。
		hThread=::CreateThread(NULL,0,listenthread,(LPVOID)m_sListening,0,&dwthread);
		// Check the return value for success. 
		if (hThread == NULL) 
		{
			char szMsg[80];
			wsprintf( szMsg, "CreateThread failed." ); 
			::MessageBox( NULL, szMsg, "OnServerStart()", MB_OK );
		}
		else 
		{
			CloseHandle( hThread );

			CString aaa;
			aaa="服务器启动！\n";
			Message(aaa.GetBuffer(0),RGB(0,0,0));
			aaa.ReleaseBuffer();
			CString strT;
			strT="P2P文件传输服务器";
			pApp->m_pMainWnd->SetWindowText(strT);
			m_bStarted=TRUE;
		}

	}
	else
	{
		CString aaa;
		aaa="服务器在以前已经被启动了，无需再启动了！\n";
		Message(aaa.GetBuffer(0),RGB(0,0,0));
		aaa.ReleaseBuffer();
	}
}



/////////////////////////////////////////////////////////////////////////////
// CServer1View message handlers
//接受用户
void CServer1View::accept()
{
	chatsocket=new mysocket(this);
	listensocket->Accept(*chatsocket);
	m_chat=TRUE;
}

void CServer1View::recevied()
{

}



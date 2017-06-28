
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

//�˺�����Ӧ�������Ӵ����еġ����͡���ť��
void CServer1View::OnSend() 
{	
	//����Ϣ
    CMainFrame* pWnd=(CMainFrame*)AfxGetMainWnd();
	CEdit* pEdit=(CEdit*)pWnd->m_sendbar.GetDlgItem(IDC_EDIT1);
	CString temp;
	pEdit->GetWindowText(temp);
	if(temp.IsEmpty())
	{
		MessageBox("���ܷ��Ϳ���Ϣ!!!","����");
		pEdit->SetFocus();
		return;
	}
	
	if(!m_chat)
	{
		MessageBox("���޿ͻ��ˣ�����","����");
		pEdit->SetFocus();
		return;
	}
	temp="�����: "+temp;
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
	//zmfileȫ�ֱ���(��һ���ṹ������)����ͷ�ļ�server1.h��������ġ�
	strcpy(zmfile[0].name,"none");
}

//��ʾ��Ϣ
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
	cfm.crTextColor=RGB(0,0,0);//��ɫ
	cfm.dwMask=CFM_CHARSET | CFM_COLOR ;
	cfm.dwEffects=0;
	//CRichEditView::GetRichEditCtrl  Call this function to retrieve the CRichEditCtrl object associated with the CRichEditView object.
	//�˺�����ԭ���ǣ�CRichEditCtrl& GetRichEditCtrl( ) const; �ҶԴ˺����Ƚ���Ϥ����΢���WordPad�����о����õ��˺�����
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

//�ô˺�������RichEdit�ؼ��е��ı������λ�ã�����ָ����ɫ��һ���ַ�����
void CServer1View::Message(LPCTSTR lpszMessage,COLORREF clr)
{
	//�ڴ�������ʾ������Ϣ
	cfm.cbSize=sizeof(cfm);
	cfm.crTextColor=clr;
	cfm.dwMask=CFM_COLOR;
	CString strTemp = lpszMessage;
	
	int len = GetWindowTextLength();
	//��Ϊ�������һ������У��Ѿ���len��ֵ�趨Ϊ�����ı����ĳ��ȣ����ԣ��������һ������
	//���þ��ǣ�����ǰλ���趨��RichEdit�ؼ��е������ı��������
	GetRichEditCtrl().SetSel(len,len);
	//��һ��������ǣ������Ժ�����ӵ��ı�����ɫ��
	GetRichEditCtrl().SetSelectionCharFormat(cfm);
	//�滻ѡ�е��ı����������ڲ�û���ı���ѡ�У����ԣ���һ������������ʵ���ǣ�
	//�ڵ�ǰλ�ò���һ������
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

//���ļ�����������
int CServer1View::addfile()
{
	//If your application is an OLE server, call this function to retrieve a pointer to the active main window of the application instead of directly referring to the m_pMainWnd member of the application object.
	//If your application is not an OLE server, then calling this function is equivalent to directly referring to the m_pMainWnd member of your application object.
	//m_wndOnline��CMainFrame��ĳ�Ա��
	//����8��������9���ˡ�
	if(((CMainFrame*)::AfxGetMainWnd())->m_wndOnline.m_ListCtrl->GetItemCount()>8)
	{
		AfxMessageBox("ͬʱ���ֻ֧��9���ļ�");
		return 0;		
	}

	CFileDialog cfiledlg(TRUE,NULL,NULL);

	if(cfiledlg.DoModal()==IDCANCEL)//IDOK
		return 0;
	//fnamepath��CServer1View������ݳ�Ա��
	fnamepath=cfiledlg.GetPathName();

	CFile myFile;
	//��CFile::CFile �Ľ���ҳ���ҵ�����Ľ��ͣ�
	//CFile::modeRead   Opens the file for reading only. 
	//CFile::typeBinary   Sets binary mode (used in derived classes only).��ʲô�ã�����
	//CFile::shareDenyNone   Opens the file without denying other processes read or write access to the file. Create fails if the file has been opened in compatibility mode by any other process. 
	myFile.Open(fnamepath, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone); 
	//CFile::GetLength  Obtains the current logical length of the file in bytes, not the amount.
	//�����ļ����ȵ�zmfile����ĵ�count��Ԫ���С�
	zmfile[count].length=myFile.GetLength();//�ļ���logical length��amount��ʲô��ͬ��
	myFile.Close();
 
	//���forѭ������������List�ؼ��������û���һ��ѡ��Ҫ�򿪵��ļ����Ƿ��Ѿ���List�д����ˡ�
	//����Ѿ������ˣ�����ǰ�˳�forѭ����
	for(int j=0;j<((CMainFrame*)::AfxGetMainWnd())->m_wndOnline.m_ListCtrl->GetItemCount();j++)
	{
		if(nameph[j]==fnamepath)
			break;
	}
	//������������˵������ǰ�˳������forѭ���ġ�
	if((j+1)<=((CMainFrame*)::AfxGetMainWnd())->m_wndOnline.m_ListCtrl->GetItemCount())
	{
		AfxMessageBox("�ļ�ͬ�������ɼ��룡");
		return 0;
	}

	if(zmfile[count].length<=0)
	{
		AfxMessageBox("�ļ���СΪ�㣬���ɼ��룡");
		return 0;
	}

	//�����������û��������
	if(!m_bStarted)
	{
		::MessageBox(NULL,"��������û����������������������Ȼ��������ļ���","",0);
		return 0;
	}

	//�����ļ�����zmfile����ĵ�count��Ԫ���С�
	strcpy(zmfile[count].name,cfiledlg.GetFileName());

	//�������ڷ���WM_ADDLIST�Զ�����Ϣ���������ᵼ��CMainFrame::OnAddMember��Ϣ�����������á�
	AfxGetMainWnd()->SendMessage(WM_ADDLIST, (LPARAM)&zmfile[count],1);

	CString aaa;
	aaa.Format("�����ļ�  %s",zmfile[count].name);
	aaa+='\n';
	//��RichEdit�ؼ��е��ı���ĩβ�������ɫ���ַ���aaa��
	Message(aaa,RGB(0,0,0));

	//����������룬��������ʼ����������һ������Ԫ�أ��ļ�������Ϊ��none����·������Ϊ
	//��һ������Ԫ�ص��ļ���·�����ԣ���Ӧ����ô��ơ�
	strcpy(zmfile[count+1].name,"none");

	//�����ά����nameph�������洢�ӵ�List�ؼ��е��ļ���ȫ·���õġ�
	//Attention����������±��õ���count����������count+1�������һ������ǲ�ͬ�ģ�
	strcpy(nameph[count],fnamepath);

	//�ԣ���Ϊ�ո������һ���µ�Ԫ�أ���������Ԫ�ص��±�Ҫ����һ��ֵ��
	count++;

	return 1;
}

void CServer1View::OnServerStart() 
{
	BOOL bReturn=0;
	//�����������û����������
	if(!m_bStarted)
	{
		//����������

		listensocket=new mysocket(this);
		//CAsyncSocket::Create  Call the Create member function after constructing a socket object to create the Windows socket and attach it.
		//Return Value  Nonzero if the function is successful; otherwise 0, and a specific error code can be retrieved by calling GetLastError.
		//��һ��������A well-known port to be used with the socket, or 0 if you want Windows Sockets to select a port. 
		//bReturn=listensocket->Create(8888);//����˿��������������Կͻ��˵����������õġ�
		bReturn=listensocket->Create(7777);//����˿��������������Կͻ��˵����������õ�.
		if(bReturn==0)
			::MessageBox(NULL,"ִ�� listensocket->Create(8888); ����","",0);
		//CAsyncSocket::Listen  Call this member function to listen for incoming connection requests.
		//Return Value  Nonzero if the function is successful; otherwise 0, and a specific error code can be retrieved by calling GetLastError. 
		bReturn=listensocket->Listen();
		if(bReturn==0)
			::MessageBox(NULL,"ִ�� listensocket->Listen(); ����","",0);
		CMainFrame* pWnd=(CMainFrame*)AfxGetMainWnd();
		CServer1App* pApp=(CServer1App*)AfxGetApp();
		DWORD dwthread;
		sockaddr_in local;
		//socket1��һ���ֲ���������Ҫע����ǣ���Ȼ�˱�����һ���ֲ����������ǣ��˱�����ָ���
		//�´�����socketȴ������һ���ֲ��Ķ��󣬳��������closesocket�����ر�������������
		//һֱ���ڣ�ֱ�����̽�����
		//������֤������SOCKETԭ������UINT_PTR�������ͣ�����һ���޷���ָ�����͡�
//		SOCKET socket1;
		int rc=0;
		local.sin_family=AF_INET;
		//���������õĶ˿���1028��������ҷ��ֳ������ԣ��Ҿ������ĳ�3962���Կ����ɹ��ˣ�
		local.sin_port=htons(3962);
		//IP��ַ���ó�INADDR_ANY����ʾ��Ҫ��ϵͳ�Զ���ȡ������IP��ַ��
		local.sin_addr.S_un.S_addr=INADDR_ANY;
		//����WinSock API������������һ����ʽ��socket���ͱ���������5�д��봦����ľֲ������С�
		//If no error occurs, socket function returns a descriptor referencing the new socket. Otherwise, a value of INVALID_SOCKET is returned, and a specific error code can be retrieved by calling WSAGetLastError.
		//�������Ҹе���ֵ��ǣ�Ϊʲô������ʹ��mysocket�࣬ȴ����WinSock API�����أ�
		//�������mysocket�������������õģ����첽�ģ��������socket�����������ļ��õģ���ͬ����socket��
		m_sListening=socket(AF_INET,SOCK_STREAM,0);
		if(m_sListening==INVALID_SOCKET)
			::MessageBox(NULL,"ִ�� socket(AF_INET,SOCK_STREAM,0); ����","",0);
		//ִ�е�����һ������ˣ����ص��Ǵ�����Ϣ��Ϊʲô�����أ�
		//����Ϊ�����˶˿ڳ�ͻ���ҰѶ˿ںŸĳ�3962�Ͳ������ˡ�
		//����WinSock API������The bind function associates a local address with a socket.
		//If no error occurs, bind returns zero. Otherwise, it returns SOCKET_ERROR, and a specific error code can be retrieved by calling WSAGetLastError.
		rc=bind(m_sListening,(LPSOCKADDR)&local,sizeof(local));
		//�����IP��ַ�Ͷ˿ڳ�����
		//		if(!(rc==SOCKET_ERROR))//���Դ���
		if(rc==SOCKET_ERROR)
		{
			int iErrorCode;
			char str1[100];
			CString aaa;
			aaa="Bind����\n";
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
			sprintf(str1,"bind�������صĴ��������:%d",iErrorCode);
			::MessageBox(NULL,str1,"",0);
			//��Ϊ������ʾ������Ϣ��View������MainFrame���ڵ��Ӵ��ڣ����ԣ���������ôһ������(xxxDescendants)
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			aaa.ReleaseBuffer();
			return;//added by yjk
		}

		HANDLE hThread; 
		//The CreateThread function creates a thread to execute within the virtual address space of the calling process. 
		//�̺߳����ǣ�listenthread�������̺߳����Ĳ����ǣ�m_sListening��
		//����һ�������ǣ�[out] Pointer to a variable that receives the thread identifier. 
		//dwthread�Ǳ������ڶ���ľֲ�������
		//����һ�����̣߳������m_sListening���Ǽ���socket��
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
			aaa="������������\n";
			Message(aaa.GetBuffer(0),RGB(0,0,0));
			aaa.ReleaseBuffer();
			CString strT;
			strT="P2P�ļ����������";
			pApp->m_pMainWnd->SetWindowText(strT);
			m_bStarted=TRUE;
		}

	}
	else
	{
		CString aaa;
		aaa="����������ǰ�Ѿ��������ˣ������������ˣ�\n";
		Message(aaa.GetBuffer(0),RGB(0,0,0));
		aaa.ReleaseBuffer();
	}
}



/////////////////////////////////////////////////////////////////////////////
// CServer1View message handlers
//�����û�
void CServer1View::accept()
{
	chatsocket=new mysocket(this);
	listensocket->Accept(*chatsocket);
	m_chat=TRUE;
}

void CServer1View::recevied()
{

}



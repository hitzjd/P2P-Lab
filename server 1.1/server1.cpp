
// server1.cpp : Defines the class behaviors for the application.

#include "stdafx.h"
#include "server1.h"
#include "mysocket.h"
#include "MainFrm.h"
#include "server1Doc.h"
#include "server1View.h"
#include "linkctrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServer1App
#define SIZE                            20480
BEGIN_MESSAGE_MAP(CServer1App, CWinApp)
	//{{AFX_MSG_MAP(CServer1App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServer1App construction

CServer1App::CServer1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CServer1App object
DWORD WINAPI clientthread(LPVOID lpparam);
//��ά���飬��һά��10����Ӧ���Ǹ�����Ԫ�أ��ڶ�ά��һ���ַ�����
//�����ά�����������洢�ӵ�List�ؼ��еĸ����ļ���ȫ·���õġ�
char nameph[10][255];
 
CServer1App theApp;

//�ļ���Ϣ
struct fileinfo
{
	int fileno;//�ļ���
	int type;//��Ϣ�����������Ч��ȡֵ��0��2 //�ͻ�����˵ʲô��ǰ�������仰����1,2��ʾ��
	long len;//�ļ�����
	int seek;//��ʼλ��
	char name[100];//�ļ���
};

int sendn(SOCKET fd,char *bp,int len);


//Ӧ�ò���Visual C++ʵ�������ϵ�д���-������ƪ-����Դ��-��8�µ����ݣ����������߳�
//����Ӧ����ô��ƲŶԡ�
//��������������һ���̺߳�������ʵ���Ҿ��ò�Ӧ�óƴ˺�������Ӧ���߳�Ϊ�������̡߳�����Ϊ����
//ֻ��һ�����õĹ��̣�����listen�������������̾Ϳ�ʼ�ˡ�Ӧ�ó���Ϊ��ѭ���ȴ������̡߳����á�
DWORD WINAPI listenthread(LPVOID lpparam)
{	
	//����lpparamָ�����һ��socket�����socket�����������ͻ��˵����������õġ�
	SOCKET  sListening=(SOCKET)lpparam;
	//�ô��ݽ����Ĳ�����ָ���socket���м�����������ܵ������������30��
	//The listen function places a socket a state where it is listening for an incoming connection.
	//Return Values  If no error occurs, listen returns zero. Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling WSAGetLastError.
	//����������ò��ᷢ��������ֻ��accept�������òŻ�������
	int rc=listen(sListening,30);

	if(rc==SOCKET_ERROR)
	{
		CString aaa;
		aaa="listen����\n";
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		return 0;
	}

	//������������ѭ�������Ͻ������Կͻ��˵��������󡣶���ÿһ������socket����Ϊ������һ��
	//�������̣߳���Ҫע����ǣ����̺߳�����clientthread���������Ǳ������̺߳�����
	//�Ҹо�����Ĵ������������ѽ����ô�˳������ѭ���أ����������߳�������������
	//Ӧ�ò���Visual C++ʵ�������ϵ�д���-������ƪ-��8�µ����ݣ������ȴ����ӵ��̵߳���Ӧ����ô��ƲŶԡ�
	while(1)
	{
		//sConnect��һ���ֲ���������Ҫע����ǣ���Ȼ�˱�����һ���ֲ����������ǣ��˱�����ָ���
		//�´�����socketȴ������һ���ֲ��Ķ��󣬳��������closesocket�����ر�������������
		//һֱ���ڣ�ֱ�����̽�����
		//������֤������SOCKETԭ������UINT_PTR�������ͣ�����һ���޷���ָ�����͡�
		//��һ�����⣬��whileѭ���У�����ִ�����������룬�����������ֲ���sConnect������
		//������һ������������һ�¡�
		//�𣺾������ԣ����ֲ�û����ÿһ��ѭ����ʱ�򶼲�����һ���µľֲ�������������ʼ�ն�
		//ֻ��һ���ֲ�����sConnect���˱����ĵ�ַʼ�ղ��䡣
		SOCKET sConnect;

		//��һ��������[in] Descriptor identifying a socket that has been placed in a listening state with the listen function. The connection is actually made with the socket that is returned by accept. 
		//����ֵ��If no error occurs, accept returns a value of type SOCKET that is a descriptor for the new socket. This returned value is a handle for the socket on which the actual connection is made.
		//����ִ�е�����������������û�пͻ��˵�������������
		sConnect=accept(sListening,NULL,NULL);

		if(sConnect==INVALID_SOCKET)
		{
			//�����ҵĲ��Է��֣����ҵ���closesocket�����رռ���socket��ʱ�����̻�ִ�е�
			//�������������ǣ����ڽ��̻���ű��жϣ����ԣ�Message Boxֻ��һ���ͱ��ر��ˣ�����
			//�Ǹ�������һ�¶�û�У����̾ͽ����ˡ�
			char szTemp[10];
			sprintf(szTemp,"123456789 ErrorCode=%d",WSAGetLastError());
			::MessageBox(NULL,szTemp,"",0);
//			continue;
			return -1;//������ƶ����Ҳ���ȷ����
		}

		CString aa;
		aa="һ�����룡\n";
		//����һ��mfc������Call this member function to send the specified Windows message to all descendant windows.
		//�ڱ������е������ǣ��Ѵ�aa�����ݣ���RichEdit�ؼ�����ʾ������
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aa.GetBuffer(0),1);
		aa.ReleaseBuffer();

		DWORD dwThread;
		//�����ﴴ����һ���µ��̣߳�����Ҫע����ǣ���һ�ε��̺߳������ˣ������clientthread��
		//����߳�����������ͻ��˵������õ��̡߳�
		//�ڡ�VC ʵ������� ������ƪ���ĵ�8�µ������У����õ����߳����̵߳���Ʒ�����
		//�Ҹ��˸о������ֲ��Ƕ�׵���Ʒ�������̫�ã�������������ѭ������Ʒ��������أ�
		//��֪�ҵĸо��Ƿ���ȷ����˭�ܸ���������������ʲô������������
		::CreateThread(NULL,0,clientthread,(LPVOID)sConnect,0,&dwThread);	
	}

	return 0;
}

//�ӿͻ��˶�ȡ���ݵĺ�����
//����1�������׽��֣�����2��ָ�򻺳�����ָ�룻����3���������ĳ��ȣ�
int readn(SOCKET fd,char *bp,int len)
{
	int cnt;//������¼�������е�ʣ����ÿռ䡣
	int rc;
	cnt=len;
	while(cnt>0)
	{
		//Platform SDK: Windows Sockets  The recv function receives data from a connected or bound socket.
		//Return Values  If no error occurs, recv returns the number of bytes received. If the connection has been gracefully closed, the return value is zero. Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling WSAGetLastError.
		//cnt������ֵ���趨Ϊ�������ĳ���ֵ�����ԣ��������ٶ��㹻�õ�����£���ȡcnt��ô
		//����ֽڣ�û���⡣�����Ļ�����whileѭ��ֻ��Ҫִ��һ�ξͻ������˳��ˡ��Ӷ�����Ҳ
		//������whileѭ�������ã����ǣ�������֤һ��Ҫ��ȡcnt��ô����ֽڣ�����������
		//�����ض���ֱ���������ˣ������Ǵ����ӱ��رյ��ˡ�
		//����һ�����ʣ�����ͻ���ֻ������50���ֽڵ����ݣ�����ô���أ���ʵ��������⣬ֻ��Ҫ�鵽���ʵ����ϣ��Ϳ������ɽ���������κε��Ѷȿ��ԡ�
		//��??????
		rc=recv(fd,bp,cnt,0);

		if(rc==SOCKET_ERROR)
		{
			CString aa;
			aa="���մ���\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aa.GetBuffer(0),1);
			aa.ReleaseBuffer();
			return -1;
		}

		//If the connection has been gracefully closed, the return value is zero.
		if(rc==0) 
			return len-cnt;
		//��ȡ��һЩ����֮�󣬻�����ָ��ҲӦ����Ӧ�����ӡ�
		bp+=rc;
		//��ȡ��һЩ����֮�󣬻������е�ʣ����ÿռ�ҲӦ����Ӧ�ؼ�С��
		cnt-=rc;
	}
	return len;
}

filesendinfo zmfile[10];//��¼�ļ�������һ���ṹ�����顣
#define SIZE_OF_zmfile 1080

//��ͻ��˷������ݵĺ�����
//����1������socket������2��������ָ�룻����3��Ҫ���͵��ֽ�������ʵ���ǻ������е���������
int sendn(SOCKET fd,char *bp,int len)
{
	int cnt;
	int rc;
	cnt=len;
	//�Ҿ��ã�֮������Ҫ��һ��whileѭ�����������ݣ��������Ϊsend����Ҳ���ܰ�ָ����������
	//һ�ζ�������ɣ�������Ҫ��һ��ѭ���������ط��ͣ�ֱ�����е����ݶ������꣬�����ǳ���
	while(cnt>0)
	{
		//send  The send function sends data on a connected socket.
		//send�����ķ���ֵ��������ʾ�Ѿ��ɹ��ط��ͳ�ȥ�˶������ݣ����ڿͻ����ܷ�ɹ����յ�
		//��Щ���ݣ����񲢲�����send�����ķ���ֵ�����ֳ�������ʵ���ܷ�ɹ����յ������ǿͻ���
		//���£������������޹ء�Ҳ�����ݱ��ͻ��˵ķ���ǽ�����ˣ��������ͻ��˾���ԶҲ�����յ�
		//��Щ�����ˣ���������Щ���߰�����£��������˿ɹܲ��š�
		rc=send(fd,bp,cnt,0);
		if(rc==SOCKET_ERROR)
		{
			CString aa;
			aa="���ʹ���\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aa.GetBuffer(0),1);
			aa.ReleaseBuffer();
			return -1;
		}
		if(rc==0)
			return len-cnt;
		//��������һ�����ݺ󣬻�����ָ�뵱ȻҪ������ˡ����ָ�������������Ѿ��������ˣ���
		//bp��ָ�򻺳�����ĩβ�ˡ�
		bp+=rc;
		//��������һ�����ݣ���cnt(������¼��û�����������)����ֵ��Ȼ��Ҫ��ȥ�Ѿ������˵��ˡ�
		cnt-=rc;
	}
	return len;
}

//���ļ��ĺ��������������ž��Ǵ����ļ��ľ��庯���ɡ�
//ʵ�ֶ��߳����غͶϵ�������ǰ���������ǣ���������Ҫ֧�������ȡ�ļ������Ҫ�󴫵�һ��
//seek��������Ϊ��Ҫ�����seek����Ѱ�ҵ��ϴεĶϵ�����ǰ��ļ��ֳɼ��ηֱ����ء�
//����1������socket������2�������ȡ�ļ��õĵĶ�λָ�룻����3���˴����ز���Ҫ���ļ��ж�ȡ���ֽ���������4���������趨�Ŀɹ����ص��ļ��б��е��ļ��ı��(����Ǵ�0��ʼ��)������nameph������±ꣻ
void readfile( SOCKET so , int seek , int len , int fino )
{
	//�ļ���ȫ·����
	CString myname;
	//��Ҫ���ص��ļ���ȫ·����ֵ��myname����
	myname.Format("%s",nameph[fino]);
	CFile myFile;
	//���ļ���Ϊ��֧�ֶ��߳����أ�����Ҫ�Թ���ķ�ʽ���ļ����У�
	myFile.Open( myname, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ); 

	//��λ��ָ��λ��
	//CFile::Seek  The Seek function permits random access to a file's contents by moving the pointer a specified amount, absolutely or relatively. No data is actually read during the seek. If the requested position is larger than the size of the file, the file length will be extended to that position, and no exception will be thrown.
	//When a file is opened, the file pointer is positioned at offset 0, the beginning of the file.
	//CFile::begin   Move the file pointer lOff bytes forward from the beginning of the file. 
	myFile.Seek(seek,CFile::begin);
	//����һ���������ļ��ж�ȡ���ݣ�Ȼ���ٷ��͵Ļ�������
	char m_buf[SIZE];
	int len2;

	//��ʼ��ͻ��˷��ͣ�ָ���ļ��еģ�ָ��λ�ô��ģ�ָ�������ģ����ݡ�
	//֮������Ҫʹ��whileѭ�����������ݣ�����Ϊÿһ�����ֻ�ܷ���SIZE��ô������ݣ����ԣ���
	//������Ҫ���ж�εķ��ͣ������Ҫ�õ�ѭ���ˡ�
	while(len>0)
	{
		//ÿһ�η��͵������������ܳ���m_buf��������������ߴ硣����ͻ���Ҫ���������С��
		//�������ĳߴ磬��ֻ��Ҫ��ȡlen��ô������ݾ����ˡ�
		len2=len>SIZE?SIZE:len;
		myFile.Read(m_buf, len2);
		//��ͻ��˷������ݡ�
		int aa=sendn(so,m_buf,len2);
		//������͹��̳��ִ�����
		if(aa<0)
		{	
			closesocket (so);
			break;
		}
		//�ԣ���������һ�����ݺ󣬾�Ӧ�ô������аѡ��Ѿ��������˵���Щ���ݵ���������ȥ��
		len=len-aa;
	}
	//�ԣ��������ļ�֮����Ҫ�ر�����
	myFile.Close();
}

//�����������������ͻ��˵�һ�������õ��̡߳����̺߳�����
//������ǣ������õ�socket��
DWORD WINAPI clientthread(LPVOID lpparam)
{
	//�ļ���Ϣ
	fileinfo* fiinfo;
	//���ջ���
	char* m_buf;
	m_buf=new char[100];
	SOCKET  sConnect1=(SOCKET)lpparam;
	//�����Զ���ĺ������ӿͻ��˶�ȡ100�ֽڵ����ݡ�
	int aa=readn(sConnect1,m_buf,100);
	//�����ȡ���ݵ�ʱ�����˴�����
	if(aa<0)
	{
		//�رմ������õ�socket��
		closesocket(sConnect1);
		return -1;
	}

	//ǿ�Ƶ���������ת�����Ѵ�������ϢתΪ������ļ���Ϣ
	fiinfo=(fileinfo*)m_buf;
	CString temp;
	temp.Format("re %d from there",aa);
	CString aaa;
	//����������switch����飬������ͻ���˵ʲô
	switch(fiinfo->type)
	{
		//type==0����ű�ʾ���ͻ�����Ҫ�ӷ������˶�ȡ�������ص��ļ��б����Ϣ��
		case 0:
			//��ͻ��˷���1080�ֽ�(����10������Ԫ��)�����ݣ�
			//zmfile����ṹ�������д�ŵ��ǣ��������˳����пɹ��û������ص��ļ�����Ϣ
			//(�ļ������ļ��ĳ���)��
			//ÿһ��zmfile����Ԫ�صĴ�С��108���ֽڣ����ԣ�10��Ԫ�ؾ�һ����1080���ֽڡ�
			//��ʵ������ֱ��д��һ�����ֵı�̷��������ã���Ϊ����Ժ�ṹ�����Ʊ��ˣ���ô
			//����Ӳ��д�ϵ����־���Ҫ���¸�д�����ң�����ڶദ���õ�������֣���ô��д����
			//�ͷǳ����鷳����ȷ��д���ǣ�����sizeof�����ߣ�������Ҫ����һ���궨�壬������
			//ֻ��Ҫ��д�����ֵ�����ˡ�
			aa=sendn(sConnect1,(char*)zmfile,SIZE_OF_zmfile);
			//added for test begin
//			char stemp[35];
//			sprintf(stemp,"SIZE_OF_zmfile=%d \n",SIZE_OF_zmfile);
//			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)stemp,1);
			//�������ԣ�����SIZE_OF_zmfile��ֵ��ȷ��1080
			//added for test end
			//����д���
			if(aa<0)
			{	
				closesocket (sConnect1);
				return -1;
			}
			//����Ϣ�������壬�������ҷ��ִ������Ϣ�ĺ���ȴ�������У��ѵ���mfc����Ϣ���ݻ���
			//����Ϣת�͸���������
			//���ҹ��ƣ�һ������ô���¡�
			aaa="�յ�LIST����\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			break;
		//type==2����ű�ʾ���ͻ���׼�����ˣ�������(ָ������)���Կ�ʼ�����ļ��ˡ�
		case 2:
			//��XX.xxx  �ļ������� �ļ���ȫ·������һ�������ǣ�TDA7293.pdf  �ļ�������C:\Documents and Settings\YJK\My Documents\TDA7293.pdf
			aaa.Format("%s  �ļ�������%s\n",zmfile[fiinfo->fileno].name,nameph[fiinfo->fileno]);
			//���ͻ���Ҫ���ص��ļ�����Ϣ����ʾ��RichEdit�ؼ��С�
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			//���������ž��Ǵ����ļ��ľ��庯���ɡ�
			readfile(sConnect1,fiinfo->seek,fiinfo->len,fiinfo->fileno);
			break;
		//���������޷����ͻ��˵�������Ϊ��ǰ��������ֻ�����type==0��type==2������������
		default:
			aaa="����Э�����\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CServer1App initialization

BOOL CServer1App::InitInstance()
{
	skinppLoadSkin(_T("AlphaOS.ssk"));//blue.sskΪ��Ŀ�µ�Ƥ���ļ�
	//���������������У�������WSAStartup������ʼ����WinSock�����ڶ�Ӧ��WSACleanup������
	//Ҳ���ص����˰ɡ���Ϊ��AppWizard�Զ����ɵ�֧��WinSock�ĳ������У�������û��
	//��WSACleanup�����ĵ��á�
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CServer1Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CServer1View));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.

	//added by author begin
	//Centers a window relative to its parent.If the pop-up window is not owned, it is centered relative to the screen.
	m_pMainWnd->MoveWindow(0,0,800,600,true);
	//���Թ��ˣ�������һ���ȷ���á�
	m_pMainWnd->CenterWindow();
	m_pMainWnd->SetWindowText("P2P������");
	
	m_pMainWnd->ShowWindow(SW_SHOW);	//�����벻����������ˣ���AppWizard�Զ����ɵġ�
	m_pMainWnd->UpdateWindow();			//�����벻����������ˣ���AppWizard�Զ����ɵġ�
    
//	WORD wVersionRequested;//commented by me!
//  WSADATA wsaData;//commented by me!
    char name[255];
    PHOSTENT hostinfo;
	//WORD  16-bit unsigned integer. 
	//The MAKEWORD macro creates a WORD value by concatenating the specified values. 
	//������8λ��BYTE���͵������ϳ�һ��16λ��������ʾҪʹ�� WinSock 2.0 �档
//  wVersionRequested = MAKEWORD( 2, 0 );//commented by me!
	//The WSAStartup function must be the first Windows Sockets function called by an application or DLL. It allows an application or DLL to specify the version of Windows Sockets required and retrieve details of the specific Windows Sockets implementation. The application or DLL can only issue further Windows Sockets functions after successfully calling WSAStartup.
	//ʹ��API�汾��WinSock��ʱ����Ҫ�ȵ��ô˺�����
	//Return Values  The WSAStartup function returns zero if successful. Otherwise, it returns one of the error codes listed in the following. 
	//�����ʼ��WinSock�ɹ�����
	//����˼��������Ϊ�������һ�����������Ƕ��࣬��Ϊ�ڱ������еĿ�ʼ���Ѿ�������if (!AfxSocketInit())
	//��һ����룬��AfxSocketInit�����ڲ��Ѿ�������һ��WSAStartup�����ˡ�
//  if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )//commented by me!
	{
		//The gethostname function returns the standard host name for the local machine.
        if( gethostname ( name, sizeof(name)) == 0)
		{
			//The gethostbyname function retrieves host information corresponding to a host name from a host database.
			//������ǣ�[in] Pointer to the null-terminated name of the host to resolve. 
			//If retrieveing host information successfully, then
            if((hostinfo = gethostbyname(name)) != NULL)
            {
				//The inet_ntoa function converts an (Ipv4) Internet network address into a string in Internet standard dotted format.
				/*
				char FAR * inet_ntoa(
				  struct   in_addr in  
				);
				  */
				//h_addr_list  Null-terminated list of addresses for the host. Addresses are returned in network byte order. The macro h_addr is defined to be h_addr_list[0] for compatibility with older software. 
				//The in_addr structure represents a host by its Internet address.
				/*
				struct in_addr {
				  union {
						  struct { u_char s_b1,s_b2,s_b3,s_b4; }   S_un_b;
						  struct { u_short s_w1,s_w2; }            S_un_w;
						  u_long                                   S_addr;
				  } S_un;
				};
				*/
				//��Ϊinet_ntoa�����Ĳ�����in_addr���͵ģ����ԣ������������ô���ӵ���������ת����
				m_strIp = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		//The WSACleanup function terminates use of the Ws2_32.dll.An application or DLL is required to perform a successful WSAStartup call before it can use Windows Sockets services. When it has completed the use of Windows Sockets, the application or DLL must call WSACleanup to deregister itself from a Windows Sockets implementation and allow the implementation to free any resources allocated on behalf of the application or DLL. 
		//����ˣ��Ҿ��ò�Ӧ��������͵���WSACleanup����ѽ��̫����ѽ����ô�����أ�
		//�Ҿ��ô˺���Ӧ�÷ŵ�App������������е��òŶԡ�
		//�𣺾������µķ���������Ϊ�������һ��������Ƕ��ࡣ
//		WSACleanup();//commented by me!
     } 
	//added by author begin

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	CLinkCtrl	m_mail;
	CLinkCtrl	m_http;
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
//	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIL, m_mail);
	DDX_Control(pDX, IDC_HTTP, m_http);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
//	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CServer1App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CServer1App message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_mail.SetLinkString("http://www.sarahclub.com/");
	m_http.SetLinkString("http://211.152.147.97/bbs/");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

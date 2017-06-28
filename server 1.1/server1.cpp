
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
//二维数组，第一维是10，对应于是个数组元素，第二维是一个字符串。
//这个二维数组是用来存储加到List控件中的各个文件的全路径用的。
char nameph[10][255];
 
CServer1App theApp;

//文件信息
struct fileinfo
{
	int fileno;//文件号
	int type;//消息类别。有两种有效的取值：0和2 //客户端想说什么（前面那两句话，用1,2表示）
	long len;//文件长度
	int seek;//开始位置
	char name[100];//文件名
};

int sendn(SOCKET fd,char *bp,int len);


//应该参照Visual C++实践与提高系列丛书-网络编程篇-配套源码-第8章的内容，看看监听线程
//到底应该怎么设计才对。
//监听函数，这是一个线程函数。其实，我觉得不应该称此函数所对应的线程为“监听线程”，因为监听
//只是一个设置的过程，调用listen函数，监听过程就开始了。应该称其为“循环等待连接线程”更好。
DWORD WINAPI listenthread(LPVOID lpparam)
{	
	//参数lpparam指向的是一个socket，这个socket是用来监听客户端的连接请求用的。
	SOCKET  sListening=(SOCKET)lpparam;
	//用传递进来的参数所指向的socket进行监听，允许接受的最大连接数是30。
	//The listen function places a socket a state where it is listening for an incoming connection.
	//Return Values  If no error occurs, listen returns zero. Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling WSAGetLastError.
	//这个函数调用不会发生阻塞，只有accept函数调用才会阻塞。
	int rc=listen(sListening,30);

	if(rc==SOCKET_ERROR)
	{
		CString aaa;
		aaa="listen错误\n";
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		return 0;
	}

	//用下面的这个死循环来不断接收来自客户端的连接请求。对于每一个连接socket，都为其启动一个
	//单独的线程，需要注意的是：其线程函数是clientthread，而并不是本监听线程函数。
	//我感觉下面的代码好像有问题呀，怎么退出这个死循环呢，这样，此线程岂不是死掉了吗？
	//应该参照Visual C++实践与提高系列丛书-网络编程篇-第8章的内容，看看等待连接的线程到底应该怎么设计才对。
	while(1)
	{
		//sConnect是一个局部变量。需要注意的是：虽然此变量是一个局部变量，但是，此变量所指向的
		//新创建的socket却并不是一个局部的对象，除非你调用closesocket函数关闭它，否则它会
		//一直存在，直至进程结束。
		//经过考证，发现SOCKET原来就是UINT_PTR数据类型，这是一个无符号指针类型。
		//有一个问题，在while循环中，反复执行下面这句代码，会产生出多个局部的sConnect变量吗？
		//可以做一个试验程序测试一下。
		//答：经过测试，发现并没有在每一次循环的时候都产生出一个新的局部变量来，而是始终都
		//只有一个局部变量sConnect，此变量的地址始终不变。
		SOCKET sConnect;

		//第一个参数：[in] Descriptor identifying a socket that has been placed in a listening state with the listen function. The connection is actually made with the socket that is returned by accept. 
		//返回值：If no error occurs, accept returns a value of type SOCKET that is a descriptor for the new socket. This returned value is a handle for the socket on which the actual connection is made.
		//流程执行到这里，将会阻塞，如果没有客户端的连接请求发来。
		sConnect=accept(sListening,NULL,NULL);

		if(sConnect==INVALID_SOCKET)
		{
			//经过我的测试发现，当我调用closesocket函数关闭监听socket的时候，流程会执行到
			//这里面来。但是，由于进程会接着被中断，所以，Message Box只是一闪就被关闭了，或者
			//是根本连闪一下都没有，进程就结束了。
			char szTemp[10];
			sprintf(szTemp,"123456789 ErrorCode=%d",WSAGetLastError());
			::MessageBox(NULL,szTemp,"",0);
//			continue;
			return -1;//这样设计对吗，我不敢确定？
		}

		CString aa;
		aa="一人联入！\n";
		//这是一个mfc函数，Call this member function to send the specified Windows message to all descendant windows.
		//在本程序中的作用是：把串aa的内容，在RichEdit控件中显示出来。
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aa.GetBuffer(0),1);
		aa.ReleaseBuffer();

		DWORD dwThread;
		//在这里创建了一个新的线程，但是要注意的是，这一次的线程函数变了，变成了clientthread，
		//这个线程是用来处理客户端的连接用的线程。
		//在“VC 实践与提高 网络编程篇”的第8章的例子中，采用的是线程套线程的设计方法，
		//我个人感觉，这种层层嵌套的设计方法好像不太好，还不如这种死循环的设计方法更好呢，
		//不知我的感觉是否正确，有谁能告诉我理论依据是什么？？？？？？
		::CreateThread(NULL,0,clientthread,(LPVOID)sConnect,0,&dwThread);	
	}

	return 0;
}

//从客户端读取数据的函数。
//参数1：连接套接字；参数2：指向缓冲区的指针；参数3：缓冲区的长度；
int readn(SOCKET fd,char *bp,int len)
{
	int cnt;//用来记录缓冲区中的剩余可用空间。
	int rc;
	cnt=len;
	while(cnt>0)
	{
		//Platform SDK: Windows Sockets  The recv function receives data from a connected or bound socket.
		//Return Values  If no error occurs, recv returns the number of bytes received. If the connection has been gracefully closed, the return value is zero. Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling WSAGetLastError.
		//cnt参数的值被设定为缓冲区的长度值，所以，在网络速度足够好的情况下，读取cnt这么
		//多的字节，没问题。这样的话，此while循环只需要执行一次就会正常退出了。从而，我也
		//明白了while循环的作用，就是：用来保证一定要读取cnt这么多的字节，读不够数就
		//反复地读，直至读够数了，或者是此连接被关闭掉了。
		//我有一个疑问：如果客户端只发过来50个字节的数据，会怎么样呢？其实，这个问题，只需要查到合适的资料，就可以轻松解决，并无任何的难度可言。
		//答：??????
		rc=recv(fd,bp,cnt,0);

		if(rc==SOCKET_ERROR)
		{
			CString aa;
			aa="接收错误！\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aa.GetBuffer(0),1);
			aa.ReleaseBuffer();
			return -1;
		}

		//If the connection has been gracefully closed, the return value is zero.
		if(rc==0) 
			return len-cnt;
		//读取了一些数据之后，缓冲区指针也应该相应地增加。
		bp+=rc;
		//读取了一些数据之后，缓冲区中的剩余可用空间也应该相应地减小。
		cnt-=rc;
	}
	return len;
}

filesendinfo zmfile[10];//记录文件，这是一个结构体数组。
#define SIZE_OF_zmfile 1080

//向客户端发送数据的函数。
//参数1：连接socket；参数2：缓冲区指针；参数3：要发送的字节数，其实就是缓冲区中的数据数；
int sendn(SOCKET fd,char *bp,int len)
{
	int cnt;
	int rc;
	cnt=len;
	//我觉得，之所以需要用一个while循环来发送数据，大概是因为send函数也许不能把指定数量数据
	//一次都发送完吧，所以需要用一个循环来反复地发送，直至所有的数据都发送完，或者是出错。
	while(cnt>0)
	{
		//send  The send function sends data on a connected socket.
		//send函数的返回值可用来表示已经成功地发送出去了多少数据，至于客户端能否成功地收到
		//这些数据，好像并不能在send函数的返回值中体现出来。其实，能否成功地收到数据是客户端
		//的事，跟服务器端无关。也许数据被客户端的防火墙拦截了，这样，客户端就永远也不能收到
		//这些数据了，不过，这些乱七八糟的事，服务器端可管不着。
		rc=send(fd,bp,cnt,0);
		if(rc==SOCKET_ERROR)
		{
			CString aa;
			aa="发送错误！\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aa.GetBuffer(0),1);
			aa.ReleaseBuffer();
			return -1;
		}
		if(rc==0)
			return len-cnt;
		//发送完了一批数据后，缓冲区指针当然要向后移了。如果指定数量的数据已经发送完了，则
		//bp就指向缓冲区的末尾了。
		bp+=rc;
		//发送完了一批数据，则cnt(用来记录还没发送完的数据)的数值当然需要减去已经发送了的了。
		cnt-=rc;
	}
	return len;
}

//读文件的函数，这个函数大概就是传送文件的具体函数吧。
//实现多线程下载和断点续传的前提条件就是：服务器端要支持随机存取文件。这就要求传递一个
//seek变量，因为需要用这个seek变量寻找到上次的断点或者是把文件分成几段分别下载。
//参数1：连接socket；参数2：随机存取文件用的的定位指针；参数3：此次下载操作要从文件中读取的字节数；参数4：服务器设定的可供下载的文件列表中的文件的编号(编号是从0开始的)，用作nameph数组的下标；
void readfile( SOCKET so , int seek , int len , int fino )
{
	//文件名全路径。
	CString myname;
	//将要下载的文件的全路径赋值给myname串。
	myname.Format("%s",nameph[fino]);
	CFile myFile;
	//打开文件。为了支持多线程下载，必须要以共享的方式打开文件才行！
	myFile.Open( myname, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ); 

	//定位到指定位置
	//CFile::Seek  The Seek function permits random access to a file's contents by moving the pointer a specified amount, absolutely or relatively. No data is actually read during the seek. If the requested position is larger than the size of the file, the file length will be extended to that position, and no exception will be thrown.
	//When a file is opened, the file pointer is positioned at offset 0, the beginning of the file.
	//CFile::begin   Move the file pointer lOff bytes forward from the beginning of the file. 
	myFile.Seek(seek,CFile::begin);
	//这是一个用来从文件中读取数据，然后再发送的缓冲区。
	char m_buf[SIZE];
	int len2;

	//开始向客户端发送，指定文件中的，指定位置处的，指定数量的，数据。
	//之所以需要使用while循环来发送数据，是因为每一次最多只能发送SIZE这么多的数据，所以，有
	//可能需要进行多次的发送，这就需要用到循环了。
	while(len>0)
	{
		//每一次发送的数据量，不能超过m_buf这个缓冲区的最大尺寸。如果客户所要求的数据量小于
		//缓冲区的尺寸，就只需要读取len这么多的数据就行了。
		len2=len>SIZE?SIZE:len;
		myFile.Read(m_buf, len2);
		//向客户端发送数据。
		int aa=sendn(so,m_buf,len2);
		//如果发送过程出现错误，则
		if(aa<0)
		{	
			closesocket (so);
			break;
		}
		//对，发送完了一批数据后，就应该从总数中把“已经发送完了的那些数据的数量”减去。
		len=len-aa;
	}
	//对，用完了文件之后，需要关闭它。
	myFile.Close();
}

//“用来处理服务器与客户端的一次连接用的线程”的线程函数。
//其参数是：连接用的socket。
DWORD WINAPI clientthread(LPVOID lpparam)
{
	//文件消息
	fileinfo* fiinfo;
	//接收缓存
	char* m_buf;
	m_buf=new char[100];
	SOCKET  sConnect1=(SOCKET)lpparam;
	//调用自定义的函数，从客户端读取100字节的数据。
	int aa=readn(sConnect1,m_buf,100);
	//如果读取数据的时候发生了错误，则
	if(aa<0)
	{
		//关闭此连接用的socket。
		closesocket(sConnect1);
		return -1;
	}

	//强制的数据类型转换，把传来的信息转为定义的文件信息
	fiinfo=(fileinfo*)m_buf;
	CString temp;
	temp.Format("re %d from there",aa);
	CString aaa;
	//用来面的这个switch代码块，来检验客户想说什么
	switch(fiinfo->type)
	{
		//type==0，大概表示：客户端需要从服务器端读取可以下载的文件列表的信息。
		case 0:
			//向客户端发送1080字节(就是10个数组元素)的数据，
			//zmfile这个结构体数组中存放的是：服务器端程序中可供用户端下载的文件的信息
			//(文件名、文件的长度)。
			//每一个zmfile数组元素的大小是108个字节，所以，10个元素就一共是1080个字节。
			//其实，这种直接写上一个数字的编程方法并不好，因为如果以后结构体的设计变了，那么
			//这种硬性写上的数字就需要重新改写，而且，如果在多处都用到这个数字，那么改写起来
			//就非常的麻烦。正确的写法是：用上sizeof，或者，最起码要用上一个宏定义，这样，
			//只需要改写宏的数值就行了。
			aa=sendn(sConnect1,(char*)zmfile,SIZE_OF_zmfile);
			//added for test begin
//			char stemp[35];
//			sprintf(stemp,"SIZE_OF_zmfile=%d \n",SIZE_OF_zmfile);
//			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)stemp,1);
			//经过测试，发现SIZE_OF_zmfile的值的确是1080
			//added for test end
			//如果有错，则
			if(aa<0)
			{	
				closesocket (sConnect1);
				return -1;
			}
			//发消息给主窗体，不过，我发现处理此消息的函数却在视类中，难道是mfc的消息传递机制
			//把消息转送给视类了吗？
			//答：我估计，一定是这么回事。
			aaa="收到LIST命令\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			break;
		//type==2，大概表示：客户端准备好了，所以你(指服务器)可以开始传送文件了。
		case 2:
			//“XX.xxx  文件被请求！ 文件的全路径”。一个例子是：TDA7293.pdf  文件被请求！C:\Documents and Settings\YJK\My Documents\TDA7293.pdf
			aaa.Format("%s  文件被请求！%s\n",zmfile[fiinfo->fileno].name,nameph[fiinfo->fileno]);
			//将客户端要下载的文件的信息，显示到RichEdit控件中。
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			//这个函数大概就是传送文件的具体函数吧。
			readfile(sConnect1,fiinfo->seek,fiinfo->len,fiinfo->fileno);
			break;
		//服务器端无法理解客户端的需求，因为当前服务器端只能理解type==0和type==2的这两种请求。
		default:
			aaa="接收协议错误！\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CServer1App initialization

BOOL CServer1App::InitInstance()
{
	skinppLoadSkin(_T("AlphaOS.ssk"));//blue.ssk为项目下的皮肤文件
	//在下面的这个函数中，调用了WSAStartup函数初始化了WinSock。至于对应的WSACleanup函数，
	//也许不必调用了吧。因为由AppWizard自动生成的支持WinSock的程序框架中，根本就没有
	//对WSACleanup函数的调用。
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
	//我试过了，下面这一句的确管用。
	m_pMainWnd->CenterWindow();
	m_pMainWnd->SetWindowText("P2P服务器");
	
	m_pMainWnd->ShowWindow(SW_SHOW);	//这句代码不是作者添加了，是AppWizard自动生成的。
	m_pMainWnd->UpdateWindow();			//这句代码不是作者添加了，是AppWizard自动生成的。
    
//	WORD wVersionRequested;//commented by me!
//  WSADATA wsaData;//commented by me!
    char name[255];
    PHOSTENT hostinfo;
	//WORD  16-bit unsigned integer. 
	//The MAKEWORD macro creates a WORD value by concatenating the specified values. 
	//用两个8位的BYTE类型的数，合成一个16位的数。表示要使用 WinSock 2.0 版。
//  wVersionRequested = MAKEWORD( 2, 0 );//commented by me!
	//The WSAStartup function must be the first Windows Sockets function called by an application or DLL. It allows an application or DLL to specify the version of Windows Sockets required and retrieve details of the specific Windows Sockets implementation. The application or DLL can only issue further Windows Sockets functions after successfully calling WSAStartup.
	//使用API版本的WinSock的时候，需要先调用此函数。
	//Return Values  The WSAStartup function returns zero if successful. Otherwise, it returns one of the error codes listed in the following. 
	//如果初始化WinSock成功，则
	//经过思考，我认为下面的这一句代码根本就是多余，因为在本函数中的开始处已经调用了if (!AfxSocketInit())
	//这一句代码，在AfxSocketInit函数内部已经调用了一次WSAStartup函数了。
//  if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )//commented by me!
	{
		//The gethostname function returns the standard host name for the local machine.
        if( gethostname ( name, sizeof(name)) == 0)
		{
			//The gethostbyname function retrieves host information corresponding to a host name from a host database.
			//其参数是：[in] Pointer to the null-terminated name of the host to resolve. 
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
				//因为inet_ntoa函数的参数是in_addr类型的，所以，下面就用了这么复杂的数据类型转换。
				m_strIp = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		//The WSACleanup function terminates use of the Ws2_32.dll.An application or DLL is required to perform a successful WSAStartup call before it can use Windows Sockets services. When it has completed the use of Windows Sockets, the application or DLL must call WSACleanup to deregister itself from a Windows Sockets implementation and allow the implementation to free any resources allocated on behalf of the application or DLL. 
		//奇怪了，我觉得不应该在这里就调用WSACleanup函数呀，太早了呀，怎么回事呢？
		//我觉得此函数应该放到App类的析构函数中调用才对。
		//答：经过最新的分析，我认为下面的这一句根本就是多余。
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

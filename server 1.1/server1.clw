; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServer1View
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "server1.h"
LastPage=0

ClassCount=7
Class1=CServer1App
Class2=CServer1Doc
Class3=CServer1View
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDD_DIALOG1
Class5=CAboutDlg
Resource3=IDR_CNTR_INPLACE
Resource4=IDD_ABOUTBOX
Class6=mysocket
Class7=charbar
Resource5=IDD_DIALOG2

[CLS:CServer1App]
Type=0
HeaderFile=server1.h
ImplementationFile=server1.cpp
Filter=N

[CLS:CServer1Doc]
Type=0
HeaderFile=server1Doc.h
ImplementationFile=server1Doc.cpp
Filter=N

[CLS:CServer1View]
Type=0
HeaderFile=server1View.h
ImplementationFile=server1View.cpp
Filter=C
BaseClass=CRichEditView
VirtualFilter=VWC
LastObject=CServer1View


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_SEND_MSG
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=server1.cpp
ImplementationFile=server1.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_HTTP,static,1342308352
Control7=IDC_MAIL,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_STAR
Command2=ID_ADD
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=CServer1View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_SELECT_ALL
Command9=ID_EDIT_FIND
Command10=ID_EDIT_REPEAT
Command11=ID_EDIT_REPLACE
Command12=ID_OLE_EDIT_PROPERTIES
Command13=ID_EDIT_UNDO
Command14=ID_EDIT_CUT
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_NEXT_PANE
Command18=ID_PREV_PANE
Command19=ID_CANCEL_EDIT_CNTR
CommandCount=19

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=CServer1View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_NEXT_PANE
Command5=ID_PREV_PANE
Command6=ID_CANCEL_EDIT_CNTR
CommandCount=6

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_STAR
Command2=ID_ADD
Command3=ID_APP_EXIT
CommandCount=3

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG2]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_SEND,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:mysocket]
Type=0
HeaderFile=mysocket.h
ImplementationFile=mysocket.cpp
BaseClass=CAsyncSocket
Filter=N

[CLS:charbar]
Type=0
HeaderFile=charbar.h
ImplementationFile=charbar.cpp
BaseClass=CListCtrl
Filter=W
LastObject=charbar


; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "client1.h"
LastPage=0

ClassCount=8
Class1=CClient1App
Class2=CClient1Doc
Class3=CClient1View
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource4=IDR_CNTR_INPLACE
Resource3=IDD_DIALOG1
Class5=CAboutDlg
Resource5=IDD_DIALOG3
Class6=downonline
Class7=chatbar
Resource6=IDD_DIALOG2
Class8=mycsocket
Resource7=IDD_DIALOG4

[CLS:CClient1App]
Type=0
HeaderFile=client1.h
ImplementationFile=client1.cpp
Filter=N

[CLS:CClient1Doc]
Type=0
HeaderFile=client1Doc.h
ImplementationFile=client1Doc.cpp
Filter=N
LastObject=CClient1Doc

[CLS:CClient1View]
Type=0
HeaderFile=client1View.h
ImplementationFile=client1View.cpp
Filter=C
LastObject=CClient1View


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=D
LastObject=ID_BLACk
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=client1.cpp
ImplementationFile=client1.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_CONNECT
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=CClient1View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_SELECT_ALL
Command10=ID_EDIT_FIND
Command11=ID_EDIT_REPEAT
Command12=ID_EDIT_REPLACE
Command13=ID_OLE_EDIT_PROPERTIES
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_NEXT_PANE
Command19=ID_PREV_PANE
Command20=ID_CANCEL_EDIT_CNTR
CommandCount=20

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=CClient1View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_BLACK
Command2=ID_NEXT1
Command3=ID_CONNECT
Command4=ID_GARBAGE
CommandCount=4

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG2]
Type=1
Class=?
ControlCount=2
Control1=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control2=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG3]
Type=1
Class=?
ControlCount=0

[CLS:downonline]
Type=0
HeaderFile=downonline.h
ImplementationFile=downonline.cpp
BaseClass=CListCtrl
Filter=W
LastObject=downonline

[CLS:chatbar]
Type=0
HeaderFile=chatbar.h
ImplementationFile=chatbar.cpp
BaseClass=CListCtrl
Filter=W
LastObject=chatbar

[DLG:IDD_DIALOG4]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_SEND,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:mycsocket]
Type=0
HeaderFile=mycsocket.h
ImplementationFile=mycsocket.cpp
BaseClass=CSocket
Filter=N
LastObject=ID_APP_ABOUT



#if !defined(AFX_CHARBAR_H__1C4960F0_8CC5_41D8_B2DA_0A049080F862__INCLUDED_)
#define AFX_CHARBAR_H__1C4960F0_8CC5_41D8_B2DA_0A049080F862__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// charbar.h : header file
/////////////////////////////////////////////////////////////////////////////
// charbar window
//The CDialogBar class provides the functionality of a Windows modeless dialog box in a control bar. A dialog bar resembles a dialog box in that it contains standard Windows controls that the user can tab between. Another similarity is that you create a dialog template to represent the dialog bar.
//�Ҳ£������Ӧ����λ���ӵ��·����������Ӵ���֮һ�ģ��Ǹ�����������Ϣ�ġ����ʹ��ڡ���
//��Ҫע����ǣ��������Ӵ��ڶ��ǿ������Ӵ��ڣ���������������Ӵ��ڡ�
class charbar : public CDialogBar
{
// Construction
public:
	charbar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(charbar)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~charbar();

	// Generated message map functions
protected:
	//{{AFX_MSG(charbar)

		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARBAR_H__1C4960F0_8CC5_41D8_B2DA_0A049080F862__INCLUDED_)

//Download by http://www.NewXing.com
// client1Doc.h : interface of the CClient1Doc class

#if !defined(AFX_CLIENT1DOC_H__7670AF71_3030_4C95_BF86_747B879A7DB4__INCLUDED_)
#define AFX_CLIENT1DOC_H__7670AF71_3030_4C95_BF86_747B879A7DB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClient1Doc : public CRichEditDoc
{
protected: // create from serialization only
	CClient1Doc();
	DECLARE_DYNCREATE(CClient1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
virtual BOOL SaveModified();
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CClient1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClient1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT1DOC_H__7670AF71_3030_4C95_BF86_747B879A7DB4__INCLUDED_)

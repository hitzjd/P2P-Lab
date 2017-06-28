
// server1Doc.h : interface of the CServer1Doc class
//

#if !defined(AFX_SERVER1DOC_H__7D76ADBF_7C1D_42E2_936D_E0EED573D464__INCLUDED_)
#define AFX_SERVER1DOC_H__7D76ADBF_7C1D_42E2_936D_E0EED573D464__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CServer1Doc : public CRichEditDoc
{
protected: // create from serialization only
	CServer1Doc();
	DECLARE_DYNCREATE(CServer1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServer1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
virtual BOOL SaveModified();
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CServer1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CServer1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVER1DOC_H__7D76ADBF_7C1D_42E2_936D_E0EED573D464__INCLUDED_)

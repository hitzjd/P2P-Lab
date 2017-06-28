//Download by http://www.NewXing.com
// CntrItem.h : interface of the CServer1CntrItem class
#if !defined(AFX_CNTRITEM_H__D0CCA703_AE95_4AFD_98BC_C5085C3BED17__INCLUDED_)
#define AFX_CNTRITEM_H__D0CCA703_AE95_4AFD_98BC_C5085C3BED17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CServer1Doc;
class CServer1View;

class CServer1CntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CServer1CntrItem)

// Constructors
public:
	CServer1CntrItem(REOBJECT* preo = NULL, CServer1Doc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CServer1Doc* GetDocument()
		{ return (CServer1Doc*)CRichEditCntrItem::GetDocument(); }
	CServer1View* GetActiveView()
		{ return (CServer1View*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServer1CntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CServer1CntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__D0CCA703_AE95_4AFD_98BC_C5085C3BED17__INCLUDED_)

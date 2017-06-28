
// client1Doc.cpp : implementation of the CClient1Doc class

#include "stdafx.h"
#include "client1.h"

#include "client1Doc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClient1Doc

IMPLEMENT_DYNCREATE(CClient1Doc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CClient1Doc, CRichEditDoc)
	//{{AFX_MSG_MAP(CClient1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient1Doc construction/destruction

CClient1Doc::CClient1Doc()
{
	// TODO: add one-time construction code here

}
BOOL CClient1Doc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
    return 1;//作者添加的这一句代码，这样，就不会在退出程序的时候，询问是否要存盘了。
//	return CRichEditDoc::SaveModified();
}
CClient1Doc::~CClient1Doc()
{
}

BOOL CClient1Doc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CClient1Doc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CClient1CntrItem(preo, (CClient1Doc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CClient1Doc serialization

void CClient1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CClient1Doc diagnostics

#ifdef _DEBUG
void CClient1Doc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CClient1Doc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClient1Doc commands

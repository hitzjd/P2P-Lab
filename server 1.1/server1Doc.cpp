
// server1Doc.cpp : implementation of the CServer1Doc class
//

#include "stdafx.h"
#include "server1.h"

#include "server1Doc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServer1Doc

IMPLEMENT_DYNCREATE(CServer1Doc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CServer1Doc, CRichEditDoc)
	//{{AFX_MSG_MAP(CServer1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServer1Doc construction/destruction

CServer1Doc::CServer1Doc()
{
	// TODO: add one-time construction code here

}

CServer1Doc::~CServer1Doc()
{
}

BOOL CServer1Doc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}
//这个函数是作者重载的
BOOL CServer1Doc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
    return 1;//作者添加了这一句代码。
//	return CRichEditDoc::SaveModified();//commented by author
}

CRichEditCntrItem* CServer1Doc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CServer1CntrItem(preo, (CServer1Doc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CServer1Doc serialization

void CServer1Doc::Serialize(CArchive& ar)
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
// CServer1Doc diagnostics

#ifdef _DEBUG
void CServer1Doc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CServer1Doc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServer1Doc commands

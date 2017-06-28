
// CntrItem.cpp : implementation of the CServer1CntrItem class
//

#include "stdafx.h"
#include "server1.h"

#include "server1Doc.h"
#include "server1View.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServer1CntrItem implementation

IMPLEMENT_SERIAL(CServer1CntrItem, CRichEditCntrItem, 0)

CServer1CntrItem::CServer1CntrItem(REOBJECT* preo, CServer1Doc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CServer1CntrItem::~CServer1CntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CServer1CntrItem diagnostics

#ifdef _DEBUG
void CServer1CntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CServer1CntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////

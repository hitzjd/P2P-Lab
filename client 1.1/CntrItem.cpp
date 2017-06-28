
// CntrItem.cpp : implementation of the CClient1CntrItem class

#include "stdafx.h"
#include "client1.h"

#include "client1Doc.h"
#include "client1View.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClient1CntrItem implementation

IMPLEMENT_SERIAL(CClient1CntrItem, CRichEditCntrItem, 0)

CClient1CntrItem::CClient1CntrItem(REOBJECT* preo, CClient1Doc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CClient1CntrItem::~CClient1CntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CClient1CntrItem diagnostics

#ifdef _DEBUG
void CClient1CntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CClient1CntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////

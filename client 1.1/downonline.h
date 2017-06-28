//Download by http://www.NewXing.com
#if !defined(AFX_DOWNONLINE_H__C6A6E851_0193_4C95_AB6B_61765FD54D7E__INCLUDED_)
#define AFX_DOWNONLINE_H__C6A6E851_0193_4C95_AB6B_61765FD54D7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// downonline.h : header file
// downonline window

class downonline : public CListCtrl
{
// Construction
public:
	downonline();
	void Remove(char* name);
	void AddItem(filesendinfo * seinfo);
void AddItemtwo(char* name,int now,int type);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(downonline)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~downonline();

	// Generated message map functions
protected:
	//{{AFX_MSG(downonline)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNONLINE_H__C6A6E851_0193_4C95_AB6B_61765FD54D7E__INCLUDED_)

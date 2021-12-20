#ifndef LIST_CTRL_H
#define LIST_CTRL_H 
 
#include "wx/wx.h"
#include "wx/listctrl.h"
#include "ruby.h"

class ListCtrl :public wxObject
{
private:
	wxListCtrl* m_listctrl;
	 
public:
	ListCtrl(int nargs, VALUE *args);
	virtual ~ListCtrl (){
		delete m_listctrl;
	};
	wxListCtrl* GetListCtrl(){
		return m_listctrl;
	};
	 

	 
	 
};
#endif

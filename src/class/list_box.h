#ifndef LIST_BOX_H
#define LIST_BOX_H 
 
#include "wx/wx.h"
#include "ruby.h"

class ListBox :public wxObject
{
public:
	ListBox(int nargs, VALUE *args);
	virtual ~ListBox (){
		delete m_listbox;
	};
	wxListBox* GetListBox(){
		return m_listbox;
	};
	 
private:
	wxListBox* m_listbox;
	 
	 
}; 
#endif

#ifndef TREECTRL
#define TREECTRL 

#include "wx/wx.h"
#include "wx/treectrl.h"
#include "ruby.h"
 
class TreeCtrl :public wxObject
{
private:
	wxTreeCtrl* m_tree_ctrl;
	 
public:
	TreeCtrl(int nargs, VALUE *args);
	virtual ~TreeCtrl (){
		delete m_tree_ctrl;
	};
	wxTreeCtrl* GetTreeCtrl(){
		return m_tree_ctrl;
	};
	 
	 
};
#endif 
 

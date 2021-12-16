#ifndef TREELIST_H
#define TREELIST_H 
 
#include "wx/wx.h"
#include "wx/treelist.h"
#include "wx/artprov.h"
#include "ruby.h"

class TreeList :public wxObject
{
private:
	wxTreeListCtrl* m_treelist_ctrl;
	wxImageList* m_imageList;
	enum
	{
		Icon_File,
		Icon_FolderClosed,
		Icon_FolderOpened
	};
	enum
	{
			Col_Component,
			Col_Files,
			Col_Size
	};
	 
	bool m_isFlat;

	 
public:
	TreeList(int nargs, VALUE *args);
	virtual ~TreeList (){};
	wxTreeListCtrl* GetTreeListCtrl(){
		return m_treelist_ctrl;
	};
	void InitImageList();

	 
};
#endif

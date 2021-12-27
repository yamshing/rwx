#ifndef TREECTRL
#define TREECTRL 

#include "wx/wx.h"
#include "wx/treectrl.h"
#include <algorithm>
 
#include "ruby.h"
 
class TreeItemData : public wxTreeItemData
{
	public:
		TreeItemData(){
			 
		};
		virtual ~TreeItemData (){
			 
		};
		 
		std::vector<int> m_index_vec{};
		 
};

class TreeCtrl :public wxObject
{
private:
	wxTreeCtrl* m_tree_ctrl;
	void AddContentToTree(wxTreeItemId root, wxArrayTreeItemIds& items, VALUE content, int level, TreeItemData* parent_item_data);
	 
public:
	TreeCtrl(int nargs, VALUE *args);
	virtual ~TreeCtrl (){
		delete m_tree_ctrl;
	};
	wxTreeCtrl* GetTreeCtrl(){
		return m_tree_ctrl;
	};
	 
	VALUE Call(int nargs, VALUE *args);
	 
};
#endif 
 

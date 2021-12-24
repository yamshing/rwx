#include "treectrl.h"
#include "static_func.h"
 

TreeCtrl::TreeCtrl(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	std::cout << "treectrl ctor (in treectrl.cpp) "  << std::endl;
	 
	m_tree_ctrl = new wxTreeCtrl(parent_p, wxID_ANY,
			wxPoint(0,0),
			parent_p->FromDIP(wxSize(160,250)),
			wxTR_DEFAULT_STYLE | wxNO_BORDER);
			
	
	 
	wxSize size = parent_p->FromDIP(wxSize(16, 16));
	wxImageList* imglist = new wxImageList(size.x, size.y, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, size));
	imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, size));
	 
	m_tree_ctrl->AssignImageList(imglist);
	 
	wxTreeItemId root = m_tree_ctrl->AddRoot("wxAUI Project", 0);
	 
	VALUE content = rb_hash_aref(option, ID2SYM(rb_intern("content")));
	 
	wxArrayTreeItemIds items;
	 
	AddContentToTree(root, items, content, 0);
	 
	m_tree_ctrl->Expand(root);
	
	/*
	wxArrayTreeItemIds items;

	items.Add(m_tree_ctrl->AppendItem(root,wxString::FromUTF8( "アイテム 1"), 0));
	items.Add(m_tree_ctrl->AppendItem(root,wxString::FromUTF8( "アイテム 2"), 0));
	items.Add(m_tree_ctrl->AppendItem(root,wxString::FromUTF8( "アイテム 3"), 0));
	items.Add(m_tree_ctrl->AppendItem(root,wxString::FromUTF8( "アイテム 4"), 0));
	items.Add(m_tree_ctrl->AppendItem(root,wxString::FromUTF8( "アイテム 5"), 0));
	 
	int i, count;
	for (i = 0, count = items.Count(); i < count; ++i)
	{
		wxTreeItemId id = items.Item(i);
		m_tree_ctrl->AppendItem(id, "Subitem 1", 1);
		m_tree_ctrl->AppendItem(id, "Subitem 2", 1);
		m_tree_ctrl->AppendItem(id, "Subitem 3", 1);
		m_tree_ctrl->AppendItem(id, "Subitem 4", 1);
		m_tree_ctrl->AppendItem(id, "Subitem 5", 1);
	}
	m_tree_ctrl->Expand(root);
	*/

}

void TreeCtrl::AddContentToTree(wxTreeItemId root, wxArrayTreeItemIds& items, VALUE content, int level)
{
	 
	int content_size = static_cast<int>(RARRAY_LEN(content));
	 
	for (int i = 0; i < content_size; ++i) {

		VALUE content_row = rb_ary_entry(content,i);
		 
		VALUE content_str_val = rb_ary_entry(content_row,0);
		VALUE sub_arr_val = rb_ary_entry(content_row,1);
		 
		int sub_arr_size = static_cast<int>(RARRAY_LEN(sub_arr_val));
		 
		if (sub_arr_size > 0) {
			 
			std::cout << "sub_arr_size (in treectrl.cpp) " << sub_arr_size << std::endl;
			//wxArrayTreeItemIds sub_items;
			//AddContentToTree(items.Item(i), sub_items, sub_arr_val, level + 1);
			
		}
		 
		std::string content_str;
		StaticFunc::ValueToString(content_str_val, content_str);
		if (level == 0) {
			items.Add(m_tree_ctrl->AppendItem(root,wxString::FromUTF8( content_str), 0));
		}else{
			m_tree_ctrl->AppendItem(root, "Subitem 2", level);
		}
	} 
}


 

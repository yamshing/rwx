#include "treectrl.h"
#include "static_func.h"
 

TreeCtrl::TreeCtrl(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	//std::cout << "treectrl ctor (in treectrl.cpp) "  << std::endl;
	 
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
	 
}

void TreeCtrl::AddContentToTree(wxTreeItemId root, wxArrayTreeItemIds& items, VALUE content, int level)
{
	 
	int content_size = static_cast<int>(RARRAY_LEN(content));
	 
	for (int i = 0; i < content_size; ++i) {

		VALUE content_row = rb_ary_entry(content,i);
		 
		VALUE content_str_val = rb_ary_entry(content_row,0);
		 

		 
		std::string content_str;
		StaticFunc::ValueToString(content_str_val, content_str);
		wxTreeItemId added = m_tree_ctrl->AppendItem(root,wxString::FromUTF8( content_str), 0);
		 
		m_tree_ctrl->SetItemText(added, content_str);
		//m_tree_ctrl->SetItemState(added, 123);
		 
		if (level == 0) {
			items.Add(added);
		}
		 
		VALUE sub_arr_val = rb_ary_entry(content_row,1);
		int sub_arr_size = static_cast<int>(RARRAY_LEN(sub_arr_val));
		 
		if (sub_arr_size > 0) {
			 
			wxArrayTreeItemIds sub_items;
			AddContentToTree(added, sub_items, sub_arr_val, level + 1);
			
		}
	} 
}

VALUE TreeCtrl::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "get_selection") {
		 
		wxTreeItemId selected = m_tree_ctrl->GetSelection();
		//int state = m_tree_ctrl->GetItemState(selected);
		 
		//std::cout << "m_tree_ctrl->GetItemText(selected) (in treectrl.cpp) " << m_tree_ctrl->GetItemText(selected) << std::endl;
		 
	}
}

 

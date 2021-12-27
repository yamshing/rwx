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
			wxTR_DEFAULT_STYLE | wxNO_BORDER | wxTR_MULTIPLE );
			
	
	 
	wxSize size = parent_p->FromDIP(wxSize(16, 16));
	wxImageList* imglist = new wxImageList(size.x, size.y, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, size));
	imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, size));
	 
	m_tree_ctrl->AssignImageList(imglist);
	 
	wxTreeItemId root = m_tree_ctrl->AddRoot("wxAUI Project", 0);
	 
	VALUE content = rb_hash_aref(option, ID2SYM(rb_intern("content")));
	 
	wxArrayTreeItemIds items;
	 
	TreeItemData* item_data = new TreeItemData();
	 
	AddContentToTree(root, items, content, 0, item_data);
	 
	m_tree_ctrl->Expand(root);
	 
}

void TreeCtrl::AddContentToTree(wxTreeItemId root, wxArrayTreeItemIds& items, VALUE content, int level, TreeItemData* parent_item_data)
{
	 
	int content_size = static_cast<int>(RARRAY_LEN(content));
	 
	parent_item_data->m_index_vec.push_back(0);
	 
	for (int i = 0; i < content_size; ++i) {
		 
		TreeItemData* item_data = new TreeItemData();
		 
		std::copy(parent_item_data->m_index_vec.begin(), parent_item_data->m_index_vec.end(), std::back_inserter(item_data->m_index_vec));
		 
		//parent_item_data->m_index_vec[level] = i;
		 
		item_data->m_index_vec[level] = i;
		 
		VALUE content_row = rb_ary_entry(content,i);
		 
		VALUE content_str_val = rb_ary_entry(content_row,0);
		 
		std::string content_str;
		StaticFunc::ValueToString(content_str_val, content_str);
		 
		std::cout << "level (in treectrl.cpp) " << level << std::endl;
		std::cout << "item_data->m_index_vec.size() (in treectrl.cpp) " << item_data->m_index_vec.size() << std::endl;
		 
		wxTreeItemId added = m_tree_ctrl->AppendItem(root,wxString::FromUTF8( content_str), 0);
		 
		//m_tree_ctrl->SetItemText(added, content_str);
		m_tree_ctrl->SetItemData(added, item_data);
		 
		if (level == 0) {
			items.Add(added);
		}
		 
		VALUE sub_arr_val = rb_ary_entry(content_row,1);
		int sub_arr_size = static_cast<int>(RARRAY_LEN(sub_arr_val));
		 
		if (sub_arr_size > 0) {
			 
			wxArrayTreeItemIds sub_items;
			AddContentToTree(added, sub_items, sub_arr_val, level + 1, parent_item_data);
			
		}
	} 
}

VALUE TreeCtrl::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	VALUE res;
	 
	if (func_name_str == "get_selection") {
		 
		//wxTreeItemId selected_id = m_tree_ctrl->GetSelection();
		wxArrayTreeItemIds selected_id_arr;
		m_tree_ctrl->GetSelections(selected_id_arr);
		 
		int cnt = selected_id_arr.GetCount();
		res = rb_ary_new();
		 
		for (int i = 0; i < cnt; ++i) {
			 
			wxTreeItemId selected_id = selected_id_arr.Item(i);
			 
			TreeItemData* selected_data = (TreeItemData*)m_tree_ctrl->GetItemData(selected_id);
			 
			VALUE sub_ary = rb_ary_new();
			 
			for (int i : selected_data->m_index_vec) {
				rb_ary_push(sub_ary, INT2NUM(i));
			}
			 
			rb_ary_push(res, sub_ary);
		}
		 
	}
	 
	return res;
}

 

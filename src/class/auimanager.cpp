
#include "auimanager.h"
#include "static_func.h"

wxBEGIN_EVENT_TABLE(wxSizeReportCtrl, wxControl)
    EVT_PAINT(wxSizeReportCtrl::OnPaint)
    EVT_SIZE(wxSizeReportCtrl::OnSize)
    EVT_ERASE_BACKGROUND(wxSizeReportCtrl::OnEraseBackground)
wxEND_EVENT_TABLE()

 
AuiManager::AuiManager(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	 
	m_parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_aui_manager = new wxAuiManager();
	m_aui_manager->SetManagedWindow(m_parent_p);
	 
	m_notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER;
	 
}

 
wxSizeReportCtrl* AuiManager::CreateSizeReportCtrl(const wxSize& size)
{
	wxSizeReportCtrl* ctrl = new wxSizeReportCtrl(m_parent_p, wxID_ANY,
			wxDefaultPosition,
			size, m_aui_manager);
	return ctrl;
}
 
 
void AuiManager::GetPaneInfo(wxAuiPaneInfo& pi, VALUE option)
{
	 std::string name  = "";
	  
	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("name")))) {
		VALUE name_val = rb_hash_aref(option, ID2SYM(rb_intern("name")));
		name = std::string(StringValuePtr(name_val));
	}
	 
	std::string direction = "center";
	 
	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("direction")))) {
		VALUE direction_val = rb_hash_aref(option, ID2SYM(rb_intern("direction")));
		direction = std::string(StringValuePtr(direction_val));
	}
	bool dockable = true;
	 
	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("dockable")))) {
		 
		VALUE dockable_val = rb_hash_aref(option, ID2SYM(rb_intern("dockable")));
		dockable = RTEST(dockable_val);
		 
	}
	 
	bool resizable = true;
	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("resizable")))) {
		 
		VALUE resizable_val = rb_hash_aref(option, ID2SYM(rb_intern("resizable")));
		resizable = RTEST(resizable_val);
	}

	bool close_button = true;

	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("close_button")))) {
		VALUE close_button_val = rb_hash_aref(option, ID2SYM(rb_intern("close_button")));
		close_button = RTEST(close_button_val);
	}
	bool maximize_button = true;

	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("maximize_button")))) {
		VALUE maximize_button_val = rb_hash_aref(option, ID2SYM(rb_intern("maximize_button")));
		maximize_button = RTEST(maximize_button_val);
	}
	bool minimize_button = true;

	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("minimize_button")))) {
		VALUE minimize_button_val = rb_hash_aref(option, ID2SYM(rb_intern("minimize_button")));
		minimize_button = RTEST(minimize_button_val);
	}
	 

	int min_w = 200;
	int min_h = 200;

	if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("min_size")))) {
		VALUE min_size_val = rb_hash_aref(option, ID2SYM(rb_intern("min_size")));
		VALUE min_w_val = rb_ary_entry(min_size_val,0);
		VALUE min_h_val = rb_ary_entry(min_size_val,1);
		min_w = NUM2INT(min_w_val);
		min_h = NUM2INT(min_h_val);
	}
	 
	pi.Name(name);
	pi.LeftDockable(dockable);
	pi.TopDockable(dockable);
	pi.RightDockable(dockable);
	pi.Floatable(dockable);
	pi.Resizable(resizable);
	pi.CloseButton(close_button);
	pi.MaximizeButton(maximize_button);
	pi.MinimizeButton(minimize_button);
	 
	pi.MinSize(min_w,min_h);
	 
	if (direction == "center") {
		pi.CenterPane().Show();
	}else if (direction == "left") {
		pi.Left().Show();
	}else if (direction == "right") {
		pi.Right().Show();
	}else if (direction == "top") {
		pi.Top().Show();
	}else if (direction == "bottom") {
		pi.Bottom().Show();
	}
	 
}
VALUE AuiManager::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	VALUE result = Qfalse;
	App* app_p = static_cast<App*>(wxTheApp);
	 
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "add_pane") {
		VALUE option = args[1];
		VALUE pane = rb_hash_aref(option, ID2SYM(rb_intern("pane")));
		 
		Toolbar* toolbar_pane_p = dynamic_cast<Toolbar*>(app_p->GetObjectFromMap(pane));
		 
		if (toolbar_pane_p) {
			 
			wxToolBar* m_tb = toolbar_pane_p->GetWxToolbarP();
			
			//------------------------------
			// Floatable no, gripper no, top right left dockable no
			//  
			wxAuiPaneInfo pi = wxAuiPaneInfo().Name(wxT("toolbar")).Caption(wxT("toolbar")).ToolbarPane()
				.Gripper(false).Floatable(false).Top().TopDockable(false).RightDockable(false).LeftDockable(false);
			 
			m_aui_manager->AddPane(m_tb, pi);
			 
			m_aui_manager->Update();
			 
		}

		Notebook* notebook_pane_p = dynamic_cast<Notebook*>(app_p->GetObjectFromMap(pane));
		if (notebook_pane_p) {
			 
			wxAuiNotebook* wx_notebook_p = dynamic_cast<wxAuiNotebook*>(notebook_pane_p->GetNotebookP());
			if (wx_notebook_p) {
				wx_notebook_p->Freeze();
				wx_notebook_p->Thaw();
			}
			 
			//wxAuiPaneInfo().Name("notebook_content").CenterPane().PaneBorder(false).Show();
			 
			wxAuiPaneInfo pi = wxAuiPaneInfo();
			GetPaneInfo(pi, option);
			m_aui_manager->AddPane(wx_notebook_p, pi);
			
			m_aui_manager->Update();
		}
		 
		TreeCtrl* treectrl_p = dynamic_cast<TreeCtrl*>(app_p->GetObjectFromMap(pane));
		 
		if (treectrl_p) {
			 
			wxTreeCtrl* tree = treectrl_p->GetTreeCtrl();
			 
			//wxAuiPaneInfo pi = wxAuiPaneInfo().Name("test8").Caption("Tree Pane").Left().CloseButton(true).MaximizeButton(true);
			 
			wxAuiPaneInfo pi = wxAuiPaneInfo();
			GetPaneInfo(pi,option);
			 
			m_aui_manager->AddPane(tree, pi);
			 
			m_aui_manager->Update();
			 
		}
		 
		Grid* grid_p = dynamic_cast<Grid*>(app_p->GetObjectFromMap(pane));
		 
		if (grid_p) {

			wxGrid* grid = grid_p->GetGrid();
			wxAuiPaneInfo pi = wxAuiPaneInfo();
			GetPaneInfo(pi, option);
			m_aui_manager->AddPane(grid, pi);
			 
			m_aui_manager->Update();
			
		}
		 
		Canvas* canvas_p = dynamic_cast<Canvas*>(app_p->GetObjectFromMap(pane));

		if (canvas_p) {
			wxAuiPaneInfo pi = wxAuiPaneInfo();
			GetPaneInfo(pi, option);
			m_aui_manager->AddPane(canvas_p, pi);
			m_aui_manager->Update();
		}
		 
		 
	}
	return result;
}

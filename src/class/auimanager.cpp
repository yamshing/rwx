
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
	 
	VALUE name_val = rb_hash_aref(option, ID2SYM(rb_intern("name")));
	VALUE direction_val = rb_hash_aref(option, ID2SYM(rb_intern("direction")));
	 
	std::string name = std::string(StringValuePtr(name_val));
	std::string direction = std::string(StringValuePtr(direction_val));
	std::cout << "name << ',' << direction << ','  (in auimanager.cpp) " << name << ',' << direction << ','  << std::endl;
	 
	pi.Name(name);
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
			 
			wxAuiPaneInfo pi = wxAuiPaneInfo()  .Name(wxT("toolbar"))
				.Caption(wxT("toolbar"))
				.ToolbarPane().Top().Floatable().Direction(wxAUI_DOCK_TOP).LeftDockable(false).RightDockable(false);
			 
			m_aui_manager->AddPane(m_tb,pi);
			 
			/*m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test3").Caption("Client Size Reporter").
					Bottom());
					*/
		
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
		 
		 
	}
	return result;
}

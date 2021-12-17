
#include "auimanager.h"
#include "static_func.h"
#include "wx/aui/framemanager.h"

 
AuiManager::AuiManager(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_aui_manager = new wxAuiManager();
	m_aui_manager->SetManagedWindow(parent_p);
	
	 
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
		std::cout << "pane (in auimanager.cpp) " << pane << std::endl;
		Toolbar* pane_p = dynamic_cast<Toolbar*>(app_p->GetObjectFromMap(pane));
		if (pane_p) {
			 
			wxToolBar* m_tb = pane_p->GetWxToolbarP();
			 
			m_tb->AddTool(wxID_ANY,wxT("tool1"),wxArtProvider::GetBitmap(wxART_FILE_OPEN,wxART_TOOLBAR));
			m_tb->AddTool(wxID_ANY,wxT("tool2"),wxArtProvider::GetBitmap(wxART_FILE_SAVE,wxART_TOOLBAR));
			 
			m_tb->Realize();
			 
			wxAuiPaneInfo pi = wxAuiPaneInfo()  .Name(wxT("toolbar"))
				.Caption(wxT("toolbar"))
				.ToolbarPane()
				.Floatable()
				.Direction(wxAUI_DOCK_TOP) // see also ticket #9722
				.LeftDockable(false)
				.RightDockable(false);
			 
			m_aui_manager->AddPane(m_tb,pi);
			m_aui_manager->Update();
	
			 
		}
		 
	}
	 
	return result;
}

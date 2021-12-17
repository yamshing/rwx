
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
	 
	wxToolBar* m_tb=new wxToolBar(parent_p,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTB_FLAT|wxTB_NODIVIDER);
	m_tb->AddTool(wxID_ANY,wxT("tool1"),wxArtProvider::GetBitmap(wxART_FILE_OPEN,wxART_TOOLBAR));
	m_tb->AddTool(wxID_ANY,wxT("tool2"),wxArtProvider::GetBitmap(wxART_FILE_SAVE,wxART_TOOLBAR));
	//m_tb->AddTool(wxID_ANY,wxT("tool1"),wxBitmap(16,15));
	//m_tb->AddTool(wxID_ANY,wxT("tool2"),wxBitmap(16,15));

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
	 
	std::cout << "auimanager constr (in auimanager.cpp) "  << std::endl;
	 
	 
}


#include "auimanager.h"
#include "static_func.h"
#include "wx/aui/framemanager.h"


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
	
	 
}
 
wxSizeReportCtrl* AuiManager::CreateSizeReportCtrl(const wxSize& size)
{
	wxSizeReportCtrl* ctrl = new wxSizeReportCtrl(m_parent_p, wxID_ANY,
			wxDefaultPosition,
			size, m_aui_manager);
	return ctrl;
}
 

wxGrid* AuiManager::CreateGrid()
{
	wxGrid* grid = new wxGrid(m_parent_p, wxID_ANY,
			wxPoint(0,0),
			m_parent_p->FromDIP(wxSize(150,250)),
			wxNO_BORDER | wxWANTS_CHARS);
	grid->CreateGrid(50, 20);
	return grid;
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
		 
		Toolbar* pane_p = dynamic_cast<Toolbar*>(app_p->GetObjectFromMap(pane));
		if (pane_p) {
			
			 
			wxToolBar* m_tb = pane_p->GetWxToolbarP();
			 
			m_tb->AddTool(wxID_ANY,wxT("tool1"),wxArtProvider::GetBitmap(wxART_FILE_OPEN,wxART_TOOLBAR));
			m_tb->AddTool(wxID_ANY,wxT("tool2"),wxArtProvider::GetBitmap(wxART_FILE_SAVE,wxART_TOOLBAR));
			 
			m_tb->Realize();
			 
			wxAuiPaneInfo pi = wxAuiPaneInfo()  .Name(wxT("toolbar"))
				.Caption(wxT("toolbar"))
				.ToolbarPane().Top()
				.Floatable()
				.Direction(wxAUI_DOCK_TOP) // see also ticket #9722
				.LeftDockable(false)
				.RightDockable(false);
			 
			m_aui_manager->AddPane(m_tb,pi);
			m_aui_manager->AddPane(CreateGrid(), wxAuiPaneInfo().Name("grid_content").
					CenterPane().Show());
			 
			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test1").Caption("Pane Caption").
					Top());

			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test2").Caption("Client Size Reporter").
					Bottom().Position(1).
					CloseButton(true).MaximizeButton(true));

			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test3").Caption("Client Size Reporter").
					Bottom().
					CloseButton(true).MaximizeButton(true));

			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test4").Caption("Pane Caption").
					Left());

			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test5").Caption("No Close Button").
					Right().CloseButton(false));

			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test6").Caption("Client Size Reporter").
					Right().Row(1).
					CloseButton(true).MaximizeButton(true));

			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test7").Caption("Client Size Reporter").
					Left().Layer(1).
					CloseButton(true).MaximizeButton(true));


			m_aui_manager->Update();
			 
			 
		}
		 
	}
	 
	return result;
}

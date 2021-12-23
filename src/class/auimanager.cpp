
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

wxTreeCtrl* AuiManager::CreateTreeCtrl()
{
	wxTreeCtrl* tree = new wxTreeCtrl(m_parent_p, wxID_ANY,
			wxPoint(0,0),
			m_parent_p->FromDIP(wxSize(160,250)),
			wxTR_DEFAULT_STYLE | wxNO_BORDER);

	wxSize size = m_parent_p->FromDIP(wxSize(16, 16));
	wxImageList* imglist = new wxImageList(size.x, size.y, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, size));
	imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, size));
	tree->AssignImageList(imglist);
	 
	wxTreeItemId root = tree->AddRoot("wxAUI Project", 0);
	wxArrayTreeItemIds items;
	 
	items.Add(tree->AppendItem(root, "Item 1", 0));
	items.Add(tree->AppendItem(root, "Item 2", 0));
	items.Add(tree->AppendItem(root, "Item 3", 0));
	items.Add(tree->AppendItem(root, "Item 4", 0));
	items.Add(tree->AppendItem(root, "Item 5", 0));


	int i, count;
	for (i = 0, count = items.Count(); i < count; ++i)
	{
		wxTreeItemId id = items.Item(i);
		tree->AppendItem(id, "Subitem 1", 1);
		tree->AppendItem(id, "Subitem 2", 1);
		tree->AppendItem(id, "Subitem 3", 1);
		tree->AppendItem(id, "Subitem 4", 1);
		tree->AppendItem(id, "Subitem 5", 1);
	}


	tree->Expand(root);

	return tree;
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
		 
		Toolbar* toolbar_pane_p = dynamic_cast<Toolbar*>(app_p->GetObjectFromMap(pane));
		 
		if (toolbar_pane_p) {
			 
			wxToolBar* m_tb = toolbar_pane_p->GetWxToolbarP();
			 
			//m_tb->AddTool(wxID_ANY,wxT("tool1"),wxArtProvider::GetBitmap(wxART_FILE_OPEN,wxART_TOOLBAR));
			//m_tb->AddTool(wxID_ANY,wxT("tool2"),wxArtProvider::GetBitmap(wxART_FILE_SAVE,wxART_TOOLBAR));
			//m_tb->Realize();
			 
			wxAuiPaneInfo pi = wxAuiPaneInfo()  .Name(wxT("toolbar"))
				.Caption(wxT("toolbar"))
				.ToolbarPane().Top()
				.Floatable()
				.Direction(wxAUI_DOCK_TOP) // see also ticket #9722
				.LeftDockable(false)
				.RightDockable(false);
			 
			m_aui_manager->AddPane(m_tb,pi);
			m_aui_manager->Update();
			 
			//m_aui_manager->AddPane(CreateGrid(), wxAuiPaneInfo().Name("grid_content").
			//		CenterPane().Show());
			//
			// Layer 1 ni suruto sotoni deru
			// Row(0). Row(1) de ue shita ni naru
			// 
			 
			/*
			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test1").Caption("Pane Caption").
					Top());
				 
			m_aui_manager->AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
					Name("test3").Caption("Client Size Reporter").
					Bottom());
				 
			m_aui_manager->AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
					Name("test8").Caption("Tree Pane").
					Left().Layer(1).Position(1).
					CloseButton(true).MaximizeButton(true));
				 
			m_aui_manager->AddPane(CreateGrid(), wxAuiPaneInfo().
					Name("test5").Caption("No Close Button").
					Right());
				 
			m_aui_manager->Update();
			*/
			 
		}

		Notebook* notebook_pane_p = dynamic_cast<Notebook*>(app_p->GetObjectFromMap(pane));
		if (notebook_pane_p) {
			 
			wxAuiNotebook* wx_notebook_p = dynamic_cast<wxAuiNotebook*>(notebook_pane_p->GetNotebookP());
			if (wx_notebook_p) {
				std::cout << "wxnotebook p ok (in auimanager.cpp) "  << std::endl;
				wx_notebook_p->Freeze();
				 
				wx_notebook_p->Thaw();
			}
			 
			m_aui_manager->AddPane(wx_notebook_p, wxAuiPaneInfo().Name("notebook_content").
				CenterPane().PaneBorder(false).Show());
			
			m_aui_manager->Update();
		}
	}
	return result;
}

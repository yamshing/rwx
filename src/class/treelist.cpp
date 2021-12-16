#include "treelist.h"
#include "static_func.h"
 
void TreeList::InitImageList()
{
    wxSize iconSize = wxArtProvider::GetSizeHint(wxART_LIST);
    if ( iconSize == wxDefaultSize )
        iconSize = wxSize(16, 16);

    m_imageList = new wxImageList(iconSize.x, iconSize.y);

    // The order should be the same as for the enum elements.
    static const wxString icons[] =
    {
        wxART_NORMAL_FILE,
        wxART_FOLDER,
        wxART_FOLDER_OPEN
    };

    for ( unsigned n = 0; n < WXSIZEOF(icons); n++ )
    {
        m_imageList->Add
                     (
                        wxArtProvider::GetIcon(icons[n], wxART_LIST, iconSize)
                     );
    }
}

TreeList::TreeList(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_treelist_ctrl = new wxTreeListCtrl(parent_p, StaticFunc::ALL_EVENT_ID,
													 wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE 
													 );
	m_treelist_ctrl->AppendColumn("Component",
			wxCOL_WIDTH_AUTOSIZE,
			wxALIGN_LEFT,
			wxCOL_RESIZABLE | wxCOL_SORTABLE);
	m_treelist_ctrl->AppendColumn("# Files",
			m_treelist_ctrl->WidthFor("1,000,000"),
			wxALIGN_RIGHT,
			wxCOL_RESIZABLE | wxCOL_SORTABLE);
	m_treelist_ctrl->AppendColumn("Size",
			m_treelist_ctrl->WidthFor("1,000,000 KiB"),
			wxALIGN_RIGHT,
			wxCOL_RESIZABLE | wxCOL_SORTABLE);

#define ADD_ITEM(item, parent, files, size) \
			wxTreeListItem item = m_treelist_ctrl->AppendItem(m_isFlat ? root : parent, \
																						 #item, \
																						 Icon_FolderClosed, \
																						 Icon_FolderOpened); \
			m_treelist_ctrl->SetItemText(item, Col_Files, files); \
			m_treelist_ctrl->SetItemText(item, Col_Size, size)
	 
	wxTreeListItem root = m_treelist_ctrl->GetRootItem();
	ADD_ITEM(Code, root, "", "");
			ADD_ITEM(wxMSW, Code, "313", "3.94 MiB");
			ADD_ITEM(wxGTK, Code, "180", "1.66 MiB");

			ADD_ITEM(wxOSX, Code, "265", "2.36 MiB");
					ADD_ITEM(Core, wxOSX, "31", "347 KiB");
					ADD_ITEM(Carbon, wxOSX, "91", "1.34 MiB");
					ADD_ITEM(Cocoa, wxOSX, "46", "512 KiB");

	ADD_ITEM(Documentation, root, "", "");
			ADD_ITEM(HTML, Documentation, "many", "");
			ADD_ITEM(CHM, Documentation, "1", "");

	ADD_ITEM(Samples, root, "", "");
			ADD_ITEM(minimal, Samples, "1", "7 KiB");
			ADD_ITEM(widgets, Samples, "28", "419 KiB");
	 
}



#include "grid.h"
#include "static_func.h"
 
Grid::Grid(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	std::cout << "grig ctor (in grid.cpp) " << std::endl;

	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_grid = new wxGrid(parent_p, wxID_ANY,
			wxPoint(0,0),
			parent_p->FromDIP(wxSize(150,250)),
			wxNO_BORDER | wxWANTS_CHARS);
	m_grid->CreateGrid(50, 20);
	 
	/*m_grid = new wxGrid(parent_p, wxID_ANY,
			wxPoint(0,0),
			parent_p->FromDIP(wxSize(160,250)),
			wxTR_DEFAULT_STYLE | wxNO_BORDER | wxTR_MULTIPLE );
			*/
	 
	 
}
 
VALUE Grid::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	VALUE res;
	 
	//if (func_name_str == "get_selection") {
	//}
	 
}


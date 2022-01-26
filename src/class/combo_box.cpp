#include "combo_box.h"
#include "static_func.h"

ComboBox::ComboBox(int nargs, VALUE *args)
{

	std::cout << "combo init (in combo_box.cpp) "  << std::endl;
	VALUE parent = args[0];
	VALUE option = args[1];
	 
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	wxArrayString   arrItems;
	arrItems.Add( "Solid" );
	arrItems.Add( "Transparent" );
	arrItems.Add( "Dot" );
	arrItems.Add( "Long Dash" );
	arrItems.Add( "Short Dash" );
	arrItems.Add( "Dot Dash" );
	arrItems.Add( "Backward Diagonal Hatch" );
	arrItems.Add( "Cross-diagonal Hatch" );
	arrItems.Add( "Forward Diagonal Hatch" );
	arrItems.Add( "Cross Hatch" );
	arrItems.Add( "Horizontal Hatch" );
	arrItems.Add( "Vertical Hatch" );
	 
	m_combo = new wxOwnerDrawnComboBox(parent_p,StaticFunc::ALL_EVENT_ID,wxEmptyString,
			wxDefaultPosition, wxDefaultSize,
			arrItems,
			wxCB_SORT // wxNO_BORDER|wxCB_READONLY
			);
	++StaticFunc::ALL_EVENT_ID;

}
VALUE ComboBox::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	VALUE result = INT2NUM(-1);
	 
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "get_selection") {
		//int combo_selected = m_combo->GetSelection();
		//result = INT2NUM(combo_selected);
	}
	return result;
	 
}



#include "combo_box.h"
#include "static_func.h"

ComboBox::ComboBox(int nargs, VALUE *args)
{

	std::cout << "combo init (in combo_box.cpp) "  << std::endl;
	VALUE parent = args[0];
	VALUE option = args[1];
	 
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	/*m_combo = new wxComboBox(parent_p, StaticFunc::ALL_EVENT_ID,
													 wxString::FromUTF8(label_str),
													 wxDefaultPosition, wxDefaultSize,
													 items,
													 majorDim,
													 0);
	 
	++StaticFunc::ALL_EVENT_ID;
	*/

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



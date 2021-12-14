#include "radio_box.h"
#include "static_func.h"

RadioBox::RadioBox(int nargs, VALUE *args)
{

	VALUE parent = args[0];
	VALUE option = args[1];
	 
	VALUE label = rb_hash_aref(option, ID2SYM(rb_intern("label")));
	std::string label_str; 
	StaticFunc::ValueToString(label, label_str);
	
	VALUE cb_inst = rb_hash_aref(option, ID2SYM(rb_intern("cb_inst")));
	VALUE cb_name = rb_hash_aref(option, ID2SYM(rb_intern("cb_name")));
	VALUE content = rb_hash_aref(option, ID2SYM(rb_intern("content")));
	 
	 
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	wxArrayString items;
	
	int size = static_cast<int>(RARRAY_LEN(content));
	for (int i = 0; i < size; ++i) {
		VALUE a_content = rb_ary_entry(content,i);
		std::string a_content_str;
		StaticFunc::ValueToString(a_content, a_content_str);
		items.push_back(wxString::FromUTF8(a_content_str));
	}
	 
	unsigned long majorDim = 0;
	m_radio = new wxRadioBox(parent_p, StaticFunc::ALL_EVENT_ID,
													 wxString::FromUTF8(label_str),
													 wxDefaultPosition, wxDefaultSize,
													 items,
													 majorDim,
													 0);
	 
	++StaticFunc::ALL_EVENT_ID;

}
VALUE RadioBox::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	VALUE result = INT2NUM(-1);
	 
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "get_selection") {
		int radio_selected = m_radio->GetSelection();
		result = INT2NUM(radio_selected);
	}
	return result;
}



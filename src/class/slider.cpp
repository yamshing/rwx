#include "slider.h"
#include "static_func.h"


Slider::Slider(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	 
	App* app_p = static_cast<App*>(wxTheApp);
	 
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	wxPanel* panel = dynamic_cast<wxPanel*>(parent_p);
	std::cout << "panel (in slider.cpp) " << panel << std::endl;
	 
	if (panel) {
		 
		m_slider_sizer = new wxStaticBoxSizer(wxVERTICAL, panel, "");
		 
		int flags = 0;
		int min_value = 0;
		int max_value = 100;
		int value = 50;
		int width = 200;
		int tick_freq = 50;
		 
		flags |= wxSL_AUTOTICKS;
		 
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("with_tick_label")))) {
			flags |= wxSL_VALUE_LABEL;
		}
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("with_min_max_label")))) {
			flags |= wxSL_MIN_MAX_LABELS;
		}
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("value")))) {
			value = NUM2INT(rb_hash_aref(option, ID2SYM(rb_intern("value"))));
		}
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("min_value")))) {
			min_value = NUM2INT(rb_hash_aref(option, ID2SYM(rb_intern("min_value"))));
		}
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("max_value")))) {
			max_value = NUM2INT(rb_hash_aref(option, ID2SYM(rb_intern("max_value"))));
		}
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("width")))) {
			width = NUM2INT(rb_hash_aref(option, ID2SYM(rb_intern("width"))));
		}
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("tick_freq")))) {
			tick_freq = NUM2INT(rb_hash_aref(option, ID2SYM(rb_intern("tick_freq"))));
		}
		 
		m_slider = new wxSlider(m_slider_sizer->GetStaticBox(), StaticFunc::ALL_EVENT_ID, value, min_value, max_value, wxDefaultPosition, wxSize(width, -1),flags);
		 
		++ StaticFunc::ALL_EVENT_ID;
		 
		m_slider->SetTickFreq(tick_freq);
		 
		m_slider_sizer->Add(m_slider);
		 
	}

	
}

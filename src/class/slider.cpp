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
		 
		m_slider_sizer = new wxFlexGridSizer(1, 1, 0, 0);
		 
		wxStaticBoxSizer *static_sizer = new wxStaticBoxSizer(wxVERTICAL, panel, "");
		 
		int flags = 0;
		 
		flags |= wxSL_MIN_MAX_LABELS;
		flags |= wxSL_VALUE_LABEL;
		flags |= wxSL_AUTOTICKS;
		 
		m_slider = new wxSlider(static_sizer->GetStaticBox(), 100, 0, 0, 100, wxDefaultPosition, wxSize(250, -1),flags);
		 
		//m_slider->SetTickFreq(10);
		 
		static_sizer->Add(m_slider);
		m_slider_sizer->Add(static_sizer, 0, wxEXPAND);
		 
		 
	}

	
}

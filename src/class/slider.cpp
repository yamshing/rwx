#include "slider.h"
#include "static_func.h"


Slider::Slider(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	App* app_p = static_cast<App*>(wxTheApp);
	 
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	wxPanel* panel = dynamic_cast<wxPanel*>(parent_p);
	 
	if (panel) {
		 
		wxBoxSizer *m_slider_sizer = new wxBoxSizer(wxVERTICAL);
		 
		wxFlexGridSizer *gs = new wxFlexGridSizer(4, 2, 10, 10);
		 
		wxStaticBoxSizer *static_sizer = new wxStaticBoxSizer(wxVERTICAL, panel, "SetProgressValue");
		 
		int flags = wxSL_MIN_MAX_LABELS | wxSL_VALUE_LABEL | wxSL_AUTOTICKS;
		 
		m_slider = new wxSlider(static_sizer->GetStaticBox(), 100,
				0, 0, 100,
				wxDefaultPosition, wxSize(250, -1),
				flags);
		 
		//m_slider->SetTickFreq(10);
		 
		static_sizer->Add(m_slider);
		gs->Add(static_sizer, 0, wxEXPAND);
		 
		m_slider_sizer->Add(gs);
		panel->SetSizer(m_slider_sizer);
		 
		 
	}

	
}

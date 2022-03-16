#include "slider.h"
#include "static_func.h"


Slider::Slider(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));

	wxPanel* panel = dynamic_cast<wxPanel*>(parent_p);
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *gs = new wxFlexGridSizer(4, 2, 10, 10);
	 
	wxStaticBoxSizer *spvSizer =
		new wxStaticBoxSizer(wxVERTICAL, panel, "SetProgressValue");
	int flags = wxSL_MIN_MAX_LABELS | wxSL_VALUE_LABEL | wxSL_AUTOTICKS;
	m_slider = new wxSlider(spvSizer->GetStaticBox(), 100,
			0, 0, 100,
			wxDefaultPosition, wxSize(250, -1),
			flags);
	m_slider->SetTickFreq(10);
	spvSizer->Add(m_slider);

	gs->Add(spvSizer, 0, wxEXPAND);
	mainSizer->Add(gs);
	panel->SetSizer(mainSizer);

	 
	std::cout << "panel (in slider.cpp) " << panel << std::endl;
	 
	std::cout << "slider ctor (in slider.cpp) " << std::endl;
	
}

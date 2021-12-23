#include "notebook.h"
#include "static_func.h"
 
 
Notebook::Notebook(int nargs, VALUE *args)
{
	std::cout << "nargs (in static_func.h) " << nargs << std::endl;
	App* app_p = static_cast<App*>(wxTheApp);

	VALUE parent = args[0];
	 
	//VALUE content = args[1];
	//std::string content_str; 
	//StaticFunc::ValueToString(content, content_str);
	 
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	m_notebook_p = new wxNotebook(parent_p, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

}
 
void Notebook::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);
	std::cout << "func_name_str (in notebook.cpp) " << func_name_str << std::endl;
	 
	if (func_name_str == "add") {
		 
		if (nargs > 2) {
			 
			VALUE panel = args[1];
			VALUE title = args[2];
			 
			rb_p(panel);
			wxPanel* panel_p = dynamic_cast<wxPanel*>(app_p->GetObjectFromMap(panel));
			std::cout << "panel_p (in notebook.cpp) " << panel_p << std::endl;
			 
			std::string title_str;
			StaticFunc::ValueToString(title, title_str);
			 
			if (panel_p) {
				  
				AddPage(panel_p, wxString::FromUTF8(title_str), false, wxWithImages::NO_IMAGE); 
				 
			}
		}
	}
	 
}

wxPanel* Notebook::CreateRadioButtonsPage(wxWindow *parent, int type)
{
	wxPanel *panel = new wxPanel(parent);
	wxBoxSizer *sizerPanel = new wxBoxSizer(wxVERTICAL);

	if (type == 0) {
		wxString animals[] =
		{ "Fox", "Hare", "Rabbit",
			"Sabre-toothed tiger", "T Rex" };

		wxRadioBox *radiobox1 = new wxRadioBox(panel, wxID_ANY, "Choose one",
				wxPoint(20,100), wxDefaultSize, 5, animals, 2, wxRA_SPECIFY_ROWS);

		sizerPanel->Add(radiobox1, 2, wxEXPAND);

	}else{

		wxString computers[] =
		{ "Amiga", "Commodore 64", "PET",
			"Another" };

		wxRadioBox *radiobox2 = new wxRadioBox(panel, wxID_ANY,
				"Choose your favourite", wxDefaultPosition, wxDefaultSize,
				4, computers, 0, wxRA_SPECIFY_COLS);
		sizerPanel->Add(radiobox2, 1, wxEXPAND);

	}
	panel->SetSizer(sizerPanel);
	 
	return panel;
	 
}

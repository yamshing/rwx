#ifndef NOTEBOOK_H
#define NOTEBOOK_H 
 
#include "wx/wx.h"
#include "wx/notebook.h"
#include "ruby.h"

class Notebook: public wxNotebook
{
	private:
		wxWindow* m_notebook_p;
		wxPanel* CreateRadioButtonsPage(wxWindow *parent, int type);
		std::string m_type;
		 
	public:
		wxWindow* GetNotebookP(){
			return m_notebook_p;
		};
		 
		/*Notebook(wxWindow* parent, int nargs, VALUE *args) : wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) 
		{
		};
		*/
		 
		Notebook (int nargs, VALUE *args);
		 
		virtual ~Notebook (){};
		 
		void Call(int nargs, VALUE *args);
		 
};
#endif

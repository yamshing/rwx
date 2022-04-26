#ifndef FRAME_H
#define FRAME_H


#include "wx/wx.h"
#include "ruby.h"

class Frame : public wxFrame
{

		wxMenuBar *m_menuBar;
	public:
		VALUE m_rwx_frame;
		Frame(const wxString& title);
		virtual ~Frame (){};
		void Call(int nargs, VALUE *args);
		void CallOnInit();
		 
		void OnCopy(wxEvent& event);
		void OnPaste(wxEvent& event);
		 
		 
	private:
		 
		void OnContextMenu(wxEvent& event);
		void OnContextMenuSelected(wxCommandEvent& event);
		 
};


#endif

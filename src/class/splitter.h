#ifndef SPLITTER_H
#define SPLITTER_H 
 
#include <wx/wx.h>
#include <wx/splitter.h>
 
#include "ruby.h"
#include "frame.h"

class Splitter: public wxSplitterWindow
{

	public:
		Splitter(Frame* parent) : wxSplitterWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE | wxCLIP_CHILDREN ) 
		{
			 
		};
		virtual ~Splitter (){};
		void Call(int nargs, VALUE *args);
		 
	private:
		
		 
};
 
#endif

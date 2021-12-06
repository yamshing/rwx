#ifndef SIZER_H
#define SIZER_H 
#include "wx/wx.h"
#include "ruby.h"

class Sizer :public wxObject
{

	public:
		Sizer(int nargs, VALUE *args);
		virtual ~Sizer (){};
		wxSizer* GetSizer(){
			return m_sizer;
		};
		void SetSizer(wxSizer* sizer){
			m_sizer = sizer;
		};
		void Call(int nargs, VALUE *args);
		 
	private:
		 
		std::string m_type;
		std::string m_dir;
		 
		wxSizer* m_sizer;
		 
};


#endif 

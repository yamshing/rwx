#ifndef AUIMANAGER_H
#define AUIMANAGER_H 
 
#include "wx/wx.h"
#include "wx/artprov.h"
#include "wx/aui/aui.h"
 
#include "ruby.h"

class AuiManager :public wxObject
{
private:
	wxAuiManager* m_aui_manager;
		 
public:
	AuiManager(int nargs, VALUE *args);
	virtual ~AuiManager (){};
	wxAuiManager* GetAuiManager(){
		return m_aui_manager;
	};
	 
};



#endif

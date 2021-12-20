#ifndef AUIMANAGER_H
#define AUIMANAGER_H 
 
#include "wx/wx.h"
#include "wx/artprov.h"
#include "wx/aui/aui.h"
#include "wx/aui/framemanager.h"
#include "ruby.h"

class AuiManager :public wxObject
{
private:
	wxAuiManager* m_aui_manager;
		 
public:
	AuiManager(int nargs, VALUE *args);
	virtual ~AuiManager (){
		delete m_aui_manager;
	};
	wxAuiManager* GetAuiManager(){
		return m_aui_manager;
	};
	 
	VALUE Call(int nargs, VALUE *args);
	 
};



#endif

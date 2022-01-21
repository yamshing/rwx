#ifndef APP_H
#define APP_H 

#include "wx/wx.h"
#include "ruby.h"
#include "frame.h"
#include "menubar.h"
 
class App : public wxApp
{
	private:
		std::unordered_map<VALUE, wxObject*> m_object_map{};
		Frame* m_frame_p;
		VALUE m_rwx_app;
		std::string m_app_path;
		std::string m_start_type;
		std::string m_start_file_name;
		 
	public:
		void SetStartFileName(std::string start_file_name){
			m_start_file_name = start_file_name;
		};
		 
		void SetStartType(std::string start_type){
			m_start_type = start_type;
		};
		 
		void SetAppPath(std::string app_path){
			m_app_path = app_path;
		};
		VALUE GetRwxApp(){
			return m_rwx_app;
		};
		void SetRwxApp(VALUE rwx_app){
			m_rwx_app = rwx_app;
		};
		 
		Frame* GetFrameP(){
			return m_frame_p;
		};
		void SetFrameP(Frame* frame_p){
			m_frame_p = frame_p;
		};
		 
		virtual bool OnInit() wxOVERRIDE;
		void SetObjectToMap(VALUE value, wxObject* obj_p)
		{
			m_object_map[value] = obj_p;
		};
		 
		wxObject* GetObjectFromMap(VALUE value)
		{
			return m_object_map[value];
		};
		 
		void GetEmbedBinObject(std::vector<unsigned char>& out_bin, std::string embed_name);
		 
};
 
 
#endif
 


#include "app.h"
 
#include "static_func.h"
#include <fstream>
#include "omusubin.h"
 

extern "C" VALUE librwx_App;
 
int StaticFunc::ALL_EVENT_ID = 0;
 
bool App::OnInit()
{
	//std::cout << "app on init (in test_wx.cpp) "  << std::endl;
	if ( !wxApp::OnInit() )
		return false;
		
	wxInitAllImageHandlers();
	 
	ruby_init();
	 
	set_app_pointer(StaticFunc::app_callback);
	void* node;
	int state;
	 
	if (m_start_type == "with_file") {
		 
		std::cout << "with file in app (in app.cpp) "  << m_start_file_name <<  std::endl;
		std::vector<std::string> file_split_vec;
		std::istringstream f(m_start_file_name);
		std::string s;

		while (getline(f, s, ',')) {
			file_split_vec.push_back(s);
		}

		std::stringstream ss;
		ss << "-e ";
		 
		for (std::string file_path : file_split_vec) {
			 
			std::ifstream is( file_path, std::ios::in );
			std::string line;
			 
			if (is.is_open()) {
				while(getline (is, line)){
					 
					//std::cout << "line (in app.cpp) " << line << std::endl;
					ss << line << std::endl;
					 
				}
				 
			}
			//std::cout << "file_path (in app.cpp) " << file_path << std::endl;
			 
		}
		 
		std::string script = ss.str();
		char* script_c = const_cast<char*>(script.c_str());
		 
		//std::cout << "script_c (in app.cpp) " << script_c << std::endl;
		 
		char* options[] = { "-v", script_c};
		 
		node = ruby_options(2, options);
		state;
		 
		if (ruby_executable_node(node, &state))
		{
			state = ruby_exec_node(node);
		}
		
	}else{
		 
		//std::cout << "with embed!!!! (in app.cpp) " << std::endl;
		Omusubin omusubin;
		 
		std::string target_name = m_app_path;
		 
		//std::vector<std::string> res_str_vec{};
		 
		omusubin.Load(target_name);
		 
		std::vector<unsigned char> val_vec{};
		 
		std::string script_key = "script";
		omusubin.GetBinDataByKey(script_key, val_vec);
		 
		//std::cout << "res_str_vec[0] (in app.cpp) " << res_str_vec[0] << std::endl;
		 
		std::stringstream ss;
		ss << "-e";
		 
		for (int i = 0; i < val_vec.size(); ++i) {
			ss << val_vec[i];
		}
		 
		std::string script = ss.str();
		//std::cout << "script (in app.cpp) " << script << std::endl;
		 
		char* script_c = const_cast<char*>(script.c_str());
		 
		char* options[] = { "-v", script_c};
		 
		node = ruby_options(2, options);
		state;
		 
		if (ruby_executable_node(node, &state))
		{
			state = ruby_exec_node(node);
		}
		 
		/*
		// no good 
		std::string image_buffer_str = res_str_vec[1];
		 
		int buffer_size = image_buffer_str.length()+1;
		 
		std::cout << "buffer_size (in app.cpp) " << buffer_size << std::endl;
		 
		unsigned char *buffer=new unsigned char[buffer_size];
		 
		strcpy((char *)buffer,image_buffer_str.c_str());
		 
		for (int i = 0; i < buffer_size; ++i) {
			printf("%x ", (int)(buffer[i]));
		}
		 
		std::cout << "end (in canvas.cpp) "  << std::endl;
		*/
		 
	}
	 
	std::string method_name = "on_init";
	bool defined = StaticFunc::CheckFuncExist(librwx_App, method_name);
	 
	if (defined) {
		VALUE args[0];
		StaticFunc::CallRwxFunc(m_rwx_app, method_name, 0, args);
	}

	return true;
}

bool App::GetEmbedBinObject(std::vector<unsigned char>& out_bin, std::string embed_name)
{
	 
	Omusubin omusubin;
	bool omusubi_found = omusubin.Load(m_app_path);
	if (omusubi_found) {
		if(omusubin.GetBinDataByKey(embed_name, out_bin)){
			return true;
		}
		return false;
	}
	return false;
	 
}
 
 

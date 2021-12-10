#include "wx/wx.h"
#include "app.h"
#include "omusubin.h"
 
#include <sstream>
 
#ifdef __MINGW64__
#include <windows.h>
#endif

 
IMPLEMENT_APP_NO_MAIN(App);
 
int main(int argc, char *argv[])
{

	std::string file_name = std::string(argv[0]);
#ifdef __MINGW64__
	FreeConsole();
#endif
	int wx_argc = 1;
	char* wx_argv[] = {argv[0]};
	 
	wxEntryStart( wx_argc, wx_argv );
	 
	dynamic_cast<App*>(wxTheApp)->SetAppPath(file_name);
	bool start_app = false;
	 
	std::cout << "argc (in test_wx.cpp) " << argc << std::endl;
	 
	if (argc > 1) {

		/*std::cout << "use argv[0] (in test_wx.cpp) " << argv[0] << std::endl;
		std::stringstream ss;
		ss << argv[1];
		 
		if (ss.str() == "embed") {
			 
			ss.str("");
			ss.clear(std::stringstream::goodbit);
			ss << argv[2];
			 
			std::string embed_file_name = ss.str();
			 
			Omusubin omusubin;
			 
			//std::vector<std::string> file_id_vec{"script","image"};
			//std::vector<std::string> file_type_vec{"TXT","DATA"};
			//std::vector<std::string> file_path_vec{embed_file_name,"./assets/test.png"};
			 
			std::vector<std::string> file_id_vec{"script"};
			std::vector<std::string> file_type_vec{"TXT"};
			std::vector<std::string> file_path_vec{embed_file_name};
			 
			if (omusubin.Insert(file_name, file_id_vec, file_type_vec, file_path_vec)) {
				std::cout << "INSERT FROM FILE NAME DONE " << std::endl;
			}

			 
		}else{
			dynamic_cast<App*>(wxTheApp)->SetStartType("with_file");
			dynamic_cast<App*>(wxTheApp)->SetStartFileName(argv[1]);
			start_app = true;
		}
		*/
		 
		dynamic_cast<App*>(wxTheApp)->SetStartType("with_file");
		dynamic_cast<App*>(wxTheApp)->SetStartFileName(argv[1]);
		start_app = true;
		 
	}else{
		 
		dynamic_cast<App*>(wxTheApp)->SetStartType("with_embed");
		start_app = true;
		 
	}
	 
	if (start_app) {
		wxTheApp->CallOnInit();
		wxTheApp->OnRun();
	}
	 
	return 0; //ruby_cleanup(state);
	 
}



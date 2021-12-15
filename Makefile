
ifeq ($(OS),Windows_NT)
	SYS = "win"
else
	SYS = "linux"
endif
 
OMUSUBIN_DIR="omusubin/src/class"
CLASS_DIR="src/class"
RWX_BIN_NAME = "rwx"
 
SOURCE=src/main.cpp $(CLASS_DIR)/app.cpp $(OMUSUBIN_DIR)/omusubin.cpp $(CLASS_DIR)/notebook.cpp $(CLASS_DIR)/radio_box.cpp $(CLASS_DIR)/check_box.cpp $(CLASS_DIR)/button.cpp $(CLASS_DIR)/text_ctrl.cpp $(CLASS_DIR)/static_text.cpp $(CLASS_DIR)/sizer.cpp $(CLASS_DIR)/panel.cpp $(CLASS_DIR)/splitter.cpp $(CLASS_DIR)/toolbar.cpp $(CLASS_DIR)/dc.cpp $(CLASS_DIR)/canvas.cpp $(CLASS_DIR)/frame.cpp $(CLASS_DIR)/menubar.cpp $(CLASS_DIR)/list_box.cpp

WXLIB = `./lib/wxwidget/bin/wx-config --static=yes  --libs base,core  --toolkit=gtk3 --version=3.1 --unicode=yes --cxxflags`  -L./lib/wxwidget/lib/wx
 
RUBYLIB = -L./lib/rwx/lib -lruby-static -I./lib/rwx/include/ruby-3.0.0 -I./lib/rwx/include/ruby-3.0.0/x86_64-linux
INCLUDE =  -I./$(CLASS_DIR) -I./$(OMUSUBIN_DIR) -I./lib/wxwidget/include/wx-3.1
 
LIB = -lpthread -ldl -lm -lgmp -lcrypt -lrt -lz -pthread
 
#-mwindows not work with ruby 

WINWXLIB = -L./winlib/wxwidget/lib    -lwx_mswu_core-3.1  -lwx_baseu-3.1        -lpng -lz -ljpeg -LC:/msys64/mingw64/lib -ltiff -llzma -ljbig  -lwxregexu-3.1  -lz -lrpcrt4 -loleaut32 -lole32 -luuid -llzma -luxtheme -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32 -ladvapi32 -lversion -lwsock32 -lgdi32 -loleacc -lwinhttp  -lz -lrpcrt4 -loleaut32 -lole32 -luuid -llzma -luxtheme -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32 -ladvapi32 -lversion -lwsock32 -lgdi32 -loleacc -lwinhttp -ldeflate -lwebp -lzstd -licuuc -licudt -licuio    -D__WXMSW__
WINRUBYLIB = -L./winlib/rwx/lib -lx64-msvcrt-ruby300-static -I./winlib/rwx/include/ruby-3.0.0 -I./winlib/rwx/include/ruby-3.0.0/x64-mingw32   -lm -lgmp  -lz -lws2_32 -lshell32 -limagehlp -liphlpapi
WININCLUDE = -I.  -I./$(CLASS_DIR) -I./$(OMUSUBIN_DIR)  -I./winlib/wxwidget/lib/wx/include/msw-unicode-static-3.1 -I./winlib/wxwidget/include/wx-3.1 
WINLIB = 
 
wx:
ifeq ($(SYS),"win")
	echo 'win'
	rm $(RWX_BIN_NAME).exe || true 
	g++ -g0 -O3 -s -o $(RWX_BIN_NAME).exe --std=c++17 -static $(SOURCE) $(WINWXLIB) $(WININCLUDE) $(WINRUBYLIB) $(WINLIB)
else
	rm $(RWX_BIN_NAME) || true;
	g++ -g0 -O3 -s --std=c++17 -static-libgcc -o $(RWX_BIN_NAME) $(SOURCE) $(WXLIB) $(RUBYLIB) $(INCLUDE) $(LIB); 
	 
endif

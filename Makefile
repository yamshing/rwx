 
ifeq ($(OS),Windows_NT)
	SYS = "win"
else
	SYS = "linux"
endif
 
OMUSUBIN_DIR="omusubin/src/class"
CLASS_DIR="src/class"
RWX_BIN_NAME = "rwx"
 
SOURCE=src/main.cpp $(CLASS_DIR)/app.cpp $(OMUSUBIN_DIR)/omusubin.cpp $(CLASS_DIR)/notebook.cpp $(CLASS_DIR)/radio_box.cpp\
			 $(CLASS_DIR)/check_box.cpp $(CLASS_DIR)/button.cpp $(CLASS_DIR)/text_ctrl.cpp $(CLASS_DIR)/static_text.cpp $(CLASS_DIR)/sizer.cpp\
			 $(CLASS_DIR)/panel.cpp $(CLASS_DIR)/splitter.cpp $(CLASS_DIR)/toolbar.cpp $(CLASS_DIR)/dc.cpp $(CLASS_DIR)/canvas.cpp $(CLASS_DIR)/frame.cpp\
			 $(CLASS_DIR)/menubar.cpp $(CLASS_DIR)/list_box.cpp  $(CLASS_DIR)/list_ctrl.cpp  $(CLASS_DIR)/treelist.cpp $(CLASS_DIR)/auimanager.cpp\
			 $(CLASS_DIR)/treectrl.cpp  $(CLASS_DIR)/grid.cpp $(CLASS_DIR)/image.cpp $(CLASS_DIR)/combo_box.cpp

WXLIB = `./lib/wxwidget/bin/wx-config --static=yes  --libs base,core,aui  --toolkit=gtk3 --version=3.1 --unicode=yes --cxxflags`  -L./lib/wxwidget/lib/wx
 
RUBYLIB = -L./lib/rwx/lib -lruby-static -I./lib/rwx/include/ruby-3.0.0 -I./lib/rwx/include/ruby-3.0.0/x86_64-linux
INCLUDE =  -I./$(CLASS_DIR) -I./$(OMUSUBIN_DIR) -I./lib/wxwidget/include/wx-3.1
 
LIB = -lpthread -ldl -lm -lgmp -lcrypt -lrt -lz -pthread
 
#-mwindows not work with ruby 

WINWXLIB = -L./winlib/wxwidget/lib  -lwx_mswu_propgrid-3.1 -lwx_mswu_ribbon-3.1 -lwx_mswu_stc-3.1 -lwx_mswu_webview-3.1 -lwx_mswu_gl-3.1 -lwx_mswu_richtext-3.1  -lwx_mswu_xrc-3.1  -lwx_mswu_aui-3.1 -lwx_mswu_html-3.1  -lwx_mswu_adv-3.1 -lwx_mswu_core-3.1 -lwx_baseu_xml-3.1 -lwx_baseu_net-3.1 -lwx_baseu-3.1 -lwxscintilla-3.1  -lwxregexu-3.1  -lwx_mswu_media-3.1  -lwx_mswu_qa-3.1           -lpng -lz -ljpeg -LC:/msys64/mingw64/lib -ltiff -llzma -ljbig  -lwxregexu-3.1  -lz -lrpcrt4 -loleaut32 -lole32 -luuid -llzma -luxtheme -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32 -ladvapi32 -lversion -lwsock32 -lgdi32 -loleacc -lwinhttp  -lz -lrpcrt4 -loleaut32 -lole32 -luuid -llzma -luxtheme -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32 -ladvapi32 -lversion -lwsock32 -lgdi32 -loleacc -lwinhttp -ldeflate -lwebp -lzstd -licuuc -licudt -licuio    -D__WXMSW__
WINRUBYLIB = -L./winlib/rwx/lib -lx64-msvcrt-ruby300-static -I./winlib/rwx/include/ruby-3.0.0 -I./winlib/rwx/include/ruby-3.0.0/x64-mingw32   -lm -lgmp  -lz -lws2_32 -lshell32 -limagehlp -liphlpapi
WININCLUDE = -I.  -I./$(CLASS_DIR) -I./$(OMUSUBIN_DIR)  -I./winlib/wxwidget/lib/wx/include/msw-unicode-static-3.1 -I./winlib/wxwidget/include/wx-3.1 
WINLIB = 
 
ruby_lib:
	./include_module.sh $(SYS)
ifeq ($(SYS),"win")
	cd zip/ruby-3_0_2 &&\
	make install -j 4;
else
	cd zip/ruby-3_0_2 &&\
	make install -j 4 && rm -r ../../lib/rwx/lib/ruby
endif

include ./mod/*/Makefile
 
#MODDIRS := $(wildcard mod/*/.)
#$(MODDIRS): FORCE
#	$(MAKE) -C $@ 
#	 
#FORCE:
	 
#wx: $(MODDIRS)
 
wx: 
ifeq ($(SYS),"win")
	echo 'win'
	rm $(RWX_BIN_NAME).exe || true 
	g++ -g0 -O3 -s -o $(RWX_BIN_NAME).exe --std=c++17 -static $(SOURCE) $(WINWXLIB) $(WININCLUDE) $(WINRUBYLIB) $(WINLIB)
else
	 
	rm $(RWX_BIN_NAME) || true;
	rm $(RWX_BIN_NAME)_omusubin.exe || true;
	g++ -g0 -O3 -s --std=c++17 -static-libgcc -o $(RWX_BIN_NAME) $(SOURCE) $(WXLIB) $(RUBYLIB) $(INCLUDE) $(LIB); 
	 
endif

embed:
ifeq ($(SYS),"win")
	./$(RWX_BIN_NAME).exe embed ./win_rwx_omusubin.conf
	chmod +x rwx.exe_omusubin.exe
else
	./$(RWX_BIN_NAME) embed ./rwx_omusubin.conf
	chmod +x rwx_omusubin.exe
endif

all:
	$(MAKE) wx;
	$(MAKE) embed;
	 
clean:
	rm rwx || true;
	rm rwx_omusubin.exe || true;
	rm rwx.exe || true;
	rm rwx.exe_omusubin.exe || true;
clean_mod:
	rm ./src/ruby/librwx/librwx.c
	 

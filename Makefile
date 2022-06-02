 
ifeq ($(OS),Windows_NT)
	SYS = "win"
	EMBED_OMUSUBIN_CONF_NAME = "./win_rwx_omusubin.conf"
	 
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		SYS = "linux"
	endif
	ifeq ($(UNAME_S),Darwin)
		SYS = "mac"
	endif
	EMBED_OMUSUBIN_CONF_NAME = "./rwx_omusubin.conf"
endif
 
  
OMUSUBIN_DIR="omusubin/src/class"
CLASS_DIR="src/class"
RWX_BIN_NAME = "rwx"
 
SOURCE=src/main.cpp $(CLASS_DIR)/app.cpp $(OMUSUBIN_DIR)/omusubin.cpp $(CLASS_DIR)/notebook.cpp $(CLASS_DIR)/radio_box.cpp\
			 $(CLASS_DIR)/check_box.cpp $(CLASS_DIR)/button.cpp $(CLASS_DIR)/text_ctrl.cpp $(CLASS_DIR)/static_text.cpp $(CLASS_DIR)/sizer.cpp\
			 $(CLASS_DIR)/panel.cpp $(CLASS_DIR)/splitter.cpp $(CLASS_DIR)/toolbar.cpp $(CLASS_DIR)/dc.cpp $(CLASS_DIR)/canvas.cpp $(CLASS_DIR)/frame.cpp\
			 $(CLASS_DIR)/menubar.cpp $(CLASS_DIR)/list_box.cpp  $(CLASS_DIR)/list_ctrl.cpp  $(CLASS_DIR)/treelist.cpp $(CLASS_DIR)/auimanager.cpp\
			 $(CLASS_DIR)/treectrl.cpp  $(CLASS_DIR)/grid.cpp $(CLASS_DIR)/image.cpp $(CLASS_DIR)/combo_box.cpp $(CLASS_DIR)/slider.cpp


WXLIB = `./lib/wxwidget/bin/wx-config --static=yes  --libs base,core,aui  --toolkit=gtk3 --version=3.1 --unicode=yes --cxxflags`  -L./lib/wxwidget/lib/wx -DwxDEBUG_LEVEL=0 
 
#------------------------------
# in mac os we must link directly static lib
# because there is no option -static option to force static linking
# check with otool -L rwx to not link dynamic version of library
# ------------------------------

MACWXLIB = -I/Users/shingo/source_code/git/shingo/rwx/lib/wxwidget/lib/wx/include/osx_cocoa-unicode-static-3.1\
					 -I/Users/shingo/source_code/git/shingo/rwx/lib/wxwidget/include/wx-3.1 -D_FILE_OFFSET_BITS=64 -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ \
					 -L/Users/shingo/source_code/git/shingo/rwx/lib/wxwidget/lib   -framework IOKit -framework Carbon -framework Cocoa -framework QuartzCore -framework AudioToolbox -framework System -framework OpenGL\
					 /Users/shingo/source_code/git/shingo/rwx/lib/wxwidget/lib/libwx_osx_cocoau_aui-3.1.a\
					 /Users/shingo/source_code/git/shingo/rwx/lib/wxwidget/lib/libwx_osx_cocoau_core-3.1.a\
					 /Users/shingo/source_code/git/shingo/rwx/lib/wxwidget/lib/libwx_baseu-3.1.a\
					 -framework WebKit -lwxregexu-3.1 -lwxscintilla-3.1 -lexpat\
					 /usr/local/opt/jpeg/lib/libjpeg.a\
					 /usr/local/Cellar/libpng/1.6.37/lib/libpng.a\
					 /usr/local/Cellar/libtiff/4.3.0/lib/libtiff.a\
					 /usr/local/opt/gmp/lib/libgmp.a\
					 /usr/local/opt/xz/lib/liblzma.a\
					 -lz -framework Security -lpthread -liconv -lcurl   -L./lib/wxwidget/lib/wx -DwxDEBUG_LEVEL=0
 
RUBYLIB = -L./lib/rwx/lib -lruby-static -I./lib/rwx/include/ruby-3.0.0 -I./lib/rwx/include/ruby-3.0.0/x86_64-linux
INCLUDE =  -I./$(CLASS_DIR) -I./$(OMUSUBIN_DIR) -I./lib/wxwidget/include/wx-3.1
 
MACRUBYLIB = -L./lib/rwx/lib -lruby.3.0-static -I./lib/rwx/include/ruby-3.0.0 -I./lib/rwx/include/ruby-3.0.0/x86_64-darwin21  -fdeclspec
MACINCLUDE =  -I./$(CLASS_DIR) -I./$(OMUSUBIN_DIR) -I./lib/wxwidget/lib/wx/include/osx_cocoa-unicode-static-3.1 -I./lib/wxwidget/include/wx-3.1 
 
LIB = -lpthread -ldl -lm -lgmp -lcrypt -lrt -lz -pthread
 
MACLIB = -lpthread -ldl -lm  -lz -pthread
 
#-mwindows not work with ruby 

#-lwx_mswu_propgrid-3.1 -lwx_mswu_ribbon-3.1 -lwx_mswu_stc-3.1 -lwx_mswu_webview-3.1\
#-lwx_mswu_gl-3.1 -lwx_mswu_richtext-3.1  -lwx_mswu_xrc-3.1  -lwx_mswu_aui-3.1 -lwx_mswu_html-3.1  -lwx_mswu_adv-3.1\
#-lwx_mswu_core-3.1 -lwx_baseu_xml-3.1 -lwx_baseu_net-3.1 -lwx_baseu-3.1 -lwxscintilla-3.1  -lwxregexu-3.1  -lwx_mswu_media-3.1  -lwx_mswu_qa-3.1  -lwxregexu-3.1

#WINWXLIB = -L./winlib/wxwidget/lib\
#					`./winlib/wxwidget/bin/wx-config --static=yes  --libs base,core,aui  --toolkit=msw  --version=3.1 --unicode=yes --cxxflags` \
#					 -lpng -lz -ljpeg  -ltiff -llzma -ljbig\
#				 	 -lz -lrpcrt4 -loleaut32 -lole32 -luuid -llzma -luxtheme\
#					 -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32 -ladvapi32 -lversion -lwsock32 -lgdi32 -loleacc -lwinhttp  -lz\
#					 -lrpcrt4 -loleaut32 -lole32 -luuid -llzma -luxtheme -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32\
#					 -ladvapi32 -lversion -lwsock32 -lgdi32 -loleacc -lwinhttp -ldeflate -lwebp -lzstd -licuuc -licudt -licuio  -llerc   -D__WXMSW__
	 
#------------------------------
# we cannot use wx-config because we must set mconsole option for ruby
#  
WINWXLIB= -D_FILE_OFFSET_BITS=64 -DwxDEBUG_LEVEL=0  -D__WXMSW__  -mconsole  ./winlib/wxwidget/lib/libwx_mswu_aui-3.1.a \
							 ./winlib/wxwidget/lib/libwx_mswu_core-3.1.a \
							 ./winlib/wxwidget/lib/libwx_baseu-3.1.a \
							 -LC:/msys64/mingw64/lib -lwxregexu-3.1 -lwxscintilla-3.1 -lexpat -lpng -ljpeg \
							 -ltiff -ljbig -lz -lrpcrt4 -loleaut32 -lole32 -luuid -llzma \
							 -luxtheme -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32 \
							 -ladvapi32 -lversion -lwsock32 -lgdi32 -loleacc -lwinhttp -ldeflate -lwebp -lzstd -licuuc -licudt -licuio  -llerc
							 
							  
WINRUBYLIB = -L./winlib/rwx/lib -lx64-msvcrt-ruby300-static -I./winlib/rwx/include/ruby-3.0.0 -I./winlib/rwx/include/ruby-3.0.0/x64-mingw32 \
						 -lm -lgmp  -lz -lws2_32 -lshell32 -limagehlp -liphlpapi
						
WIN_WX_INCLUDE_DIR = ./winlib/wxwidget/include/wx-3.1
WININCLUDE = -I.  -I./$(CLASS_DIR) -I./$(OMUSUBIN_DIR)  -I./winlib/wxwidget/lib/wx/include/msw-unicode-static-3.1 -I$(WIN_WX_INCLUDE_DIR)
WIN_RC_NAME = rwx
WIN_RC_DIR = asset/
 
WINLIB = 
 
ruby_lib:
	./include_module.sh $(SYS);
ifeq ($(SYS),"win")
	cd winzip/ruby-3_0_2 &&\
	make install -j 4;
else
	cd zip/ruby-3_0_2 &&\
	make install -j 4 && rm -r ../../lib/rwx/lib/ruby
endif

include_submake:
ifneq ($(wildcard ./mod/*),)
	echo $(wildcard ./mod/*)
include ./mod/*/Makefile  
else
	echo "NO MODULE"
endif
 
#MODDIRS := $(wildcard mod/*/.)
#$(MODDIRS): FORCE
#	$(MAKE) -C $@ 
#	 
#FORCE:
	 
#wx: $(MODDIRS)
 
wx:  include_submake
	./include_module.sh $(SYS);
ifeq ($(SYS),"win")
	echo 'win'
	rm $(RWX_BIN_NAME).exe || true 
	windres -i./$(WIN_RC_DIR)$(WIN_RC_NAME).rc -o$(WIN_RC_NAME)_rc.o --include-dir $(WIN_WX_INCLUDE_DIR) 
	g++ -g0 -O3 -s -o $(RWX_BIN_NAME).exe --std=c++17 -static $(SOURCE) $(WIN_RC_NAME)_rc.o $(WINWXLIB) $(WININCLUDE) $(WINRUBYLIB) $(WINLIB)
	 
else ifeq ($(SYS),"mac")
	rm $(RWX_BIN_NAME) || true;
	rm $(RWX_BIN_NAME)_omusubin.exe || true;
	g++ -g0 -O3 -s --std=c++17 -o $(RWX_BIN_NAME) $(SOURCE) $(MACWXLIB) $(MACRUBYLIB) $(MACINCLUDE) $(MACLIB); 
	 
else
	 
	rm $(RWX_BIN_NAME) || true;
	rm $(RWX_BIN_NAME)_omusubin.exe || true;
	g++ -g0 -O3 -s --std=c++17 -static-libgcc -o $(RWX_BIN_NAME) $(SOURCE) $(WXLIB) $(RUBYLIB) $(INCLUDE) $(LIB); 
	 
endif

embed:
ifeq ($(SYS),"win")
	./$(RWX_BIN_NAME).exe embed $(EMBED_OMUSUBIN_CONF_NAME)
	chmod +x rwx.exe_omusubin.exe
else
	./$(RWX_BIN_NAME) embed $(EMBED_OMUSUBIN_CONF_NAME) 
	chmod +x rwx_omusubin.exe
endif

all_embed:
	$(MAKE) wx;
	$(MAKE) embed;
	 
all_mod: include_submake
	$(MAKE) wx;
	$(MAKE) embed_mod;
	 
all:
	$(MAKE) wx;
	
	
clean:
	rm rwx || true;
	rm rwx_omusubin.exe || true;
	rm rwx.exe || true;
	rm rwx.exe_omusubin.exe || true;
	rm rwx_rc.o
	 
clean_mod: 
	rm ./src/ruby/librwx/librwx.c || true;
	rm ./src/class/mod_static_func.h || true;
	 
recompile_mod:
	$(MAKE) clean_mod;
	$(MAKE) ruby_lib;
	$(MAKE) wx;
	 
	 


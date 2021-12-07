#!/bin/sh

ROOT_DIR=`pwd`
echo $ROOT_DIR
LIB_DIR="lib"
ABS_LIB_DIR="$ROOT_DIR/$LIB_DIR"
 
WXWIDGET_LIB_DIR="$ABS_LIB_DIR/wxwidget"
RWX_LIB_DIR="$ABS_LIB_DIR/rwx"
 
ZIP_DIR="zip"
 
RUBY_ZIP_NAME="ruby_302"
CATCH_ZIP_NAME="catch"
WXWIDGET_ZIP_NAME="wxwidget"

CATCH_DIR_NAME="Catch-master"
RUBY_DIR_NAME="ruby-3_0_2"
WXWIDGET_DIR_NAME="wxWidgets-3.1.5"
LIBRWX_DIR_NAME="src"
 
#------------------------------ 
# zip lib dir つくる
#------------------------------ 
 
if [ ! -d "$ZIP_DIR" ]; then
	mkdir $ZIP_DIR;
fi
 
if [ ! -d "$LIB_DIR" ]; then
	mkdir $LIB_DIR;
fi
 
#------------------------------ 
# zip file なかったらダウンロード
#------------------------------ 

if [ ! -f "$ZIP_DIR/$RUBY_ZIP_NAME.zip" ]; then
	wget https://github.com/ruby/ruby/archive/refs/tags/v3_0_2.zip -O $ZIP_DIR/$RUBY_ZIP_NAME.zip;
fi

if [ ! -f "$ZIP_DIR/$WXWIDGET_ZIP_NAME.zip" ]; then
	wget https://github.com/wxWidgets/wxWidgets/archive/refs/tags/v3.1.5.zip -O $ZIP_DIR/$WXWIDGET_ZIP_NAME.zip;
fi
 
if [ ! -f "$ZIP_DIR/$CATCH_ZIP_NAME.zip" ]; then
  wget https://github.com/wxWidgets/Catch/archive/refs/heads/master.zip -O $ZIP_DIR/$CATCH_ZIP_NAME.zip;
fi
 
cd $ZIP_DIR;
 
#------------------------------ 
# folder なかったら unzip
#------------------------------ 

if [ ! -d "$RUBY_DIR_NAME" ]; then
	unzip $RUBY_ZIP_NAME;
fi
 
if [ ! -d "$WXWIDGET_DIR_NAME" ]; then
	unzip $WXWIDGET_ZIP_NAME;
fi
 
if [ ! -d "$CATCH_DIR_NAME" ]; then
	unzip $CATCH_ZIP_NAME;
	mv $CATCH_DIR_NAME/* $WXWIDGET_DIR_NAME/3rdparty/catch/;
fi
 
#------------------------------ 
# wx compile 
#------------------------------ 

cd $WXWIDGET_DIR_NAME;
#./configure --prefix=$WXWIDGET_LIB_DIR --disable-shared --disable-debug;
./configure --prefix=$WXWIDGET_LIB_DIR --disable-shared;
make -j 4 install;
 
cd ..;
 
#------------------------------ 
# ruby compile 
#------------------------------ 

cp ../$LIBRWX_DIR_NAME/ruby/common.mk ./$RUBY_DIR_NAME/
cp ../$LIBRWX_DIR_NAME/ruby/inits.c ./$RUBY_DIR_NAME/
cp ../$LIBRWX_DIR_NAME/ruby/revision.h ./$RUBY_DIR_NAME/
cp -R ../$LIBRWX_DIR_NAME/ruby/librwx ./$RUBY_DIR_NAME/
 
cd $RUBY_DIR_NAME;
./autogen.sh;
./configure --prefix=$RWX_LIB_DIR --disable-install-doc;
make -j 4  install;
 
rm -r $RWX_LIB_DIR/lib/ruby;
 
 

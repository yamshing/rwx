
echo "include module"
echo $1

if  test $1 = "linux" ; then
	 
	echo "linux";
	 
	rwx_define_str=""
	rwx_call_str=""
	 
	static_define_str=""
	static_call_str=""
	
	 
	for name in ./mod/*
	do
		echo $(basename ${name})
		filename=$(basename ${name})
		rwx_define_str="${rwx_define_str}`cat ${name}/rwx_define` \n"
		rwx_call_str="${rwx_call_str}`cat ${name}/rwx_call` \n"
		static_define_str="${rwx_define_str}`cat ${name}/static_define` \n"
		static_call_str="${rwx_call_str}`cat ${name}/static_call` \n"
	
		 
	done
	 
	if [ ! -e src/ruby/librwx/librwx.c ]
	then
		sed -e "s/\/\*DEFINE\*\//\/\*DEFINE\*\/\n${rwx_define_str}/g" src/ruby/librwx/librwx_base.c > src/ruby/librwx/librwx.c
		sed -i -e "s/\/\*CALL\*\//\/\*CALL\*\/\n${rwx_call_str}/g" src/ruby/librwx/librwx.c
	else
		echo "librwx.c exist"
	fi
	 
	if [ ! -e src/class/mod_static_func.h ]
	then
		sed -e "s/\/\*DEFINE\*\//\/\*DEFINE\*\/\n${rwx_define_str}/g" src/class/mod_static_func_base.h > src/class/mod_static_func.h
		sed -i -e "s/\/\*CALL\*\//\/\*CALL\*\/\n${rwx_call_str}/g" src/class/mod_static_func.h
	else
		echo "mod_static_func.h exist"
	fi
	
	 
	 
	 
else
	 
	echo "win"
	 
fi


echo "include module"
echo $1

if  test $1 = "linux" ; then
	 
	echo "linux";
	 
	rwx_define_str=""
	rwx_call_str=""
	 
	for name in ./mod/*
	do
		echo $(basename ${name})
		filename=$(basename ${name})
		rwx_define_str="${rwx_define_str}`cat ${name}/rwx_define` \n"
		rwx_call_str="${rwx_call_str}`cat ${name}/rwx_call` \n"
		 
	done
	 
	if [ ! -e src/ruby/librwx/librwx.c ]
	then
		sed -e "s/\/\*DEFINE\*\//\/\*DEFINE\*\/\n${rwx_define_str}/g" src/ruby/librwx/librwx_base.c > src/ruby/librwx/librwx.c
		sed -i -e "s/\/\*CALL\*\//\/\*CALL\*\/\n${rwx_call_str}/g" src/ruby/librwx/librwx.c
	else
		echo "librwx.c exist"
	fi
	 
	 
	 
else
	 
	echo "win"
	 
fi

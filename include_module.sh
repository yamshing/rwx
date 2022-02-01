
echo "include module"
echo $1

if  test $1 = "linux" ; then
	 
	echo "linux";
	 
	define_str=""
	call_str=""
	for name in ./mod/*
	do
		echo $(basename ${name})
		filename=$(basename ${name})
		define_str="${define_str}`cat ${name}/rwx_define`"
		call_str="${call_str}`cat ${name}/rwx_call`"
		 
	done
	 
	sed -e "s/\/\*DEFINE\*\//\/\*DEFINE\*\/\n${define_str}/g" src/ruby/librwx/librwx_base.c > src/ruby/librwx/librwx.c
	sed -i -e "s/\/\*CALL\*\//\/\*CALL\*\/\n${call_str}/g" src/ruby/librwx/librwx.c
	 
else
	 
	echo "win"
	 
fi

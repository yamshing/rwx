
echo "include module"
echo $1

if  test $1 = "linux" ; then
	 
	echo "linux";
	 
	define_str=""
	for name in ./mod/*
	do
		echo $(basename ${name})
		define_str="${define_str} $(basename ${name})\n"
	done
	 
	sed -e "s/\/\*DEFINE\*\//\/\*DEFINE\*\/\n${define_str}/g" src/ruby/librwx/librwx_base.c > src/ruby/librwx/librwx.c
	 
else
	 
	echo "win"
	 
fi

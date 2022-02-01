
echo "include module"
echo $1

if  test $1 = "linux" ; then
	 
	echo "linux";
	 
	cp src/ruby/librwx/librwx_base.c  src/ruby/librwx/librwx.c
	 
else
	 
	echo "win"
	 
fi

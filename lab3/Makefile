all:
	swig -c++ -python Big_integer.i
	g++ -fPIC -c Big_integer.cpp
	g++ -fPIC -c Big_integer_wrap.cxx -I/usr/include/python3.4m
	g++ -shared Big_integer.o Big_integer_wrap.o -o _Big_integer.so
	
windows32:
	swig -c++ -python Big_integer.i
	g++ -c Big_integer.cpp
	g++ -c Big_integer_wrap.cxx -IC:\Python27\include
	g++ Big_integer.o Big_integer_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _Big_integer.pyd
		
windows64:
	swig -c++ -python Big_integer.i
	C:\TDM-GCC-64\bin\g++ -c Big_integer.cpp
	C:\TDM-GCC-64\bin\g++ -c Big_integer_wrap.cxx -IC:\Python27\include
	C:\TDM-GCC-64\bin\g++ Big_integer.o Big_integer_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _Big_integer.pyd

clear:
	rm Big_integer.o Big_integer_wrap.cxx Big_integer_wrap.o
	
clearWin:
	del Big_integer.o Big_integer_wrap.cxx Big_integer_wrap.o

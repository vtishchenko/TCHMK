all: main.cpp Big_integer.cpp
	g++ -c -fPIC Big_integer.cpp
	g++ -shared -o libBig_integer.so Big_integer.o
	LD_LIBRARY_PATH=./ g++ main.cpp -lBig_integer -I. -Wl,-rpath,. -L. -o long_ariph
	
windows: main.cpp Big_integer.cpp
	g++ -c Big_integer.cpp
	g++ -shared -o Big_integer.dll Big_integer.o
	g++ main.cpp Big_integer.dll -I. -Wl,-rpath,. -L. -o long_ariph.exe

all: compile link

# Compile the source files
compile:
	g++ -c src/main.cpp -o main.o -std=c++11
	g++ -c src/router.cpp -o router.o -std=c++11

# Link the object files to create the executable
link:
	g++ -g -o server.exe main.o router.o -std=c++11 -lpthread -lws2_32 -lcrypt32

# Clean up the build files
clean:
	del -f *.o server.exe mingw32-make

# CMake g++ compiler Configuration

GCC := g++
CFLAGS := -I./src -std=c++17
LDFLAGS := -g -lpthread -lws2_32 -lcrypt32 -lstdc++fs
WINCLEAN := del *.o
LINUXCLEAN := rm -f *.o

all: compile link

# Compile the source files
compile:
	$(GCC) $(CFLAGS) -c src/main.cpp -o main.o
	$(GCC) $(CFLAGS) -c src/services/files.config.cpp -o files.config.o
	$(GCC) $(CFLAGS) -c src/controllers/root.cpp -o root.o
	$(GCC) $(CFLAGS) -c src/controllers/upload.cpp -o upload.o
	$(GCC) $(CFLAGS) -c src/routes/routes.cpp -o routes.o

# Link the object files to create the executable
link:
	$(GCC) main.o files.config.o root.o upload.o routes.o -o server.exe $(LDFLAGS)
	$(WINCLEAN)

# Clean up the build files. for linux [rm -f *.o], for windows [del *.o]
clean:
	del *.o

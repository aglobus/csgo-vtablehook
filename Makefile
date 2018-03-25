CXX := g++
CXXFLAGS := -std=c++11 -Iinclude -Wall #-stdlib=libc++ -ggdb 
LDFLAGS := -lpthread -fPIC -shared -static-libstdc++ -lX11 -lXtst -lXext #-fvisibility=hidden

.PHONY: all clean

all:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) *.cpp $(LDFLAGS) -o bin/lib.so
	@strip bin/lib.so

clean:
	@rm -f *.o bin/*.so

# Linux/macOS/WSL:  make        (build all)   make clean
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
SOURCES := $(wildcard 0*/*.cpp)
BINARIES := $(patsubst %.cpp,build/%,$(SOURCES))

all: $(BINARIES)

build/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build

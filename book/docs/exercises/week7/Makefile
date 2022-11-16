source_files = $(wildcard *.cpp)
executables = $(subst .cpp,.x,$(source_files))

CXXFLAGS = -std=c++11

all: $(executables)
%.x: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(executables)

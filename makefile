INCLUDES=-I includes/
CXXFLAGS=-std=c++14 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

exec: bin/main.out
	$<

tests: bin/tests.out
	- $<

clean:
	rm -f bin/*

bin/main.out: src/main.cpp src/graph.cpp cs225/HSLAPixel.cpp cs225/lodepng.cpp cs225/PNG.cpp cs225/circle.cpp cs225/line.cpp cs225/shape.cpp cs225/vector2.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests.out: tests/tests.cpp src/graph.cpp cs225/HSLAPixel.cpp cs225/lodepng.cpp cs225/PNG.cpp cs225/circle.cpp cs225/line.cpp cs225/shape.cpp cs225/vector2.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@

src/%.cpp: includes/%.hpp
	touch $@

cs225/%.cpp: cs225/%.hpp
	touch $@




.DEFAULT_GOAL := tests
.PHONY: test clean exec


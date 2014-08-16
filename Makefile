CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra -O3

ising-3d-SA: ising-3d-SA.cc
	$(CXX) $(CXXFLAGS) -Isrc -o $@ $^

clean:
	rm -rf ising-3d-SA result*.txt


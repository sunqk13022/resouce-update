CXX := g++
CXXFLAGS := -g3 -O2 -fstrict-aliasing -Wall -fPIC -std=c++0x
LDFLAGS := -pthread


TARGET := res_refresh_test

all:
	$(MAKE) $(TARGET)

SRC := $(wildcard *.cc)
OBJ := $(patsubst %.cc, %.o, $(SRC))

res_refresh_test: $(OBJ)
	$(CXX) $^  -o $@  $(LDFLAGS)

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	-rm -rf gen-cpp $(OBJ) $(TARGET) *.pid *.log *.core

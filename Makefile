CXX ?= g++

CXXFLAGS += -Wall -Wextra -Wpedantic

SOURCEZ = main.cpp
OBJECTZ = $(SOURCEZ:.cpp=.o)

.PHONY: all, clean, link, rebuild, OB, SC

OB:
	echo $(OBJECTZ)
SC:
	echo $(SOURCEZ)
all: $(OBJECTZ) link

link:
	$(CXX) -o szereg.exe $(OBJECTZ) 

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

rebuild: clean all

clean:
	rm -rf $(OBJECTZ)

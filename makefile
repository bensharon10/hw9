CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CCLINK = $(CXX)
OBJS   = string.o field.o port.o ip.o
EXEC = firewall.exe
RM = rm -rf *.o *.exe


$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

string.o: string.cpp
	$(CXX) $(CXXFLAGS) -c string.cpp
	
field.o: field.cpp
	$(CXX) $(CXXFLAGS) -c field.cpp
	
port.o: port.cpp field.h
	$(CXX) $(CXXFLAGS) -c port.cpp
	
ip.o: ip.cpp field.h
	$(CXX) $(CXXFLAGS) -c ip.cpp

clean:
	$(RM)

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CCLINK = $(CXX)
OBJS   = main.o string.o field.o port.o ip.o libfirewall.so libinput.so
EXEC = firewall.exe
RM = rm -rf *.o *.so *.exe


$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

libfirewall.so: string.o field.o port.o ip.o
	$(CCLINK) $(CXXFLAGS) -shared string.o field.o port.o ip.o -o libfirewall.so

string.o: string.h string.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic string.cpp

field.o: field.h string.h ip.h port.h field.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic field.cpp

port.o: port.h string.h port.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic port.cpp

ip.o: ip.h string.h ip.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic ip.cpp

clean:
	$(RM)

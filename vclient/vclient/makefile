SRCPATH=./
INCPATH=./
FLAGS= -Wall -fPIC

all: libVC.so buildTest

libVC.so: vclient.o RDBHandler.o 
	g++ $(FLAGS) -o libVC.so -shared vclient.o RDBHandler.o

vclient.o: $(SRCPATH)vclient.cpp $(INCPATH)vclient.h
	g++ $(FLAGS) -o vclient.o -c $(SRCPATH)vclient.cpp
	
RDBHandler.o: $(SRCPATH)RDBHandler.cc $(INCPATH)RDBHandler.hh
	g++ $(FLAGS) -o RDBHandler.o -c $(SRCPATH)RDBHandler.cc

buildTest: test.cpp $(INCPATH)vclient.h libVC.so
	g++ $(FLAGS) -o test.exe test.cpp -L. -l:libVC.so

clean:
	rm -rf *.o

mrproper: clean
	rm -rf libVC.so
	rm -rf test.exe

.PHONY: clean mrproper
